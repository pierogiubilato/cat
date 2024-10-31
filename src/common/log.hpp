//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Logging utility                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"25 Aug 2024"
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

// Console library.
#include<oof.h>

// Application units.
//#include "../include/caf.hpp"    // Console IO formatting.




//______________________________________________________________________________
//! Log utility with verbosity control.
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
		enum class severity : int {
			critical = 0,
			error = 1,
			warning = 2,
			section = 3,
			message = 4,
			info = 5,
			debug = 6,
			all = 99
		};
		
		// Log base width.
		enum class width : int {
			small = 80,
			normal = 120,
			wide = 160,
		};

		// Special members.
		log(const severity& = severity::info, const width& = width::normal);	//!< Verbosity ctor.
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
		void critical(const std::string&, const severity & = severity::critical);
		void error(const std::string&, const severity & = severity::error);
		void warning(const std::string&, const severity & = severity::warning);
		void section(const std::string&, const severity& = severity::section);
		void message(const std::string&, const severity& = severity::message);
		void info(const std::string&, const severity & = severity::info);
		void debug(const std::string&, const severity & = severity::debug);
		

		// Add/print methods.
		void print(const std::stringstream&, const severity& = severity::info) const;
		//std::ostream& add(const level&, std::ostream&) const;			

		//std::string print(const level&, const std::string&) const;   	

		//std::ostream& add(std::iostream&, const level&);   


	protected:

		// No protected at the moment

	private:

		// Message indent level.
		enum class indent : int {
			main = 0,
			sction = 3,
			l2 = 6,
			l3 = 9,
			l4 = 12,
			l5 = 15
		};

		// Current verbosity level.
		severity _verb;

		// Current log width.
		width _width;

		// Current indent level.
		indent _indent;

		// The local temporary log storage deque.
		std::deque<std::stringstream> _log;
		std::deque<int> _lvl;

		// Formatting support routines.
		std::string atab(const int& = 0) const;


		// Tabbing.
		//std::string tab(const char&, const int&) const;
};


// #############################################################################
}  // Close namespaces


// Overloading check
#endif