#include "MeterComponent.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

DynamicsAudioProcessorEditor::DynamicsAudioProcessorEditor(DynamicsAudioProcessor& p) :
    AudioProcessorEditor(&p), audioProcessor(p),
    genericParameterEditor(audioProcessor.getParameterManager()),
    inputMeterComponent(audioProcessor.getInputMeter()),
    outputMeterComponent(audioProcessor.getOutputMeter())
{
    unsigned int numParams { static_cast<unsigned int>(audioProcessor.getParameterManager().getParameters().size()) };
    unsigned int paramHeight { static_cast<unsigned int>(genericParameterEditor.parameterWidgetHeight) };

    addAndMakeVisible(genericParameterEditor);
    addAndMakeVisible(inputMeterComponent);
    addAndMakeVisible(outputMeterComponent);
    setSize(300 + 2 * METER_WIDTH, numParams * paramHeight);
}

DynamicsAudioProcessorEditor::~DynamicsAudioProcessorEditor()
{
}

void DynamicsAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void DynamicsAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    inputMeterComponent.setBounds(area.removeFromLeft(METER_WIDTH));
    outputMeterComponent.setBounds(area.removeFromRight(METER_WIDTH));
    genericParameterEditor.setBounds(area);
}