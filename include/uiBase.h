//------------------------------------------------------------------------------
// Primitives object for the CAT Graphics User Interface	  				  --
// (C) Piero Giubilato 2011-2013, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"ui.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"10 Sep 2024"
// [Language]		"C++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef uiBase_H
#define uiBase_H

// Application
#include "acMain.h"
#include "afStream.h"

// Windows checks and inclusions for OpenGL.
#if defined(_WIN32) || defined(_WIN64)
	//#include <windows.h> // required by gl.h
	//#include <oleauto.h>
#endif

// Open GL - with extensions up to OpenGL 3.1. GLEW manages
// the extention, otherwise the provided Windows .h files
// just manages up to the version 1.2
////#include <glew/glew.h>


// #############################################################################
namespace cat { namespace ui {

	// *****************************************************************************
	// **							Types and Structures						  **
	// *****************************************************************************


	// *****************************************************************************
	// **							The basic pear UI							  **
	// *****************************************************************************

	/*! cat::ui::base is the base class for all pear user interface elements. This 
	 *  class implements a very basic container, providing virtual interface and 
	 *  includes.
	 *
	 *	\author Piero Giubilato
	 *	\version 1.0
	 *	\date 10 Sep 2024
	 */

	 //______________________________________________________________________________
	class base
	{
	private:

	protected:
	public:
	};

	// #############################################################################
}
} // Close namespaces

// Overloading check
#endif
