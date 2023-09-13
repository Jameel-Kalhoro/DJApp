#include <JuceHeader.h> 
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(
    DJAudioPlayer* _player1,
    DJAudioPlayer* _player2)

    :player1{ _player1 }, player2{ _player2 } 

{
    // Push stuff to trackTitles vector

    for (int i = 1; i < 25; i++)
    {
        
        trackTitles.push_back("Open Slot Track " + std::to_string(i));
    }

    // For loop that determines the number of trackTitles and initalizes the size of the trackFiles vector
    for (int i = 0; i < trackTitles.size(); i++)
    {
        // Create an empty file
        juce::File myFile;

        // Pushes the empty file into the trackTitles array
        trackFiles.push_back(myFile);

        // Create an empty double variable
        std::string emptyString;

        trackTimes.push_back(emptyString);

        // Create an empty url
        juce::URL emptyURL;

        trackURL.push_back(emptyURL);
    }


    // Access header of tableComonent and add a column to that
    //the columnId parameter for addColumn must not be zero.


    // Column 1 Track title
    tableComponent.getHeader().addColumn("Load Music", 1, 200);
    // Column 2 Track Length
    tableComponent.getHeader().addColumn("Play Right Track", 2, 200);

    // Column 3 Play button
    tableComponent.getHeader().addColumn("Play Left Track", 3, 100);
    // Column 4 Play button
    tableComponent.getHeader().addColumn("Track Length", 4, 100);
    // Column 5 Load Music button
    tableComponent.getHeader().addColumn("Track Title", 5, 200);

    // Set model pointing to itself
    tableComponent.setModel(this);

    // Makes tableComponent visible
    addAndMakeVisible(tableComponent);

    // Makes searchbox visible
    addAndMakeVisible(songSearchBox);

    // Searchbox parameters
    songSearchBox.addListener(this);

    // Show text telling users that this box can be used to search for songs
    songSearchBox.setTextToShowWhenEmpty("Search Songs here! Press enter to submit",
        juce::Colours::white);

    // If user presses the enter button after typing in their keywords in the search function
    songSearchBox.onReturnKey = [this]
    {
        // Lauches the search song function with the values user
        // Has inputted into to search for song
        searchSong(songSearchBox.getText());
    };

    // Loads library
    loadLibrary();
}

PlaylistComponent::~PlaylistComponent()
{
    saveLibrary();

    // remember to set the setLookAndFeel pointer to null when user shuts down the application
    setLookAndFeel(nullptr);
}

void PlaylistComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black); // Set the background color to black

    g.setColour(juce::Colours::white); // Set the text color to white

    g.setFont(14.0f);
    g.drawText("PlaylistComponent", getLocalBounds(),
        juce::Justification::centred, true); // draw some placeholder text

    // Custom Graphics for all the buttons
    setLookAndFeel(&button);
}

void PlaylistComponent::resized()
{
    // Set bounds for tableComponent
    songSearchBox.setBounds(0, 0, getWidth(), 25);
    tableComponent.setBounds(0, 25, getWidth(), getHeight() - 25);
}

int PlaylistComponent::getNumRows()
{
    // Returns number of rows in the trackTitles array
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(
    juce::Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    // If user clicks on a row in the table
    if (rowIsSelected)
    {
        // Selected row will have orange fill
        g.fillAll(juce::Colours::white);
    }
    // Rest of the rows
    else
    {
        // Define the gradient colors for the non-selected row background
        juce::ColourGradient nonSelectedRowGradient(juce::Colours::darkgrey, 0, 0,
            juce::Colours::black, 0, static_cast<float>(height), false);

        // Fill the non-selected row background with the gradient
        g.setGradientFill(nonSelectedRowGradient);
        g.fillAll();

        // Set the text color to white for visibility
        g.setColour(juce::Colours::white);
    }
}

void PlaylistComponent::paintCell(
    juce::Graphics & g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    // Added condition rowNumber < getNumRows() so that juce does not try to get stuff out of the vector's range (trackTitle vector size)
    if (columnId == 5 && rowNumber < getNumRows())
    {
        g.drawText(
            trackTitles[rowNumber],
            1,
            0,
            width - 4,
            height,
            juce::Justification::centredLeft,
            true);

    }


    // Added condition rowNumber < getNumRows() so that juce does not try to get stuff out of the vector's range (trackTitle vector size)
    if (columnId == 4 && rowNumber < getNumRows())
    {
        g.drawText(
            trackTimes[rowNumber],
            1,
            0,
            width - 4,
            height,
            juce::Justification::centredLeft,
            true);

    }
}

juce::Component* PlaylistComponent::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    juce::Component* existingComponentToUpdate)
{
    // If column Selected is playbutton (id is 3)
    if (columnId == 3)
    {
        // If the existingComponenttoUpdate is null
        if (existingComponentToUpdate == nullptr)
        {
            // Create actual text button pointer and store new text button in there
            juce::TextButton* btn = new juce::TextButton{ "Play Left Track" };

            // Convert the int rowNumber to string using std library and assigns it to a juce::string
            // called id
            juce::String id{ std::to_string(rowNumber) };

            // Assigns that juce::string id to the TextButton that was created above
            btn->setComponentID(id);

            // Add button listener
            btn->addListener(this);

            // Store the text play button to the variable
            existingComponentToUpdate = btn;
        }
    }
    if (columnId == 2)
    {
        // If the existingComponenttoUpdate is null
        if (existingComponentToUpdate == nullptr)
        {
            // Create actual text button pointer and store new text button in there
            juce::TextButton* btn = new juce::TextButton{ "Play Right Track" };

            // Convert the int rowNumber to string using std library and assigns it to a juce::string
            // called id
            juce::String id{ std::to_string(rowNumber) };

            // Assigns that juce::string id to the TextButton that was created above
            btn->setComponentID(id);

            // Add button listener
            btn->addListener(this);

            // Store the text play button to the variable
            existingComponentToUpdate = btn;

        }
    }
    if (columnId == 1)
    {
        // If the existingComponenttoUpdate is null
        if (existingComponentToUpdate == nullptr)
        {
            // Create actual text button pointer and store new text button in there
            juce::TextButton* btn = new juce::TextButton{ "load" };

            // Convert the int rowNumber to string using std library and assigns it to a juce::string
            // called id
            juce::String id{ std::to_string(rowNumber) };

            // Assigns that juce::string id to the TextButton that was created above
            btn->setComponentID(id);

            // Add button listener
            btn->addListener(this);

            // Store the text play button to the variable
            existingComponentToUpdate = btn;
        }
    }
    // Return said variable
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    // Convert juce::string into standard string and 
    // then converts the standard string into an integer
    int id = std::stoi(button->getComponentID().toStdString());
    std::string buttonText = button->getButtonText().toStdString();

    // If the address is playButton
    if (buttonText == "Play Left Track")
    {
        // Plays the selected music using the trackTitles[id] in the array
        player1->loadURL(trackURL[id]);

        tempURL = trackURL[id];
       
        repaint();
    }
    // If the address is playButton
    else if (buttonText == "Play Right Track")
    {
        // Plays the selected music using the trackTitles[id] in the array
        player2->loadURL(trackURL[id]);

        // Sets global variable as the current trackURL chosen
        tempURL = trackURL[id];

        repaint();

    }
    // If the address is stopButton
    else if (buttonText == "load")
    {
        // Let user select file, then file will be 
        // pushed to array that contain the 
        // song metadata ( name of song, type of file and duration of song)
        // song file aka soundwave


        // Ready made component to trigger a file chooser
        juce::FileChooser chooser{ "Select a file..." };

        if (chooser.browseForFileToOpen())
        {
            // Local file that stores user's chosen song temporarily
            juce::File myFile;

            // Sets the chosen song into the local file
            myFile = chooser.getResult();


            // Save the file to the trackFiles vector with the id as a pointer
            trackFiles[id] = myFile;

            // Gets file name and replaces the text in the row user has decided to choose
            juce::String Filename = trackFiles[id].getFileName();

            // Saves the new tracktitle name as Filename which has been converted from juce
            // juce string to std string
            trackTitles[id] = Filename.toStdString();


            // Gets track url and saves it to the vector
            trackURL[id] = juce::URL{ chooser.getResult() };

            // Setups an temporary format manager to read the file
            juce::AudioFormatManager formatManager;

            // Registers basic song formats so that the file manager can read the file
            formatManager.registerBasicFormats();

            juce::AudioFormatReader* reader = formatManager.createReaderFor(myFile);
            
            //auto reader = formatManager.createReaderFor(myFile)
            // If a reader is able to be created for the file user has chosen
            if (reader != nullptr)
            {
                // Calculate the total time taken for the song from start to finish
                float timeTaken = reader->lengthInSamples / reader->sampleRate;

                timeTaken = timeTaken / 60;

                // convert the number into a string
                std::string trackTime = std::to_string(timeTaken);

                // Convert length

                // sets the time of the song that user has chosen to the vector and using the trackTimes id
                trackTimes[id] = trackTime + " Mins";
            };

            // Removes the initalized reader so that there is no juce leak
            reader->~AudioFormatReader();

            // Updates the graphics as the name in the table row = id has changed
            repaint();
        }
    }
}

