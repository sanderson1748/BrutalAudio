////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// Wav_File.cpp
//
// This has been messed up as I have been moving other pieces around
// - 32Bit, 48k, Mono mayyyyyy produce the correct output, but maybe not
// - Other configurations definitely will not
//

#include "Wav_File.h"

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

	function_list.clear();
}

// - Audio_File ------------------------------------------------------------ //
void Wav_File::Prepare_File(Settings_Struct* in_settings, std::vector<Base_Function*>* in_funcc)
{
}

void Wav_File::Add_Function(Base_Function* new_funcc)	// remove
{
	function_list.push_back(new_funcc);
}

void Wav_File::Set_Settings(Settings_Struct* inbound)	// remove
{
	settings = inbound;
}

void Wav_File::Clear_File()
{
	settings = nullptr;
	function_list.clear();
}

float Wav_File::Evaluate_All(float theta)
{
	float sum = 0;
	for (unsigned int i=0; i<function_list.size(); i++)	sum += function_list[i]->Evaluate_Float(theta);
	return sum;
}

// Going to assume that functions/settings have already been set
void Wav_File::To_File()
{
	std::ofstream fout;
	fout.open(FILE_LOCATION, std::ofstream::binary);

	// tmp
	Print_Settings();

	Write_Head(&fout);
	Write_Body(&fout);

	fout.close();
}

#include <iostream>	// tmp; easy to debug
void Wav_File::Print_Settings()
{
	std::cout << "wav file settings";
	std::cout << "\n- amplitude: " << settings->max_amplitude;
	std::cout << "\n- file time: " << settings->file_time_ms;
	std::cout << "\n- sam rate : " << settings->sample_rate;
	std::cout << "\n- depth    : " << settings->audio_depth;

	if (settings->audio_format == MONO_L)		std::cout << "\n- Mono Left" ;
	else if (settings->audio_format == MONO_R)	std::cout << "\n- Mono Right";
	else if (settings->audio_format == STEREO)	std::cout << "\n- Stereo"    ;
	else						std::cout << "\n- Ch Error"  ;

	std::cout << "\n- round off: " << settings->round_tail << std::endl;

	std::cout << "Functions:" << std::endl;
	for (unsigned int i=0; i<function_list.size(); i++)	std::cout << function_list[i]->Get_String() << std::endl;
}

// - wav ------------------------------------------------------------------- //
void Wav_File::Write_Head(std::ofstream* fout)
{
	uint32_t go;
	uint32_t total_channels, bytes;
	uint32_t data_chunk_size;

	if (settings->audio_format == MONO_L || settings->audio_format == MONO_R || settings->audio_format == STEREO)	total_channels = 2;

	bytes = settings->audio_depth / 8;

	data_chunk_size = (bytes * total_channels * settings->sample_rate * settings->file_time_ms) / (1000);

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
	go = settings->sample_rate;		//
	fout->write((char*)&go,4);

	// 28 - Byte Rate
	go = settings->sample_rate * bytes * total_channels;	//
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

// for 32 bit!
// - This did work for 32Bit, 48k, Mono
// - but that was as settings were hardcoded; there have been a lot of changes made
// - (functions have been moved, etc), and I am focusing on the plot at the moment.
// Plan is to have different sets of functions for each output stream, but that is much later
void Wav_File::Write_Body(std::ofstream* fout)
{
	uint32_t i, j;
	 int32_t L0, R0;
	float    value_back, theta;
	uint32_t total_channels;
	uint32_t count;

	uint32_t bytes = settings->audio_depth / 8;

	uint32_t highbound_i = (settings->sample_rate * settings->file_time_ms) / (bytes * 1000);
	uint32_t highbound_j = settings->audio_depth / 8;
	 int32_t int_max;	// make 64?

	if      (settings->audio_depth == AUDIO_DEPTH_32)	int_max = INT_MAX_VALUE_32;
	//else if (settings->audio_depth == AUDIO_DEPTH_64)	int_max = INT_MAX_VALUE_64;
	else							int_max = INT_MAX_VALUE_32; // just for now (tm)

	double   coefficient = int_max / settings->max_amplitude;	// will be a bug for higher quality

	if (settings->audio_format == MONO_L || settings->audio_format == MONO_R || settings->audio_format == STEREO)	total_channels = 2;	// idk

	count = 0;
	for(i=0; i<highbound_i; i++)
	{
		for(j=0; j<highbound_j; j++)
		{
			// Ready
			theta = ((float) count * total_channels) / settings->sample_rate;
			value_back = Evaluate_All(theta);

			// Left
			// TMP!
			if (settings->audio_format == MONO_L || settings->audio_format == STEREO)
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
			if (settings->audio_format == MONO_R || settings->audio_format == STEREO)
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
