/*
  ==============================================================================

    Envelope.h
    Created: 15 Feb 2019 9:13:30pm
    Author:  Johnathan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
// public Slider::Listener
class Envelope    : public Component
{
public:
    Envelope(BasicSynthAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;

	// void sliderValueChanged(Slider* slider) override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	BasicSynthAudioProcessor& processor;

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> attackTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> decayTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> sustainTree;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> releaseTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
