/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FirstPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Button::Listener,
                                            public juce::Slider::Listener,
                                            public juce::ComboBox::Listener
{
public:
    FirstPluginAudioProcessorEditor (FirstPluginAudioProcessor&);
    ~FirstPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked (Button*) override; // provide implementation for pure virtual function
    
    void sliderValueChanged (Slider *) override;
    
    void comboBoxChanged(ComboBox * comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstPluginAudioProcessor& audioProcessor;
    
    
    ToggleButton bypassButton;
    
    Slider gainKnob;
    
    Slider freqKnob;
    
    Slider filterAmpKnob;
    
    Slider filterQKnob;

    ComboBox filterSelector;
    
    float refWidth = 450.f;
    float refHeight = 300.f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstPluginAudioProcessorEditor)
};
