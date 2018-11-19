/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EightifierAudioProcessor::EightifierAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	ChorusEffect_ = new Chorus();
	OverdriveEffect_ = new Overdrive();
	DelayEffect_ = new Delay();

	//Default parameter values

	chorusDelay_ = 21.37;
	chorusDepth_ = .87;
	chorusSweepWidth_ = 4.75;
	chorusLFOFrequency_ = 0.76;

	overdriveToggle_ = 2;
	overdriveAmount_ = 2.75;
	overdriveHigh_ = 3;
	overdriveLow_ = .04;
	overdriveTone_ = .28;

	delayLength_ = 0.35;
	delayFeedback_ = 0.05;
	delayDry_ = 1;
	delayWet_ = .5;


	inputGain_ = 21.3;

	ReverbEffectParameters_.dryLevel = 1;
	ReverbEffectParameters_.wetLevel = .37;
	ReverbEffectParameters_.roomSize = .37;
	ReverbEffectParameters_.damping = .1;
	ReverbEffectParameters_.width = .5;
	ReverbEffect_.setParameters(ReverbEffectParameters_);
}

EightifierAudioProcessor::~EightifierAudioProcessor()
{
}

//==============================================================================
const String EightifierAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EightifierAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EightifierAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EightifierAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EightifierAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EightifierAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EightifierAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EightifierAudioProcessor::setCurrentProgram (int index)
{
}

const String EightifierAudioProcessor::getProgramName (int index)
{
    return {};
}

void EightifierAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EightifierAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

	ChorusEffect_->prepareToPlay(sampleRate, samplesPerBlock);
	OverdriveEffect_->prepareToPlay(sampleRate, samplesPerBlock);
	DelayEffect_->prepareToPlay(sampleRate, samplesPerBlock);
	ReverbEffect_.setSampleRate(sampleRate);
}

void EightifierAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EightifierAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EightifierAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
	const auto minNumChannels = jmin(totalNumInputChannels, totalNumOutputChannels);

	const int numSamples = buffer.getNumSamples(); // How many samples in the buffer

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	//apply input gain
	buffer.applyGain(Decibels::decibelsToGain(inputGain_));
	
	//apply overdrive effect
	OverdriveEffect_->update(numSamples, overdriveToggle_, overdriveAmount_, overdriveHigh_, overdriveLow_, overdriveTone_);
	OverdriveEffect_->Apply(buffer, totalNumInputChannels);

	//Applying chorus after overdrive sounds better
	ChorusEffect_->update(numSamples, chorusDelay_, chorusDepth_, chorusSweepWidth_, chorusLFOFrequency_);
	ChorusEffect_->Apply(buffer, totalNumInputChannels);

	//Apply Delay effect
	DelayEffect_->update(numSamples, delayLength_, delayFeedback_, delayDry_, delayWet_);
	DelayEffect_->Apply(buffer, totalNumInputChannels);

	//Apply Reverb effect
	ReverbEffect_.setParameters(ReverbEffectParameters_);
	//apply it depending on the number of available channels
	if(minNumChannels == 1){
		ReverbEffect_.processMono(buffer.getWritePointer(0), numSamples);
	} else if(minNumChannels == 2){
		ReverbEffect_.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), numSamples);
	}

}

//==============================================================================
bool EightifierAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EightifierAudioProcessor::createEditor()
{
    return new EightifierAudioProcessorEditor (*this);
}

//==============================================================================
void EightifierAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EightifierAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


int EightifierAudioProcessor::getNumParameters(){
	return kNumParameters;
}

