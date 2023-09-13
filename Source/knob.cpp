

// MOST OF THE CODE HERE IS REFERRED FROM THE JUCE TUTORIAL : Customise the look and feel of your app
// WEBSITE: https://docs.juce.com/master/tutorial_look_and_feel_customisation.html

#include "knob.h"


void Knob::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    // Calculates the radius of the knob
    auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;

    // Centre X position of the knob
    auto centreX = (float)x + (float)width * 0.5f;

    // Centre Y position of the knob
    auto centreY = (float)y + (float)height * 0.5f;

    // Radius X of the knob
    auto rX = centreX - radius;

    // Radius Y of the knob
    auto rY = centreY - radius;

    // Radius Width of the knob
    auto rW = radius * 2.0f;

    // Calculates the angle of the knob after turn
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    juce::ColourGradient gradient(juce::Colours::yellowgreen,
        centreX + radius * std::cos(angle),
        centreY + radius * std::sin(angle),
        juce::Colours::darkgreen,
        centreX - radius * std::cos(angle),
        centreY - radius * std::sin(angle),
        false);


    // Fill the knob's background with the gradient
    g.setGradientFill(gradient);
    g.fillEllipse(rX, rY, rW, rW);

    // Sets outline of the knob
    g.setColour(juce::Colours::white);
    g.drawEllipse(rX, rY, rW, rW, 1.0f);

    // Draw a shadow effect for the knob (3D effect)
    auto shadowWidth = 4.0f; // Adjust the shadow width as needed
    g.setColour(juce::Colours::black.withAlpha(0.3f));
    g.drawEllipse(rX + shadowWidth, rY + shadowWidth, rW - 2 * shadowWidth, rW - 2 * shadowWidth, 2.0f);
    
    // Draw the pointer in the knob
    juce::Path p;

    // Length of the pointer
    //auto pointerLength = radius * 0.33f;

    auto pointerLength = radius * 0.60f;

    // Thickness of the pointer
    auto pointerThickness = 2.0f;

    auto halfPointerthickness = 1.0f;

    auto firstCoordinateX = -pointerThickness * 0.5f;

    // Draws the triangle which is the pointer itself
    p.addTriangle(
        -pointerThickness * 0.5f, -radius,
        firstCoordinateX - 1.0f, -radius + pointerLength,
        firstCoordinateX + 1.0f, -radius + pointerLength);

    // transforms the rectangle (rotates) about its centreX and centreY as its coordinates
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // Fills the pointer with a gradient-like effect
    juce::ColourGradient pointerGradient(juce::Colours::white,
        centreX - radius * std::cos(angle),
        centreY - radius * std::sin(angle),
        juce::Colours::lightblue,
        centreX + radius * std::cos(angle),
        centreY + radius * std::sin(angle),
        false);
    g.setGradientFill(pointerGradient);
    g.fillPath(p);
}