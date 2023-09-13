
// MOST OF THE CODE HERE IS REFERRED FROM THE JUCE TUTORIAL : Customise the look and feel of your app
// WEBSITE: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html

#pragma once
#include <JuceHeader.h>

// MOST OF THE CODE HERE IS REFERRED FROM THE JUCE TUTORIAL : Customise the look and feel of your app
// WEBSITE: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html
class Knob : public juce::LookAndFeel_V4
{
public:
    Knob() 
    {
        // Highlights text yellow that is semi opaque
        setColour(juce::Slider::textBoxHighlightColourId, juce::Colours::yellow.withAlpha(0.5f));
    };

    /** Customizes the slider into a rotary slider*/
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
};