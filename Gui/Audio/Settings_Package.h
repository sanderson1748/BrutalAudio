////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Settings_Package.h
//
// Boy that handles output file options
//

#ifndef __SETTINGS_PACKAGE__
#define __SETTINGS_PACKAGE__

#include <juce_gui_basics/juce_gui_basics.h>
#include "../../Headers.h"

#if 0//defined BITS_64
#define BITS_PER_SAMPLE		64
#define BYTES_PER_SAMPLE	8
#else // BITS_32
#define BITS_PER_SAMPLE		32
#define BYTES_PER_SAMPLE	4
#endif

#define AUDIO_DEPTH_64		64
#define INT_MAX_VALUE_64	0x7fffffffffffffffffffffff

#define AUDIO_DEPTH_32		32
#define INT_MAX_VALUE_32	0x7fffffff

#define SAMPLE_RATE_192		192000
#define SAMPLE_RATE_96		96000
#define SAMPLE_RATE_48		48000

enum
{
	MONO_L,
	MONO_R,
	STEREO,
};

typedef struct
{
	float    max_amplitude;	
	uint32_t file_time_ms;

	uint32_t sample_rate;
	uint32_t audio_depth;	// update name
	uint32_t audio_format;

	bool     round_tail;
} Settings_Struct;

class ButtonListener_SettingsPackage : public juce::Button::Listener
{
	private:
	public:
		void buttonClicked(juce::Button*);
		void buttonStateChanged(juce::Button*);
};

class EditorListener_SettingsPackage : public juce::TextEditor::Listener
{
	private:
	public:
		void textEditorTextChanged(juce::TextEditor&);
		void textEditorReturnKeyPressed(juce::TextEditor&);
		void textEditorEscapeKeyPressed(juce::TextEditor&);
		void textEditorFocusLost(juce::TextEditor&);
};

class Settings_Package : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Settings_Package);

		// Settings
		Settings_Struct* settings_guy;

		// Controls
		juce::ScopedPointer<ButtonListener_SettingsPackage> listen_butt;
		juce::ScopedPointer<EditorListener_SettingsPackage> listen_edit;

		juce::ScopedPointer<juce::Label>        label_samples;
		juce::ScopedPointer<juce::TextEditor>   edit_samples;
		juce::ScopedPointer<juce::TextButton>   butt_samples;

		juce::ScopedPointer<juce::Label>        label_depth;
		juce::ScopedPointer<juce::TextEditor>   edit_depth;
		juce::ScopedPointer<juce::TextButton>   butt_depth;

		juce::ScopedPointer<juce::Label>        label_channels;
		juce::ScopedPointer<juce::TextEditor>   edit_channels;
		juce::ScopedPointer<juce::TextButton>   butt_channels;

		juce::ScopedPointer<juce::ToggleButton> butt_roundtail;

	public:
		// General
		Settings_Package(void);
		~Settings_Package(void);

		// Work
		void Update_Inputs(void);	// change to pass Settings_Struct* ?

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
