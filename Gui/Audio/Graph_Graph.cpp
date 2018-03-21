////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Graph_Graph.cpp
//

#include <cmath> // tmp

#include "Graph_Graph.h"

#include "../Gui_Headers.h"

#if defined DEBUG
#include <iostream>
#endif

#include "Graph_Package.h"
#include "Audio_Window.h"

#define TEXT_AMP_HELPER		"Amplitude"
#define TEXT_TIME_HELPER	"Time (s)"
#define HELPER_DROPSET		(LABEL_HEIGHT)	// tmp

// move this, idk
static float dash[] = {5.0, 3.0, 3.0, 3.0};	// A on, B off, C on, D off

// Graph_Graph -------------------------------------------------------------- //
// -- General --------------------------------------------------------------- //
Graph_Graph::Graph_Graph()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Graph_Graph::Construct" << std::endl;
#endif

	// General
	clipping  = false;
	edge_buffer = 1.05;

	// Background
	background_rectangles[0] = new Two_Points;
	background_rectangles[1] = new Two_Points;
	background_rectangles[2] = new Two_Points;

	// Grid
	num_sub_lines_h = 0;	// zero? idk for now
	num_sub_lines_v = 0;

	main_line_h = new Two_Points;
	main_line_v = new Two_Points;

	// Function
	resolution = RESOLUTION;
	for (unsigned int i=0; i<(RESOLUTION + 1); i++)	plot_points[i] = new juce::Point<float>;

	// Helper
	text_helpers[0] = new Graph_Helper;
	text_helpers[1] = new Graph_Helper;

	for (unsigned int i=0; i<ARROW_POINTS; i++)	grid_arrow_a[i] = new juce::Point<float>;
	for (unsigned int i=0; i<ARROW_POINTS; i++)	grid_arrow_b[i] = new juce::Point<float>;
}

Graph_Graph::~Graph_Graph()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Graph_Graph::Destruct" << std::endl;
#endif

	// Background
	background_rectangles[0] = nullptr;
	background_rectangles[1] = nullptr;
	background_rectangles[2] = nullptr;

	// Grid
	main_line_h = nullptr;
	main_line_v = nullptr;

	sub_lines_h.clear();
	sub_lines_v.clear();

	// Function
	for (unsigned int i=0; i<(RESOLUTION + 1); i++)	plot_points[i] = nullptr;

	// Helper
	horizontal_helpers.clear();
	vertical_helpers.clear();

	text_helpers[0] = nullptr;
	text_helpers[1] = nullptr;

	for (unsigned int i=0; i<ARROW_POINTS; i++)	grid_arrow_a[i] = nullptr;
	for (unsigned int i=0; i<ARROW_POINTS; i++)	grid_arrow_b[i] = nullptr;
}

// -- Work ------------------------------------------------------------------ //
// change
void Graph_Graph::Hit_It()
{
	Plan_Graph();
	Set_Background();
	Set_Grid();
	Set_Plot();
	Set_Helpers();

	repaint();
}

void Graph_Graph::Plan_Graph()
{
	Graph_Package* graph_parent  = (Graph_Package*)               getParentComponent();
	Audio_Editor*  editor_parent = (Audio_Editor*)  graph_parent->getParentComponent();

	Settings_Struct* tmp_settings = editor_parent->Get_Settings();

	// Max -> may move to audio editor
	abs_maxxx = editor_parent->Find_AbsMax();

	// Clipping -> may move to Audio_Editor
	if (abs_maxxx > tmp_settings->max_amplitude)	clipping = true;
	else						clipping = false;

	// Scales
	scale_x_pixels = (float) GRAPH_GRAPH_WIDTH;
	scale_y_pixels = (float) GRAPH_GRAPH_HEIGHT;

	// - x
	working_x_max = (tmp_settings->file_time_ms) / 1000;

	if      (working_x_max <=  1.0)		working_x_max =  1.0;
	else if (working_x_max <=  5.0)		working_x_max =  5.0;
	else if (working_x_max <= 10.0)		working_x_max = 10.0;
	else if (working_x_max <= 50.0)		working_x_max = 50.0;
	else					working_x_max =  1.0;	// idk

	// - y
	if (clipping)	working_y_max = abs_maxxx;
	else		working_y_max = tmp_settings->max_amplitude;

	if      (working_y_max <=  1.0)		working_y_max =  1.0;
	else if (working_y_max <=  5.0)		working_y_max =  5.0;
	else if (working_y_max <= 10.0)		working_y_max = 10.0;
	else if (working_y_max <= 50.0)		working_y_max = 50.0;
	else					working_y_max =  1.0;	// idk

	//working_y_max *= edge_buffer;
}

