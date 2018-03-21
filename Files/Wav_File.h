////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
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

#include "../Functions/Base_Function.h"

class Wav_File : public Audio_File
{
	private:
		Settings_Struct* settings;
		std::vector<Base_Function*> function_list ;

	public:
		// General
		Wav_File(void);
		~Wav_File(void);

		// Audio_File
		void  Prepare_File(Settings_Struct*, std::vector<Base_Function*>*);
		void  Add_Function(Base_Function*);	// remove
		void  Set_Settings(Settings_Struct*);	// remove
		void  Clear_File(void);

		float Evaluate_All(float);

		void  To_File(void);

		void  Print_Settings(void);	// tmp?

		// wav
		void Write_Head(std::ofstream*);	// make static/private
		void Write_Body(std::ofstream*);	// make static/private
};

#endif

//
