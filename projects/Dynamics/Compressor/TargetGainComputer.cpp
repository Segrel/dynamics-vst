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
    // infer the threshold, ratio and width values and denormalize
    float outputs[3];
    la2aGainComputer.compute(outputs, &peakReduction);
    threshold = -80.0f * outputs[0];
    ratio = 30.0f * outputs[1] + 1.0f;
    width = 30.0f * outputs[2];
}

void TargetGainComputer::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

void TargetGainComputer::setRatio(float newRatio)
{
    ratio = newRatio;
}

void TargetGainComputer::setKneeWidth(float newWidth)
{
    width = newWidth;
}

float TargetGainComputer::compute(float rectifiedLevel)
{
    float transition = 2.0f * (rectifiedLevel - threshold);
    float compressedLevel = 0.0f;
    if (transition <= -width) {
       compressedLevel = rectifiedLevel;
    } else if (std::fabsf(transition) < width) {
        compressedLevel = rectifiedLevel + ((1 / ratio - 1.0f) * (rectifiedLevel - threshold + width / 2) * (rectifiedLevel - threshold + width / 2)) / (2 * width);
    } else {
        compressedLevel = threshold + (rectifiedLevel - threshold) / ratio;
    }
    return compressedLevel - rectifiedLevel;
}

}
