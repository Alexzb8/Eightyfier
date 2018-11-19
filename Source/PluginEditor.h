/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class EightifierAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public Timer
{
public:
    EightifierAudioProcessorEditor (EightifierAudioProcessor&);
    ~EightifierAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged(Slider*) override;
	void timerCallback() override;

private:

	Slider inputGainSlider_;
	Label inputGainLabel_;

	//Chorus
	Label chorusDelayLabel_, chorusDepthLabel_, chorusSweepWidthLabel_, chorusLFOFrequencyLabel_;
	Slider chorusDelaySlider_, chorusDepthSlider_, chorusSweepWidthSlider_, chorusLFOFrequencySlider_;

	//Overdrive
	Slider overdriveToggleSlider_, overdriveAmountSlider_, overdriveHighSlider_, overdriveLowSlider_, overdriveToneSlider_;
	Label overdriveToggleLabel_, overdriveAmountLabel_, overdriveHighLabel_, overdriveLowLabel_, overdriveToneLabel_;

	//Reverb
	Slider reverbDrySlider_, reverbWetSlider_, reverbRoomSizeSlider_, reverbDampingSlider_, reverbWidthSlider_;
	Label reverbDryLabel_, reverbWetLabel_, reverbRoomSizeLabel_, reverbDampingLabel_, reverbWidthLabel_;

	//Delay
	Label delayLengthLabel_, delayFeedbackLabel_, delayDryLabel_, delayWetLabel_;
	Slider delayLengthSlider_, delayFeedbackSlider_, delayDrySlider_, delayWetSlider_;



	

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EightifierAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EightifierAudioProcessorEditor)
};
