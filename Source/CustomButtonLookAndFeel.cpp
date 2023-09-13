#include "CustomButtonLookAndFeel.h"

CustomButtonLookAndFeel::CustomButtonLookAndFeel()
{
    // Customize the play button's appearance
    setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setColour(juce::TextButton::textColourOnId, juce::Colours::white);

    // Customize the stop button's appearance
    setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setColour(juce::TextButton::textColourOnId, juce::Colours::white);

    // Customize the load button's appearance
    setColour(juce::TextButton::buttonColourId, juce::Colours::blue);
    setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    setColour(juce::TextButton::textColourOnId, juce::Colours::white);
}
