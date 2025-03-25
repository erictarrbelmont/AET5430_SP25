/*
  ==============================================================================

    TremoloEffectProcessor.h
    Created: 20 Feb 2025 1:39:03pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class TremoloEffectProcessor {
public:
    
    void processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples);
    
    void prepare(float sampleRate);
    void setRate(float r);
    void setDepth(float d);
    
private:
    
    float currentPhase[2] = {0.f}; // in radians
    float rate = 1.f; // Hz
    float depth = 1.f; // [0-1]
    
    float Fs = 48000.f;
    float phaseChange = rate * 2.f * M_PI / Fs;
    float A = depth * 0.5f;
    float offset = (1.f - A);
    
    const float PIx2 = 2.f * M_PI;
    
};
