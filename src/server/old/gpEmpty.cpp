//------------------------------------------------------------------------------
// CAT empty Graphic Primitive class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpEmpty.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Components
#include "gpEmpty.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType empty::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpEmpty;
}

//______________________________________________________________________________
cat::coVer_t empty::version() const
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
void empty::dump(const int& ind) const
{
	/*! Send out all the box data. */
	std::string pad(ind, ' ');
	std::cout << pad << "[" << COL(LWHITE) << stem() << COL(DEFAULT) << ": ";
	GP::dump();
	std::cout << " ]";
}

//______________________________________________________________________________
bool empty::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// The parent
	GP::stream(o, read);

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