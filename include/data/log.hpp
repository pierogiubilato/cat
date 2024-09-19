//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Logging utility                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"01 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef log_HPP
#define log_HPP

// Standard library
#include <string>
#include <deque>
#include <iostream>
#include <ostream>
#include <sstream>

// Application units.
#include "../include/caf.hpp"    // Console IO formatting.




//______________________________________________________________________________
//! Logger utility with verbosity control.
/*!	The log overloads the standard << operator to provide some very basic

*/

//______________________________________________________________________________


// #############################################################################
namespace cat {


//______________________________________________________________________________
class log
{

	public:

		// Message severity threshold.
		enum severity {
			V_CRITICAL = 0,
			V_ERROR = 1,
			V_WARNING = 2,
			V_FLOW = 3,
			V_MESSAGE = 4,
			V_INFO = 5,
			V_DEBUG = 6,
			V_ALL = 99
		};
		
		// Log base width.
		enum widht {
			L_SMALL = 80,
			L_DEFAULT = 120,
			L_WIDE = 160,
		};

		// Special members.
		log(const severity& = V_INFO, const widht& = L_DEFAULT);	//!< Verbosity ctor.
		~log();					//!< Dtor.

		// Friend stream operators.
		//friend std::ostream& operator<<(std::ostream&, const log&);
		//friend std::ostream& operator<<(const std::string&, const level&);

		// Methods - support.
		void verb(const severity&);		
		severity verb() const;					
		bool isShow(const severity&) const;
		void print(const std::ostream&, const severity&) const;


		// Methods - logging.
		void critical(const std::string&, const severity & = V_CRITICAL);
		void warning(const std::string&, const severity & = V_WARNING);
		void error(const std::string&, const severity & = V_ERROR);
		void section(const std::string&, const severity& = V_FLOW);
		void message(const std::string&, const severity& = V_MESSAGE);
		void info(const std::string&, const severity & = V_INFO);
		void debug(const std::string&, const severity & = V_DEBUG);
		

		// Add/print methods.
		void print(const std::stringstream&, const severity& = V_INFO) const;
		//std::ostream& add(const level&, std::ostream&) const;			

		//std::string print(const level&, const std::string&) const;   	

		//std::ostream& add(std::iostream&, const level&);   


	protected:

		// No protected at the moment

	private:

		// Message indent level.
		enum indent {
			I_MAIN = 0,
			I_SECTION = 3,
			I_L2 = 6,
			I_L3 = 9,
			I_L4 = 12,
			I_l5 = 15
		};

		// Format class.
		cat::caf _caf;
		
		// Current verbosity level.
		severity _verb;

		// Current log width.
		widht _widht;

		// Current indent level.
		indent _indent;

		// The local temporary log storage deque.
		std::deque<std::stringstream> _log;
		std::deque<int> _lvl;

		// Formatting suppor routines.
		std::string atab(const int& = 0) const;


		// Tabbing.
		//std::string tab(const char&, const int&) const;
};


// #############################################################################
}  // Close namespaces


// Overloading check
#endif