float EightifierAudioProcessor::getParameter(int index){
	// This method will be called by the host, probably on the audio thread, so
	// it's absolutely time-critical. Don't use critical sections or anything
	// UI-related, or anything at all that may block in any way!
	switch(index){
	case kchorusDelayParam: return chorusDelay_;
	case kchorusSweepWidthParam: return chorusSweepWidth_;
	case kchorusDepthParam: return chorusDepth_;
	case kchorusLFOFrequencyParam: return chorusLFOFrequency_;
	case koverdriveToggleParam: return overdriveToggle_;
	case koverdriveAmountParam: return overdriveAmount_;
	case kinputGainParam: return inputGain_;
	case koverdriveHighParam: return overdriveHigh_;
	case koverdriveLowParam: return overdriveLow_;
	case koverdriveToneParam: return overdriveTone_;
	case kreverbDryParam: return ReverbEffectParameters_.dryLevel;
	case kreverbWetParam: return ReverbEffectParameters_.wetLevel;
	case kreverbRoomSizeParam: return ReverbEffectParameters_.roomSize;
	case kreverbDampingParam: return ReverbEffectParameters_.damping;
	case kreverbWidthParam: return ReverbEffectParameters_.width;
	case kdelayLengthParam: return delayLength_;
	case kdelayFeedbackParam: return delayFeedback_;
	case kdelayDryParam: return delayDry_;
	case kdelayWetParam: return delayWet_;
	default: return 0.0f;
	}
}

void EightifierAudioProcessor::setParameter(int index, float newValue){
	// This method will be called by the host, probably on the audio thread, so
	// it's absolutely time-critical. Don't use critical sections or anything
	// UI-related, or anything at all that may block in any way!
	switch(index){
	case kchorusDelayParam:
		chorusDelay_ = newValue;
		break;
	case kchorusLFOFrequencyParam:
		chorusLFOFrequency_ = newValue;
		break;
	case kchorusDepthParam:
		chorusDepth_ = newValue;
		break;
	case kchorusSweepWidthParam:
		chorusSweepWidth_ = newValue;
		break;
	case koverdriveToggleParam:
		overdriveToggle_ = newValue;
		break;
	case koverdriveAmountParam:
		overdriveAmount_ = newValue;
		break;
	case kinputGainParam:
		inputGain_ = newValue;
		break;
	case koverdriveHighParam:
		overdriveHigh_ = newValue;
		break;
	case koverdriveLowParam:
		overdriveLow_ = newValue;
		break;
	case koverdriveToneParam:
		overdriveTone_ = newValue;
		break;
	case kreverbDryParam:
		ReverbEffectParameters_.dryLevel = newValue;
		break;
	case kreverbWetParam:
		ReverbEffectParameters_.wetLevel = newValue;
		break;
	case kreverbRoomSizeParam:
		ReverbEffectParameters_.roomSize = newValue;
		break;
	case kreverbDampingParam:
		ReverbEffectParameters_.damping = newValue;
		break;
	case kreverbWidthParam:
		ReverbEffectParameters_.width = newValue;
		break;
	case kdelayLengthParam:
		delayLength_ = newValue;
		break;
	case kdelayFeedbackParam:
		delayFeedback_ = newValue;
		break;
	case kdelayDryParam:
		delayDry_ = newValue;
		break;
	case kdelayWetParam:
		delayWet_ = newValue;
		break;
	default:
		break;
	}
}

const String EightifierAudioProcessor::getParameterName(int index){
	switch(index){
	case kchorusDelayParam: return "Chorus delay";
	case kchorusLFOFrequencyParam: return "chorus LFO frequency";
	case kchorusDepthParam: return "Chorus depth";
	case kchorusSweepWidthParam: return "Chorus Sweep Width";
	case koverdriveToggleParam: return "Overdrive Type";
	case koverdriveAmountParam: return "Overdrive Amount";
	case kinputGainParam: return "Input Gain";
	case koverdriveHighParam: return "Overdrive Highs";
	case koverdriveLowParam: return "Overdrive Lows";
	case koverdriveToneParam: return "Overdrive Tone";
	case kreverbDryParam: return "Reverb Dry";
	case kreverbWetParam: return "Reverb Wet";
	case kreverbRoomSizeParam: return "Reverb Room Size";
	case kreverbDampingParam: return "Reverb Damping";
	case kreverbWidthParam: return "Reverb Width";
	case kdelayLengthParam: return "Delay Length";
	case kdelayFeedbackParam: return "Delay Feedback";
	case kdelayDryParam: return "Delay Dry";
	case kdelayWetParam: return "Delay Wet";
	default: break;
	}

	return String::empty;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EightifierAudioProcessor();
}
