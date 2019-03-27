/*
  ==============================================================================

    Envelope.cpp
    Created: 15 Feb 2019 9:13:30pm
    Author:  Johnathan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(BasicSynthAudioProcessor& p) :
processor(p)
{
	setSize(200, 200);

	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setRange(0.1f, 5000.0f, 0.1f);
	attackSlider.setValue(0.1f);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	attackSlider.setPopupDisplayEnabled(true, false, this);
	attackSlider.setTextValueSuffix(" ms");
	addAndMakeVisible(&attackSlider);

	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(1.0f, 2000.0f);
	decaySlider.setValue(1.0f);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	decaySlider.setPopupDisplayEnabled(true, false, this);
	decaySlider.setTextValueSuffix(" ms");
	addAndMakeVisible(&decaySlider);

	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.0f, 1.0f);
	sustainSlider.setValue(0.8f);
	sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	sustainSlider.setPopupDisplayEnabled(true, false, this);
	sustainSlider.setTextValueSuffix(" dB");
	addAndMakeVisible(&sustainSlider);

	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.1f, 5000.0f);
	releaseSlider.setValue(0.8f);
	releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	releaseSlider.setPopupDisplayEnabled(true, false, this);
	releaseSlider.setTextValueSuffix(" ms");
	addAndMakeVisible(&releaseSlider);

	attackTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
	decayTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
	sustainTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
	releaseTree = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Envelope", titleArea, Justification::centredTop);

	g.drawText("A", 53, 150, 20, 20, Justification::centredTop);
	g.drawText("D", 77, 150, 20, 20, Justification::centredTop);
	g.drawText("S", 103, 150, 20, 20, Justification::centredTop);
	g.drawText("R", 120, 150, 20, 20, Justification::centredTop);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::cornflowerblue);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(50);

	int sliderWidth = 25;
	int sliderHeight = 175;

	attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
	
}

