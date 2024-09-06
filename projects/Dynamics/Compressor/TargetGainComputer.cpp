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
    la2aWidth = 30.0f * outputs[2];
    ratio = la2aRatio;
    threshold = la2aThreshold;
    width = la2aWidth;
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

void TargetGainComputer::setKneeWidth(float newWidth)
{
    manualWidth = newWidth;
    width = manualWidth;
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
