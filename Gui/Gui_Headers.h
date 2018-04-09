////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Gui_Headers.h
//
// Temporary constants and things
//
// Running GUI is real ugly
//

#ifndef __GUI_HEADERS__
#define __GUI_HEADERS__

// General
#define GUI_ZERO		(  0)

#define GAP_SPACE		(  5)

#define BUTTON_WIDTH		( 50)
#define BUTTON_WIDTH_BIG	(100)
#define BUTTON_HEIGHT		( 25)

#define LABEL_WIDTH_SMALL	( 25)
#define LABEL_WIDTH_MEDIUM	( 75)
#define LABEL_WIDTH_LARGE	(150)
#define LABEL_HEIGHT		( 25)

#define EDITOR_WIDTH_SMALL	( 75)
#define EDITOR_HEIGHT		( 25)

// Different General
#define INPUTS			(  5)	// this refers to Function_Input. rename, move, etc
#define MAX_FUNCTIONS		(  8)	// Maximum number of functions

// Commonn Text / for buttons
#define TEXT_CHANGE		"Change"

// Text Justification
#define JUSTIFY_LEFT		(  1)
#define JUSTIFY_RIGHT		(  2)
#define JUSTIFY_CENTRE		(  4)

// Move this
#define HELPER_PRECISION	(  1)

// Audio Window 
// - Graph_Package
#define GRAPH_GRAPH_WIDTH	(800)
#define GRAPH_GRAPH_HEIGHT	(400)
#define GRAPH_PACKAGE_WIDTH	(GRAPH_GRAPH_WIDTH)
#define GRAPH_PACKAGE_HEIGHT	(GRAPH_GRAPH_HEIGHT + EDITOR_HEIGHT)

// - Control_Package
#define CONTROL_PACKAGE_WIDTH	(4 * BUTTON_WIDTH)
#define CONTROL_PACKAGE_HEIGHT	(BUTTON_HEIGHT)

// - Function_Package
#define FUNCTION_INPUT_WIDTH	(INPUTS * (LABEL_WIDTH_SMALL + EDITOR_WIDTH_SMALL))
#define FUNCTION_INPUT_HEIGHT	(LABEL_HEIGHT + LABEL_HEIGHT)	// weird

#define FUNCTION_HOUSE_WIDTH	(FUNCTION_INPUT_WIDTH)
#define FUNCTION_HOUSE_HEIGHT	(MAX_FUNCTIONS * FUNCTION_INPUT_HEIGHT)

#define FUNCTION_PACKAGE_WIDTH	(FUNCTION_HOUSE_WIDTH)
#define FUNCTION_PACKAGE_HEIGHT	(FUNCTION_HOUSE_HEIGHT + BUTTON_HEIGHT)
#define FUNPACK_LABEL_HELP	(FUNCTION_PACKAGE_WIDTH - BUTTON_WIDTH)

// - Settings_Package
#define SETTINGS_PACKAGE_WIDTH	(LABEL_WIDTH_LARGE + EDITOR_WIDTH_SMALL + BUTTON_WIDTH)
#define SETTINGS_PACKAGE_HEIGHT	(6 * LABEL_HEIGHT)

// Sum it
#define AUDIO_WINDOW_WIDTH	(GRAPH_PACKAGE_WIDTH + FUNCTION_PACKAGE_WIDTH + SETTINGS_PACKAGE_WIDTH + 4*GAP_SPACE)	
#define AUDIO_WINDOW_HEIGHT	(GRAPH_PACKAGE_HEIGHT + 2*GAP_SPACE)	

#endif

//
