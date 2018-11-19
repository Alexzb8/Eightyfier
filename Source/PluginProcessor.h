/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Chorus.h"
#include "Overdrive.h"
#include "Delay.h"


//==============================================================================
/**
*/
class EightifierAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EightifierAudioProcessor();
    ~EightifierAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================

	int getNumParameters() override;

	float getParameter(int index) override;
	void setParameter(int index, float newValue) override;

	const String getParameterName(int index) override;

	enum Parameters{
		kchorusDelayParam,
		kchorusDepthParam,
		kchorusSweepWidthParam,
		kchorusLFOFrequencyParam,
		koverdriveToggleParam,
		koverdriveAmountParam,
		kinputGainParam,
		koverdriveHighParam,
		koverdriveLowParam,
		koverdriveToneParam,
		kreverbDryParam,
		kreverbWetParam,
		kreverbRoomSizeParam,
		kreverbDampingParam,
		kreverbWidthParam,
		kdelayLengthParam,
		kdelayFeedbackParam,
		kdelayDryParam,
		kdelayWetParam,
		kNumParameters
	};

	// Adjustable parameters:
	float chorusDelay_;
	float chorusDepth_;
	float chorusSweepWidth_;
	float chorusLFOFrequency_;

	float overdriveToggle_;
	float overdriveAmount_;
	float overdriveHigh_;
	float overdriveLow_;
	float overdriveTone_;

	float inputGain_;

	
	float delayLength_;
	float delayFeedback_;
	float delayDry_;
	float delayWet_;

	Reverb::Parameters ReverbEffectParameters_;

private:

	Chorus *ChorusEffect_;
	Overdrive *OverdriveEffect_;
	Reverb ReverbEffect_;
	Delay *DelayEffect_;
	

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EightifierAudioProcessor)
};
