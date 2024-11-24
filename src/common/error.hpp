//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT error object							  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coSet.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"24 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catError_HPP
#define catError_HPP

// Standard library
#include <vector>
#include <string>

//#include <ostream>
#include <sstream>


// Application units.
//#include "coAbc.hpp"


// #############################################################################
// Forward declarations of the class and the global friend function operator<< 
// to avoid the compiler preventing its definition within the namespaced class.
//namespace cat {
//	class error;
//}
// #############################################################################

// #############################################################################
namespace cat {

	// Error type.
	//typedef uint32_t error_t;


	//__________________________________________________________________________
	//! \brief The 'cat::error' class is a simple list of possible error 
	//!		conditions, which are handled by the ostream operator overload
	//!		to provide a minimal explanation.
	enum class error : int
	{
		// No error.
		free,
		
		
		// Connection and network.
		
		
		// cat::co::objects handling.
		coNoOwner,
		coNoChild,
		coNoThisChild,

		// Unhandled errors.
		unknown		= 65535
	};


// #############################################################################
}  // Close namespace


//!_____________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const cat::error& c) {

	switch (c) {
		case cat::error::free: os << "no error"; break;
		
		// cat::co::abc family
		case cat::error::coNoOwner: os << "the object has no owner"; break;
		case cat::error::coNoChild: os << "the object has not thae specified child"; break;
		case cat::error::coNoThisChild: os << "the object has not the specified child"; break;
		
		default: os << "unknown";
	}
	return os;
}


// Overloading check
#endif