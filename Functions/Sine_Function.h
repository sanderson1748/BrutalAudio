////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Sine_Function.h
//
// Trig
//
// f(theta) = amp sin(theta + phi) + c
//

#ifndef __FUNCTION_SINE__
#define __FUNCTION_SINE__

#include "Base_Function.h"

// f(x) = amp * sin(x * freq + phi) + con
typedef struct
{
	float amp;	// Amplitude
	float freq;	// Frequency
	float phi;	// Phi
	float con;	// Constant
} Sine_Struct;

class Sine_Function: public Base_Function
{
	private:
		static const int id = SINE;
		Sine_Struct dude;

	public:
		// General
		Sine_Function(void);
		~Sine_Function(void);

		// Base_Function
		int          Get_Id(void);	// update to references!
		float*       Get_Values(void);
		juce::String Get_String(void);

		void Set(float,float,float,float,float);

		uint32_t Evaluate_U32(float);
		 int32_t Evaluate_I32(float);
		   float Evaluate_Float(float);

		// Sine
		// - pass
};

#endif

//
