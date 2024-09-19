//------------------------------------------------------------------------------
// CAT polygon Graphic Primitive class										  --
// (C) Piero Giubilato, Sarah Zalusky 2011-2024, Padova University			  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpPolygon.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application components.
#include "gpPolygon.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
polygon::polygon()
{
	/*! Polygon ctor, automatic version. This is usually the one called by the
	 *	GP objects factory. Set a polygon actually made by no points.
	 */
	_vtx.clear();
	_vtx.push_back(ge::point(0, 0, 0)); 
	_vtx.push_back(ge::point(1, 0, 0));
	_vtx.push_back(ge::point(1, 1, 0));
	_vtx.push_back(ge::point(1, 1, 1));
	_closed = false;
}

//______________________________________________________________________________
polygon::polygon(const ge::point* v, const Uint64& vCnt, const bool& closed)
{
	/*! Polygon constructor with an array of vertexes. */
	_vtx.clear();
	_vtx.reserve(vCnt);
	for (Uint64 i = 0; i < vCnt; i++) {
		_vtx.push_back(ge::point(v[i])); 	
	}
	_Closed = closed;	
}

	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 polygon::type() const
{
	/*! Returns a numeric identification. */
	return stroked::type() + GP::ktype::polygon;
}

//______________________________________________________________________________
Uint64 polygon::version() const
{
	/*! Returns a numeric version. */
	return 100;
}

//______________________________________________________________________________
std::string polygon::stem() const
{
	/*! Returns a string identification. */
	return "polygon";
}

//______________________________________________________________________________
size_t polygon::size(const bool& dynamic) const
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = stroked::size(true);
	tSize += _vtx.capacity() * sizeof(ge::point);

	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}

//______________________________________________________________________________
void polygon::dump(const Uint64& ind) const
{
	/*! Send out all the GP data. */
	stroked::dump(ind);
	
	// The polygon.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "Polygon specific\n";
	for (Uint64 i = 0; i < _vtx.size(); i ++) {
		std::cout << pad3 << "Vtx #" << i << ": " << _vtx[i] << "\n";
	}
}

//______________________________________________________________________________
bool polygon::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	stroked::stream(o, read);
		
	// Reads from stream.
	if (read) {
		af::stream::read(o, _closed);
		Uint64 count = 0;
		af::stream::Read(o, count);
		_vtx.clear();
		_vtx.reserve(count);
		for (Uint64 i = 0; i < count; i++) {
			_vtx.push_back(ge::point());
			_vtx[i].stream(o, read);
		}
		
	// Writes to stream.
	} else {
		af::stream::write(o, _closed);
		Uint64 count = _vtx.size();
		af::stream::Write(o, count);
		for (Uint64 i = 0; i < count; i++) _vtx[i].stream(o, read);
	}

	// Everything fine.
	return false;
}

//______________________________________________________________________________
polygon& polygon::trsf(const ge::ref& rf, const bool& inv)
{
	/*! Transforms the box coordinates applying the rf transformation directly
	 *	if inv = false, and by applying the inverse transformation if inv = true. 
	 */
	for (unsigned int i = 0; i < _vtx.size(); i++) rf.trsf(_vtx[i], inv);
	return *this;
}


// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
ge::point polygon::vtx(const Uint64& idx) const
{
	/*! Returns the Idx th vertex of the box. Returns a (0,0,0) vertex in case
	 *	of OOB call. */
	if (idx < _vtx.size()) return _vtx[idx];
	else return ge::point(0, 0, 0);
}

//______________________________________________________________________________
size_t polygon::vtxCount() const
{
	return _vtx.size();
}


// *****************************************************************************
// **								SERVER SIDE								  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER

// *****************************************************************************
// **								gl Functions							  **
// *****************************************************************************

//______________________________________________________________________________
void polygon::glDrawSel()
{
	/*!	Draws a the line selection skeleton. */
	
	// Set up the selection drwing style.
	stroked::glDrawSel(); 	

	// Assign object color
//	glColor4fv(_selColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
//	glLightSuspend();
		
	// Start listing GL vertices 
//	_closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP); 
//	for (Uint64 i = 0; i < _vtx.size(); i++) glVertex(_vtx[i]);
//	glEnd();
	
	// Re-enable light in case.
//	glLightRestore();
}

//______________________________________________________________________________
void polygon::glDraw()
{
	/*!	Draws a polygon object with two vertices in the 3D space. */
	
	// Begins drawing operations.
	stroked::glDraw(); 

	// If not visible, bye bye.
	if (!modeVisible() || _vtx.size() == 0) return;
		
	// Stroke outline.
	if (_strkEnable) {
	
		// Assign object color
//		glColor4fv(_strkColor);
		
		// Switch off lighting in case for the stroke part of the drawing.
//		glLightSuspend();
		
		// Start listing GL vertices. 
//		_closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP); 
		for (Uint64 i = 0; i < _vtx.size(); i++) glVertex(_vtx[i]);
//		glEnd();

		// Re-enable light in case.
//		glLightRestore();
	}
}

//______________________________________________________________________________
void polygon::glDrawEnd()
{
	// Complete drawing operations.
	stroked::glDrawEnd(); 
}


// *****************************************************************************
// **								ui Functions							  **
// *****************************************************************************

// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace