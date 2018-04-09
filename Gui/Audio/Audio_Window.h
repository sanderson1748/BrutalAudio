////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Audio_Window.h
//
// Audio Guy
//
// This file has Window and Editor
//

#ifndef __AUDIO_WINDOW__
#define __AUDIO_WINDOW__

#include <vector>
#include <thread>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"

#include "Graph_Package.h"
#include "Control_Package.h"
#include "Function_Package.h"
#include "Settings_Package.h"
#include "../../Files/Audio_File.h"
#include "../../Functions/Base_Function.h"

// Window is GUI base component thingy needed by JUCE main, holds Editor
class Audio_Window : public juce::DocumentWindow
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Audio_Window);

	public:
		Audio_Window(juce::String);
		void closeButtonPressed(void) override;
};

// Editor 
// - Has Modules
// - Runs ALL functions from controls
class Audio_Editor : public juce::Component
{
	private:
		// For JUCE
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Audio_Editor);

		// Threading
#if 0	// later
		std::thread export_thread;
#endif

		// Data
		juce::ScopedPointer<Audio_File>       file_output;
		juce::ScopedPointer<Settings_Struct>  file_settings;
		std::vector<juce::ScopedPointer<Base_Function>> function_list;

		// Packages
		juce::ScopedPointer<Graph_Package>    graphs;
		juce::ScopedPointer<Control_Package>  controls;
		juce::ScopedPointer<Function_Package> functions;
		juce::ScopedPointer<Settings_Package> settings;

	public:
		// General
		Audio_Editor(void);
		~Audio_Editor(void);

		// Work 
		Audio_File*      Get_File(void);
		Settings_Struct* Get_Settings(void);

		float Find_AbsMax(void);	// may create member variable
		float Evaluate_All(float);

		// From Graph Package
		void GraphBounds_Pressed(void);
		void GraphTime_Pressed(void);

		// From Control Package
		void ControlStream_Pressed(void);
		void ControlExport_Pressed(void);
		void ControlSave_Pressed(void);
		void ControlQuit_Pressed(void);

		// From Function Package
		void FunctionsAdd_Pressed(void);
		void InputsSwap_Pressed(unsigned int);
		void InputsSub_Pressed(unsigned int);
		void InputsEditor_Changed(void);

		// From Settings Package
		void SettingsSamples_Pressed(void);
		void SettingsDepth_Pressed(void);
		void SettingsFormat_Pressed(void);
		void SettingsRound_Pressed(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
