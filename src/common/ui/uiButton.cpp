//------------------------------------------------------------------------------
// CAT - C++ Analysis Toolkit - Application user interface button impl.		  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiButton.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// STL components.
#include <algorithm>

// Application components - Shared with end User.
#include "console.hpp"

// Application components - Shared between Server and client.
#include "uiButton.hpp"


//##############################################################################
//namespace cat {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
//! GP (Graphic Primitive) is the root object for all the PEAR graphic
//!	primitives intended for drawing. It contains the default properties 
//! shared by every primitive, plus the management for the "family ties" 
//! and other related tasks.
cat::ui::button::button()
{
}

//______________________________________________________________________________
//! Destructor	*/
cat::ui::button::~button()
{

} 


// *****************************************************************************
// **							  Friend members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Dump the object to the standard stream.
//! \brief dump to the console the object status and main properties.
std::ostream& operator<<(std::ostream& os, const cat::ui::button& c)
{
	// Return the stream.
	return os;
}

// *****************************************************************************
// **							  Public members							  **
// *****************************************************************************