// Get points for rectangels that will be generate later
// background_rectangles = { middle (white), top, bottom }
void Graph_Graph::Set_Background()
{
	Graph_Package* graph_parent  = (Graph_Package*)               getParentComponent();
	Audio_Editor*  editor_parent = (Audio_Editor*)  graph_parent->getParentComponent();

	Settings_Struct* tmp_settings = editor_parent->Get_Settings();

	float y_converge;	// pixel! distance from centre to interface
	float set_y;
	float y_centre   = scale_y_pixels / 2;

	y_converge  = (tmp_settings->max_amplitude / working_y_max) * (scale_y_pixels / 2);
	y_converge /= edge_buffer;

	// Middle (white)
	set_y = y_centre - y_converge;
	background_rectangles[0]->a.setX((float) GUI_ZERO);
	background_rectangles[0]->a.setY(set_y);

	set_y = y_centre + y_converge;
	background_rectangles[0]->b.setX(scale_x_pixels);
	background_rectangles[0]->b.setY(set_y);

	// Top
	set_y = (float) GUI_ZERO;
	background_rectangles[1]->a.setX((float) GUI_ZERO);
	background_rectangles[1]->a.setY(set_y);

	set_y = y_centre  - y_converge;
	background_rectangles[1]->b.setX(scale_x_pixels);
	background_rectangles[1]->b.setY(set_y);

	// Bottom
	set_y = y_centre  + y_converge;
	background_rectangles[2]->a.setX((float) GUI_ZERO);
	background_rectangles[2]->a.setY(set_y);

	set_y = scale_y_pixels;
	background_rectangles[2]->b.setX(scale_x_pixels);
	background_rectangles[2]->b.setY(set_y);
}

