//
//  FBCF.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "FBCF.hpp"

// Constructor function (special function - no return type, name = Class name)
FBCF::FBCF(){
}

FBCF::FBCF( float delay, float speed):delay(delay),speed(speed){
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
}

// Destructor
FBCF::~FBCF(){
}


float FBCF::processSample(float x, int channel){
    
    float y = x + gain * delaySample;
    
    delaySample = fractionalDelay.processSample(y, channel);
    
    // returning "y" puts the delay in the feed-back path
    //return y;
    
    // returning "delaySample" puts the delay block on the thru path
    return delaySample;
}

void FBCF::setFs(float Fs){
    this->Fs = Fs;
    fractionalDelay.setFs(Fs);
}


void FBCF::setDelaySamples(float delay){
    this->delay = delay;
    fractionalDelay.setDelaySamples(delay);
}

void FBCF::setGain(float gain){
    this->gain = gain;
}

void FBCF::setSpeed(float speed){
    if (speed >= 0.1f && speed <= 10.0f){
        this->speed = speed;
        fractionalDelay.setSpeed(speed);
    }
}

void FBCF::setDepth(float depth){
    if (depth >= 1.0f && depth <= 10.0f){
        this->depth = depth;
        fractionalDelay.setDepth(depth);
    }
}
