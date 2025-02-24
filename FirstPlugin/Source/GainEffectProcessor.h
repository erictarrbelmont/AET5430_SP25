/*
  ==============================================================================

    GainEffectProcessor.h
    Created: 20 Feb 2025 12:58:38pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once


class GainEffectProcessor
{
    public:
    
    void processBuffer(juce::AudioBuffer<float>& buffer, const int numChannels, const int numSamples){
        
        for (int c = 0; c < numChannels; ++c){
            for (int n = 0; n < numSamples ; ++n){
                float x = buffer.getWritePointer(c)[n];
                x = processSample(x);
                buffer.getWritePointer(c)[n] = x;
            }
        }
        
    }
    
    void process(float * buffer, const int numSamples){
        // processing of buffer that does not use Juce Data Types
        for (int n = 0; n < numSamples ; ++n){
            float x = buffer[n]; // pointer to primative array
            x = processSample(x);
            buffer[n] = x;
        }
    }
    
    
    float processSample(float x){
        float y = x * linGain;
        return y;
    }
    
    void setGaindB(float dBGain){
        linGain = std::powf(10.f,dBGain/20.f);
    }
    
    private:
    
    float linGain = 1.f;
};
