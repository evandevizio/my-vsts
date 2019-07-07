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

		g.setColour(Colours::black);

		Path dialTick;
		dialTick.addRectangle(-5, -radius, 12.0f, radius * 0.66f);

		g.fillPath(dialTick, AffineTransform::rotation(angle).translated(centerX, centerY));

		g.setColour(Colours::blanchedalmond);
		g.drawEllipse(rx, ry, diameter, diameter, 6.0f);
	}

	static Typeface::Ptr getTypefaceForFont()
	{
		static Typeface::Ptr theFont = Typeface::createSystemTypefaceFor(BinaryData::Montserrat_ttf,
			BinaryData::Montserrat_ttfSize);

		return theFont;
	}
};
//==============================================================================
class AstateVariableFilterAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    AstateVariableFilterAudioProcessorEditor (AstateVariableFilterAudioProcessor&);
    ~AstateVariableFilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    AstateVariableFilterAudioProcessor& processor;

	OtherLookAndFeel otherLookAndFeel;

	Font myFont;

	Slider filterCutoffDial;
	Slider filterResDial;
	ComboBox filterTypeMenu;

	Label filterCutoffLabel;
	Label filterResLabel;
	Label filterTypeLabel;

	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> filterResonanceValue;
	ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AstateVariableFilterAudioProcessorEditor)
};
