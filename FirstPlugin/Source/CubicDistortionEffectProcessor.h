/*
  ==============================================================================

    CubicDistortionEffectProcessor.h
    Created: 25 Feb 2025 1:40:55pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once
#include "AudioEffectProcessor.h"
// Implemented as "derived" class. Reuses the functionality of the generic "AudioEffectProcessor" base class

class CubicDistortionEffectProcessor : public AudioEffectProcessor
{
    public:
    float processSample(float x, const int channel) override
    {
        float y = x - (1.f/3.f) * std::powf(x,3.f);
    }
};
