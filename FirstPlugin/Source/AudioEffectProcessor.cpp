/*
  ==============================================================================

    AudioEffectProcessor.cpp
    Created: 25 Feb 2025 1:30:22pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "AudioEffectProcessor.h"


void AudioEffectProcessor::prepare(double sampleRate){
    Fs = sampleRate;
}

void AudioEffectProcessor::processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples){
    for (int n = 0 ; n < numSamples ; ++n){
        float x = buffer.getSample(channel,n); // current sample
        float y = processSample(x,channel);
        buffer.setSample(channel,n,y);
    }
}

// Remove if Abstract, base class with a pure virtual function
//float AudioEffectProcessor::processSample(float x, const int channel){
//    return x; // This is "wire" effect
//}
