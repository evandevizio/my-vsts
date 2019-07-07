/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AstateVariableFilterAudioProcessorEditor::AstateVariableFilterAudioProcessorEditor (AstateVariableFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	setSize(600, 300);

	myFont = OtherLookAndFeel::getTypefaceForFont();

	myFont.setHeight(20.0f);

	// FILTER CUTOFF
	filterCutoffDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterCutoffDial.setLookAndFeel(&otherLookAndFeel);
	filterCutoffDial.setRange(20.0f, 18000.0f); //Hz
	filterCutoffDial.setValue(600.0f);
	filterCutoffDial.setSkewFactorFromMidPoint(1000.0f);
	filterCutoffDial.setTextBoxStyle(Slider::TextBoxBelow, true, 80, filterCutoffDial.getTextBoxHeight());
	filterCutoffDial.setTextValueSuffix(" Hz");
	addAndMakeVisible(&filterCutoffDial);
	filterCutoffLabel.setLookAndFeel(&otherLookAndFeel);
	filterCutoffLabel.setFont(myFont);
	filterCutoffLabel.setText("Cutoff", dontSendNotification);
	filterCutoffLabel.setJustificationType(Justification::centred);
	filterCutoffLabel.setColour(juce::Label::textColourId, juce::Colour(0, 0, 0));
	filterCutoffLabel.attachToComponent(&filterCutoffDial, false);
	filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
		"filterCutoff", filterCutoffDial);

	// FILTER RESONANCE
	filterResDial.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	filterResDial.setLookAndFeel(&otherLookAndFeel);
	filterResDial.setRange(1.0f, 10.0f);
	filterResDial.setValue(1.0f);
	filterResDial.setTextBoxStyle(Slider::TextBoxBelow, true, 40, filterResDial.getTextBoxHeight());
	addAndMakeVisible(&filterResDial);
	filterResLabel.setLookAndFeel(&otherLookAndFeel);
	filterResLabel.setFont(myFont);
	filterResLabel.setColour(juce::Label::textColourId, juce::Colour(0, 0, 0));
	filterResLabel.setText("Resonance", dontSendNotification);
	filterResLabel.setJustificationType(Justification::centred);
	filterResLabel.attachToComponent(&filterResDial, false);
	filterResonanceValue = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,
		"filterResonance", filterResDial);

	// FILTER TYPE
	filterTypeMenu.addItem("Low Pass", 1);
	filterTypeMenu.addItem("Band Pass", 2);
	filterTypeMenu.addItem("High Pass", 3);
	filterTypeMenu.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterTypeMenu);
	filterTypeLabel.setLookAndFeel(&otherLookAndFeel);
	filterTypeLabel.setFont(myFont);
	filterTypeLabel.setText("Filter Type", dontSendNotification);
	filterTypeLabel.setJustificationType(Justification::centred);
	filterTypeLabel.setColour(juce::Label::textColourId, juce::Colour(0, 0, 0));
	filterTypeLabel.attachToComponent(&filterTypeMenu, false);
	filterTypeValue = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree,
		"filterType", filterTypeMenu);
}

AstateVariableFilterAudioProcessorEditor::~AstateVariableFilterAudioProcessorEditor()
{
}

//==============================================================================
void AstateVariableFilterAudioProcessorEditor::paint (Graphics& g)
{
	Image background = ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize);
	g.fillAll(Colours::cadetblue);
	g.drawImageAt(background, 0, 0);
}

void AstateVariableFilterAudioProcessorEditor::resized()
{
	filterCutoffDial.setBounds(230, 50, 150, 125);
	filterResDial.setBounds(400, 50, 150, 125);
	filterTypeMenu.setBounds(50, 50, 150, 50);
}
