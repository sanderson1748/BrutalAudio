////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Settings_Package.cpp
//

#include "Settings_Package.h"

#include "../Gui_Headers.h"

#include "Audio_Window.h"

#if defined DEBUG
#include <iostream>
#endif

#define TEXT_SAMPLES	"Sample Rate"
#define TEXT_DEPTH	"Audio Depth"
#define TEXT_FORMAT	"Audio Format"
#define TEXT_ROUNDTAIL	"Round Off Tail"

// Listeners ---------------------------------------------------------------- //
void ButtonListener_SettingsPackage::buttonClicked(juce::Button* butt)
{
	Settings_Package* settings_parent = (Settings_Package*) butt           ->getParentComponent();
	Audio_Editor*     editor_parent   = (Audio_Editor*)     settings_parent->getParentComponent();

	if      (butt->getName() == TEXT_SAMPLES)	editor_parent->SettingsSamples_Pressed();
	else if (butt->getName() == TEXT_DEPTH)		editor_parent->SettingsDepth_Pressed();
	else if (butt->getName() == TEXT_FORMAT)	editor_parent->SettingsFormat_Pressed();
	else if (butt->getName() == TEXT_ROUNDTAIL)	editor_parent->SettingsRound_Pressed();
	//else						throw something
}

void ButtonListener_SettingsPackage::buttonStateChanged(juce::Button* butt)
{
}

void EditorListener_SettingsPackage::textEditorTextChanged(juce::TextEditor& edit)
{
}

void EditorListener_SettingsPackage::textEditorReturnKeyPressed(juce::TextEditor& edit)
{
}

void EditorListener_SettingsPackage::textEditorEscapeKeyPressed(juce::TextEditor& edit)
{
}

void EditorListener_SettingsPackage::textEditorFocusLost(juce::TextEditor& edit)
{
}

// Settings_Package --------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Settings_Package::Settings_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Settings_Package::Construct" << std::endl;
#endif

	// Settings 
	Audio_Editor* edit_parent = (Audio_Editor*) getParentComponent();

	// Controls
	// - Listeners
	listen_butt = new ButtonListener_SettingsPackage();
	listen_edit = new EditorListener_SettingsPackage();
	
	// - Samples
	label_samples = new juce::Label(juce::String(TEXT_SAMPLES), juce::String(TEXT_SAMPLES));
	label_samples->setSize(LABEL_WIDTH_LARGE, LABEL_HEIGHT);
	label_samples->setVisible(true);

	edit_samples = new juce::TextEditor(juce::String(TEXT_SAMPLES));
	edit_samples->setSize(EDITOR_WIDTH_SMALL, EDITOR_HEIGHT);
	edit_samples->setVisible(true);

	edit_samples->setJustification(juce::Justification(JUSTIFY_RIGHT));
	edit_samples->setReadOnly(true);
	edit_samples->addListener((juce::TextEditor::Listener*) listen_edit);

	butt_samples = new juce::TextButton(TEXT_SAMPLES);
	butt_samples->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_samples->setVisible(true);
	butt_samples->setButtonText(juce::String(TEXT_CHANGE));
	butt_samples->addListener((juce::Button::Listener*) listen_butt);

	// - Bytes
	label_depth= new juce::Label(juce::String(TEXT_DEPTH), juce::String(TEXT_DEPTH));
	label_depth->setSize(LABEL_WIDTH_LARGE, LABEL_HEIGHT);
	label_depth->setVisible(true);

	edit_depth = new juce::TextEditor(juce::String(TEXT_DEPTH));
	edit_depth->setSize(EDITOR_WIDTH_SMALL, EDITOR_HEIGHT);
	edit_depth->setVisible(true);

	edit_depth->setJustification(juce::Justification(JUSTIFY_RIGHT));
	edit_depth->setReadOnly(true);
	edit_depth->addListener((juce::TextEditor::Listener*) listen_edit);

	butt_depth = new juce::TextButton(TEXT_DEPTH);
	butt_depth->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_depth->setVisible(true);
	butt_depth->setButtonText(juce::String(TEXT_CHANGE));
	butt_depth->addListener((juce::Button::Listener*) listen_butt);

	// - Channels
	label_channels = new juce::Label(juce::String(TEXT_FORMAT), juce::String(TEXT_FORMAT));
	label_channels->setSize(LABEL_WIDTH_LARGE, LABEL_HEIGHT);
	label_channels->setVisible(true);

	edit_channels = new juce::TextEditor(juce::String(TEXT_FORMAT));
	edit_channels->setSize(EDITOR_WIDTH_SMALL, EDITOR_HEIGHT);
	edit_channels->setVisible(true);

	edit_channels->setJustification(juce::Justification(JUSTIFY_RIGHT));
	edit_channels->setReadOnly(true);
	edit_channels->addListener((juce::TextEditor::Listener*) listen_edit);

	butt_channels = new juce::TextButton(TEXT_FORMAT);
	butt_channels->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_channels->setVisible(true);
	butt_channels->setButtonText(juce::String(TEXT_CHANGE));
	butt_channels->addListener((juce::Button::Listener*) listen_butt);

	// - Round Tail
	butt_roundtail = new juce::ToggleButton(TEXT_ROUNDTAIL);
	butt_roundtail->setSize(BUTTON_WIDTH_BIG, BUTTON_HEIGHT);
	butt_roundtail->setVisible(true);
	butt_roundtail->addListener((juce::Button::Listener*) listen_butt);

	// Finalize
	addAndMakeVisible(label_samples);
	addAndMakeVisible(edit_samples);
	addAndMakeVisible(butt_samples);

	addAndMakeVisible(label_depth);
	addAndMakeVisible(edit_depth);
	addAndMakeVisible(butt_depth);

	addAndMakeVisible(label_channels);
	addAndMakeVisible(edit_channels);
	addAndMakeVisible(butt_channels);

	addAndMakeVisible(butt_roundtail);

	resized();
}

