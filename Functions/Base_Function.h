////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Base_Function.h
//
// Virtual base class for Functions
//

#ifndef __FUNCTION_BASE__
#define __FUNCTION_BASE__

#include <cstdint>			// doesn't seem to be needed for OSX

#include <juce_core/juce_core.h>	// for jstring

#include "../Headers.h"

enum
{
	SINE,
	SAW,
	DEG0,
	DEG1,
	//TAYLOR,
	//more
};

class Base_Function
{
	private:
		
	public:
		// General
		virtual ~Base_Function(void) {}

		virtual int          Get_Id(void)     = 0;
		virtual float*       Get_Values(void) = 0;	// Return an ("unknown") array which is parsed by the caller
		virtual juce::String Get_String(void) = 0;

		virtual void Set(float,float,float,float,float) = 0;

		//  8 Bit
//		virtual uint8_t  Evaluate_U08(float)    = 0;
//		virtual  int8_t  Evaluate_I08(float)    = 0;

		// 16 Bit
//		virtual uint64_t Evaluate_U16(float)    = 0;
//		virtual  int64_t Evaluate_I16(float)    = 0;

		// 32 Bit
		virtual uint32_t Evaluate_U32(float)    = 0;
		virtual  int32_t Evaluate_I32(float)    = 0;

		// 64 Bit
//		virtual uint64_t Evaluate_U64(double)   = 0;
//		virtual  int64_t Evaluate_I64(double)   = 0;

		// Floating Point
		virtual    float Evaluate_Float(float)  = 0;
//		virtual   double Evaluate_Float(double) = 0;
};

#endif
