#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse) :
    audioThumb(1000, formatManagerToUse, cacheToUse),
    // Initalize file loaded boolean to be false
    fileLoaded(false),
    // Initalize position to be 0 intially
    position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    // Add audio thumb listener in case of user changes
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);   // clear the background

    g.setColour(juce::Colours::yellow);
    

    // If file is loaded
    if (fileLoaded)
    {
        // Draw thumbnail (waves of the music)
        // Draw thumbnail (waves of the music)
        juce::ColourGradient gradient(juce::Colours::blue, 0, 0, juce::Colours::red, getWidth(), 0, false);
        g.setGradientFill(gradient);
        audioThumb.drawChannel(
            g,
            // Area
            getLocalBounds(), 
            // Start time
            0,
            // end time
            audioThumb.getTotalLength(),
            // Channel Number
            0,
            // Vertical Zoom
            1.0f);

        // Animate the position indicator
        double scrollX = position * getWidth();
        g.setColour(juce::Colours::white);
        g.drawLine(static_cast<float>(scrollX), 0.0f, static_cast<float>(scrollX), static_cast<float>(getHeight()), 2.0f);

        // Sets song name text to white
        g.setColour(juce::Colours::white);

        // Draws the songName file text, sets the text to centered bottom of the sound wave
        g.drawText(songName, getLocalBounds(), juce::Justification::centredBottom, true);

    }
    // If file not loaded
    else
    {
        // Text telling user that they need to add a file
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }

}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    // Clear any remaining files in case if there is any files in audioThumb
    audioThumb.clear();

    // Set source for audiothumbnail to be the URL file user chosen
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));

    if (fileLoaded)
    {
        // Gets file name and saves it to songName
        songName = audioURL.getFileName();

        // Repaints the audioWave
        repaint();
    }
    else
    {
        DBG("wfd: file NOT loaded!");
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    // if position is not equal to stored position
    if (pos != position && pos > 0)
    {
        // Store the position
        position = pos;

        // repaint
        repaint();
    }

}

