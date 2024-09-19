//------------------------------------------------------------------------------
// CAT color console facility												  --
// (C) Piero Giubilato 2011-2013, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afConsole.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"C++"
// [Project]		"CAT"
//______________________________________________________________________________

//______________________________________________________________________________
//! Console addons for the PEAR package
/*! The Console overloads the standard << operator to provide some very basic
 *	formatting options for the console environment of both Linux and Windows	
 *	systems. No support for MAC is yet provided at the moment.
 *	This header put all its the functions in the global namespace, as they are
 *	all overloads of the basic << stream operator.
 */

// Description
//	Adds the COL(new_Color) directive to the standard output, allowing
//	to change the foreground and background color of the std output.
//		
// Important:
//	Correctly define a WINSDK variable in order to enable the color functions.
//
// Parameters for the color(new_Color) directive
//	Colors follow the standard numerical color coding, and can be
//	called both by number that by keyword:
//	BLACK  = 0,		LBLACK	= 8
//	BLUE   = 1,		LBLUE	= 9
//	GREEN  = 2,		LGREEN	= 10
//	CYAN   = 3,		LCYAN	= 11
//	RED    = 4,		LRED	= 12
//	PURPLE = 5,		LPURPLE	= 13
//	YELLOW = 6,		LYELLOW	= 14
//	WHITE  = 7,		LWITHE	= 15
//	The keyword L (light) can be added to get the maximum luminosity color
//	The keyword BG (background) can be used as multiplier to set the background
// color as well 
//
// Examples
//	cout <<	COL(DEFAULT) << "Usual white\n";
//	cout <<	"This is white: " << color(L + YELLOW) << 
//				"this is light yellow" << endl;
//	cout <<	COL(L + WHITE) << "This is light white" << endl;
//	cout <<	COL(12) << "This is light red\n";
//	cout <<	COL(L + RED) << "This is still light red\n";
//	cout <<	COL(LRED) << "This is still light red\n";
//	cout <<	COL(L + RED + BG * YELLOW) << 
//				"This is light red on yellow background\n";
//	cout <<	COL(8 + BG * (L + 5)) << 
//				"This is light black on light yellow background\n";

//______________________________________________________________________________

// Overloading check
#ifndef afConsole_H
#define afConsole_H


// All subsequent statements are valid for Windows systems
// _____________________________________________________________________________
#if defined(_WIN32) || defined(_WIN64)
//#ifdef PEAR_WIN
	
	// This library calls many others windows libs.
	#ifndef _WINDOWS_
		#include <windows.h>
	#endif
		
	// Color constants definitions
	enum COL {
		FG		= 0,
		BG		= 16,
		
		// Keep in case CINT out of this
		L		= FOREGROUND_INTENSITY,
		DEFAULT	= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		BLACK	= 0,
		BLUE	= FOREGROUND_BLUE,
		GREEN	= FOREGROUND_GREEN,
		CYAN	= FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED		= FOREGROUND_RED,
		PURPLE	= FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW	= FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE	= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		LBLACK	= L | BLACK,
		LBLUE	= L | BLUE,
		LGREEN	= L | GREEN,
		LCYAN	= L | CYAN,
		LRED	= L | RED,
		LPURPLE	= L | PURPLE,
		LYELLOW	= L | YELLOW,
		LWHITE	= L | WHITE
	};
		
	// Overloads the << operator in case the color keyword is found,
	// setting the new color for the console standard output
	template <class _Elem, class _Traits>
	inline std::basic_ostream<_Elem,_Traits>& operator <<(std::basic_ostream<_Elem,_Traits>& out_Stream, COL new_Color)
	{
		// Get the console handle 
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	
		// Set the new console color
		SetConsoleTextAttribute(hStdout, (WORD)new_Color);
   
		// Return the rightmost stream object to the next operator(s)
		return out_Stream;
	};

	// Definition for the clear directive (still to complete)
	//inline std::ostream& clear(std::ostream &out_Stream)
	//{
   		// Get the console handle
		//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
		
		// Return the rightmost stream object to the next operator(s)
		//return out_Stream;
	//};
	

// All subsequent statements are valid in LINUX (Mac to be tested)
// _____________________________________________________________________________

#else

	// Color constants definitions
	enum COL {
		FG		= 0,   
		BG		= 16,
		L		= 0,
		DEFAULT = 255,
		BLACK	= 0,
		BLUE	= 1,
		GREEN	= 2,
		CYAN	= 3,
		RED	= 4,
		PURPLE = 5,
		YELLOW = 6,
		WHITE	= 7,
		LBLACK = 8,
		LBLUE	= 9,
		LGREEN = 10,
		LCYAN	= 11,
		LRED	= 12,
		LPURPLE	= 13,
		LYELLOW	= 14,
		LWHITE	= 15
	};
	
	// Overload << operator for col structure
	inline std::ostream& operator<<(std::ostream& o, const COL& c)
	{
		//o << "(" <<  p.x << ", " << p.y <<")";
		/*! Uses console escape commands to set a color. This is a quick
			and dirty way which works just for Linux consoles. If you need
			somthing more portable and robust, use the .*/
	  	switch (c) {
			case DEFAULT: std::cout	<< "\033[0m"; break;
			case BLACK: std::cout	<< "\033[22;30m"; break;
			case BLUE: std::cout	<< "\033[22;34m"; break;
			case GREEN: std::cout	<< "\033[22;32m"; break;
			case CYAN: std::cout	<< "\033[22;36m"; break;
			case RED: std::cout		<< "\033[22;31m"; break;
			case PURPLE: std::cout	<< "\033[22;35m"; break;
			case YELLOW: std::cout	<< "\033[22;33m"; break;
			case WHITE: std::cout	<< "\033[22;37m"; break;
			case LBLACK: std::cout	<< "\033[01;30m"; break;
			case LBLUE: std::cout	<< "\033[01;34m"; break;
			case LGREEN: std::cout	<< "\033[01;32m"; break;
			case LCYAN: std::cout	<< "\033[01;36m"; break;
			case LRED: std::cout	<< "\033[01;31m"; break;
			case LPURPLE: std::cout	<< "\033[01;35m"; break;
			case LYELLOW: std::cout	<< "\033[01;33m"; break;
			case LWHITE: std::cout	<< "\033[01;37m"; break;
			default: std::cout << "";
		}

		// Return
		return o;
	}

// End of WINSDK defined IF
#endif

// Overloading check
#endif