Settings_Package::~Settings_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Settings_Package::Destruct" << std::endl;
#endif

	// Yeah
	listen_butt    = nullptr;
	listen_edit    = nullptr;

	label_samples  = nullptr;
	edit_samples   = nullptr;
	butt_samples   = nullptr;

	label_depth    = nullptr;
	edit_depth     = nullptr;
	butt_depth     = nullptr;

	label_channels = nullptr;
	edit_channels  = nullptr;
	butt_channels  = nullptr;

	butt_roundtail = nullptr;
}

// -- Work ------------------------------------------------------------------ //
// Update the text values in the user input things
void Settings_Package::Update_Inputs()
{
	// Get
	Audio_Editor* editor_parent = (Audio_Editor*) this->getParentComponent();
	Settings_Struct* tmp_settings = editor_parent->Get_Settings();

	// Go
	edit_samples->setText(juce::String((int) tmp_settings->sample_rate), false);
	edit_depth  ->setText(juce::String((int) tmp_settings->audio_depth), false);

	if      (tmp_settings->audio_format == MONO_L)	edit_channels->setText(juce::String("Mono L"), false);
	else if (tmp_settings->audio_format == MONO_R)	edit_channels->setText(juce::String("Mono R"), false);
	else						edit_channels->setText(juce::String("Stereo"), false);

	if      (tmp_settings->round_tail)		butt_roundtail->setToggleState(true,  false);
	else						butt_roundtail->setToggleState(false, false);
}

// -- JUCE ------------------------------------------------------------------ //
void Settings_Package::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::orange);
}

void Settings_Package::resized()
{
	// Samples
	label_samples ->setTopLeftPosition( GUI_ZERO                               , (0*LABEL_HEIGHT));
	edit_samples  ->setTopLeftPosition( LABEL_WIDTH_LARGE                      , (0*LABEL_HEIGHT));
	butt_samples  ->setTopLeftPosition((LABEL_WIDTH_LARGE + EDITOR_WIDTH_SMALL), (0*LABEL_HEIGHT));

	// Bytes
	label_depth   ->setTopLeftPosition( GUI_ZERO                               , (1*LABEL_HEIGHT));
	edit_depth    ->setTopLeftPosition( LABEL_WIDTH_LARGE                      , (1*LABEL_HEIGHT));
	butt_depth    ->setTopLeftPosition((LABEL_WIDTH_LARGE + EDITOR_WIDTH_SMALL), (1*LABEL_HEIGHT));

	// Channels
	label_channels->setTopLeftPosition( GUI_ZERO                               , (2*LABEL_HEIGHT));
	edit_channels ->setTopLeftPosition( LABEL_WIDTH_LARGE                      , (2*LABEL_HEIGHT));
	butt_channels ->setTopLeftPosition((LABEL_WIDTH_LARGE + EDITOR_WIDTH_SMALL), (2*LABEL_HEIGHT));

	// Round it
	butt_roundtail->setTopLeftPosition( GUI_ZERO                               , (3*LABEL_HEIGHT));
}

//
