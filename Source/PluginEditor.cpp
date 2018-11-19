/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EightifierAudioProcessorEditor::EightifierAudioProcessorEditor (EightifierAudioProcessor& p)
    : AudioProcessorEditor (&p), 
	chorusDelayLabel_("","Delay"), 
	chorusDepthLabel_("","Depth"), 
	chorusSweepWidthLabel_("","SweepWidth"), 
	chorusLFOFrequencyLabel_("","LFOSpeed"),
	overdriveToggleLabel_("", "Type"),
	overdriveAmountLabel_("", "Amount"),
	overdriveHighLabel_("", "Highs"),
	overdriveLowLabel_("", "Lows"),
	overdriveToneLabel_("", "Tone"),
	inputGainLabel_("", "Input Gain"),
	reverbDryLabel_("", "Dry"),
	reverbWetLabel_("", "Wet"),
	reverbRoomSizeLabel_("", "Room Size"),
	reverbDampingLabel_("", "Damping"),
	reverbWidthLabel_("", "Width"),
	delayLengthLabel_("", "Length"),
	delayFeedbackLabel_("", "Feedback"),
	delayDryLabel_("", "Dry"),
	delayWetLabel_("", "Wet"),
	processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(906, 525);

	// Set up the sliders

	addAndMakeVisible(&chorusDelaySlider_);
	chorusDelaySlider_.setSliderStyle(Slider::Rotary);
	chorusDelaySlider_.addListener(this);
	chorusDelaySlider_.setRange(10.0, 40.0, 0.01);
	chorusDelaySlider_.setValue(processor.getParameter(EightifierAudioProcessor::kchorusDelayParam));

	addAndMakeVisible(&chorusDepthSlider_);
	chorusDepthSlider_.setSliderStyle(Slider::Rotary);
	chorusDepthSlider_.addListener(this);
	chorusDepthSlider_.setRange(0.0, 1.0, 0.01);
	chorusDepthSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kchorusDepthParam));

	addAndMakeVisible(&chorusSweepWidthSlider_);
	chorusSweepWidthSlider_.setSliderStyle(Slider::Rotary);
	chorusSweepWidthSlider_.addListener(this);
	chorusSweepWidthSlider_.setRange(1.0, 20.0, 0.01);
	chorusSweepWidthSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kchorusSweepWidthParam));

	addAndMakeVisible(&chorusLFOFrequencySlider_);
	chorusLFOFrequencySlider_.setSliderStyle(Slider::Rotary);
	chorusLFOFrequencySlider_.addListener(this);
	chorusLFOFrequencySlider_.setRange(0.2, 5.0, 0.01);
	chorusLFOFrequencySlider_.setValue(processor.getParameter(EightifierAudioProcessor::kchorusLFOFrequencyParam));

	addAndMakeVisible(&overdriveToggleSlider_);
	overdriveToggleSlider_.setSliderStyle(Slider::Rotary);
	overdriveToggleSlider_.addListener(this);
	overdriveToggleSlider_.setRange(0.0, 2.0, 1.0);
	overdriveToggleSlider_.setValue(processor.getParameter(EightifierAudioProcessor::koverdriveToggleParam));

	addAndMakeVisible(&overdriveAmountSlider_);
	overdriveAmountSlider_.setSliderStyle(Slider::Rotary);
	overdriveAmountSlider_.addListener(this);
	overdriveAmountSlider_.setRange(1.0, 20.0, 0.01);
	overdriveAmountSlider_.setValue(processor.getParameter(EightifierAudioProcessor::koverdriveAmountParam));


	addAndMakeVisible(&inputGainSlider_);
	inputGainSlider_.setSliderStyle(Slider::Rotary);
	inputGainSlider_.addListener(this);
	inputGainSlider_.setRange(-20.0, 40.0, 0.01);
	inputGainSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kinputGainParam));

	addAndMakeVisible(&overdriveHighSlider_);
	overdriveHighSlider_.setSliderStyle(Slider::Rotary);
	overdriveHighSlider_.addListener(this);
	overdriveHighSlider_.setRange(0.01, 10.0, 0.01);
	overdriveHighSlider_.setValue(processor.getParameter(EightifierAudioProcessor::koverdriveHighParam));

	addAndMakeVisible(&overdriveLowSlider_);
	overdriveLowSlider_.setSliderStyle(Slider::Rotary);
	overdriveLowSlider_.addListener(this);
	overdriveLowSlider_.setRange(0.01, 5.0, 0.01);
	overdriveLowSlider_.setValue(processor.getParameter(EightifierAudioProcessor::koverdriveLowParam));

	addAndMakeVisible(&overdriveToneSlider_);
	overdriveToneSlider_.setSliderStyle(Slider::Rotary);
	overdriveToneSlider_.addListener(this);
	overdriveToneSlider_.setRange(0.01, 2.0, 0.01);
	overdriveToneSlider_.setValue(processor.getParameter(EightifierAudioProcessor::koverdriveToneParam));

	addAndMakeVisible(&reverbDrySlider_);
	reverbDrySlider_.setSliderStyle(Slider::Rotary);
	reverbDrySlider_.addListener(this);
	reverbDrySlider_.setRange(0.0, 1.0, 0.01);
	reverbDrySlider_.setValue(processor.getParameter(EightifierAudioProcessor::kreverbDryParam));

	addAndMakeVisible(&reverbWetSlider_);
	reverbWetSlider_.setSliderStyle(Slider::Rotary);
	reverbWetSlider_.addListener(this);
	reverbWetSlider_.setRange(0.0, 1.0, 0.01);
	reverbWetSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kreverbWetParam));

	addAndMakeVisible(&reverbRoomSizeSlider_);
	reverbRoomSizeSlider_.setSliderStyle(Slider::Rotary);
	reverbRoomSizeSlider_.addListener(this);
	reverbRoomSizeSlider_.setRange(0.0, 1.0, 0.01);
	reverbRoomSizeSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kreverbRoomSizeParam));

	addAndMakeVisible(&reverbDampingSlider_);
	reverbDampingSlider_.setSliderStyle(Slider::Rotary);
	reverbDampingSlider_.addListener(this);
	reverbDampingSlider_.setRange(0.0, 1.0, 0.01);
	reverbDampingSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kreverbDampingParam));

	addAndMakeVisible(&reverbWidthSlider_);
	reverbWidthSlider_.setSliderStyle(Slider::Rotary);
	reverbWidthSlider_.addListener(this);
	reverbWidthSlider_.setRange(0.0, 1.0, 0.01);
	reverbWidthSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kreverbWidthParam));

	addAndMakeVisible(&delayLengthSlider_);
	delayLengthSlider_.setSliderStyle(Slider::Rotary);
	delayLengthSlider_.addListener(this);
	delayLengthSlider_.setRange(0.01, 2.0, 0.01);
	delayLengthSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kdelayLengthParam));

	addAndMakeVisible(&delayFeedbackSlider_);
	delayFeedbackSlider_.setSliderStyle(Slider::Rotary);
	delayFeedbackSlider_.addListener(this);
	delayFeedbackSlider_.setRange(0.0, 0.995, 0.01);
	delayFeedbackSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kdelayFeedbackParam));

	addAndMakeVisible(&delayDrySlider_);
	delayDrySlider_.setSliderStyle(Slider::Rotary);
	delayDrySlider_.addListener(this);
	delayDrySlider_.setRange(0.0, 1.0, 0.01);
	delayDrySlider_.setValue(processor.getParameter(EightifierAudioProcessor::kdelayDryParam));

	addAndMakeVisible(&delayWetSlider_);
	delayWetSlider_.setSliderStyle(Slider::Rotary);
	delayWetSlider_.addListener(this);
	delayWetSlider_.setRange(0.0, 1.0, 0.01);
	delayWetSlider_.setValue(processor.getParameter(EightifierAudioProcessor::kdelayWetParam));

	chorusDelayLabel_.attachToComponent(&chorusDelaySlider_, true);
	chorusDepthLabel_.attachToComponent(&chorusDepthSlider_, true);
	chorusSweepWidthLabel_.attachToComponent(&chorusSweepWidthSlider_, true);
	chorusLFOFrequencyLabel_.attachToComponent(&chorusLFOFrequencySlider_, true);

	overdriveToggleLabel_.attachToComponent(&overdriveToggleSlider_, true);
	overdriveAmountLabel_.attachToComponent(&overdriveAmountSlider_, true);
	overdriveHighLabel_.attachToComponent(&overdriveHighSlider_, true);
	overdriveLowLabel_.attachToComponent(&overdriveLowSlider_, true);
	overdriveToneLabel_.attachToComponent(&overdriveToneSlider_, true);

	inputGainLabel_.attachToComponent(&inputGainSlider_, true);
	
	reverbDryLabel_.attachToComponent(&reverbDrySlider_, true);
	reverbWetLabel_.attachToComponent(&reverbWetSlider_, true);
	reverbRoomSizeLabel_.attachToComponent(&reverbRoomSizeSlider_, true);
	reverbDampingLabel_.attachToComponent(&reverbDampingSlider_, true);
	reverbWidthLabel_.attachToComponent(&reverbWidthSlider_, true);

	delayLengthLabel_.attachToComponent(&delayLengthSlider_, true);
	delayFeedbackLabel_.attachToComponent(&delayFeedbackSlider_, true);
	delayDryLabel_.attachToComponent(&delayDrySlider_, true);
	delayWetLabel_.attachToComponent(&delayWetSlider_, true);

}

