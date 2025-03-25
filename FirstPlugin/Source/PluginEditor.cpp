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
    
    float scalar = 1.4f;
    int windowWidth = (int) (scalar * refWidth);
    int windowHeight = (int) (scalar * refHeight);
    setSize (windowWidth, windowHeight);
    
    int xPos = (int) ((20.f / refWidth) * windowWidth);
    int yPos = (int) ((30.f / refHeight) * windowHeight);
    int width = (int) ((150.f / refWidth) * windowWidth);
    int height = (int) ((20.f / refHeight) * windowHeight);
    
    bypassButton.addListener(this);
    bypassButton.setBounds(xPos,yPos,width,height); // x , y, width, height
    bypassButton.setButtonText("Bypass");
    bypassButton.setToggleState(audioProcessor.BYPASSED_DEFAULT, dontSendNotification); // set the initial state "on"
    addAndMakeVisible(bypassButton); // include this on the plugin window
    
    
    xPos = (int) ((200.f / refWidth) * windowWidth);
    yPos = (int) ((30.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
    gainKnob.addListener(this);
    gainKnob.setBounds(xPos, yPos, width, height );
    gainKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainKnob.setRange(-48.f, 12.f, .1f);
    gainKnob.setValue(audioProcessor.GAIN_DEFAULT);
    gainKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(gainKnob);
    
    xPos = (int) ((20.f / refWidth) * windowWidth);
    yPos = (int) ((160.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
    freqKnob.addListener(this);
    freqKnob.setBounds(xPos, yPos, width, height );
    freqKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqKnob.setRange(20.f, 20000.f, 1.f);
    freqKnob.setValue(audioProcessor.FREQ_DEFAULT);
    freqKnob.setSkewFactorFromMidPoint(1000.0);
    freqKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(freqKnob);
    
    xPos = (int) ((125.f / refWidth) * windowWidth);
    yPos = (int) ((160.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
    filterAmpKnob.addListener(this);
    filterAmpKnob.setBounds(xPos, yPos, width, height );
    filterAmpKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterAmpKnob.setRange(-12.f, 12.f, 0.1f);
    filterAmpKnob.setValue(audioProcessor.FILTER_AMP_DEFAULT);
    filterAmpKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(filterAmpKnob);
    
    xPos = (int) ((230.f / refWidth) * windowWidth);
    yPos = (int) ((160.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = width; //(int) ((20.f / refHeight) * windowHeight);
    
    filterQKnob.addListener(this);
    filterQKnob.setBounds(xPos, yPos, width, height );
    filterQKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterQKnob.setRange(0.1f, 10.f, 0.01f);
    filterQKnob.setSkewFactorFromMidPoint(2.0);
    filterQKnob.setValue(audioProcessor.FILTER_Q_DEFAULT);
    filterQKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(filterQKnob);
    
    xPos = (int) ((335.f / refWidth) * windowWidth);
    yPos = (int) ((160.f / refHeight) * windowHeight);
    width = (int) ((100.f / refWidth) * windowWidth);
    height = (int) ((40.f / refHeight) * windowHeight);
    
    filterSelector.addListener(this);
    filterSelector.setBounds(xPos,yPos,width,height);
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

    
    auto bounds = getLocalBounds();
    
    float windowWidth = (float) bounds.getWidth();
    float windowHeight = (float) bounds.getHeight();
    
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f * windowHeight/refHeight));
    
    int xPos = (int) ((20.f / refWidth) * windowWidth);
    int yPos = (int) ((140.f / refHeight) * windowHeight);
    int width = (int) ((100.f / refWidth) * windowWidth);
    int height = (int) ((20.f / refHeight) * windowHeight);
    
    //g.drawFittedText ("My First Plugin", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("Freq", xPos,yPos,width,height, juce::Justification::centred, 1);
    xPos = (int) ((125.f / refWidth) * windowWidth);
    g.drawFittedText ("Amp", xPos,yPos,width,height, juce::Justification::centred, 1);
    xPos = (int) ((230.f / refWidth) * windowWidth);
    g.drawFittedText ("Q", xPos,yPos,width,height, juce::Justification::centred, 1);
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
