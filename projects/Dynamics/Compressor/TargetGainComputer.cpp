#include "TargetGainComputer.h"

#include <algorithm>

namespace DSP {

TargetGainComputer::TargetGainComputer()
{
}

TargetGainComputer::~TargetGainComputer()
{
}

void TargetGainComputer::setThreshold(float newThreshold)
{
    threshold = newThreshold;
}

void TargetGainComputer::setRatio(unsigned int newRatio)
{
    ratio = newRatio;
}

float TargetGainComputer::compute(float rectifiedLevel)
{
    return std::fminf(threshold + (rectifiedLevel - threshold) / static_cast<float>(ratio), rectifiedLevel) - rectifiedLevel;
}

}
