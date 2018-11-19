/*
  ==============================================================================

    Delay.cpp
    Author:  Alex

  ==============================================================================
*/

#include "Delay.h"

Delay::Delay(){
	//Set default values

	bufferSize_= 100; 
	samplerate_ = 44100;
	feedback_ = .75; 
	wet_ = .5; 
	dry_ = 1; 
	length_ = .5;
	delayBufferLength_ = 44100;
	dpw = 0;  
	dpr = 0; 
	delayReadPosition_ = 0;
	delayWritePosition_ = 0;
}

Delay::~Delay(){
}

void Delay::update(int buffsize, float length, float feedback, float dry, float wet){
	//get the newest parameters
	bufferSize_ = buffsize;
	length_ = length;
	feedback_ = feedback;
	dry_ = dry;
	wet_ = wet;

	//compute the read position relative to the write position
	delayReadPosition_ = (int)(delayWritePosition_ - (length_ * samplerate_) + delayBufferLength_) % delayBufferLength_;
}

void Delay::prepareToPlay(double sampleRate, int samplesPerBlock){
	//Run on the prepare to play method of the main processing class

	samplerate_ = sampleRate;
	//the delay buffer is going to be of length 2 seconds, which is be the max value the delay can take
	delayBufferLength_ = (int)(sampleRate) * 2;
	if(delayBufferLength_ < 1)
		delayBufferLength_ = 1;
	delayBuffer_.setSize(2, delayBufferLength_); //make it two channnels in case input is stereo
	delayBuffer_.clear(); //clear the delay buffer from garbage
	
}

void Delay::Apply(AudioSampleBuffer & buffer, int numInputChannels){

	for(int channel = 0; channel < numInputChannels; ++channel){
		// channelData is an array which contains the audio for one channel
		float* channelData = buffer.getWritePointer(channel);

		// delayData is the circular buffer for implementing delay on this channel
		float* delayData = delayBuffer_.getWritePointer(jmin(channel,
			delayBuffer_.getNumChannels() - 1));

		//keep track of the initial pointer positions
		dpr = delayReadPosition_;
		dpw = delayWritePosition_;

		for(int i = 0; i < buffer.getNumSamples(); ++i){
			const float in = channelData[i];
			float out = 0.0;

			//compute the output as the weighted sum of the dry and wet signals
			out = (dry_ * in + wet_ * delayData[dpr]);

			//store values in the delay buffer, with the feedback
			delayData[dpw] = in + (delayData[dpr] * feedback_);

			//increment the pointers
			if(++dpr >= delayBufferLength_)
				dpr = 0;
			if(++dpw >= delayBufferLength_)
				dpw = 0;

			// Store the output sample in the buffer, replacing the input
			channelData[i] = out;
		}
	}
	delayReadPosition_ = dpr;
	delayWritePosition_ = dpw;

}


