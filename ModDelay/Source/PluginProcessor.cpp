/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ModDelayAudioProcessor::ModDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ModDelayAudioProcessor::~ModDelayAudioProcessor()
{
}

//==============================================================================
const String ModDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ModDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ModDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ModDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ModDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ModDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ModDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ModDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String ModDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void ModDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ModDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    //fractionalDelay.setFs(sampleRate);
}

void ModDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ModDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ModDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //fractionalDelay.setDepth(depth);
    //fractionalDelay.setSpeed(rate);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        //fractionalDelay.processSignal(buffer, buffer.getNumSamples(), channel);
        
        for (int n = 0 ; n < buffer.getNumSamples() ; n++){
            float x = buffer.getReadPointer(channel)[n];
            
            //float delaySample = fractionalDelay.processSample(x, channel);
            float out1 = fbcf1.processSample(x,channel);
            float out2 = fbcf2.processSample(x,channel);
            
            // "x" is the dry path, "out1 and out2" are in parallel 
            float y = (1.f - wet) * x + wet * (out1+out2);
            
            buffer.getWritePointer(channel)[n] = y;
        }

    }
}

//==============================================================================
bool ModDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ModDelayAudioProcessor::createEditor()
{
    return new ModDelayAudioProcessorEditor (*this);
}

//==============================================================================
void ModDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ModDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ModDelayAudioProcessor();
}
