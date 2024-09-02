#pragma once

#include "Compressor/GainSmoother.h"
#include "Compressor/TargetGainComputer.h"
#include "Compressor/MakeUpGain.h"

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
    void setRatio(int newRatio);
    void setThreshold(float newThreshold);
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
