/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AdistortionEffectAudioProcessorEditor::AdistortionEffectAudioProcessorEditor (AdistortionEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (600, 360);

	myFont = OtherLookAndFeel::getTypefaceForFont();

	myFont.setHeight(25.0f);

	// DRIVE
	driveDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	driveDial.setTextBoxStyle(Slider::NoTextBox, true, 60, driveDial.getHeight());
	driveDial.setPopupDisplayEnabled(true, true, &driveDial);
	driveDial.setLookAndFeel(&otherLookAndFeel);
	driveDial.setValue(0.0f, dontSendNotification);
	driveLabel.setLookAndFeel(&otherLookAndFeel);
	driveLabel.setFont(myFont);
	driveLabel.setText("Drive", dontSendNotification);
	driveLabel.setJustificationType(Justification::centred);
	driveLabel.setColour(juce::Label::textColourId, juce::Colour(250, 245, 200));
	driveLabel.attachToComponent(&driveDial, false);
	addAndMakeVisible(driveDial);
	driveAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "drive", driveDial);

	// RANGE (Labeled DEPTH in GUI)
	rangeDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	rangeDial.setTextBoxStyle(Slider::NoTextBox, true, 60, rangeDial.getHeight());
	rangeDial.setPopupDisplayEnabled(true, true, &rangeDial);
	rangeDial.setLookAndFeel(&otherLookAndFeel);
	rangeDial.setValue(0.0f, dontSendNotification);
	rangeLabel.setLookAndFeel(&otherLookAndFeel);
	rangeLabel.setFont(myFont);
	rangeLabel.setText("Depth", dontSendNotification);
	rangeLabel.setJustificationType(Justification::centred);
	rangeLabel.setColour(juce::Label::textColourId, juce::Colour(250, 245, 200));
	rangeLabel.attachToComponent(&rangeDial, false);
	addAndMakeVisible(rangeDial);
	rangeAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "range", rangeDial);

	// BLEND (Labeled MIX in GUI)
	blendDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	blendDial.setTextBoxStyle(Slider::NoTextBox, true, 60, blendDial.getHeight());
	blendDial.setPopupDisplayEnabled(true, true, &blendDial);
	blendDial.setLookAndFeel(&otherLookAndFeel);
	blendDial.setValue(0.0f, dontSendNotification);
	blendLabel.setLookAndFeel(&otherLookAndFeel);
	myFont.setHeight(20.0f);
	blendLabel.setFont(myFont);
	blendLabel.setBorderSize(juce::BorderSize<int>(10));
	blendLabel.setText("Mix\n(Caution!)", dontSendNotification);
	blendLabel.setJustificationType(Justification::centred);
	blendLabel.setColour(juce::Label::textColourId, juce::Colour(250, 245, 200));
	blendLabel.attachToComponent(&blendDial, false);
	addAndMakeVisible(blendDial);
	blendAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "blend", blendDial);

	// VOLUME
	volumeDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	volumeDial.setTextBoxStyle(Slider::NoTextBox, true, 60, volumeDial.getHeight());
	volumeDial.setPopupDisplayEnabled(true, true, &volumeDial);
	volumeDial.setLookAndFeel(&otherLookAndFeel);
	volumeDial.setValue(1.0f, dontSendNotification);
	volumeLabel.setLookAndFeel(&otherLookAndFeel);
	myFont.setHeight(25.0f);
	volumeLabel.setFont(myFont);
	volumeLabel.setText("Volume", dontSendNotification);
	volumeLabel.setJustificationType(Justification::centred);
	volumeLabel.setColour(juce::Label::textColourId, juce::Colour(250, 245, 200));
	volumeLabel.attachToComponent(&volumeDial, false);
	addAndMakeVisible(volumeDial);
	volumeAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "volume", volumeDial);

	// AUDIO VISUALIZER
	addAndMakeVisible(processor.visualiser);
}

AdistortionEffectAudioProcessorEditor::~AdistortionEffectAudioProcessorEditor()
{
}

//==============================================================================
void AdistortionEffectAudioProcessorEditor::paint (Graphics& g)
{
	Image background = ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize);
	g.fillAll(juce::Colour(0, 100, 0));
	g.drawImageAt(background, 0, 0);
}

void AdistortionEffectAudioProcessorEditor::resized()
{
	driveDial.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - (50 / 2) - 80, 100, 100);
	rangeDial.setBounds(((getWidth() / 5) * 2) - (100 / 2), (getHeight() / 2) - (50 / 2) - 80, 100, 100);
	blendDial.setBounds(((getWidth() / 5) * 3) - (100 / 2), (getHeight() / 2) - (50 / 2) - 80, 100, 100);
	volumeDial.setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2) - (50 / 2) - 80, 100, 100);
	processor.visualiser.setBounds(100, 220, 400, 125);

}
