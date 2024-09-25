//------------------------------------------------------------------------------
// CAT box Graphic Primitive class											  --
// (C) Sarah Zalusky, Piero Giubilato 2011-2013, CERN						  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpBox.cpp"
// [Author]			"Sarah Zalusky"
// [Version]		"1.0"
// [Modified by]	"Sarah Zalusky, Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Application components.
#include "gpBox.h"

#include <glad.h>

// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
box::box()
{
	/*! box constructor with the provided dimensions width (\c xW ), 
	 *	length (\c yL ) and height (\c zH ). By default the box is 
	 *	(0,0,0) centered, xyz aligned and of dimension (2,2,2). 
	 */
	_vtx[0].xyz(-1,-1,-1);
	_vtx[1].xyz( 1,-1,-1);
	_vtx[2].xyz( 1,-1, 1);
	_vtx[3].xyz(-1,-1, 1);
	_vtx[4].xyz(-1, 1,-1);
	_vtx[5].xyz( 1, 1,-1);
	_vtx[6].xyz( 1, 1, 1);
	_vtx[7].xyz(-1, 1, 1);
}

//______________________________________________________________________________
box::box(const double& cX, const double& cY, const double& cZ,
		 const double& sX, const double& sY, const double& sZ)
{
	/*! box constructor with the box centered at \c cX \c cY \c cZ and of size 
	 *	\c sX \c sY \c sZ. By default the box is xyz aligned. 
	 */
	
	// Derive halved dimensions.
	double x = fabs(sX) / 2;
	double y = fabs(sY) / 2;
	double z = fabs(sZ) / 2;
	
	// Set Standard box Vertices
	_vtx[0].xyz(cX - x, cY - y, cZ - z);
	_vtx[1].xyz(cX + x, cY - y, cZ - z);
	_vtx[2].xyz(cX + x, cY - y, cZ + z);
	_vtx[3].xyz(cX - x, cY - y, cZ + z);
	_vtx[4].xyz(cX - x, cY + y, cZ - z);
	_vtx[5].xyz(cX + x, cY + y, cZ - z);
	_vtx[6].xyz(cX + x, cY + y, cZ + z);
	_vtx[7].xyz(cX - x, cY + y, cZ + z);
}

//______________________________________________________________________________
box::box(const double& xW, const double& yL, const double& zH)
{
	/*! box constructor with the provided dimensions width (\c xW ), 
	 *	length (\c yL ) and height (\c zH ). By default the box is 
	 *	(0,0,0) centered and xyz aligned. 
	 */
	
	// Derive dimensions.
	double x = fabs(xW) / 2;
	double y = fabs(yL) / 2;
	double z = fabs(zH) / 2;
		
	// Set Standard box Vertices
	_vtx[0].xyz(-x,-y,-z);
	_vtx[1].xyz( x,-y,-z);
	_vtx[2].xyz( x,-y, z);
	_vtx[3].xyz(-x,-y, z);
	_vtx[4].xyz(-x, y,-z);
	_vtx[5].xyz( x, y,-z);
	_vtx[6].xyz( x, y, z);
	_vtx[7].xyz(-x, y, z);
}

//______________________________________________________________________________
box::box(const double* vtx)
{	
	/*! Overloaded box ctor, takes a 24 floats array to define the box vertexes.
		The array order is {x1, y1, z1, x2, y2, z2, ......, x8, y8, z8}. */
	for (auto i = 0; i < 8; i++) _vtx[i].xyz(vtx[i*3], vtx[i*3+1], vtx[i*3+2]); 
}
	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType box::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpBox;
}

//______________________________________________________________________________
cat::coVer_t box::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string box::stem() const
{
	/*! Returns a string identification. */
	return "box";
}

//______________________________________________________________________________
size_t box::size(const bool& dynamic) const
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = filled::size(true);
	
	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}
//______________________________________________________________________________
void box::dump(const int& ind) const
{
	/*! Send out all the GP data. */
	filled::dump(ind);
	
	// The box.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "box specific\n";
	for (auto i = 0; i < 8; i ++) {
		std::cout << pad3 << "Vtx #" << i << ": " << _vtx[i] << "\n";
	}
}

//______________________________________________________________________________
bool box::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	if(GP::stream(o, read)) return true;
		
	// Streams the vertexes
	for (auto i = 0; i < 8; i++) _vtx[i].stream(o, read);
	
	// Everything fine.
	return false;
}

//______________________________________________________________________________
box& box::trsf(const ge::ref& rf, const bool& inv)
{
	/*! Transforms the box coordinates applying the rf transformation directly
	 *	if inv = false, and by applying the inverse transformation if inv = true. 
	 */
	for (auto i = 0; i < 8; i++) rf.trsf(_vtx[i], inv);
	return *this;
}	


// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
ge::point box::vtx(const int& Idx) const
{
	/*! Returns the Idx th vertex of the box. Returns a (0,0,0) vertex in case
		of OOB call. */
	if (Idx < 8) return _vtx[Idx];
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
void box::glDrawSel()
{
	/*! Draws the selection skeleton. */

	// Common drawing properties are handled by the parent.
	filled::glDrawSel(); 

	// We are drawing the selection even if the object is invisible!.
	
	// Assign object color.
//	glColor4fv(_selColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
//	glLightSuspend();
		
	// Start listing GL vertices 
//	glBegin(GL_LINES); 
		
//	glVertex(_vtx[0]); glVertex(_vtx[1]);
//	glVertex(_vtx[0]); glVertex(_vtx[3]);
//	glVertex(_vtx[0]); glVertex(_vtx[4]);
//	glVertex(_vtx[2]); glVertex(_vtx[1]);
//	glVertex(_vtx[2]); glVertex(_vtx[3]);
//	glVertex(_vtx[2]); glVertex(_vtx[6]);
//	glVertex(_vtx[7]); glVertex(_vtx[3]);
//	glVertex(_vtx[7]); glVertex(_vtx[4]);
//	glVertex(_vtx[7]); glVertex(_vtx[6]);
//	glVertex(_vtx[5]); glVertex(_vtx[1]);
//	glVertex(_vtx[5]); glVertex(_vtx[4]);
//	glVertex(_vtx[5]); glVertex(_vtx[6]);
		
	// box complete!
//	glEnd();

	// Re-enable light in case.
//	glLightRestore();
}

//______________________________________________________________________________
void box::glDraw()
{
	/*! Draws a box/cube object with eight vertices specified as follows: 
	 * 
	 *           y+
	 *           |  z-
	 *           | /
	 *    x-_____|/____x+
	 *           /
	 *          /
	 *         z+
	 *      4-------5
	 *     /|      /|
	 *    7-------6 |
	 *    | 0-----|-1
	 *    |/      |/
	 *    3-------2
	 * 
	 * ORDER IS IMPORTANT! Normal vector calculation assumes points are 
	 * received in an order which maintains right-handed orientation of 
	 * the surface.  
	 */
	
	// Common drawing properties are handled by the parent.
	filled::glDraw(); 

	// If not visible, bye bye.
	if (!modeVisible()) return;
	
	// Stroke outline.
	if (_strkEnable) {

		// Assign object color.
//		glColor4fv(_strkColor);
		
		// Switch off lighting in case for the stroke part of the drawing.
//		glLightSuspend();
		
		// Start listing GL vertices 
//		glBegin(GL_LINES); 
		
		// Draw al 12 edges.
//		glVertex(_vtx[0]); glVertex(_vtx[1]);
//		glVertex(_vtx[0]); glVertex(_vtx[3]);
//		glVertex(_vtx[0]); glVertex(_vtx[4]);
//		glVertex(_vtx[2]); glVertex(_vtx[1]);
//		glVertex(_vtx[2]); glVertex(_vtx[3]);
//		glVertex(_vtx[2]); glVertex(_vtx[6]);
//		glVertex(_vtx[7]); glVertex(_vtx[3]);
//		glVertex(_vtx[7]); glVertex(_vtx[4]);
//		glVertex(_vtx[7]); glVertex(_vtx[6]);
//		glVertex(_vtx[5]); glVertex(_vtx[1]);
//		glVertex(_vtx[5]); glVertex(_vtx[4]);
//		glVertex(_vtx[5]); glVertex(_vtx[6]);
		
		// box complete!
//		glEnd();

		// Re-enable light in case.
//		glLightRestore();
	}
	
	// Solid filling.
	if (_fillEnable) {

		// Assign object color
//		glColor4fv(_fillColor);
		
		// Draw model in two passes (In case of transparency) rendering the 
		// back faces on the first pass and front faces on the second pass.
		//for(auto pass = 0; pass < 2; ++pass ) {	
		
			//glCullFace((pass == 0) ? GL_FRONT : GL_BACK);
		
			// Start listing GL vertices 
//			glBegin(GL_QUADS); 
		
			// Back Face.
//			glNormal(_vtx[0], _vtx[4], _vtx[1]);
//			glVertex(_vtx[0]); glVertex(_vtx[4]); glVertex(_vtx[5]); glVertex(_vtx[1]);

			// Front Face.
//			glNormal(_vtx[3], _vtx[2], _vtx[7]);
//			glVertex(_vtx[3]); glVertex(_vtx[2]); glVertex(_vtx[6]); glVertex(_vtx[7]);

			// Left Face.
//			glNormal(_vtx[0], _vtx[3], _vtx[4]);
//			glVertex(_vtx[0]); glVertex(_vtx[3]); glVertex(_vtx[7]); glVertex(_vtx[4]);

			// Right Face.
//			glNormal(_vtx[1], _vtx[5], _vtx[2]);
//			glVertex(_vtx[1]); glVertex(_vtx[5]); glVertex(_vtx[6]); glVertex(_vtx[2]);

			// Bottom Face.
//			glNormal(_vtx[0], _vtx[1], _vtx[3]);
//			glVertex(_vtx[0]); glVertex(_vtx[1]); glVertex(_vtx[2]); glVertex(_vtx[3]);

			// Top Face.
//			glNormal(_vtx[4], _vtx[7], _vtx[5]);
//			glVertex(_vtx[4]); glVertex(_vtx[7]); glVertex(_vtx[6]); glVertex(_vtx[5]);
	
			// Done writing vertex list!	
//			glEnd();
		//}
	}
}

//______________________________________________________________________________
void box::glDrawEnd()
{
	/*! Closes the GP drawing. */
	filled::glDrawEnd();
}

// *****************************************************************************
// **							     ui Functions							  **
// *****************************************************************************


// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace
