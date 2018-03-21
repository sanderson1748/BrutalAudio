////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Launch_Window.cpp
//

#include "Launch_Window.h"

#include "../Gui_Headers.h"
#include "../Audio/Audio_Window.h"
#include "../Image/Image_Window.h"

#if defined DEBUG
#include <iostream>
#endif

// Launch_Window ----------------------------------------------------------- //
Launch_Window::Launch_Window(juce::String name) : DocumentWindow(name, juce::Colours::black, 0)
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Launch_Window::Contruct" << std::endl;
#endif

	// Create Editor
	setContentOwned(new Launch_Editor(), true);

	// Configure Window
	setUsingNativeTitleBar(true);
	setSize(210,215);
	setResizable(false,false);
	setVisible(true);
}

void Launch_Window::closeButtonPressed()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Launch_Window::closeButtonPressed" << std::endl;
#endif

	juce::JUCEApplication::getInstance()->systemRequestedQuit();
}


// Launch_Editor ----------------------------------------------------------- //
Launch_Editor::Launch_Editor()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Launch_Editor::Construct" << std::endl;
#endif

	// Create Buttons
	// - Listener
	listen = new Launch_Listener;

	// - Start Audio
	button_audio = new Launch_Button("Audio", go_audio);
	button_audio->Set_Id(1);

	button_audio->setSize(200,100);
	button_audio->setVisible(true);

	button_audio->addListener((juce::Button::Listener*) listen);

	// - Start Image
	button_image = new Launch_Button("Image", go_image);
	button_image->Set_Id(2);

	button_image->setSize(200,100);
	button_image->setVisible(true);

	button_image->addListener((juce::Button::Listener*) listen);

	// Place Modules
	resized();

	// Enable Modules
	addAndMakeVisible(button_audio);
	addAndMakeVisible(button_image);
}

Launch_Editor::~Launch_Editor()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Launch_Editor::Destruct" << std::endl;
#endif

	// Delete Buttons
	button_audio = nullptr;
	button_image = nullptr;
	listen       = nullptr;

	// Delete Window
	go_audio = nullptr;
	go_image = nullptr;
}

void Launch_Editor::paint(juce::Graphics& g)
{
#if 0//defined SHOW_FUNCTIONS
	std::cout << "Debug> Launch_Window::paint(..)" << std::endl;
#endif

	g.fillAll(juce::Colours::green);
}

void Launch_Editor::resized()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Launch_Window::resized" << std::endl;
#endif

	// Position Modules
	button_audio->setTopLeftPosition(GAP_SPACE,GAP_SPACE);
	button_image->setTopLeftPosition(GAP_SPACE,110);
}

//
