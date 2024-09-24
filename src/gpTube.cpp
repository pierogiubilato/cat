//------------------------------------------------------------------------------
// CAT tube Graphics Primitive class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpTube.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Application components.
#include "gpTube.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							 Special members							  **
// *****************************************************************************

//______________________________________________________________________________
tube::tube()
{
	/*! Tube ctor, automatic version. This is usually the one called by the
	 *	GP objects factory.	It creates a close cylinder.
	 */
	_riBase = 0;
	_roBase = 1;
	_riTop = 0;
	_roTop = 1;
	_Height = 2;
	_Slices = 10;
	_Stacks = 1;	
}

//______________________________________________________________________________
tube::tube(const double& riBase, const double& roBase, const double& riTop, 
		   const double& roTop, const double& height, const Uint32& slices, 
		   const Uint32& stacks)
{
	/*! Constructor with base and top radiuses (riBase, roBase, riTop, roTop), 
	 *	height and number of faces around the z axis (slices) and subdivisions 
	 *	along the z axis (stacks).
	 */
	_riBase = riBase;	if (_riBase < 0) _riBase = 0;
	_roBase = roBase;	if (_roBase < _riBase) _roBase = _riBase;
	_riTop = riTop;		if (_riTop < 0) _riTop = 0;
	_roTop = roTop;		if (_roTop < _riTop) _roTop = _riTop;
	_height = height;	if (_height <= 0) _height = 1;
	_slices = slices;	if (_slices < 4) _slices = 4;
	_stacks = stacks;	if (_stacks < 1) _stacks = 1;
}

	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType tube::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpTube;
}

//______________________________________________________________________________
Uint64 tube::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string tube::stem() const
{
	/*! Returns a string identification. */
	return "tube";
}

//______________________________________________________________________________
size_t tube::size(const bool& dynamic) const
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
void tube::dump(const Uint64& ind) const
{
	/*! Send out all the GP data. */
	
	// Quick out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)

	// The parent.
	filled::dump(ind);
		
	// The box.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "Sphere specific\n";
	std::cout << pad3 << "Base radius: " << CLW << _riBase << CD << " (inner), " 
										 << CLW << _roBase << CD << " (outer)\n"
			  << pad3 << "Top radius:  " << CLW << _riTop << CD << " (inner), " 
										 << CLW << _roTop << CD << " (outer)\n"
			  << pad3 << "Height:      " << CLW << _height << CD << "\n"
			  << pad3 << "Slices:      " << CLW << _slices << CD << "\n"
			  << pad3 << "Stacks:      " << CLW << _stacks << CD << "\n";

	// Release.
	#undef CLW
	#undef CD
}

//______________________________________________________________________________
bool tube::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	filled::stream(o, read);
		
	// Streams the cylinder properties.
	af::stream::RW(o, _riBase, read);
	af::stream::RW(o, _roBase, read);
	af::stream::RW(o, _riTop, read);
	af::stream::RW(o, _roTop, read);
	af::stream::RW(o, _Height, read);
	af::stream::RW(o, _slices, read);
	af::stream::RW(o, _stacks, read);
		
	// Everything fine.
	return false;
}

// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************


// *****************************************************************************
// **							  Drawing functions							  **
// *****************************************************************************

// Drawing function are available only for the SERVER.
#ifdef CAT_SERVER

//______________________________________________________________________________
void tube::glDrawSel()
{
	/*!	Draws a the line selection skeleton. */
	
	// Set up the selection drawing style.
	filled::glDrawSel(); 	

	// Assign object color
//	glColor4fv(_selColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
//	glLightSuspend();
		
	// Draw the external cylinder wireframe.
//	GLUquadricObj* qObj = gluNewQuadric();
//	gluQuadricDrawStyle(qObj, GLU_LINE); /* flat shaded */
//	gluQuadricNormals(qObj, GLU_FLAT);
//	gluCylinder(qObj, _roBase, _roTop, _Height, _Slices, _Stacks);
//	gluDeleteQuadric(qObj);

	// If it is a tube, draw the inner wireframe also.
	if (type() & ktype::tube) {
//		GLUquadricObj* qObj = gluNewQuadric();
//		gluQuadricDrawStyle(qObj, GLU_LINE); /* flat shaded */
//		gluQuadricNormals(qObj, GLU_FLAT);
//		gluCylinder(qObj, _riBase, _riTop, _Height, _Slices, _Stacks);
//		gluDeleteQuadric(qObj);
	}
		
	// Re-enable light in case.
//	glLightRestore();
}

