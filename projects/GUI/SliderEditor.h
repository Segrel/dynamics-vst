#pragma once

#include <JuceHeader.h>

namespace GUI
{

class SliderEditor : public juce::Component
{
public:
    SliderEditor(mrta::ParameterManager& parameterManager,
                           int parameterWidgetHeight = 80,
                           const juce::StringArray& parameterIDs = {});
    SliderEditor() = delete;

    void paint(juce::Graphics&) override;
    void resized() override;

    const int parameterWidgetHeight;
    std::vector<std::unique_ptr<juce::Slider>> parameterComponents;

private:
    juce::StringArray parameterIDs;
    std::vector<std::unique_ptr<juce::Label>> parameterLabels;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderEditor)
};

}
