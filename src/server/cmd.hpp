//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Logging utility                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"23 Oct 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef cmd_HPP
#define cmd_HPP

// Standard library
#include <string>
#include <vector>
#include <map>




//_____________________________________________________________________________


// #############################################################################
namespace cat {


//______________________________________________________________________________
class cmd
{

	public:

		// Special members.
		cmd();		//!< Ctor.
		~cmd();		//!< Dtor.

		// Friend stream operators.


		// Standard methods.
		void addArg(const std::string&, const std::string& = "", const bool& = true); //!< Add argument.
		void addOpt(const std::string&, const std::string& = "", const bool& = false, const bool& = false); //!< Add option.
		bool isOptionPresent(const std::string&) const; //!< Returns whether an option is present.
		std::string getOptionValue(const std::string&, const std::string&) const; //!< Returns an option value.
		std::string getArgumentValue(const std::string&) const; //!< Returns specific argument value.
		void printHelp() const;							//!< Show short help.
		int parse(int argc, char* argv[]);				//!< Parse the command line.

	protected:

		// No protected at the moment

	private:

		// Argument(s) and option(s) storage structure.
		struct argOption {
			bool present;
			std::string description;
			std::string value;
			bool required;
			bool requiresValue;
		};

		// Arguments DB.
		std::map<std::string, argOption> _args;
		std::map<std::string, argOption> _options;
};


// #############################################################################
}  // Close namespaces


// Overloading check
#endif