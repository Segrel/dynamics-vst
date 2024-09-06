#pragma once

#include "GainSmoother.h"
#include "TargetGainComputer.h"
#include "MakeUpGain.h"

namespace DSP
{

class Compressor {
public:
    Compressor();
    ~Compressor();

    Compressor(const Compressor&) = delete;
    Compressor(Compressor&&) = delete;
    const Compressor& operator=(const Compressor&) = delete;
    const Compressor& operator=(Compressor&&) = delete;

    void prepare(double sampleRate, unsigned int numChannels);
    void setGain(float newGain);
    void setRatio(float newRatio);
    void setThreshold(float newThreshold);
    void setKneeWidth(float newWidth);
    void setLA2APeakReduction(float newPeakReduction);
    void setAttackTime(float newAttackTime);
    void setReleaseTime(float newReleaseTime);
    void process(float* const* output, const float* const* input, unsigned int numChannels, unsigned int numSamples);

private:
    double sampleRate { 48000.0 };

    DSP::TargetGainComputer gainComputer;
    DSP::GainSmoother gainSmoother;
    DSP::MakeUpGain makeUpGain;

    float gain { 1.0 };
};

}
