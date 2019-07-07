/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OtherLookAndFeel : public LookAndFeel_V4
{
public:
	void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos,
		float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
	{
		float diameter = jmin(width, height) - 20;
		float radius = diameter / 2;
		float centerX = x + width / 2;
		float centerY = y + height / 2;
		float rx = centerX - radius;
		float ry = centerY - radius;
		float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

		g.setColour(juce::Colour(255, 246, 0)); // Cadmium yellow 
		g.drawEllipse(rx, ry, diameter, diameter, 3.0f);
		g.setColour(juce::Colour(227, 0, 34)); // Cadmium red
		g.fillEllipse(rx, ry, diameter, diameter);

		g.setColour(juce::Colour(255, 246, 0)); // Cadmium yellow

		Path dialTick;
		dialTick.addRectangle(-5, -radius, 10.0f, radius * 0.6f);

		g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));
	}

	static Typeface::Ptr getTypefaceForFont ()
	{
		static Typeface::Ptr theFont = Typeface::createSystemTypefaceFor(BinaryData::MOZART_0_ttf,
			BinaryData::MOZART_0_ttfSize);

		return theFont;
	}
};

	//==============================================================================
class AbitcrusherEffectAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AbitcrusherEffectAudioProcessorEditor (AbitcrusherEffectAudioProcessor&);
    ~AbitcrusherEffectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	Slider bitReductDial, rateReductDial, noiseDial;
	Label bitReductLabel, rateReductLabel, noiseLabel;

private:
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>
		bitReductAttach, rateReductAttach, noiseAttach;

	OtherLookAndFeel otherLookAndFeel;

	Font myFont;

    // This is for your editor to access the processor object that created it.
    AbitcrusherEffectAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AbitcrusherEffectAudioProcessorEditor)
};
