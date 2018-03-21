////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// Deg0_Function.cpp

#include <cmath>

#include "DegreeZero_Function.h"

#if defined DEBUG
#include <iostream>
#endif

// General ----------------------------------------------------------------- //
Deg0_Function::Deg0_Function()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Deg0_Function::Construct" << std::endl;
#endif

	// Default Degree 1
	dude.con = 1.0;
}

Deg0_Function::~Deg0_Function()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Deg0_Function::Destruct" << std::endl;
#endif
}

// Base_Function ----------------------------------------------------------- //
int Deg0_Function::Get_Id()
{
	return id;
}

float* Deg0_Function::Get_Values()
{
	return (float*) (&dude);
}

juce::String Deg0_Function::Get_String()
{
	juce::String str1("f(x) = ");
	juce::String str2(dude.con, FLOAT_PRECISION);

	juce::String ret = str1 + str2;

	return ret;
}

void Deg0_Function::Set(float in_con, float no_1, float no_2, float no_3, float no_4)
{
	dude.con = in_con;

#if defined SHOW_GET_SET
	std::cout << "Debug> Deg0_Function::Set(" << dude.con << ")" << std::endl;
#endif
}

uint32_t Deg0_Function::Evaluate_U32(float in_x)
{
	return 22;
}

int32_t Deg0_Function::Evaluate_I32(float in_x)
{
	return -22;
}

float Deg0_Function::Evaluate_Float(float in_x)
{
	float ret;
#if USE_C
	ret = dude.con;
#else
#endif
	return ret;
}

// Zero Degrees ------------------------------------------------------------ //

//
