

#pragma once

#include <JuceHeader.h>


class DJAudioPlayer : public juce::AudioSource 
{
// Public stuff here
public:
    // Constructor
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);

    /** Sets gain of the audio*/
    void setGain(double gain);

    /** Set speed of the audio*/
    void setSpeed(double ratio);

    /** Set reverb for the audio*/
    void setReverbDamping(double reverbValue);

    /** Set reverb dryness for the audio*/
    void setReverbDryness(double reverbValue);

    /** Set reverb wetness for the audio*/
    void setReverbWetness(double reverbValue);

    /** Set reverb roomSize for the audiio*/
    void setReverbRoomSize(double reverbValue);

    /** Sets current audio playing position*/
    void setPosition(double posInSecs);

    /** Sets the visual audio playing position in the audio wave*/
    void setPositionRelative(double pos);

    /** Starts looping audio*/
    void loopAudio(juce::URL _tempURL, bool isLooping);
        
    /** Starts playing audio*/
    void start();

    /** Stops playing audio*/
    void stop();

    /** Get the relative position of the playhead*/
    double getPositionRelative();
//Private stuff here
private:

    // Class for keeping a list of available audio formats
    // Helps decide which one to use to open a given file
    // Used as reference
    juce::AudioFormatManager& formatManager;

    // Type of audio source that will read from an AudioFormatReader
    // Make it into a unique pointer
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;

    // Allows Audio Source to be played, stopped, started, etc
    // More control over Audio Source
    juce::AudioTransportSource transportSource;

    // Function for resample / edit the sound source, constructor receives a reference to transport source
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};

    // Variables for manipulating the reverb of the resampleSource
    juce::ReverbAudioSource reverbSource{ &resampleSource, false };
    // Stores the reverb Parameters
    juce::Reverb::Parameters reverbParameters;


    // Local private booleans 

    // isLoop toggles the algo
    bool isLoop = false;
    bool positionReset = false;

    juce::URL singleURL;
};