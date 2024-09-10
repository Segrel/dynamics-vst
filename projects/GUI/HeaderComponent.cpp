#include "HeaderComponent.h"

namespace GUI
{

HeaderComponent::HeaderComponent()
{
    manualLabel.setText("Manual Control", juce::dontSendNotification);
    manualLabel.setFont(juce::FontOptions(24.f));
    manualLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(manualLabel);

    la2aLabel.setText("LA2A", juce::dontSendNotification);
    la2aLabel.setFont(juce::FontOptions(24.f));
    la2aLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(la2aLabel);
}

HeaderComponent::~HeaderComponent()
{
}

void HeaderComponent::resized()
{
}

void HeaderComponent::paint(juce::Graphics& g)
{
    juce::Rectangle<int> totalArea = getLocalBounds();
    static juce::Rectangle<float> manualArea { 0.025f, 0.2f, 0.7f, 0.8f };
    static juce::Rectangle<float> la2aArea { 0.725f, 0.2f, 0.3f, 0.8f };
    manualLabel.setBounds(totalArea.getProportion(manualArea));
    la2aLabel.setBounds(totalArea.getProportion(la2aArea));
}

}
