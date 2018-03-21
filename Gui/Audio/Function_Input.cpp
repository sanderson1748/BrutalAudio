////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Function_Input.cpp
//

#include "Function_Input.h"

#include "../Gui_Headers.h"
#include "../../Functions/Sine_Function.h"
#include "../../Functions/DegreeZero_Function.h"
#include "../../Functions/DegreeOne_Function.h"

#include "Function_Package.h"
#include "Audio_Window.h"

#if defined DEBUG
#include <iostream>
#endif

// ButtonListener_FunctionInput --------------------------------------------- //
// Delete current Function, and move to next one
void ButtonListener_FunctionInput::buttonClicked(juce::Button* butt)
{
#if 1
	Function_Input*   input_parent    = (Function_Input*)   butt           ->getParentComponent();
	Function_House*   house_parent    = (Function_House*)   input_parent   ->getParentComponent();
	Function_Package* function_parent = (Function_Package*) house_parent   ->getParentComponent();
	Audio_Editor*     editor_parent   = (Audio_Editor*)     function_parent->getParentComponent();

	input_parent->Swap_Funcc();	// this is uncomfortable, but it's better than grabbing index,etc

	editor_parent->InputsSwap_Pressed();
#else
	int choose;
	Function_Input* input_parent = (Function_Input*) butt->getParentComponent();

	if (input_parent->Get_Funcc() == nullptr) 
	{
		std::cout << "its null" << std::endl;
		return;
	}
	
	switch (input_parent->Get_Funcc()->Get_Id())
	{
		case (SINE):	choose = DEG0;		break;
//		case (SINE):	choose = SAW;		break;
//		case (SAW):	choose = DEG0;		break;
		case (DEG0):	choose = DEG1;		break;
		case (DEG1):	choose = SINE;		break;
		default:
		{
			std::cout << "Debug> InputButton_Listener::buttonClicked() bad Function Id" << std::endl;
			break;
		}
	}

	input_parent->New_Funcc(choose);
	input_parent->Refresh_All();
#endif
}

void ButtonListener_FunctionInput::buttonStateChanged(juce::Button* butt)
{
	// pass
}

// EditorListener_FunctionInput --------------------------------------------- //
void EditorListener_FunctionInput::textEditorTextChanged(juce::TextEditor& edit)
{
	Function_Input*   input_parent    = (Function_Input*)   edit.getParentComponent();
	Function_House*   house_parent    = (Function_House*)   input_parent   ->getParentComponent();
	Function_Package* function_parent = (Function_Package*) house_parent   ->getParentComponent();
	Audio_Editor*     editor_parent   = (Audio_Editor*)     function_parent->getParentComponent();

	input_parent->Update_Function();
	input_parent->Update_Helper();

	editor_parent->InputsSwap_Pressed();
}

// This shouldn't do anything - values are updated from TextChanged
void EditorListener_FunctionInput::textEditorReturnKeyPressed(juce::TextEditor& edit)
{
	// pass
}

void EditorListener_FunctionInput::textEditorEscapeKeyPressed(juce::TextEditor& edit)
{
	// pass
}

void EditorListener_FunctionInput::textEditorFocusLost(juce::TextEditor& edit)
{
	// pass
}

