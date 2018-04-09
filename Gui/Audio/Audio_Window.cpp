////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Audio_Window.cpp
//

#include "Audio_Window.h"

#include "../Gui_Headers.h"

#include "../../Files/Wav_File.h"
#include "../../Functions/Sine_Function.h"
#include "../../Functions/DegreeZero_Function.h"
#include "../../Functions/DegreeOne_Function.h"

#if defined DEBUG
#include <iostream>
#endif

// Audio_Window ------------------------------------------------------------- //
Audio_Window::Audio_Window(juce::String name) : DocumentWindow(name, juce::Colours::black, juce::DocumentWindow::allButtons)
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Audio_Window::Contruct" << std::endl;
#endif

	// Create Editor
	//setContentOwned(new Audio_Editor(), true);	// Lin?
	setContentOwned(new Audio_Editor(), false);	// OSX?

	// Configure Window
	setUsingNativeTitleBar(true);
	setVisible(true);
	setResizable(false,false);
	setSize(AUDIO_WINDOW_WIDTH, AUDIO_WINDOW_HEIGHT);
}

void Audio_Window::closeButtonPressed()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Audio_Window::closeButtonPressed" << std::endl;
#endif

#if TEST_AUDIO
	juce::JUCEApplication::getInstance()->systemRequestedQuit();
#else
	delete this;
#endif
}

// Audio_Editor ------------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Audio_Editor::Audio_Editor()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Audio_Editor::Contruct" << std::endl;
#endif

	// Data
	// - Files; set as nothing for now
	file_output = new Wav_File();

	// - Settings
	file_settings = new Settings_Struct;

	file_settings->max_amplitude = 1.0;
	file_settings->file_time_ms  = 5000;
	file_settings->sample_rate   = SAMPLE_RATE_48;
	file_settings->audio_depth   = AUDIO_DEPTH_32;
	file_settings->audio_format  = MONO_L;
	file_settings->round_tail    = false;

	// - Functions
	// pass

	// Packages
	// - Graph Package
	graphs = new Graph_Package();
	graphs->setSize(GRAPH_PACKAGE_WIDTH, GRAPH_PACKAGE_HEIGHT);
	graphs->setVisible(true);

	// - Command Package
	controls = new Control_Package();
	controls->setSize(CONTROL_PACKAGE_WIDTH, CONTROL_PACKAGE_HEIGHT);
	controls->setVisible(true);

	// - Function Package
	functions = new Function_Package();
	functions->setSize(FUNCTION_PACKAGE_WIDTH, FUNCTION_PACKAGE_HEIGHT);
	functions->setVisible(true);

	// - Settings Package
	settings = new Settings_Package();
	settings->setSize(SETTINGS_PACKAGE_WIDTH, SETTINGS_PACKAGE_HEIGHT);
	settings->setVisible(true);

	// Finalize
	// - Move these?
	addAndMakeVisible(graphs);
	addAndMakeVisible(controls);
	addAndMakeVisible(functions);
	addAndMakeVisible(settings);

	graphs  ->Update_Graph();
	graphs  ->Update_Inputs();
	settings->Update_Inputs();

	resized();
}

Audio_Editor::~Audio_Editor()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Audio_Editor::Destruct" << std::endl;
#endif

	// Maybe reverse these?
	// Data
	file_output   = nullptr;
	file_settings = nullptr;
	function_list.clear();

	// Packages
	graphs    = nullptr;
	controls  = nullptr;
	functions = nullptr;
	settings  = nullptr;
}

// -- Work ------------------------------------------------------------------ //
Audio_File* Audio_Editor::Get_File()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::Get_File()" << std::endl;
#endif

	return file_output;
}

Settings_Struct* Audio_Editor::Get_Settings()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::Get_Settings()" << std::endl;
#endif

	return file_settings;
}

// Returns absolute value of largest value generated
// Is going to be a hella mess
// Also, think about creating a member variable for absolute max
float Audio_Editor::Find_AbsMax()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::Find_AbsMax()" << std::endl;
#endif

	float max = 0.0;

	unsigned int total_samples = file_settings->file_time_ms * file_settings->sample_rate / 1000;
	unsigned int grind_rate = 64; // tmp

	float tmp, theta;

	for (unsigned int i=0; i<total_samples; i+=grind_rate)
	{
		theta = ((float) i) / file_settings->sample_rate;
		tmp = abs(Evaluate_All(theta));
		if (tmp > max)		max = tmp;
	}

	/////////////////////
	// OR 
	// Audio_Editor::abs_max = max;
	/////////////////////
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Max = " << max << std::endl;
#endif
	return max;
}

// Is buggy?
float Audio_Editor::Evaluate_All(float theta)
{
#if 0//defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::Evaluate_All()" << std::endl;
#endif

	float sum = 0;
	for (size_t i=0; i<function_list.size(); i++)
	{
		sum += function_list[i]->Evaluate_Float(theta);
	}
	return sum;
}

// -- From Graph Package ---------------------------------------------------- //
void Audio_Editor::GraphBounds_Pressed()
{
	float tmp_bounds = graphs->Grab_Bounds();

	if (file_settings->max_amplitude != tmp_bounds)
	{
		file_settings->max_amplitude = tmp_bounds;
		graphs->Update_Graph();
	}
}

void Audio_Editor::GraphTime_Pressed()
{
	unsigned int tmp_time_ms = graphs->Grab_TimeMs();

	if (file_settings->file_time_ms != tmp_time_ms)
	{
		file_settings->file_time_ms = tmp_time_ms;
		graphs->Update_Graph();
	}
}

