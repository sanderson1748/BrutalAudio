////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// DegreeOne_Function.cpp

#include <cmath>

#include "DegreeOne_Function.h"

#if defined DEBUG
#include <iostream>
#endif

// General ----------------------------------------------------------------- //
Deg1_Function::Deg1_Function()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Deg1_Function::Construct" << std::endl;
#endif

	// Default Degree 1
	dude.slope = 1.0;
	dude.con   = 0.0;
}

Deg1_Function::~Deg1_Function()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Deg1_Function::Destruct" << std::endl;
#endif
}

// Base_Function ----------------------------------------------------------- //
int Deg1_Function::Get_Id()
{
	return id;
}

float* Deg1_Function::Get_Values()
{
	return (float*) (&dude);
}

juce::String Deg1_Function::Get_String()
{
	juce::String str1("f(x) = ");
	juce::String str2(dude.slope, FLOAT_PRECISION);
	juce::String str3(" x + ");
	juce::String str4(dude.con, FLOAT_PRECISION);

	juce::String ret = str1 + str2 + str3 + str4;

	return ret;
}

void Deg1_Function::Set(float in_a, float in_con, float no_1, float no_2, float no_3)
{
	dude.slope = in_a;
	dude.con   = in_con;

#if defined SHOW_GET_SET
	std::cout << "Debug> Deg1_Function::Set(" << dude.slope << ", " << dude.con << ")" << std::endl;
#endif
#if defined SHOW_ADDRESSES
	std::cout << "First_Degree > &this: " << this << "\n\t&Deg0_Struct: " << &dude << "\n\t&slope: " << &dude.slope << ", &con: " << &dude.con << std::endl;
#endif
}

uint32_t Deg1_Function::Evaluate_U32(float in_x)
{
	return 22;
}

int32_t Deg1_Function::Evaluate_I32(float in_x)
{
	return -22;
}

float Deg1_Function::Evaluate_Float(float in_x)
{
	float ret;
#if USE_C
	ret = (dude.slope * in_x) + dude.con;
#else
#endif
	return ret;
}

// One Degree -------------------------------------------------------------- //

//
