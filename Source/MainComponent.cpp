#include "MainComponent.h"

// Global variable called tempURL to store the url of the song before load
juce::URL tempURL;

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1350, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });

    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    // Make deckGUI1 Visible
    addAndMakeVisible(deckGUI1);

    // Make deckGUI2 Visible
    addAndMakeVisible(deckGUI2);

    // Make playlistComponent Visible
    addAndMakeVisible(playlistComponent);

    // Prepares formatManager to know how to play the basic file formats
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    playing = false;

    // Use the music player
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

}
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{ 
    // Tells transport source to do the work and read files
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    player1.releaseResources();
    
    player2.releaseResources();

    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour(0xFF000000));

}

void MainComponent::resized()
{
    // Set bounds for the first deckGUI
    deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight() / 2);

    // Set bounds for the second deckGUI
    deckGUI2.setBounds(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);

    // Set bounds for the playlistComponent
    playlistComponent.setBounds(getWidth() /2 , 0, getWidth() / 2, getHeight());
}


