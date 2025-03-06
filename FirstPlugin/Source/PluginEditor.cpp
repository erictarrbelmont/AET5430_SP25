/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstPluginAudioProcessorEditor::FirstPluginAudioProcessorEditor (FirstPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    bypassButton.addListener(this);
    bypassButton.setBounds(20,30,150,20); // x , y, width, height
    bypassButton.setButtonText("Bypass");
    bypassButton.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(bypassButton); // include this on the plugin window
    
    gainKnob.addListener(this);
    gainKnob.setBounds(200, 30, 100, 100 );
    gainKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnob.setRange(-48.f, 12.f, .1f);
    gainKnob.setValue(audioProcessor.GAIN_DEFAULT);
    gainKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(gainKnob);
    
}

FirstPluginAudioProcessorEditor::~FirstPluginAudioProcessorEditor()
{
}

//==============================================================================
void FirstPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::green);

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("My First Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void FirstPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void FirstPluginAudioProcessorEditor::buttonClicked (Button* button){
    
    if (button == &bypassButton){
        audioProcessor.isBypassed = button->getToggleState();
    }
}


void FirstPluginAudioProcessorEditor::sliderValueChanged (Slider * slider){
    
    if (slider == &gainKnob){
        audioProcessor.gainValue = slider->getValue();
    }
    
}
