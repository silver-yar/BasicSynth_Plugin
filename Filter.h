/*
  ==============================================================================

    Filter.h
    Created: 16 Feb 2019 8:31:45pm
    Author:  Johnathan

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(BasicSynthAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	BasicSynthAudioProcessor & processor;

	Slider filterCutoff;
	Slider filterRes;

	ComboBox filterMenu;

	ScopedPointer <AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> filterVal;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> resVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
