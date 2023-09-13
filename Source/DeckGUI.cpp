#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(
    DJAudioPlayer* _player,
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse
) : player{ _player },
    // Adds a member initalizer list so that the private data can be passed down to other
    // stuff
    waveformDisplay(formatManagerToUse, cacheToUse)
{
    makeVisible();

    sliderStyle();

    checkBoxesStyle();

    setRangeSliders();

    addListeners();


    // Start the gui timer, repeats every 500ms
    startTimer(500);
    
}

DeckGUI::~DeckGUI()
{
    // Stop timer when it gets destructed
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    //getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::green);

}

void DeckGUI::makeVisible()
{
    // Add the waveform display and make it visible
    addAndMakeVisible(waveformDisplay);

    // Make volSlider visible
    addAndMakeVisible(volSlider);

    // Make Label for volSlider visible
    addAndMakeVisible(volSliderLabel);
    volSliderLabel.setText("Volume", juce::dontSendNotification);
    volSliderLabel.attachToComponent(&volSlider, false);

    // Make speedSlider visible
    addAndMakeVisible(speedSlider);
    speedSliderLabel.setText("Speed", juce::dontSendNotification);
    speedSliderLabel.attachToComponent(&speedSlider, false);


    // Make reverbSliderDamp visible
    addAndMakeVisible(reverbSliderDamp);
    reverbSliderDampLabel.setText("Dampness", juce::dontSendNotification);
    reverbSliderDampLabel.attachToComponent(&reverbSliderDamp, false);

    // Make reverbDryLevelSlider visible
    addAndMakeVisible(reverbDryLevelSlider);
    reverbDryLevelSliderLabel.setText("Dryness", juce::dontSendNotification);
    reverbDryLevelSliderLabel.attachToComponent(&reverbDryLevelSlider, false);

    // Make reverbWetLevelSlider visible
    addAndMakeVisible(reverbWetLevelSlider);
    reverbWetLevelSliderLabel.setText("Wetness", juce::dontSendNotification);
    reverbWetLevelSliderLabel.attachToComponent(&reverbWetLevelSlider, false);

    // Make reverbRoomSizeSlider visible
    addAndMakeVisible(reverbRoomSizeSlider);
    reverbRoomSizeSliderLabel.setText("Room Size", juce::dontSendNotification);
    reverbRoomSizeSliderLabel.attachToComponent(&reverbRoomSizeSlider, false);


    // Makes posSlider visible
    addAndMakeVisible(posSlider);
    // Make Text next to pos slider visible
    posSliderLabel.setText("Position", juce::dontSendNotification);
    // Attach posSliderLabel to the left side of the slider
    posSliderLabel.attachToComponent(&posSlider, true);

    // Make loopCheckbox visible
    addAndMakeVisible(loopCheckbox);

    // Makes playButton visible
    addAndMakeVisible(playButton);

    // Makes stopButton visible
    addAndMakeVisible(stopButton);

    // Add the Load Button and make it visible
    addAndMakeVisible(loadButton);

    // Custom Graphics for buttons
    buttonStyle();
}

void DeckGUI::sliderStyle()
{
    // Customize vol slider into a Rotary Slider
    volSlider.setSliderStyle(juce::Slider::Rotary);

    // Custom Graphics to make vol slider into knob
    volSlider.setLookAndFeel(&knob);

    // Customize speedSlider into a Rotary Slider
    speedSlider.setSliderStyle(juce::Slider::Rotary);

    // Custom Graphics to make speed slider into knob
    speedSlider.setLookAndFeel(&knob);

    // Customize reverbSliderDamp into a Rotary Slider
    reverbSliderDamp.setSliderStyle(juce::Slider::Rotary);

    // Custom Graphics to make reverb slider into knob
    reverbSliderDamp.setLookAndFeel(&knob);

    // Customize reverbDryLevelSlider into a Rotary Slider
    reverbDryLevelSlider.setSliderStyle(juce::Slider::Rotary);

    // Custom Graphics to make reverb slider into knob
    reverbDryLevelSlider.setLookAndFeel(&knob);

    // Customize reverbWetLevelSlider into a Rotary Slider
    reverbWetLevelSlider.setSliderStyle(juce::Slider::Rotary);

    // Custom Graphics to make reverb slider into knob
    reverbWetLevelSlider.setLookAndFeel(&knob);

    // Customize reverbRoomSizeSlider into a Rotary Slider
    reverbRoomSizeSlider.setSliderStyle(juce::Slider::Rotary);

    // Custom Graphics to make reverb slider into knob
    reverbRoomSizeSlider.setLookAndFeel(&knob);



    // Customize position slider into Linear bar
    posSlider.setSliderStyle(juce::Slider::LinearBar);
    posSlider.setLookAndFeel(&posSliderStyling);
}

