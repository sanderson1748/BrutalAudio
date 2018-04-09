////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Asm_Boys.h
//
// Asm Functions
// - Only working for 32-Bit Linux for now!
//

#ifndef __ASM_BOYS__
#define __ASM_BOYS__

#include "../Headers.h"

#if LINUX_32
int   Linux32_Square(int,int);
int   Linux32_Root(int);
float Linux32_Pyth(float,float);
float Linux32_Sine(float,void*);
#endif

#endif

//
