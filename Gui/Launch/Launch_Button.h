////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// Launch_Button.h
//
// Buttons and Listeners for Launch Window
//
// This is old; will move/merge/etc
//

#ifndef __LAUNCH_BUTTON__
#define __LAUNCH_BUTTON__

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"

class Launch_Listener : public juce::Button::Listener
{
	private:
	public:
		void buttonClicked(juce::Button*);
		void buttonStateChanged(juce::Button*);
};

class Launch_Button : public juce::TextButton
{
	private:
		int id;

	public:
		juce::ScopedPointer<juce::DocumentWindow> fella;

		Launch_Button(const char*, juce::DocumentWindow*);
		void Set_Id(int);
		int  Get_Id(void);
};

#endif

//
