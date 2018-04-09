////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Image_Window.cpp
//

#include "Image_Window.h"

// Image_Window ------------------------------------------------------------ //
Image_Window::Image_Window(juce::String name) : DocumentWindow(name, juce::Colours::black, 0)
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Image_Window::Contruct" << std::endl;
#endif

	setContentOwned(new Image_Editor(), true);
	setUsingNativeTitleBar(true);
	setSize(200,200);
	setVisible(true);
}

void Image_Window::closeButtonPressed()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Image_Window::closeButtonPressed" << std::endl;
#endif

	delete this;
}

// Image_Editor ------------------------------------------------------------ //
Image_Editor::Image_Editor()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Image_Editor::Contruct" << std::endl;
#endif
}

Image_Editor::~Image_Editor()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Image_Editor::Destruct" << std::endl;
#endif
}

void Image_Editor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::blue);
}

void Image_Editor::resized()
{
}

//
