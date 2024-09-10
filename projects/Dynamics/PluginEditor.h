#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MeterComponent.h"
#include "HeaderComponent.h"
#include "SliderEditor.h"
#include "Compressor/Compressor.h"

class DynamicsAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                      public juce::Timer
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
    void timerCallback() override;

private:
    DynamicsAudioProcessor& audioProcessor;
    GUI::SliderEditor paramEditor1;
    GUI::SliderEditor paramEditor2;
    GUI::SliderEditor paramEditor3;
    GUI::SliderEditor paramEditor4;
    GUI::MeterComponent inputMeterComponent;
    GUI::MeterComponent outputMeterComponent;
    GUI::HeaderComponent headerComponent;
    DSP::Compressor& compressor { audioProcessor.getCompressor() };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicsAudioProcessorEditor)
};