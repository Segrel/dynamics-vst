#pragma once

namespace DSP {

class TargetGainComputer {
public:
    TargetGainComputer();
    ~TargetGainComputer();

    TargetGainComputer(const TargetGainComputer&) = delete;
    TargetGainComputer(TargetGainComputer&&) = delete;
    const TargetGainComputer& operator=(const TargetGainComputer&) = delete;
    const TargetGainComputer& operator=(TargetGainComputer&&) = delete;

    void setThreshold(float newThreshold);
    void setRatio(unsigned int newRatio);
    float compute(float rectifiedLevel);

private:
    int ratio { 5 };
    float threshold { -25.f };
};

}
