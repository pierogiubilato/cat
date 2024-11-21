//------------------------------------------------------------------------------
// CAT - C++ Analysis Toolkit - Application user interface abstract class	  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiAbc.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"21 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// STL components.
#include <algorithm>

// Application components - Shared with end User.
#include "console.hpp"

// Application components - Shared between Server and client.
#include "uiAbc.hpp"


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
cat::ui::abc::abc()
{
}

//______________________________________________________________________________
//! Destructor	*/
cat::ui::abc::~abc()
{

} 


// *****************************************************************************
// **							  Friend members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Dump the object to the standard stream.
//! \brief dump to the console the object status and main properties.
std::ostream& operator<<(std::ostream& os, const cat::ui::abc& c)
{
	// Return the stream.
	return os;
}

// *****************************************************************************
// **							  Public members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Write/Read the object into a stream.
//! \brief write/read the object to/from a std::stringstream. This is used to 
//!		save/load the object and/or duplicate it across sockets or other means.
//!		Important: thw function writes all the object data, except the object 
//!		type, which MUST be pre-happened to the writing call, so that a factory
//!		will create the right object in the read phase, and then call the stream
//!		read function to recreate it.
//! \argument \c ss is the std::stringstream the object must be written into, or
//!		read from.
//! \argument \c read is a boolean (default false) setting whether the operation
//!		is a write (default) or read one.
//! \return \c 0 if everything right, error code otherwise.
//! 
int cat::ui::abc::stream(std::stringstream& ss, const bool& read)
{

	/*
	// Version/Type check.
	if (read) {

		// Check type and version consistency
		uint64_t typeCheck = 0;
		uint64_t versionCheck = 0;
		af::stream::read(o, typeCheck);
		if (typeCheck != type()) {
			throw std::runtime_error("cat::GP::stream incorrect Type!");
		}
		af::stream::read(o, versionCheck);
		if (versionCheck != version()) {
			throw std::runtime_error("cat::GP::Stream incorrect Version!");
		}

	// Write type and version for later checking.
	} else {
		af::stream::write(o, type());
		af::stream::write(o, version());
	}

	// Read/Write all the GP properties from/into the stream.

	// General.
	af::stream::rw(o, _handle, read);
	af::stream::rw(o, _parentHnd, read);
	af::stream::rw(o, _name, read);
	af::stream::rw(o, _info, read);

	// Style.
	af::stream::rw(o, _modeVisible, read);
	af::stream::rw(o, _modeWire, read);
	af::stream::rw(o, _modeFrozen, read);
	af::stream::rw(o, _modeSelected, read);

	// Inheritance.
	af::stream::rw(o, _inhrAppear, read);
	af::stream::rw(o, _inhrVisible, read);
	af::stream::rw(o, _inhrAlpha, read);
	af::stream::rw(o, _inhrWire, read);
	af::stream::rw(o, _inhrRef, read);

	// Everything fine!
	return false;

	*/


	// Return the stream.
	//return ss;
	return 0;
}