// -- From Control Package -------------------------------------------------- //
void Audio_Editor::ControlStream_Pressed()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::ControlStream_Pressed()" << std::endl;
#endif
}

void Audio_Editor::ControlExport_Pressed()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::ControlExport_Pressed()" << std::endl;
#endif

#if 0
	// thread this!
	// - also, syntax
	if (thread_still_running)	return;

	export_thread(file_output->To_File(file_settings, (void*) &function_list);
#else
	file_output->To_File(file_settings, (void*) &function_list);
#endif
}

void Audio_Editor::ControlSave_Pressed()
{
#if defined SHOW_FUNCTIONS
	std::cout << "Debug> Audio_Editor::ControlSave_Pressed()" << std::endl;
#endif
}

// Will be removed
void Audio_Editor::ControlQuit_Pressed()
{
	// Watch out for Image Windows/Launch boys, too
	Audio_Window* window_parent = (Audio_Window*) getParentComponent();
	window_parent->closeButtonPressed();
}

// -- From Function Package ------------------------------------------------- //
// Create Input, add to Function_Package(House)
// Calls Function_Package resized
void Audio_Editor::FunctionsAdd_Pressed()
{
	size_t hold = function_list.size();

	if (hold >= MAX_FUNCTIONS)	return;

	function_list.push_back(new Sine_Function);	// sine is defualt
	functions->Add_Input(hold, function_list[hold]);

	functions->resized();
	graphs->Update_Graph();
}

// Notes
void Audio_Editor::InputsSwap_Pressed(unsigned int in_choose)
{
	// Check
	if (function_list.size() == 0)	return;

	// Update function_list
	switch (function_list[in_choose]->Get_Id())
	{
		case (SINE):
		{
			function_list[in_choose] = nullptr;
			function_list[in_choose] = new Deg0_Function;
			break;
		}
		case (DEG0):
		{
			function_list[in_choose] = nullptr;
			function_list[in_choose] = new Deg1_Function;

			break;
		}
		case (DEG1):
		{
			function_list[in_choose] = nullptr;
			function_list[in_choose] = new Sine_Function;
			break;
		}
		default:
		{
			// idk, pass
			break;
		}
	}

	// Update functions(Function_Package)
	functions->Sub_Input(in_choose);
	functions->Add_Input(in_choose, function_list[in_choose]);

	// Update GUI
	functions->resized();
	graphs->Update_Graph();
}

// Notes
void Audio_Editor::InputsSub_Pressed(unsigned int in_choose)
{
	std::cout << in_choose << std::endl;

	// Update internal
	functions->Sub_Input(in_choose);
	function_list.erase(function_list.begin() + in_choose);

	// Update GUI
	functions->resized();
	graphs->Update_Graph();
}

void Audio_Editor::InputsEditor_Changed()
{
	graphs->Update_Graph();
}

// -- From Settings Package ------------------------------------------------- //
void Audio_Editor::SettingsSamples_Pressed()
{
	if      (file_settings->sample_rate == SAMPLE_RATE_48)	file_settings->sample_rate = SAMPLE_RATE_96;
	else if (file_settings->sample_rate == SAMPLE_RATE_96)	file_settings->sample_rate = SAMPLE_RATE_192;
	else 							file_settings->sample_rate = SAMPLE_RATE_48;

	settings->Update_Inputs();
	settings->resized();
}

void Audio_Editor::SettingsDepth_Pressed()
{
	if      (file_settings->audio_depth == AUDIO_DEPTH_32)	file_settings->audio_depth = AUDIO_DEPTH_64;
	else 							file_settings->audio_depth = AUDIO_DEPTH_32;

	settings->Update_Inputs();
	settings->resized();
}

void Audio_Editor::SettingsFormat_Pressed()
{
	if      (file_settings->audio_format == MONO_L)		file_settings->audio_format = MONO_R;
	else if (file_settings->audio_format == MONO_R)		file_settings->audio_format = STEREO;
	else 							file_settings->audio_format = MONO_L;

	settings->Update_Inputs();
	settings->resized();
}

void Audio_Editor::SettingsRound_Pressed()
{
	if (file_settings->round_tail)				file_settings->round_tail = false;
	else							file_settings->round_tail = true;

	settings->Update_Inputs();
	settings->resized();
}

// -- JUCE ------------------------------------------------------------------ //
void Audio_Editor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::brown);	// tbd
}

void Audio_Editor::resized()
{
	// Make these positions (sort of) dynamic
	graphs   ->setTopLeftPosition((                                               1*GAP_SPACE), 1*GAP_SPACE);
	functions->setTopLeftPosition((GRAPH_PACKAGE_WIDTH +                          2*GAP_SPACE), 1*GAP_SPACE);
	settings ->setTopLeftPosition((GRAPH_PACKAGE_WIDTH + FUNCTION_PACKAGE_WIDTH + 3*GAP_SPACE), 1*GAP_SPACE);
	controls ->setTopLeftPosition((GRAPH_PACKAGE_WIDTH + FUNCTION_PACKAGE_WIDTH + 3*GAP_SPACE), AUDIO_WINDOW_HEIGHT - CONTROL_PACKAGE_HEIGHT - GAP_SPACE); // temp

	graphs   ->resized();
	controls ->resized();
	functions->resized();
	settings ->resized();
}

//
