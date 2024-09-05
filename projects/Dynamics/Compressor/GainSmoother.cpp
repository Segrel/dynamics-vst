#include "GainSmoother.h"
#include <algorithm>
#include <cmath>

namespace DSP {

GainSmoother::GainSmoother()
{
}

GainSmoother::~GainSmoother()
{
}

void GainSmoother::prepare(double newSampleRate)
{
    sampleRate = newSampleRate;
    smoothedLevel = 0.0f;
}

void GainSmoother::setAttackTime(float newAttackTime)
{
    attackTime = newAttackTime;
    attackCoeff = std::exp(-1.f / (static_cast<float>(sampleRate * 0.001) * attackTime));
}

void GainSmoother::setReleaseTime(float newReleaseTime)
{
    releaseTime = newReleaseTime;
    releaseCoeff = std::exp(-1.f / (static_cast<float>(sampleRate * 0.001) * releaseTime));
}

float GainSmoother::smooth(float targetGain)
{
    float coeff;
    if (targetGain > smoothedLevel) {
        coeff = attackCoeff;
    } else {
        coeff = releaseCoeff;
    }
    smoothedLevel = (smoothedLevel - targetGain) * attackCoeff + targetGain;
    return smoothedLevel;
}

}