void DeckGUI::buttonStyle()
{
    // Custom graphics for the play, stop and load buttons
    playButton.setLookAndFeel(&button);
    stopButton.setLookAndFeel(&button);
    loadButton.setLookAndFeel(&button);
}



void DeckGUI::checkBoxesStyle()
{
    // Change loopCheckbox button from a click button to a toggleable button
    loopCheckbox.setClickingTogglesState(true);
    
    // Custom Graphics for the loopCheckbox button
    loopCheckbox.setLookAndFeel(&onOffSwitch);
}

void DeckGUI::setRangeSliders()
{
    // Set range of volume slider from 0 to 1
    volSlider.setRange(0.0, 1.0);
    volSlider.setNumDecimalPlacesToDisplay(2);

    // Set range of speed slider
    speedSlider.setRange(0.0, 100.0, 0.1);
    speedSlider.setNumDecimalPlacesToDisplay(2);

    // Set range of pos slider from 0 to 1
    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(2);

    // Set range of reverb slider damp from 0 to 1
    reverbSliderDamp.setRange(0.0, 1.0);
    reverbSliderDamp.setNumDecimalPlacesToDisplay(2);

    // Set range of reverb slider dry level from 0 to 1
    reverbDryLevelSlider.setRange(0.0, 1.0);
    reverbDryLevelSlider.setNumDecimalPlacesToDisplay(2);

    // Set range of wet level slider from 0 to 1
    reverbWetLevelSlider.setRange(0.0, 1.0);
    reverbWetLevelSlider.setNumDecimalPlacesToDisplay(2);

    // Set range of reverb room size slider from 0 to 1
    reverbRoomSizeSlider.setRange(0.0, 1.0);
    reverbRoomSizeSlider.setNumDecimalPlacesToDisplay(2);


}

void DeckGUI::addListeners()
{
    // Add listeners for sliders
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    reverbSliderDamp.addListener(this);
    reverbDryLevelSlider.addListener(this);
    reverbWetLevelSlider.addListener(this);
    reverbRoomSizeSlider.addListener(this);

    // Add listeners for checkBox
    loopCheckbox.addListener(this);

    // Add listeners for buttons
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
}


void DeckGUI::resized()
{
    // Create double called rowH which is 1/6 of the row height in the user's window
    double rowH = getHeight() / 8;

    double rowW = getWidth() / 2;

    double sliderWidthColumn = getWidth() / 3;

    // Set size of the play button if user resizes the window
    playButton.setBounds(0, rowH * 5, sliderWidthColumn, rowH);

    // Set size of the play button if user resizes the window
    stopButton.setBounds(sliderWidthColumn, rowH * 5, sliderWidthColumn, rowH);

    // Set size of load button if user resizes the window
    loadButton.setBounds(sliderWidthColumn * 2, rowH * 5, sliderWidthColumn, rowH);

    // Waveform display height takes on 2 rows instead of the usual 1 row
    waveformDisplay.setBounds(0, rowH * 3, getWidth(), rowH * 2);

    // Set size of the slider if user resizes the window 
    int labelOffsetValue = 20;

    // Sets the positon of the volSlider and volSliderLabel
    volSliderLabel.setBounds(0, rowH * 1, sliderWidthColumn, labelOffsetValue);
    volSlider.setBounds(0, rowH * 1 + labelOffsetValue, sliderWidthColumn, rowH * 2 - labelOffsetValue);

    // Sets the position of the speedSlider and speedSliderLabel
    speedSliderLabel.setBounds(sliderWidthColumn, rowH * 1, sliderWidthColumn, rowH * 2);
    speedSlider.setBounds(sliderWidthColumn, rowH * 1 + labelOffsetValue, sliderWidthColumn, rowH * 2 - labelOffsetValue);

    // Sets the position of the reverbSlider and reverbSliderLabel
    reverbSliderDampLabel.setBounds(sliderWidthColumn * 2, rowH * 1, sliderWidthColumn, rowH * 2);
    reverbSliderDamp.setBounds(sliderWidthColumn * 2, rowH * 1 + labelOffsetValue, sliderWidthColumn, rowH * 2 - labelOffsetValue);

    // Sets the position of the dry level slider and dry level slider label
    reverbDryLevelSliderLabel.setBounds(0, rowH * 6, sliderWidthColumn, rowH * 2);
    reverbDryLevelSlider.setBounds(0, rowH * 6 + labelOffsetValue, sliderWidthColumn, rowH * 2 - labelOffsetValue);

    // Sets the position of the wet level slider and wet level slider label
    reverbWetLevelSliderLabel.setBounds(sliderWidthColumn, rowH * 6, sliderWidthColumn, rowH * 2);
    reverbWetLevelSlider.setBounds(sliderWidthColumn, rowH * 6 + labelOffsetValue, sliderWidthColumn, rowH * 2 - labelOffsetValue);

    // Sets the position of the room size level slider and wet level slider label
    reverbRoomSizeSliderLabel.setBounds(sliderWidthColumn * 2, rowH * 6, sliderWidthColumn, rowH * 2);
    reverbRoomSizeSlider.setBounds(sliderWidthColumn * 2, rowH * 6 + labelOffsetValue, sliderWidthColumn, rowH * 2 - labelOffsetValue);

    // Sets position of position slider
    posSlider.setBounds(60,0, sliderWidthColumn * 2, rowH - 4);

    // Set position and size of loopCheckbox
    loopCheckbox.setBounds(sliderWidthColumn * 2 + 65, 0, sliderWidthColumn - 65, rowH);
}





