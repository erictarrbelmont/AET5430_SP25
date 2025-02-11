//
//  main.cpp
//  AudioExample
//
//  Created by Hack Audio on 10/5/19.
//  Copyright © 2019 Eric Tarr. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
using namespace std;

// Declare functions outside of the scope of their use
// Declaration is based on function signature

// OUTPUT VAR TYPE - FUNCTION NAME(INPUT VAR TYPE w/ NAME)
int myFunction(int inVar, int & out1, int &out2); // & means pass by reference

void gainChange(vector<float> & sig, int N, float dBAmp);

void stereoPanner(vector<float> & input, vector<vector<float>> & output, const float panValue);

struct AudioInfo
{
    string filename;
    int Fs;
    int bitDepth;
    int numChannels;
};

class DistortionEffectProcessor
{
public:
    
    enum Type
    {
        FULLWAVE,
        HALFWAVE,
        ARCTAN
    };
    
    // Add special "optional" function that is called only at the time the object is created
    // Called a constructor function
//    DistortionEffectProcessor()
//    {
//        alpha = 5.f;
//    }
    
    //DistortionEffectProcessor(float a){
    //    alpha = a;
    //}
    
    DistortionEffectProcessor(Type t){
        distortionType = t;
    }
    
    // Destructor
    //~DistortionEffectProcessor(){
    //    int n = 5;
    //}
    
    void processStereo(vector<vector<float>> & signal, const int N, const int numChannels){
        for (int c = 0; c < numChannels; ++c){
            //for (int n = 0; n < N ; ++n){
            //    signal[c][n] = processSample(signal[c][n]);
            //}
            processInPlace(signal[c],N);
        }
    }
    
    void process(vector<float> & input, vector<float> & output, const int N){
        for (int n = 0; n < N; ++n){
            output[n] = processSample(input[n]);
        }
    }
    
    void processInPlace(vector<float> & signal, const int N){
        for (int n = 0; n < N; ++n){
            signal[n] = processSample(signal[n]);
        }
    }
    
    float processSample(float x){
        float y = 0.f;
        if (distortionType == Type::ARCTAN){
            y = (2.f/M_PI) * atan(alpha * x);
        }
        else if(distortionType == Type::FULLWAVE){
            y = abs(x);
        }
        else {
            y = max(0.f,x);
        }
        return y;
    }
    
    void setDrive(float a){
        alpha = a;
    }
private:
    
    float alpha = 1.f; // [1-10]
    
    Type distortionType;
    
};


class AudioBuffer
{
public:
    
    void fillChannelOfBuffer(vector<float> & signal, int channel, int & sigIndex){
        int N = signal.size();
        for (int n = 0 ; n < bufferSize ; ++n ){
            if (sigIndex < N){
                buffer[channel][n] = signal[sigIndex];
                sigIndex++;
            }
            else {
                buffer[channel][n] = 0.f;
            }
        }
    }
    
    
    void fillSignalWithBuffer(vector<float> & signal, int channel, int & sigIndex){
        int N = signal.size();
        for (int n = 0 ; n < bufferSize ; ++n ){
            if (sigIndex < N){
                signal[sigIndex] = buffer[channel][n];
                sigIndex++;
            }
            else {
                buffer[channel][n] = 0.f;
            }
        }
    }
    
    
    void setSample(float value, int channel, int sampleNumber){
        buffer[channel][sampleNumber] = value;
    }
    
    float getSample(int channel, int sampleNumber){
        return buffer[channel][sampleNumber];
    }
    
    void setBufferSize(int size){
        bufferSize = size;
    }
    
    int getBufferSize(){
        return bufferSize;
    }
    
private:
    static const int NUMCHANNELS = 2;
    static const int MAXBUFFERSIZE = 1024;
    float buffer[NUMCHANNELS][MAXBUFFERSIZE] = {0.f};
    
    // Whatever the DAW says what the current bufferSize is
    int bufferSize = 512;
};


class GainEffectProcessor{
  
public:
    
    void processBuffer(AudioBuffer & buffer, int channel, int numSamples){
        for (int n = 0; n < numSamples ; ++n){
            float x = buffer.getSample(channel,n);
            buffer.setSample(x * linGain, channel, n);
        }
    }
    
