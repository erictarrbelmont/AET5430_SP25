/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GainEffectProcessor.h"
#include "TremoloEffectProcessor.h"
#include "CubicDistortionEffectProcessor.h"
#include "AudioEffectProcessor.h"
#include "Biquad.h"

//==============================================================================
/**
*/
class FirstPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FirstPluginAudioProcessor();
    ~FirstPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static const bool BYPASSED_DEFAULT = false;
    
    bool isBypassed = BYPASSED_DEFAULT;
    
    static constexpr float GAIN_DEFAULT = 0.f;
    
    float gainValue = GAIN_DEFAULT;
    
    static constexpr float FREQ_DEFAULT = 1000.f;
    
    float freqValue = FREQ_DEFAULT;
    
    static constexpr float FILTER_AMP_DEFAULT = 0.f;
    
    float filterAmpValue = FILTER_AMP_DEFAULT;
    
    static constexpr float FILTER_Q_DEFAULT = 0.7071f;
    
    float filterQValue = FILTER_Q_DEFAULT;
    
    
    Biquad::FilterType filterType = Biquad::FilterType::LPF;
    
private:
    
    GainEffectProcessor gain;
    
    TremoloEffectProcessor tremolo;
    
    AudioPlayHead* playhead;
    
    
    CubicDistortionEffectProcessor distortion;
    //AudioEffectProcessor effect;
    
    Biquad filter {Biquad::FilterType::LPF,0.7071f};
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstPluginAudioProcessor)
};
