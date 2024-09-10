#pragma once

#include "LA2AComputer.h"
#include "LA2AComputerParameters.h"

namespace DSP {

class TargetGainComputer {
public:
    TargetGainComputer();
    ~TargetGainComputer();

    TargetGainComputer(const TargetGainComputer&) = delete;
    TargetGainComputer(TargetGainComputer&&) = delete;
    const TargetGainComputer& operator=(const TargetGainComputer&) = delete;
    const TargetGainComputer& operator=(TargetGainComputer&&) = delete;

    void setLA2APeakReduction(float peakReduction);
    void setThreshold(float newThreshold);
    float getThreshold() { return threshold; };
    void setRatio(float newRatio);
    float getRatio() { return ratio; };
    void setKneeWidth(float newWidth);
    float getKneeWidth() { return width; };
    float compute(float rectifiedLevel);

private:
    float ratio { 5.0f };
    float threshold { -25.f };
    float width { 10.0f };

    float manualRatio { 5.0f };
    float manualThreshold { -25.f };
    float manualWidth { 10.0f };

    float la2aPeakReduction { -1.0f };
    float la2aRatio { 5.0f };
    float la2aThreshold { -25.f };
    float la2aWidth { 10.0f };

    static const size_t INPUT_SIZE = 1u;
    static const size_t OUTPUT_SIZE = 3u;
    static const size_t HIDDEN_SIZE = 20u;
    static const size_t NUM_LAYERS = 4u;

    LA2AComputer<INPUT_SIZE, OUTPUT_SIZE, HIDDEN_SIZE, NUM_LAYERS> la2aGainComputer;
    LA2AComputerParameters la2aGainComputerParameters;
};

}
