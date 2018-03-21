////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Audio_Window.cpp
//

#include "Audio_Window.h"

#include "../Gui_Headers.h"

#include "../../Files/Wav_File.h"

#if defined DEBUG
#include <iostream>
#endif

// Audio_Window ------------------------------------------------------------- //
Audio_Window::Audio_Window(juce::String name) : DocumentWindow(name, juce::Colours::black, 0)
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Audio_Window::Contruct" << std::endl;
#endif

	// Create Editor
	//setContentOwned(new Audio_Editor(), true);	// Lin?
	setContentOwned(new Audio_Editor(), false);	// OSX?

	// Configure Window
	setUsingNativeTitleBar(true);
	if (AUDIO_WINDOW_HEIGHT_L > AUDIO_WINDOW_HEIGHT_R)	setSize(AUDIO_WINDOW_WIDTH, AUDIO_WINDOW_HEIGHT_L);
	else 							setSize(AUDIO_WINDOW_WIDTH, AUDIO_WINDOW_HEIGHT_R);
	setResizable(false,false);
	setVisible(true);
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
	controls->setSize(FILE_PACKAGE_WIDTH, FILE_PACKAGE_HEIGHT);
	controls->setVisible(true);

	// - Function Package
	functions = new Function_Package(graphs);
	functions->setSize(FUNCTION_PACKAGE_WIDTH, FUNCTION_PACKAGE_HEIGHT);
	functions->setVisible(true);

	// - Settings Package
	settings = new Settings_Package();
	settings->setSize(SETTINGS_PACKAGE_WIDTH, SETTINGS_PACKAGE_HEIGHT);
	settings->setVisible(true);

	// Finalize
	addAndMakeVisible(graphs);
	addAndMakeVisible(controls);
	addAndMakeVisible(functions);
	addAndMakeVisible(settings);

	resized();

	graphs  ->Update_Graph();
	graphs  ->Update_Inputs();	// pass file_settings ?
	settings->Update_Inputs();	// pass file_settings ?
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
	return file_output;
}

Settings_Struct* Audio_Editor::Get_Settings()
{
	return file_settings;
}

// Returns absolute value of largest value generated
// Is going to be a hella mess
// Also, think about creating a member variable for absolute max
float Audio_Editor::Find_AbsMax()
{
	float max = 0.0;

	unsigned int total_samples = file_settings->file_time_ms * file_settings->sample_rate / 1000;
	unsigned int grind_rate = 64;

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
	std::cout << "Debug> Max = " << max << std::endl;
	return max;
}

// Is buggy?
float Audio_Editor::Evaluate_All(float theta)
{
	float sum = 0;
	for (unsigned int i=0; i<function_list.size(); i++)
	{
		sum += function_list[i]->Get_Funcc()->Evaluate_Float(theta);
	}
	return sum;
}

// -- From Graph Package ---------------------------------------------------- //
void Audio_Editor::GraphBounds_Pressed()
{
	if (file_settings->max_amplitude != graphs->Grab_Bounds())
	{
		file_settings->max_amplitude = graphs->Grab_Bounds();
		graphs->Update_Graph();
	}
}

void Audio_Editor::GraphTime_Pressed()
{
	if (file_settings->file_time_ms != graphs->Grab_TimeMs())
	{
		file_settings->file_time_ms = graphs->Grab_TimeMs();
		graphs->Update_Graph();
	}
}

// -- From Control Package -------------------------------------------------- //
void Audio_Editor::ControlStream_Pressed()
{
	std::cout << "Later> Audio_Editor::ControlStream_Pressed()" << std::endl;
}

void Audio_Editor::ControlExport_Pressed()
{
	std::cout << "Export_Audio - Start" << std::endl;

	// Prepare Output File
	file_output->Set_Settings(file_settings);
	for (unsigned int i=0; i<function_list.size(); i++)	file_output->Add_Function(function_list[i]->Get_Funcc());

	// Do it
	file_output->To_File();

	// Clear settings/files
	file_output->Clear_File();

	std::cout << "Export_Audio - Done" << std::endl;
}

void Audio_Editor::ControlSave_Pressed()
{
	std::cout << "Later> Audio_Editor::ControlSave_Pressed()" << std::endl;
}

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
	if (function_list.size() >= MAX_FUNCTIONS)	return;

	function_list.push_back(new Function_Input);
	functions->Add_Input(function_list[function_list.size() - 1]);

	functions->resized();
	graphs->Update_Graph();
}

// Remove from Function_Package(House), remove last Input
// Always does last input
// Calls Function_Package resized
void Audio_Editor::FunctionsSub_Pressed()
{
	if (function_list.size() == 0)			return;

	unsigned int choose = 0;	// for future; function just pops 

	functions->Sub_Input(choose);
	function_list.pop_back();

	functions->resized();
	graphs->Update_Graph();
}

// Skipping this?
// - Or fix it?
void Audio_Editor::InputsSwap_Pressed()
{
	//if (old_value != new_value)
	//{
		functions->resized();
		graphs->Update_Graph();
	//}
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
	if      (file_settings->audio_format == MONO_L)	file_settings->audio_format = MONO_R;
	else if (file_settings->audio_format == MONO_R)	file_settings->audio_format = STEREO;
	else 						file_settings->audio_format = MONO_L;

	settings->Update_Inputs();
	settings->resized();
}

void Audio_Editor::SettingsRound_Pressed()
{
	if (file_settings->round_tail)	file_settings->round_tail = false;
	else				file_settings->round_tail = true;

	settings->Update_Inputs();
	settings->resized();
}

// -- JUCE ------------------------------------------------------------------ //
void Audio_Editor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::brown);
}

void Audio_Editor::resized()
{
	// Make these positions (sort of) dynamic
	graphs   ->setTopLeftPosition(GAP_SPACE, GAP_SPACE);
	controls ->setTopLeftPosition(GAP_SPACE, (GRAPH_PACKAGE_HEIGHT + 2*GAP_SPACE));

	functions->setTopLeftPosition((GRAPH_PACKAGE_WIDTH + 2*GAP_SPACE), GAP_SPACE);
	settings ->setTopLeftPosition((GRAPH_PACKAGE_WIDTH + 2*GAP_SPACE), (FUNCTION_PACKAGE_HEIGHT + 2*GAP_SPACE));

	graphs   ->resized();
	controls ->resized();
	functions->resized();
	settings ->resized();
}

//
