/*
  ==============================================================================

    TremoloEffectProcessor.cpp
    Created: 20 Feb 2025 1:39:03pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "TremoloEffectProcessor.h"

void TremoloEffectProcessor::processBuffer(juce::AudioBuffer<float> & buffer, const int channel, const int numSamples){
    
    for (int n = 0 ; n < numSamples ; ++n){
        float x = buffer.getSample(channel,n); // current sample
        float lfo = A * sin(currentPhase[channel]) + offset;
        float y = x * lfo;
        buffer.setSample(channel,n,y);
        currentPhase[channel] += phaseChange;
        if (currentPhase[channel] > PIx2){
            currentPhase[channel] -= PIx2;
        }
            
    }
}

void TremoloEffectProcessor::prepare(float sampleRate){
    Fs = sampleRate;
}


void TremoloEffectProcessor::setRate(float r){
    rate = r;
    phaseChange = rate * PIx2 / Fs;
}

void TremoloEffectProcessor::setDepth(float d){
    depth = d; //
    A = depth * 0.5f;
    offset = (1.f - A);
}
