#include "MeterComponent.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "HeaderComponent.h"

DynamicsAudioProcessorEditor::DynamicsAudioProcessorEditor(DynamicsAudioProcessor& p) :
    AudioProcessorEditor(&p), audioProcessor(p),
    paramEditor1(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::Threshold, Param::ID::Attack }),
    paramEditor2(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::Ratio, Param::ID::Release }),
    paramEditor3(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::KneeWidth, Param::ID::Gain }),
    paramEditor4(audioProcessor.getParameterManager(), PARAM_HEIGHT, { Param::ID::PeakReduction, Param::ID::Warmth }),
    inputMeterComponent(audioProcessor.getInputMeter()),
    outputMeterComponent(audioProcessor.getOutputMeter()),
    headerComponent()
{
    addAndMakeVisible(paramEditor1);
    addAndMakeVisible(paramEditor2);
    addAndMakeVisible(paramEditor3);
    addAndMakeVisible(paramEditor4);
    addAndMakeVisible(inputMeterComponent);
    addAndMakeVisible(outputMeterComponent);
    addAndMakeVisible(headerComponent);
    setSize(4 * PARAM_WIDTH + 2 * METER_WIDTH, 2 * PARAM_HEIGHT + HEADER_HEIGHT);
}

DynamicsAudioProcessorEditor::~DynamicsAudioProcessorEditor()
{
}

void DynamicsAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    juce::Rectangle<float> manualArea(METER_WIDTH + 2.5, 2.5, 3 * PARAM_WIDTH - 2.5, HEADER_HEIGHT + 2 * PARAM_HEIGHT - 4);
    g.setColour(juce::Colours::lightgrey);
    g.drawRoundedRectangle(manualArea, 5.f, 4.f);

    juce::Rectangle<float> la2aArea(METER_WIDTH + 3 * PARAM_WIDTH + 2.5, 2.5, PARAM_WIDTH - 5.0, HEADER_HEIGHT + 2 * PARAM_HEIGHT - 4);
    g.setColour(juce::Colours::lightgrey);
    g.drawRoundedRectangle(la2aArea, 5.f, 4.f);
}

void DynamicsAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    inputMeterComponent.setBounds(area.removeFromLeft(METER_WIDTH));
    outputMeterComponent.setBounds(area.removeFromRight(METER_WIDTH));
    headerComponent.setBounds(area.removeFromTop(HEADER_HEIGHT));
    paramEditor1.setBounds(area.removeFromLeft(PARAM_WIDTH));
    paramEditor2.setBounds(area.removeFromLeft(PARAM_WIDTH));
    paramEditor3.setBounds(area.removeFromLeft(PARAM_WIDTH));
    paramEditor4.setBounds(area);
}