void PlaylistComponent::searchSong(juce::String search)
{
    // If the searchbox is not empty
    if (search != "")
    {
        // launches searchSongRow function that returns the row number of the matched word
        int rowNumber = searchSongRow(search);
        
        // Highlights the row that has the match result
        tableComponent.selectRow(rowNumber);
    }
}

int PlaylistComponent::searchSongRow(juce::String keyWord)
{
    // finds index where track title contains searchText
    auto it = find_if(
        trackTitles.begin(), 
        trackTitles.end(),
        [&keyWord](const juce::String& obj) {return obj.contains(keyWord); });

    // Sets integer i as -1
    int i = -1;

    // If the result of the it is not equal to the length of the trackTitles end length
    if (it != trackTitles.end())
    {
        // Get the index of i which there was a match
        i = std::distance(trackTitles.begin(), it);
    }

    //return i;
    return i;
}

void PlaylistComponent::saveLibrary()
{
    // Creates a file to save the songFiles
    std::ofstream songLibrary("songLibrary.csv");

    int x = 0;

    // Saves the songs to file
    for (juce::File& t : trackFiles)
    {
        // Pushes the full path name of songs into file
        songLibrary << t.getFullPathName() << "," << trackTimes[x] << "\n";
        
        ++x;
    }
    x = 0;
}

void PlaylistComponent::loadLibrary()
{
    // Creates an input stream
    std::ifstream songLibrary("songLibrary.csv");

    // Stores the path of file
    std::string filePath;

    // Stores the duration of file
    std::string fileTime;

    // Create x and initalize it to 0
    int x = 0;

    if (songLibrary.is_open())
    {
        // gets line from songLibrary
        while (getline(songLibrary, filePath, ',')) {

            // 1st thing before comma is the file of the item
            juce::File file{ filePath };

            // Gets the time of the song file which is after the comma
            getline(songLibrary, fileTime);
            
            // stores the file name temporarily
            std::string tempFileName;

            // Gets the full path of the file
            juce::URL fileURL = file.getFullPathName();

            // Saves the file name to tempFileName
            tempFileName = file.getFileName().toStdString();

            // Saves the file url to the trackURL Vector
            trackURL[x] = juce::URL{ file };

            // Save the file time to the trackTimes Vector
            trackTimes[x] = fileTime;

            // Save the file name to the trackTitles vector
            trackTitles[x] = tempFileName;

            // Save the file to the trackFiles vector
            trackFiles[x] = file;
   
            // Increment the x value by 1
            ++x;
        }
    }
    songLibrary.close();

    // Draws the track titles, time on the music library
    repaint();
}

