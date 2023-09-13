#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include"DeckGUI.h"
#include "button.h"

//==============================================================================

// Loads global variable into this playlistComponent file
extern juce::URL tempURL;

class PlaylistComponent :
    // Inherit Component
    public juce::Component,

    // Inherit TableListBoxModel
    public juce::TableListBoxModel,

    // Inherit button listener
    public juce::Button::Listener,

    // Inherit textBox listener
    public juce::TextEditor::Listener,

    public juce::URL
{
public:
    PlaylistComponent(DJAudioPlayer* _player1, DJAudioPlayer* _player2);
    
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // Pure virtual functions of TableListBoxModel (Needed)

    /** Return number of rows currently in table*/
    int getNumRows() override;

    /** Draws background behind 1 row in table*/
    void paintRowBackground(
        juce::Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    
    /** Draws Cells in table*/
    void paintCell(
        juce::Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    /** Create or update a custom component to go in a cell*/
    juce::Component* refreshComponentForCell(
        int rowNumber,
        int columnId,
        bool isRowSelected,
        juce::Component *existingComponentToUpdate) override;

    /** Function is called when the button is clicked*/
    void buttonClicked(juce::Button* button) override;

private:
    /** Saves the library when user exits from application*/
    void saveLibrary();

    /** Loads the library when user reopens the application*/
    void loadLibrary();

    /** textbox for user song search */ 
    juce::TextEditor songSearchBox;

    /** Runs user's words written in the search box against the songs loaded in the song library*/
    void searchSong(juce::String search);

    /** Function to search the keyword row by row in the tablecomponent*/
    int searchSongRow(juce::String keyWord);

    // Add TableListBox to called tableComponent
    juce::TableListBox tableComponent;

    // Vector called trackFiles that stores the song files that user chooses in table
    std::vector<juce::File> trackFiles;

    // Vector called trackTitles that store the trackTitles
    std::vector<std::string> trackTitles;

    // Vector called trackTimes that stores the song times that user chooses in table
    std::vector<std::string> trackTimes;

    // Vector called trackURL that stores the song URL that user chooses in table
    std::vector<juce::URL> trackURL;

    // Add pointer reference for player 1 and player 2
        // Add pointer reference
    DJAudioPlayer* player1;

    // Add pointer reference
    DJAudioPlayer* player2;

    // Custom graphics button
    Button button;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
