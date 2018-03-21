////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// Sine_Function.cpp
//

#include <cmath>
#include <string>

#include "Sine_Function.h"

#if 0//LINUX_32
extern "C"
{
  #include "../Asm/Asm_Boys.h"
}
#endif

#if defined DEBUG
#include <iostream>
#endif

// General ----------------------------------------------------------------- //
Sine_Function::Sine_Function()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Sine_Function::Construct" << std::endl;
#endif

	// Default Sine
	dude.amp  = 1.0;
	dude.freq = 1.0 * PI;//440 * PI;
	dude.phi  = 0.0;
	dude.con  = 0.0;
}

Sine_Function::~Sine_Function()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Sine_Function::Destruct" << std::endl;
#endif
}

// Base_Function ----------------------------------------------------------- //
int Sine_Function::Get_Id()
{
	return id;
}

float* Sine_Function::Get_Values()
{
	return (float*) (&dude);
}

juce::String Sine_Function::Get_String()
{
	juce::String str1("f(x) = ");
	juce::String str2(dude.amp, FLOAT_PRECISION);
	juce::String str3(" sin(");
	juce::String str4(dude.freq/PI, FLOAT_PRECISION);
	juce::String str5(" pi x + ");
	juce::String str6(dude.phi, FLOAT_PRECISION);
	juce::String str7(") + ");
	juce::String str8(dude.con, FLOAT_PRECISION);

	juce::String ret = str1 + str2 + str3 + str4 + str5 + str6 + str7 + str8; 

	return juce::String(ret);
}

void Sine_Function::Set(float in_amp, float in_freq, float in_phi, float in_con, float no_1)
{
	dude.amp  = in_amp;
	dude.freq = in_freq;
	dude.phi  = in_phi;
	dude.con  = in_con;

#if defined SHOW_GET_SET
	std::cout << "Debug> Sine_Function::Set(" << dude.amp << ", " << (dude.freq/PI) << "pi, " << dude.phi << ", " << dude.con << ")" << std::endl;
#endif
#if defined SHOW_ADDRESSES
	std::cout << "Sine_Function> &this: " << this << "\n\t&Sine_Struct: " << &dude << "\n\t&amp: " << &dude.amp << ", &freq: " << &dude.freq << ", &phi: " << &dude.phi << ", &con: " << &dude.con << std::endl;
#endif
}

uint32_t Sine_Function::Evaluate_U32(float in_x) // x is theta!
{
	return 10;
}

int32_t Sine_Function::Evaluate_I32(float in_x)	// x is theta!
{
	return -10;
}

float Sine_Function::Evaluate_Float(float in_x)	// x is theta!
{
	float ret;
#if USE_C
	ret = dude.amp * sin(in_x * dude.freq + dude.phi) + dude.con;
#elif LINUX_32
	ret = Asm_Sine(in_x, (void*) &dude);
#endif
	return ret;
}

// Sine -------------------------------------------------------------------- //

//
