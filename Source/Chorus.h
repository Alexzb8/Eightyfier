/*
  ==============================================================================

    Chorus.h
    Author:  Jorge Zuniga

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
class Chorus{
public:
	Chorus();
	~Chorus();
	void update(int buffsize, float Delay, float depth, float sweepWidth, float LFOfrequency); //update the values used by the chorus
	void Apply(AudioSampleBuffer& buffer, int numInputChannels);
	void prepareToPlay(double sampleRate, int samplesPerBlock);
private:

	int bufferSize_; //Size of the input buffer
	double pi_; //value of pi
	float sweepWidth_; //Width of the LFO in samples. 
	float ph_; //Current LFO phase, always between 0-1
	float samplerate_; //Sampling rate
	float feedback_; //Amount of feedback (>=0, <1)
	float depth_; //Amount of delayed signal mixed with original (0-1)
	float frequency_; //LFO frequency (1-3)
	float Delay_; //Amount of delay 
	
	// Circular buffer variables for implementing delay
	AudioSampleBuffer delayBuffer_;
	int delayBufferLength_; //Length of the delay buffer in samples
	int dpw; //Write pointer into the delay Buffer 
	int delayWritePosition_;
	
};

