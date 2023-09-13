 #include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager) 
    : formatManager(_formatManager)
{

};
DJAudioPlayer::~DJAudioPlayer() 
{

};

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) 
{
    // tells transport source to get ready
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // Prepare to play the resampled resource
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // Prepare to play reverb source
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
};

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) 
{
    // If the song wants to be looped (isLoop == true)
    if (isLoop)
    {
        // Gets the length of the current song playing in seconds
        double totalTime = transportSource.getLengthInSeconds();

        // Gets the current time of the song playing in seconds
        double currentTime = transportSource.getCurrentPosition();
        
        // Calculate the time left before the song reaches the end in seconds
        double differenceTime = totalTime - currentTime;

        // If the song playing is at its end
        if (differenceTime < 0)
        {
            // Sets positionReset to true
            positionReset = true;

            // Calls loopAudio with the stored URL of the current song playing with position reset as true
            loopAudio(singleURL, positionReset);
        }
    }

    // If song DOES NOT want to be looped
    if (isLoop == false)
    {
        // Sets position reset as false
        positionReset = false;
    }

    // Pass the work onto transport
    //resampleSource.getNextAudioBlock(bufferToFill);
    reverbSource.getNextAudioBlock(bufferToFill);
};
void DJAudioPlayer::releaseResources() 
{
    // Release the audio block in transport, resample and reverbSource
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
};

void DJAudioPlayer::loadURL(juce::URL audioURL) 
{
    // Take audio url and convert it into a input stream and place it into a reader
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));

    // Check if it is creation of reader is successfull
    if (reader != nullptr) // Good file!!
    {
        // Create an AudioFormatReaderSource, takes low level file reader and makes it into an audio source
        // Only temporary
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));

        // parse audio source into transport source
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);

        // pass ownership of pointer to class scope variable, retain access to it
        readerSource.reset(newSource.release());
    }
};

void DJAudioPlayer::setGain(double gain)
{
    // Make sure gain is in appropriate range
    if (gain < 0 || gain > 1.0)
    {
        // Gives warning to user that gain is out of range
        DBG("DJAudioPlayer::setGain - Gain value is out of range, should be between 0 - 1");
    }
    else
    {
        transportSource.setGain(gain);
    }
};
void DJAudioPlayer::setSpeed(double ratio) 
{
    // Make sure ratio is in appropriate range
    if (ratio < 0 || ratio > 100)
    {
        // Gives warning to user that ratio is out of range
        DBG("DJAudioPlayer::setSpeed - Gain ratio is out of range, should be between 0 - 100");
    }
    else
    {
        // Sets the speed of the audio
        resampleSource.setResamplingRatio(ratio);
    }
};

void DJAudioPlayer::setReverbDamping(double reverbValue)
{
    // Makes sure reverb value is not out of range
    if (reverbValue < 0 || reverbValue > 1.0)
    {
        // Gives warning to user that the ratio is out of range
        DBG("DJAudioPlayer::setReverbDamping - Reverb value is out of range, should be between 0 - 1");
    }
    else // Reverb values is in range
    {
        // Sets level of damping
        reverbParameters.damping = reverbValue;
        // Sets the source parameters
        reverbSource.setParameters(reverbParameters);
    }

};

void DJAudioPlayer::setReverbDryness(double reverbValue)
{
    // Makes sure reverb value is not out of range
    if (reverbValue < 0 || reverbValue > 1.0)
    {
        // Gives warning to user that the ratio is out of range
        DBG("DJAudioPlayer::setReverbDryness - Reverb value is out of range, should be between 0 - 1");
    }
    else // Reverb values is in range
    {
        // Sets dry level of reverb
        reverbParameters.dryLevel = reverbValue;
        // Sets the source parameters
        reverbSource.setParameters(reverbParameters);
    }
};

void DJAudioPlayer::setReverbWetness(double reverbValue)
{
    // Makes sure reverb value is not out of range
    if (reverbValue < 0 || reverbValue > 1.0)
    {
        // Gives warning to user that the ratio is out of range
        DBG("DJAudioPlayer::setReverbWetness - Reverb value is out of range, should be between 0 - 1");
    }
    else // Reverb values is in range
    {
        // Sets wet level of reverb
        reverbParameters.wetLevel = reverbValue;
        // Sets the source parameters
        reverbSource.setParameters(reverbParameters);
    }
};

void DJAudioPlayer::setReverbRoomSize(double reverbValue)
{
    // Makes sure reverb value is not out of range
    if (reverbValue < 0 || reverbValue > 1.0)
    {
        // Gives warning to user that the ratio is out of range
        DBG("DJAudioPlayer::setReverbRoomSize - Reverb value is out of range, should be between 0 - 1");
    }
    else // Reverb values is in range
    {
        // Sets room size level of reverb
        reverbParameters.roomSize = reverbValue;
        // Sets the source parameters
        reverbSource.setParameters(reverbParameters);
    }
};


void DJAudioPlayer::setPosition(double posInSecs)
{
    // Changes the current playback position in seconds
    transportSource.setPosition(posInSecs);
};

void DJAudioPlayer::setPositionRelative(double pos)
{
    // Make sure pos is in appropriate range
    if (pos < 0 || pos > 1.0)
    {
        // Gives warning to user that pos is out of range
        DBG("DJAudioPlayer::setPositionrelative - pos ratio is out of range, should be between 0 - 1");
    }
    else
    {
        // Calculating the pos
        double posInSecs = transportSource.getLengthInSeconds() * pos;

        // Sets the position in seconds
        setPosition(posInSecs);
    }
};

void DJAudioPlayer::loopAudio(juce::URL _tempURL, bool isLooping)
{
    // If user does not want to loop song
    if (isLooping == false)
    {
        // Create an temporary empty URL
        juce::URL emptyURL;

        // Clears out the singleURL as an empty URL
        singleURL = emptyURL;

        // Sets isLoop to false to stop the loopAudio function from being looped 
        isLoop = false;

        // Stops the function
        return;
    }
    // If user wants to loop song
    else if (isLooping == true)
    {
        // Starts the calculation of the time left in DJAudioPlayer::getNextAudioBlock()
        // loopAudio() will always be called until isLoop is false
        isLoop = true;

        // Sets the singleURL with the _tempURL input parameter from loopAudio
        singleURL = _tempURL;
    }
    
    
    // If the song reaches the end with loop on (positionReset is true)
    if (positionReset == true)
    {
        // Resets the positionReset back to default (FALSE)
        positionReset = false;

        // Loads the storedURl into the player
        loadURL(singleURL);

        // Starts the player
        start();
    }
}

void DJAudioPlayer::start() 
{
    // Starts the music
    transportSource.start();
};

void DJAudioPlayer::stop() 
{
    // Stops the music
    transportSource.stop();
};

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
