//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Console ANSI Formatting                      --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"caf.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef caf_HPP
#define caf_HPP

// Standard library
#include <string>
#include <sstream>


//______________________________________________________________________________
//! ANSI console commands and codes
/*!	Quick shortcuts for ANSI-compatible console formatting.

*/

//______________________________________________________________________________


// #############################################################################
namespace cat {


//______________________________________________________________________________
	class caf
	{

	public:

		// Colors.
		enum col {
			BLACK = 30,
			RED = 31,
			GREEN = 32,
			YELLOW = 33,
			BLUE = 34,
			MAGENTA = 35,
			CYAN = 36,
			WHITE = 37,

			BBLACK = 90,
			BRED = 91,
			BGREEN = 92,
			BYELLOW = 93,
			BBLUE = 94,
			BMAGENTA = 95,
			BCYAN = 96,
			BWHITE = 97,
		};

		// ANSI font codes.
		enum style {
			RESET = 0,
			BOLD = 1,
			ITALIC = 3,
			UNDERLINE = 4,
			BLINK = 5,
			CROSSED = 9,
			DEFAULT = 10,
		};


		// Special members.
		caf();		//!< Ctor.
		~caf();		//!< Dtor.

		// Methods.
		static std::string rst();				//!< Reset to standard.
		static std::string fcol(const col&);	//!< Set foreground color with standard ANSI codes.
		static std::string fcol(const int&, const int&, const int&); //!< Set foreground color with arbitrary RGB palette.
		static std::string font(const style&);	//!< Set font style.
		static std::string fstyle(const col&, const style&); //!< Set foreground color and font style.
		static std::string bcol(const col&);	//!< Set background color with standard ANSI codes.
		static std::string bcol(const int&, const int&, const int&); //!< Set background color with arbitrary RGB palette.
		static std::string rev();				//!< Reverse foreground and background.
		
	protected:

		// No protected at the moment

	private:

		// Pivot structures.
		std::stringstream _ss;
		
};


// #############################################################################
}  // Close namespaces



//______________________________________________________________________________

// Few color conventions through the application.


// Pixels.
#define C_PX_COL cat::caf::col::YELLOW
#define C_PX_ROW cat::caf::col::CYAN
#define C_PX_TSP cat::caf::col::MAGENTA

// Clusters.
#define C_CL_COL cat::caf::col::YELLOW
#define C_CL_ROW cat::caf::col::CYAN
#define C_CL_TSP cat::caf::col::MAGENTA

// Geometry.
#define C_GEO_X cat::caf::col::RED
#define C_GEO_Y cat::caf::col::GREEN
#define C_GEO_Z cat::caf::col::BLUE

// Hit.
#define C_HIT_T cat::caf::col::BMAGENTA
#define C_HIT_CL cat::caf::col::WHITE


// Tracks.







// Overloading check
#endif