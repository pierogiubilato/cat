//------------------------------------------------------------------------------
// CAT - C++ Analysis Toolkit - Application objects container implementation  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"co.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"24 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________




// Application components - Shared with end User.
#include "console.hpp"

// Application components - Shared between Server and Client.
#include "coSet.hpp"
#include "error.hpp"



// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Ctor.
cat::co::set::set()
{

	// The first object within the objects vector is an empty one..
	_obj.push_back(nullptr);
}

//______________________________________________________________________________
//! Dtor.
cat::co::set::~set()
{

} 





// *****************************************************************************
// **							  Friend members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Dump the object to the standard stream.
//! \brief dump to the console the object status and main properties.
std::ostream& operator<<(std::ostream& os, const cat::co::set& c)
{
	// Object status.
	return (os << "cat::co::set");
}