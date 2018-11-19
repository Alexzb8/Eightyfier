/*
  ==============================================================================

    Delay.h
    Author:  Alex

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
class Delay{
public:
	Delay();
	~Delay();
	void update(int buffsize, float length, float feedback, float dry, float wet); //update the values used by the delay
	void Apply(AudioSampleBuffer& buffer, int numInputChannels);
	void prepareToPlay(double sampleRate, int samplesPerBlock);
private:

	int bufferSize_; //Size of the input buffer
	float samplerate_; //Sampling rate
	float feedback_; //Amount of feedback (>=0, <1)
	float wet_; //wet gain
	float dry_; //dry gain
	float length_; //Length of the delay

	// Circular buffer variables for implementing delay
	AudioSampleBuffer delayBuffer_;
	int delayBufferLength_; //Length of the delay buffer in samples
	int dpw; //Write pointer into the delay Buffer 
	int dpr; //Read pointer
	int delayReadPosition_, delayWritePosition_;

};

