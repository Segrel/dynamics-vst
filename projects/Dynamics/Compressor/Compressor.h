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

    void prepare(double sampleRate, unsigned int numChannels, unsigned int samplesPerBlock);
    void setGain(float newGain);
    void setRatio(float newRatio);
    float getRatio() { return gainComputer.getRatio(); };
    void setThreshold(float newThreshold);
    float getThreshold() { return gainComputer.getThreshold(); };
    void setKneeWidth(float newWidth);
    float getKneeWidth() { return gainComputer.getKneeWidth(); };
    void setLA2APeakReduction(float newPeakReduction);
    void setLA2AWarmth(float newWarmth);
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
