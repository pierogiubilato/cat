//______________________________________________________________________________	
/*!
 *  Utility Classes for the P-E-A-R Drawing Package
 *
 *	 \author (C) Sarah Zalusky 2010-2013, CERN										  
 */
//______________________________________________________________________________	

//______________________________________________________________________________
// [File name]		"pear_af_Utilities.h"
// [Author]			"Sarah Zalusky"
// [Version]		"1.0"
// [Modified by]	"Sarah Zalusky, Piero Giubilato"
// [Date]			"11 May 2011"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined pear_af_Utilities_H
#define pear_af_Utilities_H

// Application components.
#include "pear_AF.h"


// #############################################################################
namespace pear { namespace af { namespace util {


// Testing utils.

	// Creates a count boxes filled scene.
	void testSceneBoxes(unsigned int count);

// #############################################################################
}}} // Close namespaces

// Overloading check
#endif
