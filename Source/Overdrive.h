/*
  ==============================================================================

    Overdrive.h
    Author:  Alex

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
class Overdrive{
public:
	Overdrive();
	~Overdrive();
	void update(int buffsize, float type, float amount, float high, float low, float tone); //update the values used by the Overdrive
	void Apply(AudioSampleBuffer& buffer, int numInputChannels);
	void prepareToPlay(double sampleRate, int samplesPerBlock);
private:

	int bufferSize_; //Size of the input buffer
	double pi_; //value of pi	
	float samplerate_; //Sampling rate
	float type_;//type of overdrive to apply
	float amount_;//amount of overdrive
	IIRFilter *highShelf_[2], *lowShelf_[2]; //make two sets of filters. a high self and a low shelf for each stereo side
	IIRFilter *toneFilter_[2] ; // a low pass filter used for the output tone
	float highs_, lows_; //amomunt of highs and lows, computed pre-overdrive
	float tone_; //amount of highs attenuated post overdrive

};

