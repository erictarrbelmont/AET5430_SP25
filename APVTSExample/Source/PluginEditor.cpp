/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
APVTSExampleAudioProcessorEditor::APVTSExampleAudioProcessorEditor (APVTSExampleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    gainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setBounds(10, 10, 75, 75);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 70, 20);
    addAndMakeVisible(gainSlider);
    
    bypassButton.setBounds(100, 10, 50, 20);
    addAndMakeVisible(bypassButton);
    
}

APVTSExampleAudioProcessorEditor::~APVTSExampleAudioProcessorEditor()
{
}

//==============================================================================
void APVTSExampleAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void APVTSExampleAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
