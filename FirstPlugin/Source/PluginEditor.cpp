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
    setSize (450, 300);
    
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
    
    freqKnob.addListener(this);
    freqKnob.setBounds(20, 160, 100, 100 );
    freqKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqKnob.setRange(20.f, 20000.f, 1.f);
    freqKnob.setValue(audioProcessor.FREQ_DEFAULT);
    freqKnob.setSkewFactorFromMidPoint(1000.0);
    freqKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(freqKnob);
    
    filterAmpKnob.addListener(this);
    filterAmpKnob.setBounds(125, 160, 100, 100 );
    filterAmpKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterAmpKnob.setRange(-12.f, 12.f, 0.1f);
    filterAmpKnob.setValue(audioProcessor.FILTER_AMP_DEFAULT);
    filterAmpKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(filterAmpKnob);
    
    filterQKnob.addListener(this);
    filterQKnob.setBounds(230, 160, 100, 100 );
    filterQKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterQKnob.setRange(0.1f, 10.f, 0.01f);
    filterQKnob.setSkewFactorFromMidPoint(2.0);
    filterQKnob.setValue(audioProcessor.FILTER_Q_DEFAULT);
    filterQKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(filterQKnob);
    
    filterSelector.addListener(this);
    filterSelector.setBounds(335,160,100,40);
    filterSelector.addItem("LPF",1);
    filterSelector.addItem("HPF",2);
    filterSelector.addItem("Low Shelf",3);
    filterSelector.addItem("High Shelf",4);
    filterSelector.addItem("Bell",5);
    filterSelector.setText("Select Type");
    addAndMakeVisible(filterSelector);
    
    filterAmpKnob.setEnabled(false); // when in LPF mode
    
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
    //g.drawFittedText ("My First Plugin", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("Freq", 20,140,100,20, juce::Justification::centred, 1);
    g.drawFittedText ("Amp", 125,140,100,20, juce::Justification::centred, 1);
    g.drawFittedText ("Q", 230,140,100,20, juce::Justification::centred, 1);
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
    
    if (slider == &freqKnob){
        audioProcessor.freqValue = slider->getValue();
    }
    
    if (slider == &filterAmpKnob){
        audioProcessor.filterAmpValue = slider->getValue();
    }
    
    if (slider == &filterQKnob){
        audioProcessor.filterQValue = slider->getValue();
    }
    
}


void FirstPluginAudioProcessorEditor::comboBoxChanged(ComboBox * comboBox){
    
    if (comboBox == &filterSelector){
        
        if (filterSelector.getSelectedId() == 1){
            audioProcessor.filterType = Biquad::FilterType::LPF;
            filterAmpKnob.setEnabled(false);
        }
        if (filterSelector.getSelectedId() == 2){
            audioProcessor.filterType = Biquad::FilterType::HPF;
            filterAmpKnob.setEnabled(false);
        }
        if (filterSelector.getSelectedId() == 3){
            audioProcessor.filterType = Biquad::FilterType::LSHELF;
            filterAmpKnob.setEnabled(true);
        }
        if (filterSelector.getSelectedId() == 4){
            audioProcessor.filterType = Biquad::FilterType::HSHELF;
            filterAmpKnob.setEnabled(true);
        }
        if (filterSelector.getSelectedId() == 5){
            audioProcessor.filterType = Biquad::FilterType::PEAK;
            filterAmpKnob.setEnabled(true);
        }
        
        
    }
    
}
