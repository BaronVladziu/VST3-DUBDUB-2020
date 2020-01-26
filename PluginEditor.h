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
class Dubdub2020AudioProcessorEditor
    : public AudioProcessorEditor, private Timer, private Slider::Listener
{
public:
    Dubdub2020AudioProcessorEditor (Dubdub2020AudioProcessor&);
    ~Dubdub2020AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Dubdub2020AudioProcessor& processor;

    Slider attackSlider;
    Label attackLabel;
    Slider decaySlider;
    Label decayLabel;
    Slider sustainSlider;
    Label sustainLabel;
    Slider releaseSlider;
    Label releaseLabel;
    Slider modulationFrequencySlider;
    Label modulationFrequencyLabel;

    void sliderValueChanged(Slider* slider) override;

    void timerCallback() override
    {
        keyboardComponent.grabKeyboardFocus();
        stopTimer();
    }
    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dubdub2020AudioProcessorEditor)
};