    void setGaindB(float dBGain){
        linGain = pow(10.f,dBGain/20.f);
    }
private:
    
    float linGain = 1.f;
};

class LPFEffectProcessor {
public:
    
    void processBuffer(AudioBuffer & buffer, int channel, int numSamples){
        for (int n = 0 ; n < numSamples ; ++n){
            float x = buffer.getSample(channel,n);
            float y = 0.5f * (x + x1[channel]);
            x1[channel] = x;
            buffer.setSample(y, channel, n);
        }
    }
    
private:
    
    float x1[2] = {0.f}; // initialize delay sample as "0"
    
};


class TremoloEffectProcessor {
public:
    
    void setRate(float r){
        rate = r;
    }
    
    void setDepth(float d){
        depth = d;
    }
    
private:
    
    float currentPhase[2] = {0.f}; // in radians
    float rate = 1.f; // Hz
    float depth = 1.f; // [0-1]
    
    float Fs = 48000.f;
    float phaseChange = rate * 2.f * M_PI / Fs;
};



int main() {
    
    // C++ Conditional Statements
    int x = 5;
    
    int output1;
    int output2;
    int y = myFunction(x,output1,output2);
    
    int w = x * 2;
//    float w;
//    if (x == 5){
//        w = 10.f;
//    }
//    else if (x == 10){
//        
//    }
//    else{
//        float k = 11.f;
//    }
//    
//    float z = 11.f;
    
    AudioInfo info;
    
    //string filename = "AcGtr.wav";
    vector<float> signal;
    //int Fs;
    //int bitDepth;
    //int numChannels;
    info.filename = "AcGtr.wav";
    
    
    // Read in the audio data to a vector of floats
    audioread(info.filename, signal, info.Fs, info.bitDepth, info.numChannels);
    
    int N = signal.size();
    
    AudioBuffer buffer;
    
    const int numSamples = 256;
    buffer.setBufferSize(numSamples);
    
    GainEffectProcessor gain;
    
    gain.setGaindB(-3.f);
    
    LPFEffectProcessor lpf;
    
    
    // Start at the beginning of signal
    int sigIndex = 0;
    int outIndex = 0;
    while (sigIndex < N){
        
        // fill up our buffer with a part of the signal (DAW does this)
        buffer.fillChannelOfBuffer(signal, 0, sigIndex);
        // sigIndex is advanced inside this function
        
        // This is our "plugin" doing its thing
        gain.processBuffer(buffer, 0, numSamples);
        lpf.processBuffer(buffer, 0, numSamples);
        
        // Fill output signal (DAW does this)
        buffer.fillSignalWithBuffer(signal, 0, outIndex);
        
        //sigIndex++;
    }
    
    
    
    //DistortionEffectProcessor effect;
    //effect.setDrive(10.f);
    //DistortionEffectProcessor::Type myType = DistortionEffectProcessor::Type::HALFWAVE;
    //DistortionEffectProcessor effect {myType}; // Input variable constructor
    //effect.processInPlace(signal,N);
    
    string newFileName = "outputFile.wav";
    audiowrite(newFileName, signal, info.Fs, info.bitDepth, info.numChannels);
    
    return 0;
}

// PUT Function definition somewhere else
int myFunction(int  m, int & o1, int & o2){
    int p = m + 5;
    m = 12;
    o1 = 15;
    o2 = 20;
    return p; // Need to specify output variable
}



void gainChange(vector<float> & sig, int N, float dBAmp){
    float g = pow(10.f, dBAmp/20.f ); //10.f^(dBAmp/20.f)
    for (int n = 0; n < N; ++n){
        float x = sig[n];
        sig[n] = x * g;
    }
}


void stereoPanner(vector<float> & input, vector<vector<float>> & output, const float panValue){
    // panValue [-100, +100]
//    if (panValue < -100.f){
//        panValue = -100.f;
//    }
//
    int N = input.size();
    float p = panValue / 200.f + 0.5f; // [0,1]
    float aR = std::sqrt(p);
    float aL = std::sqrt(1.f-p);
    
    for (int n = 0; n < N; ++n){
        float x = input[n];
        output[0][n] = aL * x;
        output[1][n] = aR * x;
    }
    
}
