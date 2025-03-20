//
//  FractionalDelay.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "FractionalDelay.hpp"

// Constructor function (special function - no return type, name = Class name)
FractionalDelay::FractionalDelay(){
}

// Destructor
FractionalDelay::~FractionalDelay(){
}


float FractionalDelay::processSample(float x, int channel){
    
    float lfo;
    
    lfo = amp * sin(currentAngle) + offset;
    
    currentAngle += angleChange;
    if (currentAngle > 2.f * M_PI){
        currentAngle -= 2.f * M_PI;
    }
    
    // Delay Buffer
    // "delay" can be fraction
    int d1 = floor(delay+lfo);
    int d2 = d1 + 1;
    float g2 = delay + lfo - (float)d1;
    float g1 = 1.0f - g2;
    
    int indexD1 = index[channel] - d1;
    if (indexD1 < 0){
        indexD1 += MAX_BUFFER_SIZE;
    }
    
    int indexD2 = index[channel] - d2;
    if (indexD2 < 0){
        indexD2 += MAX_BUFFER_SIZE;
    }
    
    float y = g1 * delayBuffer[indexD1][channel] + g2 * delayBuffer[indexD2][channel];
    
    delayBuffer[index[channel]][channel] = x;
    
    if (index[channel] < MAX_BUFFER_SIZE - 1){
        index[channel]++;
    }
    else{
        index[channel] = 0;
    }
    
    return y;
}

void FractionalDelay::setFs(float Fs){
    this->Fs = Fs;
}


void FractionalDelay::setDelaySamples(float delay){
    this->delay = delay;
}


void FractionalDelay::setSpeed(float speed){
    if (speed >= 0.1f && speed <= 10.0f){
        this->speed = speed;
        angleChange = speed * (1.f/Fs) * 2 * M_PI;
    }
}

void FractionalDelay::setDepth(float depth){
    if (depth >= 1.0f && depth <= 10.0f){
        this->depth = depth;
        amp = depth;
        offset = amp + 1.0f;
    }
}