void DeckGUI::loadSong(juce::URL fileURL)
{
    // Loads the url into the waveform display so that the waveform can be updated
    waveformDisplay.loadURL(fileURL);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    // Look at memory address of playbutton
    // If the address is playButton
    if (button == &playButton)
    {   
        // If else function to detect if there is a need to redraw the waveformDisplay
        // Depending if the tempURL is empty
        if(tempURL.isEmpty() == false)
        {
            // nameOfLoadedURL stores the global variable for url reference for looping music
            // User has chosen
            nameOfLoadedURL = tempURL;
            
            // Reloads the waveformDisplay to the current global URL stored
            waveformDisplay.loadURL(tempURL);

            // Create an empty url temporarily
            juce::URL emptyURL;

            // Clears the global value tempURL to be empty
            tempURL = emptyURL;
        }

        // Call start on the transport source, starts playing music
        player->start();
    }
    // If the address is stopButton
    if (button == &stopButton)
    {
        // Call stop on the transport source, stops playing music
        player->stop();
    }

    // If the address is loadButton
    if (button == &loadButton)
    {
        // Ready made component to trigger a file chooser
        juce::FileChooser chooser{ "Select a file..." };

        if (chooser.browseForFileToOpen())
        {
            player->loadURL(juce::URL{chooser.getResult()});
            // Call it on waveform display (not a pointer hence no need to use ->)
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });

            // Saves nameOfLoadedURL as the url file user has chosen
            nameOfLoadedURL = juce::URL{ chooser.getResult() };

            // Saves tempURL as the url file user has chosen (global variable)
            tempURL = juce::URL{ chooser.getResult() };
        }
    }

    // If user presses on the loop checkbox
    if (button == &loopCheckbox)
    {
        // Local loopURl will store the loopURL
        juce::URL loopURL = nameOfLoadedURL;

        // If loop box is checked
        if (loopCheckbox.getToggleState() == true)
        {
            // Starts looping audio
            player->loopAudio(loopURL, true);
        }
        // If loop box is not checked
        else if(loopCheckbox.getToggleState() == false)
        {
            // Stops looping audio
            player->loopAudio(loopURL, false);
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    // If user changes value of volume slider
    if (slider == &volSlider)
    {
        // Controls the gain value of the sound by using the values of the slider
        player->setGain(slider -> getValue());
    }

    // If user changes value of the speed slider
    if (slider == &speedSlider)
    {
        // Controls the speed of the sound by using the values of the slider
        player->setSpeed(slider->getValue());
    }

    // If user changes value of the reverbslider
    if (slider == &reverbSliderDamp)
    {
        // Controls the reverb of the sound by using the v,alues of the slider
        player->setReverbDamping(slider->getValue());
    }

    // If user changes value of the reverbslider
    if (slider == &reverbDryLevelSlider)
    {
        // Controls the reverb of the sound by using the values of the slider
        player->setReverbDryness(slider->getValue());
    }

    // If user changes value of the reverbslider
    if (slider == &reverbWetLevelSlider)
    {
        // Controls the reverb of the sound by using the values of the slider
        player->setReverbWetness(slider->getValue());
    }

    // If user changes value of the reverbslider
    if (slider == &reverbRoomSizeSlider)
    {
        // Controls the reverb of the sound by using the values of the slider
        player->setReverbRoomSize(slider->getValue());
    }

    // If user changes the value of position slider
    if (slider == &posSlider)
    {
        // Controls the position of the time positon of the music playing
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) 
{
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    // If there is only one file
    if (files.size() == 1)
    {
        // Loads the url to the player
        player->loadURL(juce::URL{ juce::File{files[0]} });
    }

}


void DeckGUI::timerCallback() 
{

    // Calling the player getPositionRelative argument and parse it into the waveformDisplay
    // setPositionRelative, -> is used as player is just a pointer
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

