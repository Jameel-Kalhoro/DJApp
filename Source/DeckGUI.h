#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistComponent.h"
#include "knob.h"
#include "button.h"
#include "OnOffSwitch.h"
#include "PosSliderStyling.h"

class DeckGUI :
    // Inherit these class
    public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Timer,
    // Lets DeckGUI inherit lookAndFeel_V4 class
    public juce::LookAndFeel_V4   
{
public:
    // DJAudioPlayer coming into the construction there
    DeckGUI(
        DJAudioPlayer* _player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI();
    

    void paint (juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener*/
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listener*/
    void sliderValueChanged(juce::Slider* slider) override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;

    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /** Pure virtual function hence needed to initalize in the public header*/
    void timerCallback() override;

    void loadSong(juce::URL fileURL);

    /** Make items visible*/
    void makeVisible();

    /** Custom Graphics for sliders*/
    void sliderStyle();

    /** Adds listeners*/
    void addListeners();

    /** Sets sliders Range*/
    void setRangeSliders();

    /** Custom Graphics for buttons*/
    void buttonStyle();

    /** Custom Graphics for checkboxes*/
    void checkBoxesStyle();



private:

    // Creates an graphical design that applies to the volume Dial
    Knob knob;

    // Creates an graphical design that applies to the start, stop and load buttons in DeckGUI
    Button button;

    // Creates an graphical design that applies to the checkBoxes in DeckGUI
    OnOffSwitch onOffSwitch;

    // Creates an graphical design that applies to the pos slider in DeckGUI
    PosSliderStyling posSliderStyling;

    // Add textbutton called PLAY
    juce::TextButton playButton{ "PLAY" };

    // Add textbutton called PLAY
    juce::TextButton stopButton{ "STOP" };

    // Add textbutton called LOAD
    juce::TextButton loadButton{ "LOAD" };

    // Add slider
    juce::Slider volSlider;
    juce::Label volSliderLabel;

    // Add speed slider
    juce::Slider speedSlider;
    juce::Label speedSliderLabel;

    // Add a pos slider for the position of the time when playing music
    juce::Slider posSlider;
    juce::Label posSliderLabel;

    // Add reverb DAMPING slider
    juce::Slider reverbSliderDamp;
    juce::Label reverbSliderDampLabel;

    // Add reverb DRYlEVEL slider
    juce::Slider reverbDryLevelSlider;
    juce::Label reverbDryLevelSliderLabel;

    // Add reverb WETLEVEL slider
    juce::Slider reverbWetLevelSlider;
    juce::Label reverbWetLevelSliderLabel;

    // Add reverb ROOMSIZE slider
    juce::Slider reverbRoomSizeSlider;
    juce::Label reverbRoomSizeSliderLabel;

    // Add a loopCheckbox
    juce::TextButton loopCheckbox{ "TOGGLE LOOP" };

    // Add pointer reference
    DJAudioPlayer* player;

    // Add waveform display
    WaveformDisplay waveformDisplay;

    // LoopSong function will use this as reference to replay song
    juce::URL nameOfLoadedURL;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
