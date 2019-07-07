/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AbitcrusherEffectAudioProcessorEditor::AbitcrusherEffectAudioProcessorEditor (AbitcrusherEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 225);

	myFont = OtherLookAndFeel::getTypefaceForFont();

	myFont.setHeight(24.0f);

	// NOISE
	noiseDial.setRange(0.f, 100.f); // %
	noiseDial.setValue(0.f);
	noiseDial.setLookAndFeel(&otherLookAndFeel);
	noiseDial.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	noiseDial.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	noiseDial.setTextValueSuffix(" %");
	noiseLabel.setLookAndFeel(&otherLookAndFeel);
	noiseLabel.setFont(myFont);
	noiseLabel.setText("Noise", dontSendNotification);
	noiseLabel.setJustificationType(Justification::centred);
	noiseLabel.setColour(juce::Label::textColourId, juce::Colour(255, 255, 255));
	noiseLabel.attachToComponent(&noiseDial, false);
	addAndMakeVisible(&noiseDial);
	noiseAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "noise", noiseDial);

	// BIT REDUCTION
	bitReductDial.setRange(2, 32);
	bitReductDial.setValue(32);
	bitReductDial.setLookAndFeel(&otherLookAndFeel);
	bitReductDial.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	bitReductDial.setTextBoxStyle(Slider::TextBoxBelow, true, 30, 20);
	bitReductLabel.setLookAndFeel(&otherLookAndFeel);
	bitReductLabel.setFont(myFont);
	bitReductLabel.setText("Bits", dontSendNotification);
	bitReductLabel.setJustificationType(Justification::centred);
	bitReductLabel.setColour(juce::Label::textColourId, juce::Colour(255, 255, 255));
	bitReductLabel.attachToComponent(&bitReductDial, false);
	addAndMakeVisible(&bitReductDial);
	bitReductAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "bitReduct", bitReductDial);

	// RATE REDUCTION
	rateReductDial.setRange(1, 50); // Division rate (rate / x)
	rateReductDial.setValue(2);
	rateReductDial.setLookAndFeel(&otherLookAndFeel);
	rateReductDial.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	rateReductDial.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	rateReductLabel.setLookAndFeel(&otherLookAndFeel);
	myFont.setHeight(20.0f);
	rateReductLabel.setFont(myFont);
	rateReductLabel.setBorderSize(juce::BorderSize<int>(5));
	rateReductLabel.setText("Rate\nReduction", dontSendNotification);
	rateReductLabel.setColour(juce::Label::textColourId, juce::Colour(255, 255, 255));
	rateReductLabel.setJustificationType(Justification::centred);
	rateReductLabel.attachToComponent(&rateReductDial, false);
	addAndMakeVisible(&rateReductDial);
	rateReductAttach = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "rateReduct", rateReductDial);
}

AbitcrusherEffectAudioProcessorEditor::~AbitcrusherEffectAudioProcessorEditor()
{
}

//==============================================================================
void AbitcrusherEffectAudioProcessorEditor::paint (Graphics& g)
{
	Image background = ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize);
    g.fillAll (Colours::black);
	g.drawImageAt(background, 0, 195);
}

void AbitcrusherEffectAudioProcessorEditor::resized()
{
	noiseDial.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2) - 50, 100, 100);
	bitReductDial.setBounds(((getWidth() / 5) * 2) - (100 / 2) + 36, (getHeight() / 2) - 50, 100, 100);
	rateReductDial.setBounds(((getWidth() / 5) * 3) - (100 / 2) + 75, (getHeight() / 2) - 50, 100, 100);
}
