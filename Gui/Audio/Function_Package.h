////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Function_Package.h
//
// Function Controls -> Function List(mostly gui) + Add/Remove
//

#ifndef __FUNCTION_PACKAGE__
#define __FUNCTION_PACKAGE__

#include <vector>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"
#include "Graph_Package.h"
#include "Function_Input.h"

class ButtonListener_FunctionPackage : public juce::Button::Listener
{
	private:
	public:
		void buttonClicked(juce::Button*);
		void buttonStateChanged(juce::Button*);
};

class Function_Package : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Function_Package);

		// Inputs
		std::vector<juce::ScopedPointer<Function_Input>> input_list;

		// Controls
		juce::ScopedPointer<ButtonListener_FunctionPackage> listen_butt;
		juce::ScopedPointer<juce::TextButton> butt_add;

	public:
		// General
		Function_Package();
		~Function_Package(void);

		// Work
		void Add_Input(unsigned int, Base_Function*);
		void Sub_Input(unsigned int);
		void Set_Ids(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
