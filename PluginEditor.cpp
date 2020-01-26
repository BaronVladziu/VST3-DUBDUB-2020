/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Dubdub2020AudioProcessorEditor::Dubdub2020AudioProcessorEditor (Dubdub2020AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
    keyboardComponent(processor.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(keyboardComponent);
    setSize(800, 400);
    startTimer(400);

    float attackDefaultValue = 1.0;
    addAndMakeVisible(attackSlider);
    attackSlider.setRange(0, 500, 1);
    attackSlider.setTextValueSuffix(" [ms]");
    attackSlider.setName("attackSlider");
    attackSlider.setSliderStyle(Slider::LinearHorizontal);
    attackSlider.setPopupDisplayEnabled(true, false, this);
    attackSlider.setValue(attackDefaultValue);
    attackSlider.addListener(this);
    processor.synthAudioSource.updateAttack(attackDefaultValue);
    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, true);

    float decayDefaultValue = 100.0;
    addAndMakeVisible(decaySlider);
    decaySlider.setRange(0, 500, 1);
    decaySlider.setTextValueSuffix(" [ms]");
    decaySlider.setName("decaySlider");
    decaySlider.setSliderStyle(Slider::LinearHorizontal);
    decaySlider.setPopupDisplayEnabled(true, false, this);
    decaySlider.setValue(decayDefaultValue);
    decaySlider.addListener(this);
    processor.synthAudioSource.updateDecay(decayDefaultValue);
    addAndMakeVisible(decayLabel);
    decayLabel.setText("Decay", dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, true);

    float sustainDefaultValue = 80.0;
    addAndMakeVisible(sustainSlider);
    sustainSlider.setRange(0, 100, 1);
    sustainSlider.setTextValueSuffix(" [%]");
    sustainSlider.setName("sustainSlider");
    sustainSlider.setSliderStyle(Slider::LinearHorizontal);
    sustainSlider.setPopupDisplayEnabled(true, false, this);
    sustainSlider.setValue(sustainDefaultValue);
    sustainSlider.addListener(this);
    processor.synthAudioSource.updateSustain(sustainDefaultValue);
    addAndMakeVisible(sustainLabel);
    sustainLabel.setText("Sustain", dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, true);

    float releaseDefaultValue = 300.0;
    addAndMakeVisible(releaseSlider);
    releaseSlider.setRange(0, 500, 1);
    releaseSlider.setTextValueSuffix(" [ms]");
    releaseSlider.setName("releaseSlider");
    releaseSlider.setSliderStyle(Slider::LinearHorizontal);
    releaseSlider.setPopupDisplayEnabled(true, false, this);
    releaseSlider.setValue(releaseDefaultValue);
    releaseSlider.addListener(this);
    processor.synthAudioSource.updateRelease(releaseDefaultValue);
    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release", dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, true);

    float modulationFrequencyDefaultValue = 300.0;
    addAndMakeVisible(modulationFrequencySlider);
    modulationFrequencySlider.setRange(10, 1200, 1);
    modulationFrequencySlider.setTextValueSuffix(" [bpm]");
    modulationFrequencySlider.setName("modulationFrequencySlider");
    modulationFrequencySlider.setSliderStyle(Slider::LinearHorizontal);
    modulationFrequencySlider.setPopupDisplayEnabled(true, false, this);
    modulationFrequencySlider.setValue(modulationFrequencyDefaultValue);
    modulationFrequencySlider.addListener(this);
    processor.synthAudioSource.updateModulationFrequency(modulationFrequencyDefaultValue);
    addAndMakeVisible(modulationFrequencyLabel);
    modulationFrequencyLabel.setText("Modulation frequency", dontSendNotification);
    modulationFrequencyLabel.attachToComponent(&modulationFrequencySlider, true);
}

Dubdub2020AudioProcessorEditor::~Dubdub2020AudioProcessorEditor()
{
}

//==============================================================================
void Dubdub2020AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("DubDub-2020", getLocalBounds(), Justification::centred, 1);
}

void Dubdub2020AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int shift = 10;
    int slidersLeft = 100;
    int sliderHeight = 40;
    attackSlider.setBounds(
        slidersLeft + shift, shift, getWidth() - slidersLeft - 2*shift, sliderHeight
    );
    decaySlider.setBounds(
        slidersLeft + shift, 1*sliderHeight + shift, getWidth() - slidersLeft - 2 * shift, sliderHeight
    );
    sustainSlider.setBounds(
        slidersLeft + shift, 2*sliderHeight + shift, getWidth() - slidersLeft - 2 * shift, sliderHeight
    );
    releaseSlider.setBounds(
        slidersLeft + shift, 3*sliderHeight + shift, getWidth() - slidersLeft - 2 * shift, sliderHeight
    );
    modulationFrequencySlider.setBounds(
        slidersLeft + shift, 5*sliderHeight + shift, getWidth() - slidersLeft - 2 * shift, sliderHeight
    );

    keyboardComponent.setBounds(
        shift, 7*sliderHeight + shift, getWidth() - 2 * shift, getHeight() - 7*sliderHeight - 2*shift
    );
}

void Dubdub2020AudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider->getName() == "attackSlider") {
        processor.synthAudioSource.updateAttack(attackSlider.getValue());
    }
    else if (slider->getName() == "decaySlider") {
        processor.synthAudioSource.updateDecay(decaySlider.getValue());
    }
    else if (slider->getName() == "sustainSlider") {
        processor.synthAudioSource.updateSustain(sustainSlider.getValue());
    }
    else if (slider->getName() == "releaseSlider") {
        processor.synthAudioSource.updateRelease(releaseSlider.getValue());
    }
    else if (slider->getName() == "modulationFrequencySlider") {
        processor.synthAudioSource.updateModulationFrequency(modulationFrequencySlider.getValue());
    }
}
