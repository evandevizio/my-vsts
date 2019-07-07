/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
//==============================================================================
class AbitcrusherEffectAudioProcessor  : public AudioProcessor
{
	AudioSampleBuffer noiseBuffer, currentOutputBuffer;

public:
    //==============================================================================
    AbitcrusherEffectAudioProcessor();
    ~AbitcrusherEffectAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	AudioProcessorValueTreeState tree;

	static Array<float> getSimpleNoise(int numSamples)
	{
		Random r = Random::getSystemRandom();
		Array<float> noise;

		for (int s = 0; s < numSamples; s++)
		{
			noise.add((r.nextFloat() - .5) * 2);
		}

		return noise;

	}

	static Array<float> getWhiteNoise(int numSamples) {

		Array<float> noise;

		float z0 = 0;
		float z1 = 0;
		bool generate = false;

		float mu = 0; // center (0)
		float sigma = 1; // spread -1 <-> 1

		float output = 0;
		float u1 = 0;
		float u2 = 0;

		Random r = Random::getSystemRandom();
		r.setSeed(Time::getCurrentTime().getMilliseconds());
		const float epsilon = std::numeric_limits<float>::min();

		for (int s = 0; s < numSamples; s++)
		{

			// GENERATE ::::
			// using box muller method
			// https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform
			generate = !generate;

			if (!generate)
				output = z1 * sigma + mu;
			else
			{
				do
				{
					u1 = r.nextFloat();
					u2 = r.nextFloat();
				} while (u1 <= epsilon);

				z0 = sqrtf(-2.0 * logf(u1)) * cosf(2 * float(double_Pi) * u2);
				z1 = sqrtf(-2.0 * logf(u1)) * sinf(2 * float(double_Pi) * u2);

				output = z0 * sigma + mu;
			}

			// NAN check ...
			jassert(output == output);
			jassert(output > -50 && output < 50);

			//
			noise.add(output);

		}

		return noise;

	}

	//==============================================================================

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AbitcrusherEffectAudioProcessor)
};
