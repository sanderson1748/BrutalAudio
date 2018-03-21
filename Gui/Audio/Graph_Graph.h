////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Graph_Graph.h
//
// Graphing, bud
//

#ifndef __GRAPH_GRAPH__
#define __GRAPH_GRAPH__

#include <vector>
#include <thread>	// not yet

#include <juce_gui_basics/juce_gui_basics.h>

#include "../../Headers.h"

#include "../Gui_Headers.h"
#define RESOLUTION	(GRAPH_GRAPH_WIDTH)

#define ARROW_POINTS	3

typedef struct
{
	juce::Point<float> a;
	juce::Point<float> b;
} Two_Points;

typedef struct 
{
	juce::String text;
	float x;
	float y;
} Graph_Helper;

class Graph_Graph : public juce::Component
{
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Graph_Graph);

		// Plan
		bool clipping;	// this may need to move to Audio_Editor

		float edge_buffer;//edge_y_buffer; 	// as a percent!
		float abs_maxxx;	// name is tmp, this is also tmp here

		// Scale
		unsigned int resolution;
		float working_x_max;	// seconds
		float working_y_max;	// amplitude (abs)

		float scale_x_pixels;
		float scale_y_pixels;

		// Background
		juce::ScopedPointer<Two_Points> background_rectangles[3];	// [0] Middle (white), [1] Top, [2] Bottom

		// Grids
		unsigned int num_sub_lines_h;
		unsigned int num_sub_lines_v;

		juce::ScopedPointer<Two_Points> main_line_h;
		juce::ScopedPointer<Two_Points> main_line_v;

		std::vector<juce::ScopedPointer<Two_Points>> sub_lines_h;
		std::vector<juce::ScopedPointer<Two_Points>> sub_lines_v;

		// Function
		juce::ScopedPointer<juce::Point<float>> plot_points[RESOLUTION + 1];	// tmp, needs that +1

		// Helpers
		std::vector<juce::ScopedPointer<Graph_Helper>> horizontal_helpers;
		std::vector<juce::ScopedPointer<Graph_Helper>> vertical_helpers;

		juce::ScopedPointer<Graph_Helper> text_helpers[2];	// amplitude, seconds

		juce::ScopedPointer<juce::Point<float>> grid_arrow_a[ARROW_POINTS];	// centre, left, right
		juce::ScopedPointer<juce::Point<float>> grid_arrow_b[ARROW_POINTS];

	public:
		// General
		Graph_Graph(void);
		~Graph_Graph(void);

		// Work
		void Hit_It(void);	// tmp, obv
		void Plan_Graph(void);
		void Set_Background(void);
		void Set_Grid(void);
		void Set_Plot(void);
		void Set_Helpers(void);

		// JUCE
		void paint(juce::Graphics&) override;
		void resized(void) override;
};

#endif

//
