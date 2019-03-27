/*
  ==============================================================================

    Oscillator.h
    Created: 13 Feb 2019 11:21:12am
    Author:  Johnathan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component,
	private ComboBox::Listener
{
public:
    Oscillator(BasicSynthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;

	void comboBoxChanged(ComboBox*) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	BasicSynthAudioProcessor& processor;

	ComboBox oscMenu;
	
	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
