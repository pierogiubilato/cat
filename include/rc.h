//------------------------------------------------------------------------------
// PEAR Remote Client, include this file into your application				  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"pear_RC.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"30 Aug 2011"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined pear_RC_H
#define pear_RC_H

#include "pear_rc_Macros.h"

// #############################################################################
namespace pear { namespace rc {

//! Pear rc::RC
/*! pear::rc::RC is the class which is accessible to the user. It is the class 
 *	to instantiate in order to open a connection with the server and start
 *	drawing your scene!
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 30 Aug 2011
 */
class RC: public Macros 
{
	public:

	// Special members.
	PEAR_API PEAR_CALL RC(const char* host, const Uint16& port, const Uint64& verb = 0)
					   :Macros(host, port, verb) {;}; 
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
