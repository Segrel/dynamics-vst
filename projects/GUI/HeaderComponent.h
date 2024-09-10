#pragma once

#include <JuceHeader.h>

namespace GUI
{

class HeaderComponent : public juce::Component
{
public:
    HeaderComponent();
    ~HeaderComponent();

    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    juce::Label manualLabel;
    juce::Label la2aLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};

}
