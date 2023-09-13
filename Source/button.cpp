

// MOST OF THE CODE HERE IS REFERRED FROM THE JUCE TUTORIAL : Customise the look and feel of your app
// WEBSITE: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html

#include "button.h"


void Button::drawButtonBackground(
    juce::Graphics& g,
    juce::Button& button,
    const juce::Colour& backgroundColour,
    bool, // isMouseOverButton
    bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();
    auto edge = 3;

    juce::ColourGradient gradientUp(juce::Colour(0xFF833ab4),  // Purple
        0, 0,
        juce::Colour(0xFFfd1d1d),  // Red
        0, button.getHeight(),
        false);

    auto offset = isButtonDown ? -edge / 2 : -edge;
    buttonArea.translate(offset, offset);

    juce::Colour shadowColor = juce::Colour(0x80000000);
    int shadowOffset = 3;

    g.setGradientFill(gradientUp);
    g.fillRoundedRectangle(buttonArea.toFloat(), 10.0f); // Adjust the corner radius as needed

    // Draw the shadow (if button is pressed)
    if (isButtonDown)
    {
        juce::Rectangle<int> shadowRect = buttonArea.translated(shadowOffset, shadowOffset);
        g.setColour(shadowColor);
        g.fillRoundedRectangle(shadowRect.toFloat(), 10.0f); // Adjust the corner radius as needed
    }
}

void Button::drawButtonText(
    juce::Graphics& g,
    juce::TextButton& button,
    bool isMouseOverButton,
    bool isButtonDown)
{
    auto font = getTextButtonFont(button, button.getHeight());
    g.setFont(font);

    // Customize the text color based on button state
    juce::Colour textColour;

    if (isButtonDown)
        textColour = juce::Colours::white;
    else if (isMouseOverButton)
        textColour = juce::Colours::lightgrey;
    else
        textColour = juce::Colours::black;

    g.setColour(textColour);

    auto yIndent = juce::jmin(4, button.proportionOfHeight(0.3f));
    auto edge = 4;
    auto offset = isButtonDown ? edge / 2 : 0;

    auto textWidth = button.getWidth() - 2 * (yIndent + offset);

    if (textWidth > 0)
        g.drawFittedText(button.getButtonText(),
            yIndent + offset,
            yIndent + offset,
            textWidth,
            button.getHeight() - 2 * (yIndent + offset),
            juce::Justification::horizontallyCentred,
            2);
}
