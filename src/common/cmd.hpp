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
		// -----------------


		//! Add an argument to search for in the command line.
		///
		/// \brief Add parameter to search for in the command line. A parameter can 
		///			be 	made mandatory or not. When a mandatory parameter(s) is not 
		///			found, the parsing function 'parse' returns an error.
		///	\param prm is a string representing the parameter signature, e.g. 
		///			"verbosity" or "v".
		///	\param desc is a string containing the parameter description, shown
		///			when the help is invoked.
		///	\param req is a boolean, which makes the parameter mandatory, i.e. 
		///			if the parameter is missing the parsing fuction will return 
		///			an error.
		///	\return nothing
		void addArg(const std::string& prm, const std::string& desc = "", const bool& req = true);
		

		//! Add an option to search for in the command line.
		///
		/// \brief Add options to search for in the command line. An option can be 
		///			made mandatory or not, as well as having mandatory or not values
		///			attached to it. When a mandatory option(s) and/or option value(s)
		///			are not found, the parsing function 'parse' returns an error.
		///	\param opt is a string representing the option signature, e.g. 
		///			"verbosity" or "v".
		///	\param desc is a string containing the option description, shown 
		///			when the help is invoked.
		///	\param req is a boolean, which makes the option mandatory, i.e. 
		///			if the parameter is missing the parsing fuction will return 
		///			an error.
		///	\param reqVal is a boolean, which makes the option having a value 
		///			mandatory, i.e. if the option value is missing the parsing 
		///			fuction will return an error.
		///	\return nothing.
		void addOpt(const std::string& opt, const std::string& desc = "", const bool& req = false, const bool& reqVal = false); //!< Add option.
		
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