////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Audio_File.h
//
// Virtual base class for Audio Files
//

#ifndef __AUDIO_FILE__
#define __AUDIO_FILE__

#include "../Headers.h"

#include "../Functions/Base_Function.h"
#include "../Gui/Audio/Settings_Package.h"

enum
{
	WAV,
	AIFF,
	MP3,
	// etc
};

class Audio_File
{
	private:

	public:
		// General
		virtual ~Audio_File() {};

		// File
		virtual void  To_File(Settings_Struct*, void*) = 0;

		// Debug
#if defined DEBUG
		virtual void  Print_Settings(void) = 0;	// tmp
#endif
};

#endif

//
