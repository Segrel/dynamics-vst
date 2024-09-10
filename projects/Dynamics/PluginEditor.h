#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MeterComponent.h"
#include "HeaderComponent.h"

class DynamicsAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DynamicsAudioProcessorEditor(DynamicsAudioProcessor&);
    ~DynamicsAudioProcessorEditor() override;

    static constexpr int METER_WIDTH { 40 };
    static constexpr int PARAM_HEIGHT { 100 };
    static constexpr int PARAM_WIDTH { 200 };
    static constexpr int HEADER_HEIGHT { 35 };

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    DynamicsAudioProcessor& audioProcessor;
    mrta::GenericParameterEditor paramEditor1;
    mrta::GenericParameterEditor paramEditor2;
    mrta::GenericParameterEditor paramEditor3;
    mrta::GenericParameterEditor paramEditor4;
    GUI::MeterComponent inputMeterComponent;
    GUI::MeterComponent outputMeterComponent;
    GUI::HeaderComponent headerComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicsAudioProcessorEditor)
};