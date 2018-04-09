////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Function_Input.h
//
// Boy that has the inputs for the Functions
//

#ifndef __FUNCTION_INPUT__
#define __FUNCTION_INPUT__

#include <vector>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"
#include "../Gui_Headers.h"	// just for INPUTS, which is going to change/move anyways

#include "../../Functions/Base_Function.h"

class ButtonListener_FunctionInput : public juce::Button::Listener
{
	public:
	private:
		void buttonClicked(juce::Button*);
		void buttonStateChanged(juce::Button*);		
};

class EditorListener_FunctionInput : public juce::TextEditor::Listener
{
	private:
	public:
		void textEditorTextChanged(juce::TextEditor&);
		void textEditorReturnKeyPressed(juce::TextEditor&);
		void textEditorEscapeKeyPressed(juce::TextEditor&);
		void textEditorFocusLost(juce::TextEditor&);
};

class Function_Input : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Function_Input);

		// General
	       unsigned int list_id;

		// Audio
		Base_Function* funcc;

		// GUI
		juce::ScopedPointer<ButtonListener_FunctionInput> listen_butt;
		juce::ScopedPointer<EditorListener_FunctionInput> listen_edit;

		juce::ScopedPointer<juce::Label> label_helper;

		juce::ScopedPointer<juce::Label> labels[INPUTS];
		juce::ScopedPointer<juce::TextEditor> inputs[INPUTS];

		juce::ScopedPointer<juce::TextButton> button_type;
		juce::ScopedPointer<juce::TextButton> button_sub;

	public:
		// General
		Function_Input(unsigned int, Base_Function*);
		~Function_Input(void);

		// Work 
		unsigned int Get_Id(void);
		void Set_Id(unsigned int);
		void New_Funcc(int);
		void Swap_Funcc(void);

		// Management
		void Refresh_All(void);
		void Define_Inputs(void);
		void Set_Inputs(void);
		void Update_Helper(void);
		void Update_Function(void);

		// JUCE
		void paint(juce::Graphics& g) override;
		void resized(void) override;
};

#endif

//