// Function_Input ----------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Function_Input::Function_Input()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_Input::Construct" << std::endl;
#endif

	// Audio
	New_Funcc(SINE);	// Sine is default

	// GUI
	// - Listeners
	listen_butt = new ButtonListener_FunctionInput();
	listen_edit = new EditorListener_FunctionInput();

	// - Helper
	label_helper = new juce::Label(juce::String("helper"));
	label_helper->setSize(FUNPACK_LABEL_HELP, LABEL_HEIGHT);
	label_helper->setVisible(true);

	// - Labels
	juce::String namename;
	for (unsigned int i=0; i<INPUTS; i++)
	{
		namename  = "In";
		namename += (int) (i + 1);

		labels[i] = new juce::Label(juce::String(namename), juce::String(namename));
		labels[i]->setSize(LABEL_WIDTH_SMALL, LABEL_HEIGHT);
		labels[i]->setVisible(true);
	}

	// - Editors
	for (unsigned int i=0; i<INPUTS; i++)
	{
		namename  = "In";
		namename += (int) (i + 1);

		inputs[i] = new juce::TextEditor(juce::String(namename));
		inputs[i]->setSize(EDITOR_WIDTH_SMALL, EDITOR_HEIGHT);
		inputs[i]->setVisible(true);

		inputs[i]->addListener((juce::TextEditor::Listener*) listen_edit);
	}

	// - Buttons
	button_type = new juce::TextButton(TEXT_CHANGE);
	button_type->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	button_type->setVisible(true);
	button_type->addListener((juce::Button::Listener*) listen_butt);

	// Finalize
	addAndMakeVisible(label_helper);
	for (unsigned int i=0; i<INPUTS; i++)
	{
		addAndMakeVisible(labels[i]);
		addAndMakeVisible(inputs[i]);
	}
	addAndMakeVisible(button_type);

	resized();

	// Populate with correct values
	Refresh_All();
}

Function_Input::~Function_Input()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Function_Input::Destruct" << std::endl;
#endif

	// Audio
	funcc        = nullptr;

	// GUI
	listen_butt  = nullptr;
	listen_edit  = nullptr;

	label_helper = nullptr;

	for (unsigned int i=0; i<INPUTS; i++)
	{
		labels[i] = nullptr;
		inputs[i] = nullptr;
	}

	button_type = nullptr;
}

// -- Work ------------------------------------------------------------------ //
Base_Function* Function_Input::Get_Funcc()
{
	return funcc;
}

// Change Function to next one in queue
void Function_Input::New_Funcc(int choose)
{
	// Clear Existing
	if (funcc != nullptr)	funcc = nullptr;

	// Create Default new one
	switch (choose)
	{
		case (SINE):	funcc = new Sine_Function();	break;
		//case (SAW):	funcc = new Saw_Function();	break;
		case (DEG0):	funcc = new Deg0_Function();	break;
		case (DEG1):	funcc = new Deg1_Function();	break;
		default:
		{
			std::cout << "Debug> Function_Input::Define_Inputs() bad Function Id" << std::endl;
			break;
		}
	}
}

void Function_Input::Swap_Funcc()
{
	// Error checking?

	switch (funcc->Get_Id())
	{
		case (SINE):	funcc = new Deg0_Function();	break;
		case (DEG0):	funcc = new Deg1_Function();	break;
		case (DEG1):	funcc = new Sine_Function();	break;
		default:
		{
			std::cout << "Debug> InputButton_Listener::buttonClicked() bad Function Id" << std::endl;
			break;
		}
	}

	Refresh_All();
}

// -- Management ------------------------------------------------------------ //
// Calls all of the Input Functions
void Function_Input::Refresh_All()
{
	Define_Inputs();
	Set_Inputs();
	Update_Helper();
}

// Enables/ReadOnlys Editors
// Justifies, too
void Function_Input::Define_Inputs()
{
	unsigned int high_bound;

	switch (funcc->Get_Id())
	{
		case (SINE):	high_bound = NUM_SINE_VALUES;	break;
		case (SAW):	high_bound = NUM_SAW__VALUES;	break;
		case (DEG0):	high_bound = NUM_DEG0_VALUES;	break;
		case (DEG1):	high_bound = NUM_DEG1_VALUES;	break;
		default:
		{
			std::cout << "Debug> Function_Input::Define_Inputs() bad Function Id" << std::endl;
			break;
		}
	}

	// Inputs
	for (unsigned int i=0; i<high_bound; i++)
	{
		inputs[i]->clear();
		inputs[i]->setJustification(juce::Justification(JUSTIFY_RIGHT));
		inputs[i]->setReadOnly(false);
	}

	// Readonly
	for (unsigned int i=high_bound; i<INPUTS; i++)
	{
		inputs[i]->setText(juce::String("--"), false);
		inputs[i]->setJustification(juce::Justification(JUSTIFY_CENTRE));
		inputs[i]->setReadOnly(true);
	}
}

