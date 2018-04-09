////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Control_Package.cpp
//

#include "Control_Package.h"

#include "../Gui_Headers.h"

#include "Audio_Window.h"

#if defined DEBUG
#include <iostream>
#endif

#define TEXT_PLAY	"Play"
#define TEXT_EXPORT	"Export"
#define TEXT_SAVE	"Save"
#define TEXT_FINISH	"Finish"

// ButtonListener_ControlPackage ------------------------------------------- //
void ButtonListener_ControlPackage::buttonClicked(juce::Button* butt)
{
	Control_Package* control_parent = (Control_Package*) butt          ->getParentComponent();
	Audio_Editor*    editor_parent  = (Audio_Editor*   ) control_parent->getParentComponent();

	if      (butt->getName() == TEXT_PLAY)		editor_parent->ControlStream_Pressed();
	else if (butt->getName() == TEXT_EXPORT)	editor_parent->ControlExport_Pressed();
	else if (butt->getName() == TEXT_SAVE)		editor_parent->ControlSave_Pressed();
	else if (butt->getName() == TEXT_FINISH)	editor_parent->ControlQuit_Pressed();
	//else						throw something!
}

void ButtonListener_ControlPackage::buttonStateChanged(juce::Button* butt)
{
}

// Control_Package --------------------------------------------------------- //
Control_Package::Control_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Control_Package::Construct" << std::endl;
#endif

	// Listeners
	listen_butt = new ButtonListener_ControlPackage();

	// Buttons
	// - Play Button
	butt_play = new juce::TextButton(TEXT_PLAY);
	butt_play->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_play->setVisible(true);
	butt_play->addListener((juce::Button::Listener*) listen_butt);

	// - Export Button
	butt_export = new juce::TextButton(TEXT_EXPORT);
	butt_export->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_export->setVisible(true);
	butt_export->addListener((juce::Button::Listener*) listen_butt);

	// - Save Button
	butt_save = new juce::TextButton(TEXT_SAVE);
	butt_save->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_save->setVisible(true);
	butt_save->addListener((juce::Button::Listener*) listen_butt);

	// - Finish Button
	butt_finish = new juce::TextButton(TEXT_FINISH);
	butt_finish->setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	butt_finish->setVisible(true);
	butt_finish->addListener((juce::Button::Listener*) listen_butt);

	// Finalize
	addAndMakeVisible(butt_play);
	addAndMakeVisible(butt_export);
	addAndMakeVisible(butt_save);
	addAndMakeVisible(butt_finish);
}

Control_Package::~Control_Package()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Control_Package::Destruct" << std::endl;
#endif

	// Listen
	listen_butt = nullptr;

	// Button
	butt_play   = nullptr;
	butt_export = nullptr;
	butt_save   = nullptr;
	butt_finish = nullptr;
}

void Control_Package::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::white);
}

void Control_Package::resized()
{
	butt_play  ->setTopLeftPosition((0*BUTTON_WIDTH), GUI_ZERO);
	butt_export->setTopLeftPosition((1*BUTTON_WIDTH), GUI_ZERO);
	butt_save  ->setTopLeftPosition((2*BUTTON_WIDTH), GUI_ZERO);
	butt_finish->setTopLeftPosition((3*BUTTON_WIDTH), GUI_ZERO);
}

//
