//------------------------------------------------------------------------------
// CAT empty Graphic Primitive class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpEmpty.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Components
#include "gpEmpty.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 empty::type() const
{
	/*! Returns a numeric identification. */
	return GP::Type() + GP::kgp_Virtual;
}

//______________________________________________________________________________
Uint64 empty::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string empty::stem() const
{
	/*! Returns a string identification. */
	return "empty";
}

//______________________________________________________________________________
void empty::dump(const Uint64& ind) const
{
	/*! Send out all the box data. */
	std::string pad(ind, ' ');
	std::cout << pad << "[" << COL(LWHITE) << Stem() << COL(DEFAULT) << ": ";
	GP::Dump();
	std::cout << " ]";
}

//______________________________________________________________________________
bool empty::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// The parent
	GP::Stream(o, read);

	// To be implemented
	return false;
}

// *****************************************************************************
// **							  Drawing functions							  **
// *****************************************************************************

// Drawing function are available only for the SERVER.
#ifdef CAT_SERVER

//______________________________________________________________________________
void empty::glDrawSel()
{
	/*!	Nothing to actually draw, just keep the drawing pipeline. */
	
	// Set up the selection drawing style.
	GP::glDrawSel(); 	
	
	// Complete drawing operations.
	GP::glDrawEnd();
}

//______________________________________________________________________________
void empty::glDraw()
{
	/*!	Draws a line object with two vertices in the 3D space. */
		
	// Common drawing properties are handled by the parent GP.
	GP::glDraw();

	// Complete drawing operations.
	GP::glDrawEnd();
}

// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace