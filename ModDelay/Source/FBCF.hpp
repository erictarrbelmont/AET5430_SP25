//
//  FBCF.hpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#ifndef FBCF_hpp
#define FBCF_hpp

#include <cmath>
#include <vector>
#include "FractionalDelay.hpp"

using namespace std;

class FBCF {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    FBCF();
    FBCF(float delay, float speed);
    
    // Destructor
    ~FBCF();
    
    //void processSignal(float * signal, int numSamples, int channel);
    
    float processSample(float x,int channel);

    void setFs(float Fs);
    
    void setDelaySamples(float delay);
    
    void setSpeed(float speed);
    void setDepth(float depth);
    void setGain(float gain);
    
private:
    
    float Fs = 48000.f;
    
    float delay = 5.f;
    
    FractionalDelay fractionalDelay;
    
    float delaySample = 0.0f;
    
    float speed = 1.0f; // Hz, frequency of LFO
    float depth = 10.0f; // percentage of intensity, control amp of LFO
    
    float gain = 0.5f;
    
};



#endif /* FractionalDelay_hpp */
