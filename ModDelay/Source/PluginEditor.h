/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ModDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener
{
public:
    ModDelayAudioProcessorEditor (ModDelayAudioProcessor&);
    ~ModDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider * slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ModDelayAudioProcessor& processor;
    
    Slider rateKnob;
    Slider depthKnob;
    Slider wetKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModDelayAudioProcessorEditor)
};
