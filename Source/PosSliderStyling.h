#pragma once
#include <JuceHeader.h>

class PosSliderStyling : public juce::LookAndFeel_V4
{
public:
    PosSliderStyling()
    {
        setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::white);
        setColour(juce::Slider::textBoxTextColourId, juce::Colours::white);
        setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);

    };
};