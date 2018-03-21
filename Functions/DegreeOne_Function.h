////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// DegreeOne_Function.h
// 
// Linear Functions
//
// f(x) = ax + con
//

#ifndef __DEGREE_1__
#define __DEGREE_1__

#include <cstdint>

#include "Base_Function.h"

// f(x) = ax + con 
typedef struct
{
	float slope;
	float con;
} Degree1_Struct;

class Deg1_Function: public Base_Function
{
	private:
		static const int id = DEG1;
		Degree1_Struct dude;

	public:
		// General
		Deg1_Function(void);
		~Deg1_Function(void);

		// Base_Function
		int          Get_Id(void);	// update to references!
		float*       Get_Values(void);
		juce::String Get_String(void);

		void         Set(float,float,float,float,float);

		uint32_t     Evaluate_U32(float);
		 int32_t     Evaluate_I32(float);
		   float     Evaluate_Float(float);

		// One Degree

};

#endif

//
