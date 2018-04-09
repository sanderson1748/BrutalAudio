////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Util_Guy.cpp
//

#include "Util_Guy.h"

Util_Guy::Util_Guy()
{
	// nothin
}

void Util_Guy::To_Big32(uint32_t* in)
{
	uint32_t hold1, hold2, hold3, hold4;
	hold1 = *in & 0x000000ff;
	hold2 = *in & 0x0000ff00;
	hold3 = *in & 0x00ff0000;
	hold4 = *in & 0xff000000;

	*in = (hold1 << 24) | (hold2 << 8) | (hold3 >> 8) | (hold4 >> 24);
}

//
