////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
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

class Function_House : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Function_House);

		std::vector<Function_Input*> entry_list;

		std::vector<juce::ScopedPointer<Function_Input>> functions;

	public:
		// General
		Function_House(void);
		~Function_House(void);

		// Work
		void Add_Entry(Function_Input*);
		void Sub_Entry(unsigned int);

		// Remove
		Base_Function* Get_BaseFunction(unsigned int);
		Base_Function* Add_Input(void);
		void Remove_Input(unsigned int);

		// JUCE
		void paint(juce::Graphics&);
		void resized(void);
};

class Function_Package : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Function_Package);

		// Function_House
		juce::ScopedPointer<Function_House>   housing;

		// Controls
		juce::ScopedPointer<ButtonListener_FunctionPackage> listen_butt;

		juce::ScopedPointer<juce::TextButton> butt_add;
		juce::ScopedPointer<juce::TextButton> butt_sub;

		// Extra
		Graph_Package* graph_pointer;

	public:
		// General
		Function_Package(Graph_Package*);
		~Function_Package(void);

		// Work
		void Add_Input(Function_Input*);
		void Sub_Input(unsigned int);	// unsigned int is for future; just pops for now

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
