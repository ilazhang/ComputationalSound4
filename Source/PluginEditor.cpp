/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //gain shift slider 
    mGainSlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    //mGainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 20);
    mGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 25, 20); //adjusted location for two sliders
    //mGainSlider.setRange (0.0f, 1.0f, 0.01f);
    mGainSlider.setRange (-0.60f, 0.0f, 0.01f);
    //mGainSlider.setValue (0.5f);
    mGainSlider.setValue (-20.0f);
    mGainSlider.addListener (this);
    addAndMakeVisible (mGainSlider);

    //pitch shift slider
    mPitchSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mPitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 25, 20);
    mPitchSlider.setRange(-1.0f, 1.0f, 0.01f); //originally 0 to 1, adjusted for new approach using pow instead of multiplication
    mPitchSlider.setValue(0.0f);
    mPitchSlider.addListener(this);
    addAndMakeVisible(mPitchSlider);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // original location of mGainSlider in center
    //mGainSlider.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);
    mGainSlider.setBounds(getWidth()*0.25 - 50, getHeight() / 2 - 75, 100, 150);
    mPitchSlider.setBounds(getWidth()*0.75 - 50, getHeight() / 2 - 75, 100, 150);
}

void NewProjectAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &mGainSlider)
    {
        audioProcessor.mGain = mGainSlider.getValue();
    }
    if (slider == &mPitchSlider)
    {
        audioProcessor.mPitchShift = mPitchSlider.getValue();
    }
}