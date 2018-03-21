////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Control_Package.h
//
// Has Buttons/etc for Go, Save, Load, etc
//

#ifndef __FILE_PACKAGE__
#define __FILE_PACKAGE__

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"

class ButtonListener_ControlPackage : public juce::Button::Listener
{
	private:
	public:
		void buttonClicked(juce::Button*);
		void buttonStateChanged(juce::Button*);
};

class Control_Package : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Control_Package);

		juce::ScopedPointer<ButtonListener_ControlPackage> listen_butt;

		juce::ScopedPointer<juce::TextButton> butt_play;
		juce::ScopedPointer<juce::TextButton> butt_export;
		juce::ScopedPointer<juce::TextButton> butt_save;
		juce::ScopedPointer<juce::TextButton> butt_finish;

	public:
		// General
		Control_Package(void);
		~Control_Package(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
