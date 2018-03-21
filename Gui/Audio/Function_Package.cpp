////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Function_Package.cpp
//

#include "Function_Package.h"

#include "../Gui_Headers.h"

#include "../../Files/Wav_File.h"
#include "Audio_Window.h"

#if defined DEBUG
#include <iostream>
#endif

#define TEXT_ADD	"Add"
#define TEXT_SUB  	"Remove"

// ButtonListener_FunctionPackage ------------------------------------------- //
void ButtonListener_FunctionPackage::buttonClicked(juce::Button* butt)
{
#if 1
	Function_Package* function_parent = (Function_Package*) butt           ->getParentComponent();
	Audio_Editor*     editor_parent   = (Audio_Editor*)     function_parent->getParentComponent();

	if      (butt->getName() == TEXT_ADD)	editor_parent->FunctionsAdd_Pressed();
	else if (butt->getName() == TEXT_SUB)	editor_parent->FunctionsSub_Pressed();
	//else					throw;
#else
	Function_Package* parent = (Function_Package*) butt->getParentComponent();
	juce::String choose = ((juce::TextButton*) butt)->getButtonText();

	if (choose == TEXT_ADD)
	{
		// Function_Package calls Function_House::Add_Function()
		// then calls Graph_Package::Add_Entry(..);
		parent->Add_Function();	
	}
	else if (choose == TEXT_SUB)
	{
		// Function_Package calls Function_House::Remove_Function()
		// then calls Graph_Package::Remove_Entry(..);
		parent->Remove_Function(0);
	}
	else
	{
		std::cout << "FunctionHouse_Listener problems" << std::endl;
	}
#endif
}

void ButtonListener_FunctionPackage::buttonStateChanged(juce::Button* butt)
{
}

// Function_House ----------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Function_House::Function_House()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_House::Construct" << std::endl;
#endif
}

Function_House::~Function_House()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_House::Destruct" << std::endl;
#endif

	// Functions
	functions.clear();
}

// -- Work ------------------------------------------------------------------ //
// Resized is called by Audio_Editor
void Function_House::Add_Entry(Function_Input* in_input)
{
	unsigned int index = entry_list.size();

	// Create
	entry_list.push_back(in_input);
	entry_list[index]->setSize(FUNCTION_INPUT_WIDTH, FUNCTION_INPUT_HEIGHT);
	entry_list[index]->setVisible(true);

	// Enable
	addAndMakeVisible(entry_list[index]);
}

// Just pops
// - Input will choose which one to pop, but not now
// Resized is called by Audio_Editor
void Function_House::Sub_Entry(unsigned int this_does_nothing_for_now)
{
	entry_list.pop_back();
}

// -- Remove ---------------------------------------------------------------- //
Base_Function* Function_House::Get_BaseFunction(unsigned int choose)
{
	return entry_list[choose]->Get_Funcc();
}

Base_Function* Function_House::Add_Input()
{
	unsigned int hold = functions.size();

	// Create Function
	functions.push_back(new Function_Input());
	functions[hold]->setSize(FUNCTION_INPUT_WIDTH, FUNCTION_INPUT_HEIGHT);
	functions[hold]->setVisible(true);
	
	// Place Modules
	resized();

	// Enable Modules
	addAndMakeVisible(functions[hold]);

	// Return address
	return functions[hold]->Get_Funcc();
}

void Function_House::Remove_Input(unsigned int choose)
{
	if (choose > functions.size())	std::cout << "Function_House::Remove_Function error" << std::endl;

	functions.pop_back();
}

// -- JUCE ------------------------------------------------------------------ //
void Function_House::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::pink);
}

void Function_House::resized()
{
	for (unsigned int i=0; i<entry_list.size(); i++)
	{
		entry_list[i]->setTopLeftPosition(GUI_ZERO, (FUNCTION_INPUT_HEIGHT * i));
		entry_list[i]->resized();
	}
}

// Function_Package --------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Function_Package::Function_Package(Graph_Package* in_graph)
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_Package::Construct" << std::endl;
#endif

	// FunctionPackage_Listener
	listen_butt = new ButtonListener_FunctionPackage();

	// Graph
#if defined DEBUG
	if (in_graph == nullptr)	std::cout << "Error> Function_Package::Set_Graph() null pointer" << std::endl;
#endif

	// Function House
	housing = new Function_House();
	housing->setSize(FUNCTION_HOUSE_WIDTH, FUNCTION_HOUSE_HEIGHT);
	housing->setVisible(true);

	// Buttons
	// - Add
	butt_add = new juce::TextButton(TEXT_ADD);
	butt_add->setSize(BUTTON_WIDTH_BIG, BUTTON_HEIGHT);
	butt_add->setVisible(true);

	butt_add->addListener((juce::Button::Listener*) listen_butt );

	// - Remove
	butt_sub = new juce::TextButton(TEXT_SUB);
	butt_sub->setSize(BUTTON_WIDTH_BIG, BUTTON_HEIGHT);
	butt_sub->setVisible(true);

	butt_sub->addListener((juce::Button::Listener*) listen_butt );

	// Place Modules
	resized();

	// Enable Modules
	addAndMakeVisible(housing);
	addAndMakeVisible(butt_add);
	addAndMakeVisible(butt_sub);
}

Function_Package::~Function_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_Package::Destruct" << std::endl;
#endif

	// Delete Listeners
	listen_butt  = nullptr;

	// Delete Modules
	housing  = nullptr;
	butt_add = nullptr;
	butt_sub = nullptr;
}

// -- Work ------------------------------------------------------------------ //
// Just pass to Function_House
// - Function_Package doesn't really care about this one
// Resized is called by Audio_Editor
void Function_Package::Add_Input(Function_Input* in_input)
{
	housing->Add_Entry(in_input);
}

// Just pops
// - Input will choose which one to pop, but not now
// - Function_Package doesn't really care about this one
// Resized is called by Audio_Editor
void Function_Package::Sub_Input(unsigned int this_does_nothing_for_now)
{
	housing->Sub_Entry(this_does_nothing_for_now);
}

// -- JUCE ------------------------------------------------------------------ //
void Function_Package::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::blue);
}

void Function_Package::resized()
{
	housing->resized();

	housing ->setTopLeftPosition(GUI_ZERO        , GUI_ZERO);
	butt_add->setTopLeftPosition(GUI_ZERO        , FUNCTION_HOUSE_HEIGHT);
	butt_sub->setTopLeftPosition(BUTTON_WIDTH_BIG, FUNCTION_HOUSE_HEIGHT);
}

//