void Graph_Graph::Set_Grid()
{
	Graph_Package* graph_parent  = (Graph_Package*)               getParentComponent();
	Audio_Editor*  editor_parent = (Audio_Editor*)  graph_parent->getParentComponent();

	Settings_Struct* tmp_settings = editor_parent->Get_Settings();

	float x_centre = scale_x_pixels - (scale_x_pixels / edge_buffer);
	float y_centre = scale_y_pixels / 2;

	float x_converge;	//  pixels
	float y_converge;	// (pixels) distance from centre

	// Main-Lines
	// - x
	main_line_h->a.setX((float) GUI_ZERO);
	main_line_h->a.setY(y_centre);

	main_line_h->b.setX(scale_x_pixels);
	main_line_h->b.setY(y_centre);

	// - y
	main_line_v->a.setX(x_centre);
	main_line_v->a.setY((float) GUI_ZERO);

	main_line_v->b.setX(x_centre);
	main_line_v->b.setY(scale_y_pixels);

	// Sub-Lines
	if (1)//sub_lines_need_updating)
	{
		// Prepare Points guys
		juce::Point<float> tmp_a;
		juce::Point<float> tmp_b;

		sub_lines_h.clear();
		sub_lines_v.clear();

		// Determine Grouping
		// - Remember, don't do gate posts
		// comparisons should be ==
		if 	(working_y_max <=   1.0)		num_sub_lines_h = 4;	// temp!
		else if (working_y_max <=   5.0)		num_sub_lines_h = 4;	// temp!
		else if (working_y_max <=  10.0)		num_sub_lines_h = 4;	// temp!
		else if (working_y_max <= 100.0)		num_sub_lines_h = 4;	// temp!
		else						num_sub_lines_h = 4;	// idk

		// - Vertical 
		// - Remember, don't do gate posts
		if      (tmp_settings->file_time_ms <=  1000)	num_sub_lines_v = 5;	// temp!
		else if (tmp_settings->file_time_ms <=  5000)	num_sub_lines_v = 5;	// temp!
		else if (tmp_settings->file_time_ms <= 10000)	num_sub_lines_v = 5;	// temp!
		else if (tmp_settings->file_time_ms <= 50000)	num_sub_lines_v = 5;	// temp!
		else						num_sub_lines_v = 5;	// idk

		// Do Points
		// - Horizontal
		// - Remember, don't do gate posts
		y_converge  = scale_y_pixels / (2 * num_sub_lines_h);	// * 2 is for one on each side
		y_converge /= edge_buffer;
		for (unsigned int i=0; i<num_sub_lines_h; i++)
		{
			// Above
			tmp_a.setX((float) GUI_ZERO);
			tmp_a.setY(y_centre - ((i + 1) * y_converge));

			tmp_b.setX(scale_x_pixels);
			tmp_b.setY(y_centre - ((i + 1) * y_converge));

			sub_lines_h.push_back(new Two_Points);
			sub_lines_h[2*i+0]->a = tmp_a;
			sub_lines_h[2*i+0]->b = tmp_b;

			// Below
			tmp_a.setX((float) GUI_ZERO);
			tmp_a.setY(y_centre + ((i + 1) * y_converge));

			tmp_b.setX(scale_x_pixels);
			tmp_b.setY(y_centre + ((i + 1) * y_converge));

			sub_lines_h.push_back(new Two_Points);
			sub_lines_h[2*i+1]->a = tmp_a;
			sub_lines_h[2*i+1]->b = tmp_b;
		}

		// - Vertical
		// - Remember, don't do gate posts
		x_converge  = scale_x_pixels / (1 * num_sub_lines_v);	// * 1 is for symmetry with ^^^
		x_converge /= 2 * edge_buffer - 1;	// need twice the percentage value; need to change this line // WHAT
		for (unsigned int i=0; i<num_sub_lines_v; i++)
		{
			// L to R
			tmp_a.setX(x_centre + (i + 1) * x_converge);
			tmp_a.setY((float) GUI_ZERO);

			tmp_b.setX(x_centre + (i + 1) * x_converge);
			tmp_b.setY(scale_y_pixels);

			sub_lines_v.push_back(new Two_Points);
			sub_lines_v[i]->a = tmp_a;
			sub_lines_v[i]->b = tmp_b;
		}
	}
}

void Graph_Graph::Set_Plot()
{
	// temp
	float theta, f_at;	// values to be plugged in for evaluation
	float x_pixel, y_pixel;	// values to be used for plot

	float x_convert;
	float y_convert;
	float grind_rate;

	float x_centre = scale_x_pixels - (scale_x_pixels / edge_buffer);
	float y_centre = scale_y_pixels / 2;

	unsigned int max_samples = 4 * 48000; // 4s * 48000 sam/s

	Graph_Package* graph_parent  = (Graph_Package*)               getParentComponent();
	Audio_Editor*  editor_parent = (Audio_Editor*)  graph_parent->getParentComponent();

	Settings_Struct* tmp_settings = editor_parent->Get_Settings();

	// Grind
	grind_rate = ((float) tmp_settings->file_time_ms) / (1000 * resolution);

	// Scales
	x_convert = scale_x_pixels * ((float) tmp_settings->file_time_ms / (working_x_max * 1000)) / ((2 * edge_buffer - 1) * 1.0 * resolution);	// WHAT - same need twice the edge buffer percentage
	y_convert = scale_y_pixels / (edge_buffer * 2.0 * working_y_max);	// * 2 for up+down halves

	// Run it
	for (unsigned int i=0; i<(RESOLUTION + 1); i++)
	{
		// Get Values
		theta = i * grind_rate;
		f_at = editor_parent->Evaluate_All(theta);

		// Convert to Pixel
		x_pixel = i    * x_convert;
		y_pixel = f_at * y_convert;

		// Set as Point
		plot_points[i]->setX(x_centre + x_pixel);	// positive, don't gotta flip it
		plot_points[i]->setY(y_centre - y_pixel);	// negative, gotta flip it
	}
}

