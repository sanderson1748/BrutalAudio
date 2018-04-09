////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Deg0_Function.h
// 
// Constant Functions
//
// f(x) = con
//

#ifndef __FUNCTION_DEG0__
#define __FUNCTION_DEG0__

#include "Base_Function.h"

// f(x) = ax + con 
typedef struct
{
	float con;	// Constant
} Degree0_Struct;

class Deg0_Function : public Base_Function
{
	private:
		static const int id = DEG0;
		Degree0_Struct dude;

	public:
		// General
		Deg0_Function(void);
		~Deg0_Function(void);

		// Base_Function
		int          Get_Id(void);	// update to references!
		float*       Get_Values(void);
		juce::String Get_String(void);

		void     Set(float,float,float,float,float);

		uint32_t Evaluate_U32(float);
		 int32_t Evaluate_I32(float);
		   float Evaluate_Float(float);

		// Zero Degree
		// - pass
};

#endif

//
