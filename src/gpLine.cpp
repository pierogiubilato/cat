//------------------------------------------------------------------------------
// CAT line Graphic Primitive class											  --
// (C) Piero Giubilato, Sarah Zalusky 2011-2024, Padova University			  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpLine.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application components.
#include "gpLine.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
line::line()
{
	/*! line ctor, automatic version. This is usually the one called by the
	 *	GP objects factory.
	 */
	_vtx[0].xyz(-1.0f, -1.0f, -1.0f);
	_vtx[1].xyz(1.0f, 1.0f, 1.0f);

}

//______________________________________________________________________________
line::line(const double& x1, const double& y1, const double& z1,
		   const double& x2, const double& y2, const double& z2)
{
	/*! line constructor with starting point (x1, y1, z1) and end 
	 *	point (x2, y2, z2). 
	 */
	_vtx[0].xyz(x1, y1, z1);
	_vtx[1].xyz(x2, y2, z2);
}

//______________________________________________________________________________
line::line(const double* _vtx)
{	
	/*! Overloaded line constructor, takes a 6 floats array to define the line
	 *	Array order is {x1, y1, z1, x2, y2, z2}.
	 */
	_vtx[0].xyz(_vtx[0], _vtx[1], _vtx[2]);
	_vtx[1].xyz(_vtx[3], _vtx[4], _vtx[5]);  
}

	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType line::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpLine;
}

//______________________________________________________________________________
Uint64 line::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string line::stem() const
{
	/*! Returns a string identification. */
	return "line";
}

//______________________________________________________________________________
size_t line::size(const bool& dynamic) const
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
void line::dump(const Uint64& ind) const
{
	/*! Send out all the GP data. */
	stroked::dump(ind);
	
	// The line.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "line specific\n"
			  << pad3 << "Vtx #0: " << _vtx[0] << "\n"
			  << pad3 << "Vtx #1: " << _vtx[1] << "\n";
}

//______________________________________________________________________________
bool line::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	stroked::stream(o, read);
		
	// Streams the vertexes
	for (Uint64 i = 0; i < 2; i++) _vtx[i].stream(o, read);
	
	// Everything fine.
	return false;
}

//______________________________________________________________________________
line& line::trsf(const ge::ref& rf, const bool& inv)
{
	/*! Transforms the line coordinates applying the rf transformation directly
	 *	if inv = false, and by applying the inverse transformation if inv = true. 
	 */
	rf.trsf(_vtx[0], inv);
	rf.trsf(_vtx[1], inv);
	return *this;
}


// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
ge::point line::_vtx(const Uint64& idx) const
{
	/*! Returns the Idx th vertex of the box. Returns a (0,0,0) vertex in case
	 *	of OOB call. 
	 */
	if (idx < 2) return _vtx[idx];
	else return ge::point(0, 0, 0);
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
void line::glDrawSel()
{
	/*!	Draws a the line selection skeleton. */
	
	// Set up the selection drawing style.
	stroked::glDrawSel(); 	

	// Assign object color
//	glColor4fv(GP::_selColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
//	glLightSuspend();
		
	// Start listing GL vertices 
//	glBegin(GL_LINES); 
//	glVertex(_vtx[0]); glVertex(_vtx[1]);
//	glEnd();
	
	// Re-enable light in case.
//	glLightRestore();
}

//______________________________________________________________________________
void line::glDraw()
{
	/*!	Draws a line object with two vertices in the 3D space. */
		
	// Common drawing properties are handled by the parent GP.
	stroked::glDraw();

	// If not visible, bye bye.
	if (!modeVisible()) return;
		
	// Stroke outline.
	if (_strkEnable) {
	
		// Assign object color
//		glColor4fv(_strkColor);
		
		// Switch off lighting in case for the stroke part of the drawing.
//		glLightSuspend();		
		
		// Start listing GL vertices 
//		glBegin(GL_LINES); 
//		glVertex(_vtx[0]); glVertex(_vtx[1]);
//		glEnd();

		// Re-enable light in case.
//		glLightRestore();
	}
}

//______________________________________________________________________________
void line::glDrawEnd()
{
	/*! Closes GP drawing. */
	stroked::glDrawEnd();	
}

// *****************************************************************************
// **							   ui Functions								  **
// *****************************************************************************

// End of PEAR_SERVER if
#endif


// #############################################################################
}} // Close namespace