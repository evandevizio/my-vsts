/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AbitcrusherEffectAudioProcessor::AbitcrusherEffectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr)
#endif
{
	tree.createAndAddParameter("noise", "Noise", "%", NormalisableRange<float>(0.f, 100.f, 1.f),
		0.f, nullptr, nullptr);
	tree.createAndAddParameter("bitReduct", "Bits", "", NormalisableRange<float>(2.f, 32.f, 1.f),
		32.f, nullptr, nullptr);
	tree.createAndAddParameter("rateReduct", "Rate", "", NormalisableRange<float>(1.f, 50.f, 0.1f),
		1.00f, nullptr, nullptr);

	tree.state = ValueTree("noise");
	tree.state = ValueTree("bitReduct");
	tree.state = ValueTree("rateReduct");
}

AbitcrusherEffectAudioProcessor::~AbitcrusherEffectAudioProcessor()
{
}

//==============================================================================
const String AbitcrusherEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AbitcrusherEffectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AbitcrusherEffectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AbitcrusherEffectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AbitcrusherEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AbitcrusherEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AbitcrusherEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AbitcrusherEffectAudioProcessor::setCurrentProgram (int index)
{
}

const String AbitcrusherEffectAudioProcessor::getProgramName (int index)
{
    return {};
}

void AbitcrusherEffectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AbitcrusherEffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AbitcrusherEffectAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AbitcrusherEffectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AbitcrusherEffectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


	int numSamples = buffer.getNumSamples();

	float noiseAmount = -120 + (120 * (*tree.getRawParameterValue("noise") / 120)); // dB
	float bitDepth = *tree.getRawParameterValue("bitReduct");
	int rateDiv = *tree.getRawParameterValue("rateReduct");

	noiseAmount = jlimit<float>(-120, 0, noiseAmount);
	noiseAmount = Decibels::decibelsToGain(noiseAmount);


	// SAFETY CHECK: since some hosts will change buffer sizes without calling prepareToPlay (e.g. Bitwig)
	if (noiseBuffer.getNumSamples() != numSamples)
	{
		noiseBuffer.setSize(2, numSamples, false, true, true); // clears
		currentOutputBuffer.setSize(2, numSamples, false, true, true); // clears
	}

	// Copy for processing...
	currentOutputBuffer.copyFrom(0, 0, buffer.getReadPointer(0), numSamples);
	if (buffer.getNumChannels() > 1) currentOutputBuffer.copyFrom(1, 0, buffer.getReadPointer(1), numSamples);

	// Create noise
	{
		noiseBuffer.clear();

		Array<float> noise = getWhiteNoise(numSamples);

		// range bound
		noiseAmount = jlimit<float>(0, 1, noiseAmount);

		FloatVectorOperations::multiply(noise.getRawDataPointer(), noiseAmount, numSamples);

		// Add the noise
		FloatVectorOperations::add(noiseBuffer.getWritePointer(0), noise.getRawDataPointer(), numSamples);
		FloatVectorOperations::add(noiseBuffer.getWritePointer(1), noise.getRawDataPointer(), numSamples); // STEREO

		// MULTIPLY MODE :::::
		// Multiply the noise by the signal ... so 0 signal -> 0 noise
		      //{
		      //     FloatVectorOperations::multiply(noiseBuffer.getWritePointer(0), currentOutputBuffer.getWritePointer(0), numSamples);
		      //     FloatVectorOperations::multiply(noiseBuffer.getWritePointer(1), currentOutputBuffer.getWritePointer(1), numSamples);
		      //}

	}

	// Add noise to incoming audio
	currentOutputBuffer.addFrom(0, 0, noiseBuffer.getReadPointer(0), numSamples);
	currentOutputBuffer.addFrom(1, 0, noiseBuffer.getReadPointer(1), numSamples);

	// Resample as needed
	for (int chan = 0; chan < currentOutputBuffer.getNumChannels(); chan++)
	{
		float* data = currentOutputBuffer.getWritePointer(chan);

		for (int i = 0; i < numSamples; i++)
		{
			// Reduce bit depth
			float totalQLevels = powf(2, bitDepth);
			float val = data[i];
			float remainder = fmodf(val, 1 / totalQLevels);

			// Quantize
			data[i] = val - remainder;

			if (rateDiv > 1)
			{
				if (i%rateDiv != 0) data[i] = data[i - i % rateDiv];
			}
		}
	}

	// Copy to the actual output buffer
	buffer.copyFrom(0, 0, currentOutputBuffer, 0, 0, numSamples);
	buffer.copyFrom(1, 0, currentOutputBuffer, 1, 0, numSamples);
}

//==============================================================================
bool AbitcrusherEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AbitcrusherEffectAudioProcessor::createEditor()
{
    return new AbitcrusherEffectAudioProcessorEditor (*this);
}

//==============================================================================
void AbitcrusherEffectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	MemoryOutputStream stream(destData, false);
	tree.state.writeToStream(stream);
}

void AbitcrusherEffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	ValueTree valueTree = ValueTree::readFromData(data, sizeInBytes);

	if (valueTree.isValid())
	{
		tree.state = valueTree;
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AbitcrusherEffectAudioProcessor();
}
