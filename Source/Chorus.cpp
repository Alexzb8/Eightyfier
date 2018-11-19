/*
  ==============================================================================

    Chorus.cpp
    Author:  Jorge Zuniga

  ==============================================================================
*/

#include "Chorus.h"

//A simple Chorus effect

Chorus::Chorus(){

	//default values
	pi_ = 4 * atan(1); // value of pi
	sweepWidth_ = 220;
	Delay_ = 882;
	ph_ = 0;
	samplerate_ = 44100;
	delayBufferLength_ = samplerate_*2; 
	feedback_ = 0;
	depth_ = 1;
	dpw = 0; 
	delayWritePosition_ = 0;
	frequency_ = 3;
}



Chorus::~Chorus(){
}



void Chorus::update(int buffsize,float Delay, float depth, float sweepWidth, float LFOfrequency){

	//Update external values(called every process block)
	depth_ = depth;
	bufferSize_ = buffsize;
	sweepWidth_ = samplerate_ *(sweepWidth /1000);//convert sweepwidth UI parameter(in ms) to seconds and get number of samples
	Delay_ = samplerate_ * (Delay / 1000);//same for the delay
	frequency_ = LFOfrequency; //frequency is in seconds already

}

void Chorus::prepareToPlay(double sampleRate, int samplesPerBlock){
	//Run on the prepare to play method of the main processing class

	samplerate_ = sampleRate;
	//the delay buffer is going to be of length 1 second, which will be the max value the delay can take
	delayBufferLength_ = (int)(sampleRate);
	if(delayBufferLength_ < 1)
		delayBufferLength_ = 1;
	delayBuffer_.setSize(2, delayBufferLength_); //make it two channnels in case input is stereo
	delayBuffer_.clear();

}

void Chorus::Apply(AudioSampleBuffer& buffer, int numInputChannels){

	float LFOStereoPhaseDifference = 0;
	float previousph = ph_; //store the value of the current LFO phase

	//cycle channels
	for(int channel = 0; channel < numInputChannels; ++channel){
	
		float* channelData = buffer.getWritePointer(channel); //get sample pointer

		// delayData is the circular buffer for implementing delay on this channel
		float* delayData = delayBuffer_.getWritePointer(channel);

		dpw = delayWritePosition_;

		ph_ = previousph; 

		//cycle samples
		for(int i = 0; i < bufferSize_; ++i){
			const float in = channelData[i];
			float interpolatedSample = 0.0f;

			//Recalculate the read pointer position with respect to the write pointer
			float currentDelay = Delay_ + (sweepWidth_ * (0.5f + (0.5f * sinf(2.0 * pi_ * ph_))));
			
			//Subtract 3 samples to the delay pointer to make sure 
			//we have enough previous samples to interpolate with
			float dpr = fmodf((float)dpw - (float)(currentDelay) + (float)delayBufferLength_ - 3.0f, (float)delayBufferLength_);

			//use linear interpolation to read a fractional index into the buffer
			float fraction = dpr - floorf(dpr);
			int previousSample = (int)floorf(dpr);
			int nextSample = (previousSample + 1) % delayBufferLength_;
			interpolatedSample = (fraction * delayData[nextSample]) + ((1.0f - fraction)*delayData[previousSample]); //apply linear interpolation
			
			delayData[dpw] = in; //write the raw samples into the delay buffer
			
			//increment delay write pointer
			if(++dpw >= delayBufferLength_) dpw = 0;

			//Store the output in the buffer, replacing the input
			channelData[i] = in + (depth_ *interpolatedSample);

			//Update the LFO phase, keeping it in the range 0-1
			ph_ += frequency_ * (1 / samplerate_);
			if(ph_ >= 1.0f)
				ph_ -= 1.0f;			
			
		}
	}
	delayWritePosition_ = dpw; //store the position of the delay write pointer
}