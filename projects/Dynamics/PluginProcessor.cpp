#include "PluginProcessor.h"
#include "Meter.h"
#include "PluginEditor.h"

#include <algorithm>

static const std::vector<mrta::ParameterInfo> Parameters
{
    { Param::ID::Threshold,  Param::Name::Threshold, Param::Units::dB,  -25.f,  Param::Ranges::ThresholdMin,  Param::Ranges::ThresholdMax,  Param::Ranges::ThresholdInc,  Param::Ranges::ThresholdSkw },
    { Param::ID::Ratio,      Param::Name::Ratio,     "",                5,      Param::Ranges::RatioMin,      Param::Ranges::RatioMax,      Param::Ranges::RatioInc,      Param::Ranges::RatioSkw },
    { Param::ID::Gain,       Param::Name::Gain,      "",                1.0f,   Param::Ranges::GainMin,       Param::Ranges::GainMax,       Param::Ranges::GainInc,       Param::Ranges::GainSkw },
    { Param::ID::Attack,     Param::Name::Attack,    Param::Units::Ms,  100.0f, Param::Ranges::AttackMin,     Param::Ranges::AttackMax,     Param::Ranges::AttackInc,     Param::Ranges::AttackSkw },
    { Param::ID::Release,    Param::Name::Release,   Param::Units::Ms,  100.0f, Param::Ranges::ReleaseMin,    Param::Ranges::ReleaseMax,    Param::Ranges::ReleaseInc,    Param::Ranges::ReleaseSkw },
};

DynamicsAudioProcessor::DynamicsAudioProcessor() :
    parameterManager(*this, ProjectInfo::projectName, Parameters)
{
    parameterManager.registerParameterCallback(Param::ID::Threshold,
    [this] (float value, bool /*force*/)
    {
        compressor.setThreshold(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Ratio,
    [this] (int value, bool /*force*/)
    {
        compressor.setRatio(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Gain,
    [this] (float value, bool /*force*/)
    {
        compressor.setGain(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Attack,
    [this] (float value, bool /*force*/)
    {
        compressor.setAttackTime(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Release,
    [this] (float value, bool /*force*/)
    {
        compressor.setReleaseTime(value);
    });
}

DynamicsAudioProcessor::~DynamicsAudioProcessor()
{
}

void DynamicsAudioProcessor::prepareToPlay(double newSampleRate, int samplesPerBlock)
{
    const unsigned int numChannels { static_cast<unsigned int>(std::max(getMainBusNumInputChannels(), getMainBusNumOutputChannels())) };

    compressor.prepare(newSampleRate, numChannels);
    inputMeter.prepare(newSampleRate, numChannels);
    outputMeter.prepare(newSampleRate, numChannels);

    parameterManager.updateParameters(true);
}

void DynamicsAudioProcessor::releaseResources()
{
}

void DynamicsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    parameterManager.updateParameters();

    const unsigned int numChannels { static_cast<unsigned int>(buffer.getNumChannels()) };
    const unsigned int numSamples { static_cast<unsigned int>(buffer.getNumSamples()) };

    const float* const* input = buffer.getArrayOfReadPointers();
    float* const* output = buffer.getArrayOfWritePointers();

    inputMeter.process(input, numChannels, numSamples);
    compressor.process(output, input, numChannels, numSamples);
    outputMeter.process(output, numChannels, numSamples);
}

void DynamicsAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    parameterManager.getStateInformation(destData);
}

void DynamicsAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    parameterManager.setStateInformation(data, sizeInBytes);
}

//==============================================================================
bool DynamicsAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* DynamicsAudioProcessor::createEditor() { return new DynamicsAudioProcessorEditor(*this); }
const juce::String DynamicsAudioProcessor::getName() const { return JucePlugin_Name; }
bool DynamicsAudioProcessor::acceptsMidi() const { return false; }
bool DynamicsAudioProcessor::producesMidi() const { return false; }
bool DynamicsAudioProcessor::isMidiEffect() const { return false; }
double DynamicsAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int DynamicsAudioProcessor::getNumPrograms() { return 1; }
int DynamicsAudioProcessor::getCurrentProgram() { return 0; }
void DynamicsAudioProcessor::setCurrentProgram(int) { }
const juce::String DynamicsAudioProcessor::getProgramName (int) { return {}; }
void DynamicsAudioProcessor::changeProgramName (int, const juce::String&) { }
//==============================================================================

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DynamicsAudioProcessor();
}