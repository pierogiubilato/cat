//------------------------------------------------------------------------------
// CAT Application Facility file class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afFile.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined afFile_H
#define afFile_H

// STL.
#include <string>
#include <vector>

// Application
//#include "af.h"


// #############################################################################
namespace cat { namespace af {

//! CAT file
/*! cat::file provides files management and I/O. To browse files/dirs it uses
 *	the dirent library (in windows environment a dirent.h files is provided
 *	in the dependencies folder to emulate the missing lib).
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 16 Apr 2024
 */

//______________________________________________________________________________
class file //: public AF
{
	private:
	
	protected:
	
	public:

		// Special members
		file(); 
		~file();

		// Fills a list with all the files of a given path.
		bool list(const std::string& path, std::vector<std::string>& list);

				
};

// *****************************************************************************
// **						Global namespace overloads						  **
// *****************************************************************************

// #############################################################################
}} // Close namespaces

// Overloading check
#endif