EightifierAudioProcessorEditor::~EightifierAudioProcessorEditor()
{
}

//==============================================================================
void EightifierAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Chorus", getLocalBounds(), Justification::centred, 1);
	//g.drawText("Chorus",)
	g.drawText("Chorus", 12, 7, 150, 10, Justification::centredBottom, false);
	g.drawText("Overdrive", 265, 7, 150, 10, Justification::centredBottom, false);
	g.drawText("Reverb", 507, 7, 150, 10, Justification::centredBottom, false);
	g.drawText("Delay", 739, 7, 150, 10, Justification::centredBottom, false);
}

void EightifierAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	chorusDelaySlider_.setBounds(60, 10, 150, 75);
	chorusDepthSlider_.setBounds(60, 70, 150, 75);
	chorusSweepWidthSlider_.setBounds(60, 130, 150, 75);
	chorusLFOFrequencySlider_.setBounds(60, 190, 150, 75);

	overdriveToggleSlider_.setBounds(280, 10, 150, 75);
	overdriveAmountSlider_.setBounds(280, 70, 150, 75);
	overdriveHighSlider_.setBounds(280, 130, 150, 75);
	overdriveLowSlider_.setBounds(280, 190, 150, 75);
	overdriveToneSlider_.setBounds(280, 250, 150, 75);

	inputGainSlider_.setBounds(400, 310, 150, 75);
	
	reverbDrySlider_.setBounds(520, 10, 150, 75);
	reverbWetSlider_.setBounds(520, 70, 150, 75);
	reverbRoomSizeSlider_.setBounds(520, 130, 150, 75);
	reverbDampingSlider_.setBounds(520, 190, 150, 75);
	reverbWidthSlider_.setBounds(520, 250, 150, 75);

	delayLengthSlider_.setBounds(760, 10, 150, 75);
	delayFeedbackSlider_.setBounds(760, 70, 150, 75);
	delayDrySlider_.setBounds(760, 130, 150, 75);
	delayWetSlider_.setBounds(760, 190, 150, 75);
}

