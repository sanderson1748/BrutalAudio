////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Wav_File.h
//
// Doin it for wavs
//

#ifndef __WAV_FILE__
#define __WAV_FILE__

#include <vector>
#include <memory>
#include <fstream>
#include <thread>

#include "../Headers.h"

#include "Audio_File.h"
#include "../Gui/Audio/Function_Input.h"

class Wav_File : public Audio_File
{
	private:
		Settings_Struct* tmp_settings;
		std::vector<Base_Function*>* tmp_functions;

	public:
		// General
		Wav_File(void);
		~Wav_File(void);

		// Audio
		void  To_File(Settings_Struct*, void*);

		// Debug
#if defined DEBUG
		void  Print_Settings(void);	// tmp?
#endif

		// wav
		void Write_Head(std::ofstream*);	// make static/private
		void Write_Body(std::ofstream*);	// make static/private
};

#endif

//
