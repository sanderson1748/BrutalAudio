////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Saw_Function.h
//
// ++ Later ++
//
// f(x) = (a(x+phi)+const) ** width; phi<width
//	maybe like this?
//

#ifndef __FUNCTION_SAW__
#define __FUNCTION_SAW__

#include "Base_Function.h"

// f(x) = [ (a * (x + phi)) + con ] <= repeated for each freq 
// start at zero (if con==0), then linear from there
// maybe use a Deg0_Function?
typedef struct
{
	// Function
	float slope;
	float phi;
	float con;
	float period;
} Saw_Struct;

class Saw_Function: public Base_Function
{
	private:
		static const int id = SAW;
		Saw_Struct dude;

	public:
		// General
		Saw_Function(void);
		~Saw_Function(void);

		// Base_Function
		int          Get_Id(void);	// update to references!
		float*       Get_Values(void);
		juce::String Get_String(void);

		void     Set(float,float,float,float,float);

		uint32_t Evaluate_U32(float);
		 int32_t Evaluate_I32(float);
		   float Evaluate_Float(float);

		// Saw
		// - pass
};

#endif

//