void EightifierAudioProcessorEditor::sliderValueChanged(Slider *slider){

	if(slider == &chorusDelaySlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kchorusDelayParam,
			(float)chorusDelaySlider_.getValue());
	} else if(slider == &chorusDepthSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kchorusDepthParam,
			(float)chorusDepthSlider_.getValue());
	} else if(slider == &chorusSweepWidthSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kchorusSweepWidthParam,
			(float)chorusSweepWidthSlider_.getValue());
	} else if(slider == &chorusLFOFrequencySlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kchorusLFOFrequencyParam,
			(float)chorusLFOFrequencySlider_.getValue());
	} else if(slider == &overdriveToggleSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::koverdriveToggleParam,
			(float)overdriveToggleSlider_.getValue());
	} else if(slider == &overdriveAmountSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::koverdriveAmountParam,
			(float)overdriveAmountSlider_.getValue());
	} else if(slider == &inputGainSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kinputGainParam,
			(float)inputGainSlider_.getValue());
	} else if(slider == &overdriveHighSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::koverdriveHighParam,
			(float)overdriveHighSlider_.getValue());
	} else if(slider == &overdriveLowSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::koverdriveLowParam,
			(float)overdriveLowSlider_.getValue());
	} else if(slider == &overdriveToneSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::koverdriveToneParam,
			(float)overdriveToneSlider_.getValue());
	} else if(slider == &reverbDrySlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kreverbDryParam,
			(float)reverbDrySlider_.getValue());
	} else if(slider == &reverbWetSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kreverbWetParam,
			(float)reverbWetSlider_.getValue());
	} else if(slider == &reverbRoomSizeSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kreverbRoomSizeParam,
			(float)reverbRoomSizeSlider_.getValue());
	} else if(slider == &reverbDampingSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kreverbDampingParam,
			(float)reverbDampingSlider_.getValue());
	} else if(slider == &reverbWidthSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kreverbWidthParam,
			(float)reverbWidthSlider_.getValue());
	} else if(slider == &delayLengthSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kdelayLengthParam,
			(float)delayLengthSlider_.getValue());
	} else if(slider == &delayFeedbackSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kdelayFeedbackParam,
			(float)delayFeedbackSlider_.getValue());
	} else if(slider == &delayDrySlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kdelayDryParam,
			(float)delayDrySlider_.getValue());
	} else if(slider == &delayWetSlider_){
		processor.setParameterNotifyingHost(EightifierAudioProcessor::kdelayWetParam,
			(float)delayWetSlider_.getValue());
	}
}