//______________________________________________________________________________
void tube::glDraw()
{
	/*!	Draws a line object with two vertices in the 3D space. */
		
	// Common drawing properties are handled by the parent GP.
	filled::glDraw();

	// If not visible, bye bye.
	if (!modeVisible()) return;
	
	// Stroke outline.
	if (_strkEnable) {
	
		// Assign object color
//		glColor4fv(_strkColor);
		
		// Switch off lighting in case for the stroke part of the drawing.
//		glLightSuspend();		
		
		// Draw the stroked outer wireframe.
//		GLUquadricObj* qObj = gluNewQuadric();
		//gluQuadricCallback(qObj, GLU_ERROR, errorCallback);
//		gluQuadricDrawStyle(qObj, GLU_LINE); /* flat shaded */
//		gluQuadricNormals(qObj, GLU_FLAT);
//		gluCylinder(qObj, _roBase, _roTop, _Height, _Slices, _Stacks);
//		gluDeleteQuadric(qObj);

		// If it is a tube, draw the inner wireframe also.
		if (type() & ktype::tube) {
//			GLUquadricObj* qObj = gluNewQuadric();
//			gluQuadricDrawStyle(qObj, GLU_LINE); /* flat shaded */
//			gluQuadricNormals(qObj, GLU_FLAT);
//			gluCylinder(qObj, _riBase, _riTop, _Height, _Slices, _Stacks);
//			gluDeleteQuadric(qObj);
		}

		// Re-enable light in case.
//		glLightRestore();
	}

	// Solid filling.
	if (_fillEnable) {

		// Assign object color
//		glColor4fv(_fillColor);
		
		// Draw the outer cylinder surface fill.
//		GLUquadricObj* qObj = gluNewQuadric();
//		gluQuadricDrawStyle(qObj, GLU_FILL);
//		gluQuadricNormals(qObj, GLU_SMOOTH);
//		gluQuadricOrientation(qObj, GLU_OUTSIDE);
//		gluCylinder(qObj, _roBase, _roTop, _Height, _Slices, _Stacks);
//		gluDeleteQuadric(qObj);

		// If it is a tube, draw the inner surface also.
		if (type() & ktype::tube) {
//			GLUquadricObj* qObj = gluNewQuadric();
//			gluQuadricDrawStyle(qObj, GLU_FILL); /* flat shaded */
//			gluQuadricNormals(qObj, GLU_SMOOTH);
//			gluQuadricOrientation(qObj, GLU_INSIDE);
//			gluCylinder(qObj, _riBase, _riTop, _Height, _Slices, _Stacks);
//			gluDeleteQuadric(qObj);
		}
		
		// Draw the base cap.
		if (_roBase > 0) {
//			GLUquadricObj* qObj = gluNewQuadric();
//			gluQuadricDrawStyle(qObj, GLU_FILL);
//			gluQuadricNormals(qObj, GLU_SMOOTH);
//			gluQuadricOrientation(qObj, GLU_INSIDE);
//			gluDisk(qObj, _riBase, _roBase, _Slices, 3);
//			gluDeleteQuadric(qObj);
		}

		// Draw the top cap.
		if (_roTop > 0) {
			
			// Move the drawing plane to the top
//			glMatrixMode(GL_MODELVIEW);
//			glPushMatrix();
//			glTranslated(0, 0, _Height);
			
			// Draw the disk
//			GLUquadricObj* qObj = gluNewQuadric();
//			gluQuadricDrawStyle(qObj, GLU_FILL);
//			gluQuadricNormals(qObj, GLU_SMOOTH);
//			gluQuadricOrientation(qObj, GLU_OUTSIDE);
//			gluDisk(qObj, _riTop, _roTop, _Slices, 1);
//			gluDeleteQuadric(qObj);
//
			// Restore reference frame.
//			glPopMatrix();
		}
	}
}

//______________________________________________________________________________
void tube::glDrawEnd()
{
	// Complete drawing operations.
	filled::glDrawEnd(); 
}

// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace