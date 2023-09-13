#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : 
    public juce::Component,
    public juce::ChangeListener
{
public:
    WaveformDisplay(
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse
    );
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    /** Loads URL file that user chooses*/
    void loadURL(juce::URL audioURL);

    /** Sets position of the playhead in the soundwave drawing*/
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumb;
    
    // Private variable called fileLoaded
    bool fileLoaded;
    double position;

    juce::String songName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
