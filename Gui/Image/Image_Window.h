////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Image_Window.h
//
// Image Guy -> MUCCCHHHHH later
//
// This file has Window and Editor
//

#ifndef __IMAGE_WINDOW__
#define __IMAGE_WINDOW__

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"

// Window is GUI base component thingy, holds Editor
class Image_Window : public juce::DocumentWindow
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Image_Window);

	public:
		Image_Window(juce::String);
		void closeButtonPressed(void) override;
};

// Editor has the Modules
class Image_Editor : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Image_Editor);

	public:
		// Build
		Image_Editor(void);
		~Image_Editor(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