#define ARROW_LENGTH	3
#define ARROW_WIDTH	2
void Graph_Graph::Set_Helpers()
{
	float x_centre = scale_x_pixels - (scale_x_pixels / edge_buffer);
	float y_centre = scale_y_pixels / 2;

	unsigned int n_helpers;

	// X-Axis
	if (1)//((unsigned int) working_x_max) % 2)
	{
		n_helpers = 5;

		for (unsigned int i=0; i<n_helpers; i++)
		{
			horizontal_helpers.push_back(new Graph_Helper);

			horizontal_helpers[i]->text = juce::String(((working_x_max / n_helpers) * (i + 1)), HELPER_PRECISION);
			horizontal_helpers[i]->x    = x_centre + (i + 1) * (scale_x_pixels / (2 * edge_buffer - 1)) / n_helpers;	// WHAT - that buffer thing
			horizontal_helpers[i]->y    = main_line_h->a.getY();
		}
	}
	else
	{
		n_helpers = 2;	// value? idk
	}

	// Y-Axis
	// - Not centre
	if (0)//((unsigned int) working_y_max) % 2)
	{
		n_helpers = 3;
	}
	else
	{
		// 1/2 and 2/2
		n_helpers = 2;

		for (unsigned int i=0; i<n_helpers; i++)
		{
			// Above
			vertical_helpers.push_back(new Graph_Helper);

			vertical_helpers[2*i+0]->text = juce::String(( 1 * working_y_max / (n_helpers - i)), HELPER_PRECISION);
			vertical_helpers[2*i+0]->x    = main_line_v->a.getX();
			vertical_helpers[2*i+0]->y    = y_centre - (i + 1) * (scale_y_pixels / edge_buffer) / (2 * n_helpers);

			// Below
			vertical_helpers.push_back(new Graph_Helper);

			vertical_helpers[2*i+1]->text = juce::String((-1 * working_y_max / (n_helpers - i)), HELPER_PRECISION);
			vertical_helpers[2*i+1]->x    = main_line_v->a.getX();
			vertical_helpers[2*i+1]->y    = y_centre + (i + 1) * (scale_y_pixels / edge_buffer) / (2 * n_helpers);
		}
	}
	// - Centre
	vertical_helpers.push_back(new Graph_Helper);

	vertical_helpers[vertical_helpers.size()-1]->text = juce::String((float) 0, HELPER_PRECISION);
	vertical_helpers[vertical_helpers.size()-1]->x    = main_line_v->a.getX();
	vertical_helpers[vertical_helpers.size()-1]->y    = y_centre;

	// Text
	// - amplitude
	text_helpers[0]->text = juce::String(TEXT_AMP_HELPER);
	text_helpers[0]->x    = main_line_v->a.getX();
	text_helpers[0]->y    = main_line_v->a.getY() + HELPER_DROPSET;

	// - seconds
	text_helpers[1]->text = juce::String(TEXT_TIME_HELPER);
	text_helpers[1]->x    = main_line_h->b.getX();
	text_helpers[1]->y    = main_line_h->b.getY() + HELPER_DROPSET;

	// Decoration
	// - Arrows [centre, left, right]
	grid_arrow_a[0]->setX(x_centre);
	grid_arrow_a[0]->setY((float) GUI_ZERO);
	grid_arrow_a[1]->setX(grid_arrow_a[0]->getX() - ARROW_WIDTH);
	grid_arrow_a[1]->setY(grid_arrow_a[0]->getY() + ARROW_LENGTH);
	grid_arrow_a[2]->setX(grid_arrow_a[0]->getX() + ARROW_WIDTH);
	grid_arrow_a[2]->setY(grid_arrow_a[0]->getY() + ARROW_LENGTH);

	grid_arrow_b[0]->setX(scale_x_pixels);
	grid_arrow_b[0]->setY(y_centre);
	grid_arrow_b[1]->setX(grid_arrow_b[0]->getX() - ARROW_LENGTH);
	grid_arrow_b[1]->setY(grid_arrow_b[0]->getY() - ARROW_WIDTH);
	grid_arrow_b[2]->setX(grid_arrow_b[0]->getX() - ARROW_LENGTH);
	grid_arrow_b[2]->setY(grid_arrow_b[0]->getY() + ARROW_WIDTH);
}

