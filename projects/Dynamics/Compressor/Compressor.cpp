#include "Compressor.h"

#include <algorithm>
#include <cmath>

namespace DSP {

Compressor::Compressor()
{
}

Compressor::~Compressor()
{
}

void Compressor::prepare(double newSampleRate, unsigned int numChannels)
{
    sampleRate = newSampleRate;

    gainSmoother.prepare(newSampleRate);
}

void Compressor::setGain(float newGain)
{
    gain = newGain;
}

void Compressor::setRatio(float newRatio)
{
    gainComputer.setRatio(newRatio);
}

void Compressor::setThreshold(float newThreshold)
{
    gainComputer.setThreshold(newThreshold);
}

void Compressor::setLA2APeakReduction(float newPeakReduction)
{
    gainComputer.setLA2APeakReduction(newPeakReduction);
}

void Compressor::setAttackTime(float newAttackTime)
{
    gainSmoother.setAttackTime(newAttackTime);
}

void Compressor::setReleaseTime(float newReleaseTime)
{
    gainSmoother.setReleaseTime(newReleaseTime);
}

void Compressor::process(float *const *output, const float *const *input, unsigned int numChannels, unsigned int numSamples)
{
    for (int n = 0; n < numSamples; ++n) {
        // Do level calculation on first channel
        float rectifiedLevel = 20.f * std::log10(std::max(std::fabsf(input[0][n]), 1e-5f));
        float targetGain = gainComputer.compute(rectifiedLevel);
        float smoothedGain = gainSmoother.smooth(targetGain);
        // Apply calculated gain to all channels
        float linearGain = std::pow(10.f, smoothedGain * 0.05f);
        for (int ch = 0; ch < numChannels; ++ch) {
            output[ch][n] = linearGain * input[ch][n];
        }
    }
    // Apply make-up gain to all channels
    makeUpGain.process(output, input, gain, numChannels, numSamples);
}

}