// Sets values in Inputs
void Function_Input::Set_Inputs()
{
	float* in_values = funcc->Get_Values();	// gets array of "unknown" size

//#if defined SHOW_ERRORS
	if (in_values == nullptr)	std::cout << "Debug> Function_Input::Define_Inputs no inputs" << std::endl;
//#endif

	switch (funcc->Get_Id())
	{
		case SINE:
		{
			// NUM_SINE_VALUES = 4
			juce::String str0(in_values[0], FLOAT_PRECISION);
			inputs[0]->setText(str0, false);

			juce::String str1(in_values[1], FLOAT_PRECISION);
			inputs[1]->setText(str1, false);

			juce::String str2(in_values[2], FLOAT_PRECISION);
			inputs[2]->setText(str2, false);

			juce::String str3(in_values[3], FLOAT_PRECISION);
			inputs[3]->setText(str3, false);

			break;
		}
		case SAW:
		{
			// NUM_SAW__VALUES = 5?
			break;
		}
		case DEG0:
		{
			// NUM_DEG0_VALUES = 1
			juce::String str0(in_values[0], FLOAT_PRECISION);
			inputs[0]->setText(str0, false);

			break;
		}
		case DEG1:
		{
			// NUM_DEG1_VALUES = 2
			juce::String str0(in_values[0], FLOAT_PRECISION);
			inputs[0]->setText(str0, false);

			juce::String str1(in_values[1], FLOAT_PRECISION);
			inputs[1]->setText(str1, false);

			break;
		}
		default:
		{
			std::cout << "Debug> Function_Input::Set_Inputs() bad Function Id" << std::endl;
			break;
		}
	}
}

// Update Helper String
void Function_Input::Update_Helper()
{
	label_helper->setText(funcc->Get_String(), juce::NotificationType(0));	// do not send notification
}

// Update values within Function Struct
#define FLOAT_NULL	0
void Function_Input::Update_Function()
{
	float f0, f1, f2, f3, f4;
	juce::String str;

	switch (funcc->Get_Id())
	{
		case (SINE):
		{
			str = inputs[0]->getText();	f0 = str.getFloatValue();
			str = inputs[1]->getText();	f1 = str.getFloatValue();
			str = inputs[2]->getText();	f2 = str.getFloatValue();
			str = inputs[3]->getText();	f3 = str.getFloatValue();

			f4 = FLOAT_NULL;

			break;
		}
		case (SAW):
		{
			break;
		}
		case (DEG0):
		{
			str = inputs[0]->getText();	f0 = str.getFloatValue();

			f1 = FLOAT_NULL;
			f2 = FLOAT_NULL;
			f3 = FLOAT_NULL;
			f4 = FLOAT_NULL;

			break;
		}
		case (DEG1):
		{
			str = inputs[0]->getText();	f0 = str.getFloatValue();
			str = inputs[1]->getText();	f1 = str.getFloatValue();

			f2 = FLOAT_NULL;
			f3 = FLOAT_NULL;
			f4 = FLOAT_NULL;

			break;
		}
		default:
		{
			std::cout << "Debug> Function_Input::Update_Function() bad Function Id" << std::endl;
			break;
		}
	}

	funcc->Set(f0, f1, f2, f3, f4);
}

// -- JUCE ------------------------------------------------------------------ //
void Function_Input::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void Function_Input::resized()
{
	// Top Side
	label_helper->setTopLeftPosition(GUI_ZERO          , GUI_ZERO);
	button_type ->setTopLeftPosition(FUNPACK_LABEL_HELP, GUI_ZERO);

	// Bottom Side
	for (unsigned int i=0; i<INPUTS; i++)
	{
		labels[i]->setTopLeftPosition(((LABEL_WIDTH_SMALL+EDITOR_WIDTH_SMALL) * i                    ), LABEL_HEIGHT);
		inputs[i]->setTopLeftPosition(((LABEL_WIDTH_SMALL+EDITOR_WIDTH_SMALL) * i + LABEL_WIDTH_SMALL), LABEL_HEIGHT);
	}
}

//
