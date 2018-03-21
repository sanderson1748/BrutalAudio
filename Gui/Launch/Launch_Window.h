////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Launch_Window.h
//
// Welcome/Menu
//
// Not in use! Just skipping to Audio_Window right now
//

#ifndef __LAUNCH_WINDOW__
#define __LAUNCH_WINDOW__

#include <vector>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"

#include "Launch_Button.h"
#include "../Audio/Audio_Window.h"
#include "../Image/Image_Window.h"

// Window is GUI base component thingy, holds Editor
class Launch_Window : public juce::DocumentWindow
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Launch_Window);

	public:
		Launch_Window(juce::String);
		void closeButtonPressed(void) override;
};

// Editor has the modules
class Launch_Editor : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Launch_Editor)

		juce::ScopedPointer<Launch_Button> button_audio;
		juce::ScopedPointer<Launch_Button> button_image;
		juce::ScopedPointer<Launch_Listener> listen;

		juce::ScopedPointer<Audio_Window> go_audio;
		juce::ScopedPointer<Image_Window> go_image;

	public:
		Launch_Editor(void);
		~Launch_Editor(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
