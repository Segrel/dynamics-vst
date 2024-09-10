#pragma once

#include <JuceHeader.h>

#include "LA2AMakeUp.h"
#include "LA2AMakeUpParameters.h"

namespace DSP {

class MakeUpGain {
public:
    MakeUpGain();
    ~MakeUpGain();

    MakeUpGain(const MakeUpGain&) = delete;
    MakeUpGain(MakeUpGain&&) = delete;
    const MakeUpGain& operator=(const MakeUpGain&) = delete;
    const MakeUpGain& operator=(MakeUpGain&&) = delete;

    void setLA2AWarmth(float newWarmth);
    void prepare(unsigned int numChannels, unsigned int samplesPerBlock);
    void process(float* const* output, const float* const* input, float gain, unsigned int numChannels, unsigned int numSamples);

private:
    float warmth { 0.0f };

    float blockerInputBuffer[2] { 0.0f, 0.0f };
    float blockerOutputBuffer[2] { 0.0f, 0.0f };

    static const unsigned int INPUT_SIZE = 1u;
    static const unsigned int OUTPUT_SIZE = 1u;
    static const unsigned int HIDDEN_SIZE = 8u;

    LA2AMakeUp<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE> la2aMakeUp[2];
    LA2AMakeUpParameters la2aMakeUpParameters;

    juce::AudioBuffer<float> warmthInBuffer;
    juce::AudioBuffer<float> warmthOutBuffer;
};

}
