////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Graph_Package.cpp
// 

#include "Graph_Package.h"

#include "../Gui_Headers.h"

#include "Audio_Window.h"

#if defined DEBUG
#include <iostream>
#endif

#define TEXT_BOUNDS	"High Bound:" 
#define TEXT_TIME	"File Time:"

// EditorListener_GraphPackage ---------------------------------------------- //
void EditorListener_GraphPackage::textEditorTextChanged(juce::TextEditor& edit)
{
	Graph_Package* graph_parent  = (Graph_Package*) edit.getParentComponent();
	Audio_Editor*  editor_parent = (Audio_Editor*)  graph_parent->getParentComponent();

	if      (edit.getName() == TEXT_BOUNDS)	editor_parent->GraphBounds_Pressed();
	else if (edit.getName() == TEXT_TIME)	editor_parent->GraphTime_Pressed();
	//else					throw;
}

void EditorListener_GraphPackage::textEditorReturnKeyPressed(juce::TextEditor& edit)
{
	std::cout << "Debug> Graph -> Return" << std::endl;
}

void EditorListener_GraphPackage::textEditorEscapeKeyPressed(juce::TextEditor& edit)
{
	std::cout << "Debug> Graph -> Escape" << std::endl;
}

void EditorListener_GraphPackage::textEditorFocusLost(juce::TextEditor& edit)
{
	std::cout << "Debug> Graph -> Focus Lost" << std::endl;
}

// Graph_Package ------------------------------------------------------------ //
// -- General --------------------------------------------------------------- //
Graph_Package::Graph_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Graph_Package::Construct" << std::endl;
#endif

	// Graph_Graph
	graph_fella = new Graph_Graph();
	graph_fella->setSize(GRAPH_GRAPH_WIDTH, GRAPH_GRAPH_HEIGHT);
	graph_fella->setVisible(true);

	// Controls
	// - Listener
	listen_edit = new EditorListener_GraphPackage();

	// - Bounds
	label_bounds = new juce::Label(juce::String(TEXT_BOUNDS), juce::String(TEXT_BOUNDS));
	label_bounds->setSize(LABEL_WIDTH_MEDIUM, LABEL_HEIGHT);
	label_bounds->setVisible(true);

	edit_bounds = new juce::TextEditor(TEXT_BOUNDS);
	edit_bounds->setSize(EDITOR_WIDTH_SMALL, EDITOR_HEIGHT);
	edit_bounds->setVisible(true);
	edit_bounds->setJustification(juce::Justification(JUSTIFY_RIGHT));
	edit_bounds->addListener((juce::TextEditor::Listener*) listen_edit);

	// - Time
	label_time = new juce::Label(juce::String(TEXT_TIME), juce::String(TEXT_TIME));
	label_time->setSize(LABEL_WIDTH_MEDIUM, LABEL_HEIGHT);
	label_time->setVisible(true);

	edit_time = new juce::TextEditor(TEXT_TIME);
	edit_time->setSize(EDITOR_WIDTH_SMALL, EDITOR_HEIGHT);
	edit_time->setVisible(true);
	edit_time->setJustification(juce::Justification(JUSTIFY_RIGHT));
	edit_time->addListener((juce::TextEditor::Listener*) listen_edit);

	label_hit = new juce::Label(juce::String("label_hit"));
	label_hit->setSize(LABEL_WIDTH_SMALL, LABEL_HEIGHT);
	label_hit->setVisible(true);

	// Go
	resized();

	addAndMakeVisible(graph_fella);

	addAndMakeVisible(label_bounds);
	addAndMakeVisible(edit_bounds);
	addAndMakeVisible(label_time);
	addAndMakeVisible(edit_time);
	addAndMakeVisible(label_hit);
}

Graph_Package::~Graph_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Graph_Package::Destruct" << std::endl;
#endif

	// Graph_Graph
	graph_fella  = nullptr;

	// Controls
	listen_edit  = nullptr;

	label_bounds = nullptr;
	edit_bounds  = nullptr;
	label_time   = nullptr;
	edit_time    = nullptr;

	label_hit    = nullptr;

	// Extra
	// - pass
}

// -- Work ------------------------------------------------------------------ //
// ditch?
void Graph_Package::Add_Entry(Base_Function* new_funcc)
{
}

// ditch?
void Graph_Package::Remove_Entry(unsigned int choose)
{
}

// Grab from editors
float Graph_Package::Grab_Bounds()
{
	juce::String str = edit_bounds->getText();
	return str.getFloatValue();
}

float Graph_Package::Grab_TimeMs()
{
	juce::String str = edit_time->getText();
	return (str.getFloatValue() * 1000);
}

void Graph_Package::Update_Inputs() // change to pass Settings_Struct* ?
{
	Audio_Editor* editor_parent = (Audio_Editor*) this->getParentComponent();
	Settings_Struct* tmp_settings = editor_parent->Get_Settings();

	edit_bounds->setText(juce::String((float)  tmp_settings->max_amplitude       , FLOAT_PRECISION), false);
	edit_time  ->setText(juce::String((float) (tmp_settings->file_time_ms / 1000), FLOAT_PRECISION), false);
}

// Update everything
void Graph_Package::Update_Graph()
{
	static int yes = 0;
	juce::String tmp(yes);
	yes++;
	label_hit->setText(tmp, juce::NotificationType(0));

	graph_fella->Hit_It();
}

// -- JUCE ------------------------------------------------------------------ //
void Graph_Package::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::green);
}

void Graph_Package::resized()
{
	// Graph_Graph
	graph_fella->setTopLeftPosition(GUI_ZERO, GUI_ZERO);
	graph_fella->resized();

	// Controls
	// - tmp like this
	label_bounds->setTopLeftPosition((0*LABEL_WIDTH_MEDIUM + 0*EDITOR_WIDTH_SMALL), GRAPH_GRAPH_HEIGHT);
	edit_bounds ->setTopLeftPosition((1*LABEL_WIDTH_MEDIUM + 0*EDITOR_WIDTH_SMALL), GRAPH_GRAPH_HEIGHT);

	label_time  ->setTopLeftPosition((1*LABEL_WIDTH_MEDIUM + 1*EDITOR_WIDTH_SMALL), GRAPH_GRAPH_HEIGHT);
	edit_time   ->setTopLeftPosition((2*LABEL_WIDTH_MEDIUM + 1*EDITOR_WIDTH_SMALL), GRAPH_GRAPH_HEIGHT);

	label_hit   ->setTopLeftPosition((2*LABEL_WIDTH_MEDIUM + 2*EDITOR_WIDTH_SMALL), GRAPH_GRAPH_HEIGHT);
}

//
