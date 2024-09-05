#include "TargetGainComputer.h"

#include <algorithm>
#include <cmath>

namespace DSP {

TargetGainComputer::TargetGainComputer()
{
    la2aGainComputer.load_parameters(la2aGainComputerParameters.params);
}

TargetGainComputer::~TargetGainComputer()
{
}

void TargetGainComputer::setLA2APeakReduction(float peakReduction)
{
    // normalize to peak reduction to range used in training
    la2aPeakReduction = 2.0f * peakReduction - 1.0f;
    // infer the threshold and ratio values and denormalize
    float outputs[3];
    la2aGainComputer.compute(outputs, &peakReduction);
    la2aThreshold = -80.0f * outputs[0];
    la2aRatio = 30.0f * outputs[1] + 1.0f;
    ratio = la2aRatio;
    threshold = la2aThreshold;
}

void TargetGainComputer::setThreshold(float newThreshold)
{
    manualThreshold = newThreshold;
    threshold = newThreshold;
}

void TargetGainComputer::setRatio(float newRatio)
{
    manualRatio = newRatio;
    ratio = newRatio;
}

float TargetGainComputer::compute(float rectifiedLevel)
{
    return std::fminf(threshold + (rectifiedLevel - threshold) / static_cast<float>(ratio), rectifiedLevel) - rectifiedLevel;
}

}
