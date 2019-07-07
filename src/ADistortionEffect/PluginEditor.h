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
//==============================================================================
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

		g.setColour(Colours::black);
		g.drawEllipse(rx, ry, diameter, diameter, 6.0f);
		g.setColour(juce::Colour(0, 0, 0));
		g.fillEllipse(rx, ry, diameter, diameter);
		g.setColour(Colours::dimgrey);
		g.fillEllipse(rx + 25, ry + 25, diameter - 51, diameter - 51);

		Path dialTick;
		dialTick.addRectangle(-5, -radius, 10.0f, radius * 0.62f);

		g.setColour(juce::Colour(255, 250, 205));
		g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));
		g.fillRect(dialTick.getBounds());
	}

	static Typeface::Ptr getTypefaceForFont()
	{
		static Typeface::Ptr theFont = Typeface::createSystemTypefaceFor(BinaryData::remington__RIVIERA__2007_ttf,
			BinaryData::remington__RIVIERA__2007_ttfSize);

		return theFont;
	}
};

class AdistortionEffectAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AdistortionEffectAudioProcessorEditor (AdistortionEffectAudioProcessor&);
    ~AdistortionEffectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

	AdistortionEffectAudioProcessor& processor;

	OtherLookAndFeel otherLookAndFeel;

	Font myFont;

	Slider driveDial;
	Slider rangeDial;
	Slider blendDial;
	Slider volumeDial;

	Label driveLabel;
	Label rangeLabel;
	Label blendLabel;
	Label volumeLabel;

	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rangeAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendAttach;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdistortionEffectAudioProcessorEditor)
};