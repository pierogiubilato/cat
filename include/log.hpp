//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Logging utility                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"25 Jul 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once


// Standard library
#include <iostream>
#include <stream>



//______________________________________________________________________________
//! Logger utility with verbosity control.
/*!	The log overloads the standard << operator to provide some very basic

*/

//______________________________________________________________________________

// Overloading check
#ifndef log_HPP
#define log_HPP



//______________________________________________________________________________



// Overload << operator in the main namespace
inline std::ostream& operator<<(std::ostream& o, const int verb)
{


}


// Overloading check
#endif