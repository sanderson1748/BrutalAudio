////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
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
		virtual void  Prepare_File(Settings_Struct*, std::vector<Base_Function*>*) = 0;
		virtual void  Add_Function(Base_Function*) = 0;		// remove
		virtual void  Set_Settings(Settings_Struct*) = 0;	// remove
		virtual void  Clear_File(void) = 0;

		virtual float Evaluate_All(float) = 0;

		virtual void  To_File(void) = 0;

		virtual void  Print_Settings(void) = 0;	// tmp
};

#endif

//
