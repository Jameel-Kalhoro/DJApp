// MOST OF THE CODE HERE IS REFERRED FROM THE JUCE TUTORIAL : Customise the look and feel of your app
// WEBSITE: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html

#pragma once
#include <JuceHeader.h>
class OnOffSwitch : public juce::LookAndFeel_V4
{
public:
	OnOffSwitch()
	{
        setColour(juce::TextButton::buttonOnColourId, juce::Colours::yellow.withAlpha(0.5f));
	};
	
	
    /** Draws the background of the button*/
    void drawButtonBackground(
        juce::Graphics& g,
        juce::Button& button,
        const juce::Colour&
        backgroundColour,
        bool,
        bool isButtonDown) override;

    /** Draws the text of the button*/
    void drawButtonText(
        juce::Graphics& g,
        juce::TextButton& button,
        bool isMouseOverButton,
        bool isButtonDown) override;
};