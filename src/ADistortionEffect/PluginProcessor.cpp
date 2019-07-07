/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AdistortionEffectAudioProcessor::AdistortionEffectAudioProcessor()
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
	tree.createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.f, 1.f, 0.0001),
		0.0f, nullptr, nullptr);
	tree.createAndAddParameter("range", "Depth", "Depth", NormalisableRange<float>(0.f, 3000.f, 0.0001),
		0.0f, nullptr, nullptr);
	tree.createAndAddParameter("blend", "Mix", "Mix", NormalisableRange<float>(0.f, 1.f, 0.0001),
		0.0f, nullptr, nullptr);
	tree.createAndAddParameter("volume", "Volume", "Volume", NormalisableRange<float>(0.f, 2.f, 0.0001),
		1.0f, nullptr, nullptr);

	tree.state = ValueTree("drive");
	tree.state = ValueTree("range");
	tree.state = ValueTree("blend");
	tree.state = ValueTree("volume");
}

AdistortionEffectAudioProcessor::~AdistortionEffectAudioProcessor()
{
}

//==============================================================================
const String AdistortionEffectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AdistortionEffectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AdistortionEffectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AdistortionEffectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AdistortionEffectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AdistortionEffectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AdistortionEffectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AdistortionEffectAudioProcessor::setCurrentProgram (int index)
{
}

const String AdistortionEffectAudioProcessor::getProgramName (int index)
{
    return {};
}

void AdistortionEffectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AdistortionEffectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	visualiser.clear();
}

void AdistortionEffectAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AdistortionEffectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AdistortionEffectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	// Get parameters
	float drive = *tree.getRawParameterValue("drive");
	float range = *tree.getRawParameterValue("range");
	float blend = *tree.getRawParameterValue("blend");
	float volume = *tree.getRawParameterValue("volume");

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			float cleanSignal = *channelData;

			*channelData *= drive * range;

			// "((2.f / float_Pi) * atan(*channelData))" == distorted signal
			*channelData = (((((2.f / float_Pi) * atan(*channelData)) * blend) + (cleanSignal * (1 - blend)))) * volume;

			channelData++;
		}

    }

	visualiser.pushBuffer(buffer);
}

//==============================================================================
bool AdistortionEffectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AdistortionEffectAudioProcessor::createEditor()
{
    return new AdistortionEffectAudioProcessorEditor (*this);
}

//==============================================================================
void AdistortionEffectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	// Save values

	MemoryOutputStream stream(destData, false);
	tree.state.writeToStream(stream);
}

void AdistortionEffectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	// Load previous values

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
    return new AdistortionEffectAudioProcessor();
}
