////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Graph_Package.h
//
// Package for grapher
// In progress; not a lot to say yet. Has some inputs, as well
//

#ifndef __GRAPH_PACKAGE__
#define __GRAPH_PACKAGE__

#include <vector>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"
#include "../../Functions/Base_Function.h"
#include "Graph_Graph.h"
#include "Settings_Package.h" // for Settings_Struct

class EditorListener_GraphPackage : public juce::TextEditor::Listener
{
	private:
	public:
		void textEditorTextChanged(juce::TextEditor&);
		void textEditorReturnKeyPressed(juce::TextEditor&);
		void textEditorEscapeKeyPressed(juce::TextEditor&);
		void textEditorFocusLost(juce::TextEditor&);
};

class Graph_Package : public juce::Component
{
	private: 
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Graph_Package);

		// Graph_Graph
		juce::ScopedPointer<Graph_Graph> graph_fella;

		// Controls
		juce::ScopedPointer<EditorListener_GraphPackage> listen_edit;

		juce::ScopedPointer<juce::Label> label_bounds;
		juce::ScopedPointer<juce::TextEditor> edit_bounds;
		juce::ScopedPointer<juce::Label> label_time;
		juce::ScopedPointer<juce::TextEditor> edit_time;

		juce::ScopedPointer<juce::Label> label_hit;

		// Extra
		// nuthin yet

	public:
		// General
		Graph_Package(void);
		~Graph_Package(void);

		// Work
		float Grab_Bounds(void);
		unsigned int Grab_TimeMs(void);

		void Update_Inputs(void);	// Change to Settings_Struct* ?
		void Update_Graph(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
