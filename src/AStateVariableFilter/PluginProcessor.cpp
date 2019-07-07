/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AstateVariableFilterAudioProcessor::AstateVariableFilterAudioProcessor()
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
	//============================== FILTER ========================================
	NormalisableRange<float> filterCutoffParam(20.0f, 18000.0f, 1.0f); //Hz
	tree.createAndAddParameter("filterCutoff", "FilterCutoff", "Cutoff", filterCutoffParam, 600.0f,
		nullptr, nullptr);
	NormalisableRange<float> filterResonanceParam(1.0f, 10.0f, 0.1f);
	tree.createAndAddParameter("filterResonance", "FilterResonance", "Resonance", filterResonanceParam, 1.0f,
		nullptr, nullptr);
	NormalisableRange<float> filterTypeParam(0, 2);
	tree.createAndAddParameter("filterType", "FilterType", "Type", filterTypeParam, 0, nullptr, nullptr);

	//==============================================================================
	tree.state = ValueTree("AStateVariableFilter");
}

AstateVariableFilterAudioProcessor::~AstateVariableFilterAudioProcessor()
{
}

//==============================================================================
const String AstateVariableFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AstateVariableFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AstateVariableFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AstateVariableFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AstateVariableFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AstateVariableFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AstateVariableFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AstateVariableFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String AstateVariableFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void AstateVariableFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AstateVariableFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	lastSampleRate = sampleRate;

	dsp::ProcessSpec spec;
	spec.sampleRate = lastSampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getMainBusNumOutputChannels();

	myFilter.reset();
	myFilter.prepare(spec);
	updateFilter();
}

void AstateVariableFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AstateVariableFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AstateVariableFilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();


	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	updateFilter();
	dsp::AudioBlock<float> block(buffer);
	myFilter.process(dsp::ProcessContextReplacing<float>(block));


	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

	}
}

//==============================================================================
bool AstateVariableFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AstateVariableFilterAudioProcessor::createEditor()
{
    return new AstateVariableFilterAudioProcessorEditor (*this);
}

//==============================================================================
void AstateVariableFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	// Store parameters in memory block as XML for saving and loading values.

	ScopedPointer <XmlElement> xml(tree.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void AstateVariableFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	// Restore parameters from memory block created in getStateInformation().

	ScopedPointer <XmlElement> xmlParams(getXmlFromBinary(data, sizeInBytes));

	if (xmlParams != nullptr)
	{
		if (xmlParams->hasTagName(tree.state.getType()))
		{
			tree.state = ValueTree::fromXml(*xmlParams);
		}
	}
}

//==============================================================================
void AstateVariableFilterAudioProcessor::updateFilter()
{
	type = *tree.getRawParameterValue("filterType");
	cutoff = *tree.getRawParameterValue("filterCutoff");
	resonance = *tree.getRawParameterValue("filterResonance");

	// Set filter type and cutoff
	switch (type)
	{
	case 0:
		myFilter.state->type = dsp::StateVariableFilter::Parameters<float>::
			Type::lowPass;
		break;
	case 1:
		myFilter.state->type = dsp::StateVariableFilter::Parameters<float>::
			Type::bandPass;
		break;
	case 2:
		myFilter.state->type = dsp::StateVariableFilter::Parameters<float>::
			Type::highPass;
		break;
	default:
		myFilter.state->type = dsp::StateVariableFilter::Parameters<float>::
			Type::lowPass;
	}

	myFilter.state->setCutOffFrequency(lastSampleRate, cutoff, resonance);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AstateVariableFilterAudioProcessor();
}
