/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ModDelayAudioProcessorEditor::ModDelayAudioProcessorEditor (ModDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    rateKnob.addListener(this);
    rateKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    rateKnob.setBounds(50,74,100,100);
    rateKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    rateKnob.setRange(.1f,10.f);
    addAndMakeVisible(rateKnob);
    
    depthKnob.addListener(this);
    depthKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    depthKnob.setBounds(150,74,100,100);
    depthKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    depthKnob.setRange(1.f,10.f);
    addAndMakeVisible(depthKnob);
    
    wetKnob.addListener(this);
    wetKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetKnob.setBounds(250,74,100,100);
    wetKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 30);
    wetKnob.setRange(0.f,1.f);
    addAndMakeVisible(wetKnob);
    
}

ModDelayAudioProcessorEditor::~ModDelayAudioProcessorEditor()
{
}

//==============================================================================
void ModDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void ModDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void ModDelayAudioProcessorEditor::sliderValueChanged(Slider * slider){
    
    if(slider == &rateKnob){
        processor.rate = rateKnob.getValue();
    }
    if(slider == &depthKnob){
        processor.depth = depthKnob.getValue();
    }
    if(slider == &wetKnob){
        processor.wet = wetKnob.getValue();
    }
}
