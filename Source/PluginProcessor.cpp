/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicSynthAudioProcessor::BasicSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
tree (*this, nullptr)
#endif
{
	NormalisableRange<float> attackParam(0.1f, 5000.0f);
	NormalisableRange<float> decayParam(1.0f, 2000.0f);
	NormalisableRange<float> sustainParam(0.0f, 1.0f);
	NormalisableRange<float> releaseParam(0.1f, 5000.0f);

	tree.createAndAddParameter("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);
	tree.createAndAddParameter("decay", "Decay", "Decay", decayParam, 1.0f, nullptr, nullptr);
	tree.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.8f, nullptr, nullptr);
	tree.createAndAddParameter("release", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr);

	NormalisableRange<float> wavetypeParam(0, 2);
	tree.createAndAddParameter("wavetype", "WaveType", "wavetype", wavetypeParam, 0, nullptr, nullptr);

	NormalisableRange<float> filterTypeVal(0, 2);
	NormalisableRange<float> filterVal(20.0f, 10000.0f);
	NormalisableRange<float> resVal(1, 5);
	tree.createAndAddParameter("filterCutoff", "FilterCutoff", "FilterCutoff", filterVal, 400.0f, nullptr, nullptr);
	tree.createAndAddParameter("filterRes", "FilterRes", "FilterRes", resVal, 1, nullptr, nullptr);
	tree.createAndAddParameter("filterType", "FilterType", "FilterType", filterTypeVal, 0, nullptr, nullptr);

	mySynth.clearVoices();
	for (int i = 0; i < 5; i++)
	{
		mySynth.addVoice(new SynthVoice());
	}
	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());
}

BasicSynthAudioProcessor::~BasicSynthAudioProcessor()
{
}

//==============================================================================
const String BasicSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String BasicSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BasicSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void BasicSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BasicSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	for (int i = 0; i < mySynth.getNumVoices(); i++)
	{
		if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
		{
			myVoice->getEnvParam(tree.getRawParameterValue("attack"), tree.getRawParameterValue("decay"), 
				tree.getRawParameterValue("sustain"), tree.getRawParameterValue("release"));

			myVoice->getOscType(tree.getRawParameterValue("wavetype"));

			myVoice->getFilterParams(tree.getRawParameterValue("filterType"),
				tree.getRawParameterValue("filterCutoff"),
				tree.getRawParameterValue("filterRes"));
		}

	}
	buffer.clear();

	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool BasicSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BasicSynthAudioProcessor::createEditor()
{
    return new BasicSynthAudioProcessorEditor (*this);
}

//==============================================================================
void BasicSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicSynthAudioProcessor();
}
