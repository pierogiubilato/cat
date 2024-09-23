//------------------------------------------------------------------------------
// CAT Remote Client, include this file into your application				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"pear_RC.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined RC_H
#define RC_H

#include "rcMacros.h"

// #############################################################################
namespace cat { namespace rc {

//! cat rc::RC
/*! cat::rc::RC is the class which is accessible to the user. It is the class 
 *	to instantiate in order to open a connection with the server and start
 *	drawing your scene!
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 23 Sep 2024
 */
class RC: public macros 
{
	public:

	// Special members.
	CAT_API CAT_CALL RC(const char* host, 
						const Uint16& port, 
						const Uint64& verb = 0)
					    : macros(host, port, verb) {;}; 
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
