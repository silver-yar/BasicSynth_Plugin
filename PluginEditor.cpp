/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthAudioProcessorEditor::BasicSynthAudioProcessorEditor (BasicSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI(p), envGUI(p), filterGUI(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);

	addAndMakeVisible(&oscGUI);
	addAndMakeVisible(&envGUI);
	addAndMakeVisible(&filterGUI);
}

BasicSynthAudioProcessorEditor::~BasicSynthAudioProcessorEditor()
{
}

//==============================================================================
void BasicSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void BasicSynthAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();

	const int componentWidth = 200;
	const int componentHeight = 200;

	oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}