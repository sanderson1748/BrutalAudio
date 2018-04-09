////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
//
// Wav_File.cpp
//
// Make it
//

#include "Wav_File.h"
#include "../Gui/Audio/Audio_Window.h"
#include "../Gui/Audio/Settings_Package.h"

#if defined DEBUG
#include <iostream>
#endif

#define WAVE_FMT_PCM		(0x0001)
#define WAVE_FMT_IEEE_FLOAT	(0x0003)
#define WAVE_FMT_ALAW		(0x0006)
#define WAVE_FMT_MULAW		(0x0007)
#define WAVE_FMT_EXTENSIBLE	(0xfffe)

#define FILE_LOCATION	"yes.wav"

// - General --------------------------------------------------------------- //
Wav_File::Wav_File()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Wav_File::Construct" << std::endl;
#endif
}

Wav_File::~Wav_File()
{
#if defined CONSTRUCTORS
	std::cout << "Debug> Wav_File::Destruct" << std::endl;
#endif
}

// - Audio_File ------------------------------------------------------------ //
// Going to assume that functions/settings have already been set
void Wav_File::To_File(Settings_Struct* in_settings, void* in_functions)	// is void* for temp
{
	// Prepare
	std::ofstream fout(FILE_LOCATION, std::ofstream::binary);
	tmp_settings  = in_settings;
	tmp_functions = (std::vector<Base_Function*>*) in_functions;

	// Go
#if defined DEBUG
	Print_Settings();
#endif
	Write_Head(&fout);
	Write_Body(&fout);

	// Clear
	tmp_settings  = nullptr;
	tmp_functions = nullptr;
	fout.close();
}

#if defined DEBUG
void Wav_File::Print_Settings()
{
	std::cout << "wav file settings";
	std::cout << "\n- amplitude: " << tmp_settings->max_amplitude;
	std::cout << "\n- file time: " << tmp_settings->file_time_ms;
	std::cout << "\n- sam rate : " << tmp_settings->sample_rate;
	std::cout << "\n- depth    : " << tmp_settings->audio_depth;

	if      (tmp_settings->audio_format == MONO_L)	std::cout << "\n- Mono Left" ;
	else if (tmp_settings->audio_format == MONO_R)	std::cout << "\n- Mono Right";
	else if (tmp_settings->audio_format == STEREO)	std::cout << "\n- Stereo"    ;
	else						std::cout << "\n- Ch Error"  ;

	std::cout << "\n- round off: " << tmp_settings->round_tail << std::endl;

	std::cout << "Functions:" << std::endl;
	for (size_t i=0; i<tmp_functions->size(); i++)	std::cout << tmp_functions->at(i)->Get_String() << std::endl;
}
#endif

// - wav ------------------------------------------------------------------- //
void Wav_File::Write_Head(std::ofstream* fout)
{
	uint32_t go;
	uint32_t total_channels, bytes;
	uint32_t data_chunk_size;

	if (tmp_settings->audio_format == FIVE_ONE)	total_channels = 6;	// sure
	else 						total_channels = 2;	// MONO_L, MONO_R, STEREO all need two channels

	bytes = tmp_settings->audio_depth / 8;
	data_chunk_size = (bytes * total_channels * tmp_settings->sample_rate * tmp_settings->file_time_ms) / (1000);

	// 00 - Chunk ID: RIFF
	go = 0x46464952;			// "RIFF"
	fout->write((char*)&go,4);

	// 04 - RIFF Chunk Size
	go = 4 + 24 + (8 + data_chunk_size);	// = this
	fout->write((char*)&go,4);

	// 08 - Wave ID
	go = 0x45564157;			// "WAVE"
	fout->write((char*)&go,4);

	// 12 - SubChunk ID: Format
	go = 0x20746d66;			// "fmt "
	fout->write((char*)&go,4);

	// 16 - Format Chunk Size
	go = 16;				// 16
	fout->write((char*)&go,4);

	// 20 - Format
	go = WAVE_FMT_PCM;			// 
	fout->write((char*)&go,2);

	// 22 - Channels
	go = total_channels;			// 
	fout->write((char*)&go,2);

	// 24 - Sample Rate
	go = tmp_settings->sample_rate;		//
	fout->write((char*)&go,4);

	// 28 - Byte Rate
	go = tmp_settings->sample_rate * bytes * total_channels;	//
	fout->write((char*)&go,4);

	// 32 - Block Align
	go = bytes * total_channels;	//
	fout->write((char*)&go,2);

	// 34 - Bits Per Sample
	go = bytes * 8;		//
	fout->write((char*)&go,2);

	// 36 - SubChunk ID: Data
	go = 0x61746164;			// "data"
	fout->write((char*)&go,4);

	// 40 - Data Chunk Size
	go = data_chunk_size;			// 
	fout->write((char*)&go,4);
}

// The good stuff
void Wav_File::Write_Body(std::ofstream* fout)
{
	uint32_t i, j;
	 int32_t L0, R0;
	float    value_back, theta;
	uint32_t total_channels;
	uint32_t count;

	uint32_t bytes = tmp_settings->audio_depth / 8;

	uint32_t highbound_i = (tmp_settings->sample_rate * tmp_settings->file_time_ms) / (bytes * 1000);
	uint32_t highbound_j = tmp_settings->audio_depth / 8;
	 int32_t int_max;	// make 64?

	if      (tmp_settings->audio_depth == AUDIO_DEPTH_32)	int_max = INT_MAX_VALUE_32;
	//else if (tmp_settings->audio_depth == AUDIO_DEPTH_64)	int_max = INT_MAX_VALUE_64;
	else							int_max = INT_MAX_VALUE_32; // just for now (tm)

	double   coefficient = int_max / tmp_settings->max_amplitude;	// will be a bug for higher quality

	if (tmp_settings->audio_format == FIVE_ONE)	total_channels = 6;	// sure
	else 						total_channels = 2;	// MONO_L, MONO_R, STEREO all need two channels

	count = 0;
	for(i=0; i<highbound_i; i++)
	{
		for(j=0; j<highbound_j; j++)
		{
			// Ready
			theta = ((float) count * total_channels) / tmp_settings->sample_rate;
			value_back = 0;//Evaluate_All(theta);	// WHAT

			// Left
			// TMP!
			if (tmp_settings->audio_format == MONO_L || tmp_settings->audio_format == STEREO)
			{
				L0 = coefficient * value_back;
			}
			else
			{
				L0 = 0;
			}
			fout->write((char*) &L0, bytes);

			// Right (Mono Left)
			// TMP!
			if (tmp_settings->audio_format == MONO_R || tmp_settings->audio_format == STEREO)
			{
				R0 = coefficient * value_back;
			}
			else
			{
				R0 = 0;
			}
			fout->write((char*) &R0, bytes);

			// Loop
			count++;
		}
	}
}

//
