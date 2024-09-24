//------------------------------------------------------------------------------
// CAT point Graphic Primitive class										  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpPoint.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2011"
// [Language]		"c++"
//______________________________________________________________________________


// Application components.
#include "gpPoint.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
point::point()
{
	/*! Point ctor, automatic version. This is usually the one called by the
	 *	GP objects factory.
	 */
	_vtx.XYZ(0, 0, 0);
	_strkWidth = 1.0f;
}

//______________________________________________________________________________
point::point(const double& x, const double& y, const double& z, const double& r)
{
	/*! Point constructor with point (x, y, z) and radius. */
	_vtx.xyz(x, y, z);
	_strkWidth = static_cast<float>(r);
}

//______________________________________________________________________________
point::point(const double* vtx, const double& r)
{	
	/*! Overloaded Point constructor, takes a 3 floats array to define the line
	 *	Array order is {x, y, z}.
	 */
	_vtx.xyz(vtx[0], vtx[1], vtx[2]);
	_strkWidth = static_cast<float>(r);  
}

	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType point::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpPoint;
}

//______________________________________________________________________________
Uint64 point::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string point::stem() const
{
	/*! Returns a string identification. */
	return "point";
}

//______________________________________________________________________________
size_t point::size(const bool& dynamic) const
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = stroked::size(true);
	
	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}

//______________________________________________________________________________
void point::dump(const Uint64& ind) const
{
	/*! Send out all the GP data. */
	Stroked::Dump(ind);
	
	// The point.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "Point specific\n"
			  << pad3 << "vtx #0: " << _Vtx << "\n";
}

//______________________________________________________________________________
bool point::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	stroked::stream(o, read);
		
	// Streams the vertexes
	_vtx.stream(o, read);
		
	// Everything fine.
	return false;
}

//______________________________________________________________________________
point& point::trsf(const ge::ref& rf, const bool& inv)
{
	/*! Transforms the point coordinates applying the rf transformation directly
	 *	if inv = false, and by applying the inverse transformation if inv = true. 
	 */
	rf.trsf(_vtx, inv);
	return *this;
}


// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
point point::vtx() const
{
	/*! Returns the Idx th vertex of the box. Returns a (0,0,0) vertex in case
	 *	of OOB call. 
	 */
	return _vtx;
}

// *****************************************************************************
// **							     SERVER SIDE							  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER


// *****************************************************************************
// **							     gl Functions							  **
// *****************************************************************************

//______________________________________________________________________________
void point::glDrawSel()
{
	/*!	Draws a the line selection skeleton. */
	
	// Set up the selection drawing style.
	stroked::glDrawSel(); 	

	// Set the point size in pixels.	
	glPointSize(_strkWidth);
	
	// Assign object color
	glColor4fv(_selColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
	glLightSuspend();
	
	// Get point position in the 2D viewport.
	ge::point p = gp::glPointTo2D(_vtx);
	
	// Draw a circle on the 2D viewport centere on point position.
	gl2DEnter();
	gl2DCircle(p.X(), p.Y(), _strkWidth + 10);
	gl2DExit();

	// Re-enable light in case.
	glLightRestore();
}

//______________________________________________________________________________
void point::glDraw()
{
	/*!	Draws a line object with two vertices in the 3D space. */
		
	// Common drawing properties are handled by the parent GP.
	stroked::glDraw();

	// If not visible, bye bye.
	if (!modeVisible()) return;
	
	// Set the point size in pixels.	
	glPointSize(_strkWidth);

	// Assign point color.
	glColor4fv(_strkColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
	glLightSuspend();
	
	// Start listing GL vertices 
	glBegin(GL_POINTS); 
	glVertex(_vtx);
	glEnd();

	// Re-enable light in case.
	glLightRestore();
}

//______________________________________________________________________________
void point::glDrawEnd()
{
	// Complete drawing operations.
	stroked::glDrawEnd(); 
}

// *****************************************************************************
// **							   ui Functions								  **
// *****************************************************************************

// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace