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
    virtual void prepare(double sampleRate); // optional to override
    
    void processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples);
    
    // Make a "pure" virtual function
    // No implementation is provided in the base class
    // Derived class must provide the implementation 
    virtual float processSample(float x, const int channel) = 0;
    
    protected:
    // available in derived classes
    
    double Fs;
    
    private:
    // not available in derived classes
    
};
