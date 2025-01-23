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
    
    string filename = "AcGtr.wav";
    vector<float> signal;
    int Fs;
    int bitDepth;
    int numChannels;
    
    // Read in the audio data to a vector of floats
    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    int N = signal.size();
    
//    for (int n = 0; n < N; ++n){
//        float x = signal[n]; // access individual sample
//        float y = abs(x);
//        signal[n] = y;
//    }
    float dB = -12.f;
    gainChange(signal,N,dB);
    
    
    string newFileName = "outputFile.wav";
    audiowrite(newFileName, signal, Fs, bitDepth, numChannels);
    
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
