#pragma once

#include <JuceHeader.h>
#include "Meter.h"
#include "Ramp.h"
#include "Compressor/Compressor.h"

namespace Param
{
    namespace ID
    {
        static const juce::String Enabled { "enabled" };
        static const juce::String Threshold { "threshold" };
        static const juce::String Ratio { "ratio" };
        static const juce::String Gain { "gain" };
        static const juce::String Attack { "attack" };
        static const juce::String Release { "release" };
        static const juce::String PeakReduction { "peakreduction" };
    }

    namespace Name
    {
        static const juce::String Enabled { "Enabled" };
        static const juce::String Threshold { "Threshold" };
        static const juce::String Ratio { "Ratio" };
        static const juce::String Gain { "Gain" };
        static const juce::String Attack { "Attack" };
        static const juce::String Release { "Release" };
        static const juce::String PeakReduction { "Peak Reduction" };
    }

    namespace Ranges
    {
        static constexpr float ThresholdMin { -80.f };
        static constexpr float ThresholdMax { 0.f };
        static constexpr float ThresholdInc { 0.001f };
        static constexpr float ThresholdSkw { 1.0f };

        static constexpr float RatioMin { 1.0f };
        static constexpr float RatioMax { 30.0f };
        static constexpr float RatioInc { 1.0f };
        static constexpr float RatioSkw { 1.0f };

        static constexpr float GainMin { 1.f };
        static constexpr float GainMax { 2.0f };
        static constexpr float GainInc { 0.01f };
        static constexpr float GainSkw { 1.f };

        static constexpr float AttackMin { 0.2f };
        static constexpr float AttackMax { 200.0f };
        static constexpr float AttackInc { 0.01f };
        static constexpr float AttackSkw { 1.f };

        static constexpr float ReleaseMin { 50.f };
        static constexpr float ReleaseMax { 5000.0f };
        static constexpr float ReleaseInc { 0.01f };
        static constexpr float ReleaseSkw { 1.f };

        static constexpr float PeakReductionMin { 0.f };
        static constexpr float PeakReductionMax { 1.0f };
        static constexpr float PeakReductionInc { 0.01f };
        static constexpr float PeakReductionSkw { 1.f };

        static const juce::String EnabledOff { "Off" };
        static const juce::String EnabledOn { "On" };
    }

    namespace Units
    {
        static const juce::String Ms { "ms" };
        static const juce::String Hz { "Hz" };
        static const juce::String dB { "dB" };
    }
}

class DynamicsAudioProcessor : public juce::AudioProcessor
{
public:
    DynamicsAudioProcessor();
    ~DynamicsAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void releaseResources() override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    mrta::ParameterManager& getParameterManager() { return parameterManager; }
    DSP::Meter& getInputMeter() { return inputMeter; }
    DSP::Meter& getOutputMeter() { return outputMeter; }

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    //==============================================================================

private:
    mrta::ParameterManager parameterManager;
    DSP::Meter inputMeter;
    DSP::Meter outputMeter;

    DSP::Compressor compressor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DynamicsAudioProcessor)
};