////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
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

#define TEXT_ADD	"Add Function"

// ButtonListener_FunctionPackage ------------------------------------------- //
void ButtonListener_FunctionPackage::buttonClicked(juce::Button* butt)
{
	Function_Package* function_parent = (Function_Package*) butt           ->getParentComponent();
	Audio_Editor*     editor_parent   = (Audio_Editor*)     function_parent->getParentComponent();

	if      (butt->getName() == TEXT_ADD)	editor_parent->FunctionsAdd_Pressed();
	//else					throw;
}

void ButtonListener_FunctionPackage::buttonStateChanged(juce::Button* butt)
{
}

// Function_Package --------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Function_Package::Function_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_Package::Construct" << std::endl;
#endif

	// FunctionPackage_Listener
	listen_butt = new ButtonListener_FunctionPackage();

	// Buttons
	// - Add
	butt_add = new juce::TextButton(TEXT_ADD);
	butt_add->setSize(FUNCTION_PACKAGE_WIDTH, BUTTON_HEIGHT);	// FUNCTION_PACK.. is temp
	butt_add->setVisible(true);

	butt_add->addListener((juce::Button::Listener*) listen_butt );

	// Enable Modules
	addAndMakeVisible(butt_add);
}

Function_Package::~Function_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_Package::Destruct" << std::endl;
#endif

	// Controls
	listen_butt  = nullptr;
	butt_add = nullptr;

	// Inputs
	input_list.clear();
}

// -- Work ------------------------------------------------------------------ //
// Set_Ids is NOT called here
void Function_Package::Add_Input(unsigned int in_choose, Base_Function* in_funcc)
{
	// Create
	input_list.insert(input_list.begin() + in_choose, new Function_Input(in_choose, in_funcc));
	input_list[in_choose]->setSize(FUNCTION_INPUT_WIDTH, FUNCTION_INPUT_HEIGHT);
	input_list[in_choose]->setVisible(true);

	// Update IDs 
	// - Not necessary for Add, but that's okay
	Set_Ids();

	// Enable
	addAndMakeVisible(input_list[in_choose]);
}

// Update_Ids is NOT called here
void Function_Package::Sub_Input(unsigned int in_choose)
{
	// Remove Entry
	input_list.erase(input_list.begin() + in_choose);

	// Update IDs 
	Set_Ids();
}

// Notes
void Function_Package::Set_Ids()
{
	// Temp like this?
	for (unsigned int i=0; i<input_list.size(); i++)	input_list[i]->Set_Id(i);
}

// -- JUCE ------------------------------------------------------------------ //
void Function_Package::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::blue);
}

void Function_Package::resized()
{
	for (unsigned int i=0; i<input_list.size(); i++)
	{
		input_list[i]->Refresh_All();
		input_list[i]->setTopLeftPosition(GUI_ZERO, (FUNCTION_INPUT_HEIGHT * i));
		input_list[i]->resized();
	}

	butt_add->setTopLeftPosition(GUI_ZERO, FUNCTION_HOUSE_HEIGHT);
}

//
