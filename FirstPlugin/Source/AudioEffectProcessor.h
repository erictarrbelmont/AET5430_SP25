/*
  ==============================================================================

    AudioEffectProcessor.h
    Created: 25 Feb 2025 1:30:22pm
    Author:  Eric Tarr

  ==============================================================================
*/

// This is a "base" class, or template class ("general" class)

// Inherit this for "derived" audio effect classes (e.g. tremolo)


#pragma once
#include <JuceHeader.h>

class AudioEffectProcessor
{
    public:
    
    virtual ~AudioEffectProcessor() {};
    
    // These are functions every audio effect will have
    void prepare(double sampleRate);
    
    void processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples);
    
    virtual float processSample(float x, const int channel);
    
    protected:
    // available in derived classes
    
    double Fs;
    
    private:
    // not available in derived classes
    
};