// -- JUCE ------------------------------------------------------------------ //
void Graph_Graph::paint(juce::Graphics& g)
{
	juce::Line<float> draw_lines;
	//juce::Path pathhh;	// <-- use this! later

	// Background
	// - Regular
	g.setColour(juce::Colours::white);
	g.fillRect(juce::Rectangle<float>(background_rectangles[0]->a, background_rectangles[0]->b));

	// - Clipping 
	if (clipping)	g.setColour(juce::Colours::red);
	else 		g.setColour(juce::Colours::yellow);
	g.fillRect(juce::Rectangle<float> (background_rectangles[1]->a, background_rectangles[1]->b));
	g.fillRect(juce::Rectangle<float> (background_rectangles[2]->a, background_rectangles[2]->b));

	// Grid
	// - Main-Lines
	g.setColour(juce::Colours::black);
	g.drawLine(juce::Line<float> (main_line_h->a, main_line_h->b));
	g.drawLine(juce::Line<float> (main_line_v->a, main_line_v->b));

	// - Sub-Lines
	g.setColour(juce::Colours::grey);
	for (unsigned int i=0; i<sub_lines_h.size(); i++)	g.drawDashedLine(juce::Line<float> (sub_lines_h[i]->a, sub_lines_h[i]->b), dash, 4);
	for (unsigned int i=0; i<sub_lines_v.size(); i++)	g.drawDashedLine(juce::Line<float> (sub_lines_v[i]->a, sub_lines_v[i]->b), dash, 4);

	// Function
	g.setColour(juce::Colours::blue);
	for (unsigned int i=0; i<(resolution-1); i++)
	{
		draw_lines.setStart(*plot_points[i  ]);
		draw_lines.setEnd  (*plot_points[i+1]);
		g.drawLine(draw_lines);
	}

	// Helpers
	g.setColour(juce::Colours::black);
	//g.setFont(...);

	// - X-Axis values
	for (unsigned int i=0; i<horizontal_helpers.size(); i++)	g.drawSingleLineText(horizontal_helpers[i]->text, horizontal_helpers[i]->x, horizontal_helpers[i]->y, JUSTIFY_RIGHT);

	// - Y-Axis values
	for (unsigned int i=0; i<vertical_helpers.size(); i++)		g.drawSingleLineText(vertical_helpers[i]->text, vertical_helpers[i]->x, vertical_helpers[i]->y, JUSTIFY_RIGHT);

	// - Text 
	g.drawSingleLineText(text_helpers[0]->text, text_helpers[0]->x, text_helpers[0]->y, JUSTIFY_LEFT);
	g.drawSingleLineText(text_helpers[1]->text, text_helpers[1]->x, text_helpers[1]->y, JUSTIFY_RIGHT);

	// - Arrows
	g.setColour(juce::Colours::black);

	g.drawLine(juce::Line<float> (*grid_arrow_a[0], *grid_arrow_a[1]));
	g.drawLine(juce::Line<float> (*grid_arrow_a[0], *grid_arrow_a[2]));

	g.drawLine(juce::Line<float> (*grid_arrow_b[0], *grid_arrow_b[1]));
	g.drawLine(juce::Line<float> (*grid_arrow_b[0], *grid_arrow_b[2]));
}

void Graph_Graph::resized()
{
}

//
