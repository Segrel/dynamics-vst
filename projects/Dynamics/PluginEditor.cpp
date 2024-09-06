#include "MeterComponent.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

DynamicsAudioProcessorEditor::DynamicsAudioProcessorEditor(DynamicsAudioProcessor& p) :
    AudioProcessorEditor(&p), audioProcessor(p),
    paramEditor1(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::Threshold, Param::ID::Attack }),
    paramEditor2(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::Ratio, Param::ID::Release }),
    paramEditor3(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::KneeWidth, Param::ID::Gain }),
    paramEditor4(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::PeakReduction }),
    inputMeterComponent(audioProcessor.getInputMeter()),
    outputMeterComponent(audioProcessor.getOutputMeter())
{
    addAndMakeVisible(paramEditor1);
    addAndMakeVisible(paramEditor2);
    addAndMakeVisible(paramEditor3);
    addAndMakeVisible(paramEditor4);
    addAndMakeVisible(inputMeterComponent);
    addAndMakeVisible(outputMeterComponent);
    setSize(4 * PARAM_WIDTH + 2 * METER_WIDTH, 2 * PARAM_HEIGHT);
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
    paramEditor1.setBounds(area.removeFromLeft(PARAM_WIDTH));
    paramEditor2.setBounds(area.removeFromLeft(PARAM_WIDTH));
    paramEditor3.setBounds(area.removeFromLeft(PARAM_WIDTH));
    paramEditor4.setBounds(area);
}