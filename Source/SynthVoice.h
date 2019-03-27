/*
  ==============================================================================

    SynthVoice.h
    Created: 7 Feb 2019 3:00:45pm
    Author:  Johnathan

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound)
	{
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}

	// =========================================================================

	void getEnvParam(float* attack, float* decay, float* sustain, float* release)
	{
		env1.setAttack(double(*attack));
		env1.setDecay(double(*decay));
		env1.setSustain(double(*sustain));
		env1.setRelease(double(*release));
	}

	// =========================================================================

	double setEnvelope()
	{
		return env1.adsr(setOscType(), env1.trigger) * level;
	}

	// =========================================================================

	void getOscType(float* selection)
	{
		theWave = *selection;
	}

	// =========================================================================

	double setOscType()
	{
		if (theWave == 0)
		{
			return osc1.sinewave(frequency);
		}
		if (theWave == 1)
		{
			return osc1.saw(frequency);
		}
		if (theWave == 2)
		{
			return osc1.square(frequency);
		}
		else {
			return osc1.sinewave(frequency);
		}
	}

	// =========================================================================

	void getFilterParams(float* filterType, float* filterCutoff, float* filterRes)
	{
		filterChoice = *filterType;
		cutoff = *filterCutoff;
		resonance = *filterRes;
	}

	double setFilter()
	{
		if (filterChoice == 0)
		{
			return filter1.lores(setEnvelope(), cutoff, resonance);
		}
		if (filterChoice == 1)
		{
			return filter1.hires(setEnvelope(), cutoff, resonance);
		}
		if (filterChoice == 2)
		{
			return filter1.bandpass(setEnvelope(), cutoff, resonance);
		}
		else {
			return filter1.lores(setEnvelope(), cutoff, resonance);
		}
	}

	// =========================================================================

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, 
		int currentPitchWheelPosition)
	{
		env1.trigger = 1;
		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	}

	// =========================================================================

	void stopNote(float velocity, bool allowTailOff)
	{
		env1.trigger = 0;
		allowTailOff = true;

		if (velocity == 0)
			clearCurrentNote();
	}

	// =========================================================================

	void pitchWheelMoved(int newPitchWheelValue)
	{

	}

	// =========================================================================

	void controllerMoved(int controllerNumber, int newControllerValue)
	{

	}

	// =========================================================================

	void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
	{
		for (int sample = 0; sample < numSamples; ++sample)
		{
			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			{
				outputBuffer.addSample(channel, startSample, setFilter());
			}
			++startSample;
		}
	}

	// =========================================================================

private:
	double level;
	double frequency;
	int theWave;

	int filterChoice;
	float cutoff;
	float resonance;

	maxiOsc osc1;
	maxiEnv env1;
	maxiFilter filter1;
};