void EightifierAudioProcessorEditor::timerCallback(){

	chorusDelaySlider_.setValue(processor.chorusDelay_, dontSendNotification);
	chorusLFOFrequencySlider_.setValue(processor.chorusLFOFrequency_, dontSendNotification);
	chorusDepthSlider_.setValue(processor.chorusDepth_, dontSendNotification);
	chorusSweepWidthSlider_.setValue(processor.chorusSweepWidth_, dontSendNotification);

	overdriveToggleSlider_.setValue(processor.overdriveToggle_, dontSendNotification);
	overdriveAmountSlider_.setValue(processor.overdriveAmount_, dontSendNotification);

	inputGainSlider_.setValue(processor.inputGain_, dontSendNotification);
	overdriveHighSlider_.setValue(processor.overdriveHigh_, dontSendNotification);
	overdriveLowSlider_.setValue(processor.overdriveLow_, dontSendNotification);
	overdriveToneSlider_.setValue(processor.overdriveTone_, dontSendNotification);
	reverbDrySlider_.setValue(processor.ReverbEffectParameters_.dryLevel, dontSendNotification);
	reverbWetSlider_.setValue(processor.ReverbEffectParameters_.wetLevel, dontSendNotification);
	reverbRoomSizeSlider_.setValue(processor.ReverbEffectParameters_.roomSize, dontSendNotification);
	reverbDampingSlider_.setValue(processor.ReverbEffectParameters_.damping, dontSendNotification);
	reverbWidthSlider_.setValue(processor.ReverbEffectParameters_.width, dontSendNotification);
	delayLengthSlider_.setValue(processor.delayLength_, dontSendNotification);
	delayFeedbackSlider_.setValue(processor.delayFeedback_, dontSendNotification);
	delayDrySlider_.setValue(processor.delayDry_, dontSendNotification);
	delayWetSlider_.setValue(processor.delayWet_, dontSendNotification);

}





























































































