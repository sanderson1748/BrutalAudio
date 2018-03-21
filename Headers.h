////////////////////////////////////////////////////////////////////////////////
// Brutal Editor                                                              //
// - Internal Development Version 24                                          //
// - 2018 March 21                                                            //
//                                                                            //
// sanderson1748@gmail.com                                                    //
////////////////////////////////////////////////////////////////////////////////
// Headers.h
//
// Global Options, Platform, etc
//

#ifndef __HEADERS__
#define __HEADERS__

// Temp ----------- //
#define PI		3.141592635

#define FLOAT_PRECISION	3

#define TEST_AUDIO (1)
#define TEST_IMAGE (0)

// Platform ------- //
//#define WINDOWS
#define OSX
//#define LINUX

#define SIMULATE_OUTPUT	(0)

#if defined WINDOWS
#define WIN_32		(0)
#define WIN_64		(0)
#endif

#if defined OSX
#define OSX_32		(0)
#define OSX_64		(0)
#endif

#if defined LINUX
#define LINUX_32	(0)
#define LINUX_64	(0)
#endif

#define USE_C		(1)

// For JUCE ------- //
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED	1
#define JUCE_STANDALONE_APPLICATION		1

// Debug ---------- //
//#define DEBUG

#if defined DEBUG
#define CONSTRUCTORS
#define SHOW_FUNCTIONS
//#define SHOW_GET_SET
//#define SHOW_ADDRESSES
#define SHOW_ERRORS
#endif

#endif

//
