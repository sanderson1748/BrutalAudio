////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// main.cpp
// 

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "Headers.h"

#if TEST_AUDIO
#include "Gui/Audio/Audio_Window.h"
#elif TEST_IMAGE
#include "Gui/Image/Image_Window.h"
#else	// Full
#include "Gui/Launch/Launch_Window.h"
#endif

// Brutal Application ------------------------------------------------------- //
class BrutalApplication : public juce::JUCEApplication
{
	public:
		BrutalApplication();
		const juce::String getApplicationName() override;
		const juce::String getApplicationVersion() override;
		bool  moreThanOneInstanceAllowed() override;

		void initialise(const juce::String& commandLine) override;
		void shutdown() override;
		void systemRequestedQuit() override;
		void anotherInstanceStarted(const juce::String& commandLine) override;

	private:
		juce::ScopedPointer<juce::DocumentWindow> launch_it;
};

// - Functions -------------------------------------------------------------- //
BrutalApplication::BrutalApplication()
{
}

const juce::String BrutalApplication::getApplicationName()
{
	return juce::String("Be concerned if you see this");
}

const juce::String BrutalApplication::getApplicationVersion()
{
	return juce::String("v2"); 
}

bool BrutalApplication::moreThanOneInstanceAllowed()
{
	return true;
}

void BrutalApplication::initialise(const juce::String& commandLine)
{
#if TEST_AUDIO
	launch_it = new Audio_Window(juce::String("Audio"));
#elif TEST_IMAGE
	launch_it = new Image_Window(juce::String("Image"));
#else	// Full
	launch_it = new Launch_Window(juce::String("Launch"));
#endif
}

void BrutalApplication::shutdown()
{
	//launch_it = nullptr;
}

void BrutalApplication::systemRequestedQuit()
{
	// This is called when the app is being asked to quit: you can ignore this
	// request and let the app carry on running, or call quit() to allow the app to close.
	quit();
}

void BrutalApplication::anotherInstanceStarted(const juce::String& commandLine)
{
	// When another instance of the app is launched while this one is running,
	// this method is invoked, and the commandLine parameter tells you what
	// the other instance's command-line arguments were.
}

// main() ------------------------------------------------------------------- //
START_JUCE_APPLICATION(BrutalApplication)

//
