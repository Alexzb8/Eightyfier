/*
  ==============================================================================

    Overdrive.cpp
    Author:  Alex

  ==============================================================================
*/

#include "Overdrive.h"

//A simple Chorus effect

Overdrive::Overdrive(){

	//default values
	pi_ = 4 * atan(1); // value of pi

	samplerate_ = 44100;

	highs_ = 3;
	lows_ = .04;
	tone_ = .28;

	//make filters
	highShelf_[0] = new IIRFilter();
	highShelf_[1] = new IIRFilter();
	lowShelf_[0] = new IIRFilter();
	lowShelf_[1] = new IIRFilter();
	toneFilter_[0] = new IIRFilter();
	toneFilter_[1] = new IIRFilter();

}



Overdrive::~Overdrive(){
}



void Overdrive::update(int buffsize, float type, float amount, float high, float low, float tone){

	//Update external values(called every process block)
	bufferSize_ = buffsize;
	type_ = type;
	amount_ = amount;
	highs_ = high;
	lows_ = low;
	tone_ = tone;

	//set coefficients for the filters
	highShelf_[0]->setCoefficients(IIRCoefficients::makeHighShelf(samplerate_, 1000, .60, highs_));
	highShelf_[1]->setCoefficients(IIRCoefficients::makeHighShelf(samplerate_, 1000, .60, highs_));
	lowShelf_[0]->setCoefficients(IIRCoefficients::makeLowShelf(samplerate_, 180, .09, lows_));
	lowShelf_[1]->setCoefficients(IIRCoefficients::makeLowShelf(samplerate_, 180, .09, lows_));

	toneFilter_[0]->setCoefficients(IIRCoefficients::makeHighShelf(samplerate_, 2400, .6, tone_));
	toneFilter_[1]->setCoefficients(IIRCoefficients::makeHighShelf(samplerate_, 2400, .6, tone_));

}

void Overdrive::prepareToPlay(double sampleRate, int samplesPerBlock){
	//Run on the prepare to play method of the main processing class

	samplerate_ = sampleRate;

}

void Overdrive::Apply(AudioSampleBuffer& buffer, int numInputChannels){

	
		//lowShelf_ -
	
	//cycle channels
	for(int channel = 0; channel < numInputChannels; ++channel){

		float* channelData = buffer.getWritePointer(channel); //get sample pointer

		//pre filtering stage
		highShelf_[channel]->processSamples(channelData, bufferSize_); 
		lowShelf_[channel]->processSamples(channelData, bufferSize_);

		//cycle samples
		for(int i = 0; i < bufferSize_; ++i){
			const float in = channelData[i];
			float out = 0.0f;

			if(type_ == 0){
				//Parabolic overdrive
				float absIn = fabsf(in); //absolute value of input

				float third = 1.0f / 3.0f; //one third
				float twoThirds = 2.0f / 3.0f;  //two thirds

				float sign = 1.0f;
				if(in < 0.0f){
					sign = -1.0f;
				}

				if(absIn < third){
					out = 2 * absIn;
				} else if(absIn < twoThirds){
					out = 1 - (powf((2.0f - (3.0f * absIn)), 2.0f) / 3.0f);
				} else{
					out = 1.0f;
				}

				out *= sign; //apply correct sign

			} else if(type_ == 1){
				//tanh distortion
				out = tanhf(amount_ * in);

			} else if(type_ == 2){
				//atan distortion
				out = atanf(amount_ * in)*(2.0f / 3.0f); //have to decrease the amplitude to snap it to 1
			}

			//Store the output in the buffer, replacing the input
			channelData[i] = out;
		}

		//post filtering stage
		toneFilter_[channel]->processSamples(channelData, bufferSize_);
	}
}