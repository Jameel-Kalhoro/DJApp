#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h";
#include "DeckGUI.h";
#include "PlaylistComponent.h";



//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent   
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    



private:
    //==============================================================================
    // Your private member variables go here...

    // Audio format manager called formatManager
    juce::AudioFormatManager formatManager;

    // Audio thumbnail cache called thumbCache with a size of 100
    // Stores 100 cached waveforms
    juce::AudioThumbnailCache thumbCache{ 100 };

    // boolean to determine if music is playing or not
    bool playing;

    // Creates instance of DJAudioPlayer called player1
    DJAudioPlayer player1{ formatManager };

    // Creates instance of DeckGUI called deckGUI
    DeckGUI deckGUI1{ &player1, formatManager, thumbCache };

    // Creates instance of DJAudioPlayer called player2
    DJAudioPlayer player2{ formatManager };


    // Creates second instance of DeckGUI called deckGUI2
    DeckGUI deckGUI2{ &player2, formatManager, thumbCache };

    // Mixer audio source to mix 2 songs together
    juce::MixerAudioSource mixerSource;

    PlaylistComponent playlistComponent{&player1, &player2};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
