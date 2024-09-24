//------------------------------------------------------------------------------
// CAT sphere Graphic Primitive class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpSphere.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Application components.
#include "gpSphere.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							 Special members							  **
// *****************************************************************************

//______________________________________________________________________________
sphere::sphere()
{
	/*! Sphere ctor, automatic version. This is usually the one called by the
	 *	GP objects factory. */
	_radius = 1;
	_slices = 10;
	_stacks = 10;
}

//______________________________________________________________________________
sphere::sphere(const double& radius, const Uint32& slices, const Uint32& stacks)
{
	/*! Sphere constructor with radius and number of slices around the z axis 
	 *	(slices) and subdivisions along the z axis (stacks).
	 */
	_radius = radius;	if (_radius <= 0) _radius = 1;
	_slices = slices;	if (_slices < 4) _slices = 4;
	_stacks = stacks;	if (_stacks < 1) _stacks = 1;
}

	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType sphere::type() const
{
	/*! Returns a numeric identification. */
	return CO::oType::gpSphere;
}

//______________________________________________________________________________
Uint64 sphere::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string sphere::stem() const
{
	/*! Returns a string identification. */
	return "sphere";
}

//______________________________________________________________________________
size_t sphere::size(const bool& dynamic) const
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
void sphere::dump(const Uint64& ind) const
{
	/*! Send out all the GP data. */
	
	// Quick out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)

	// The parent.
	Filled::Dump(ind);
		
	// The box.	
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "Sphere specific\n";
	std::cout << pad3 << "Radius: " << CLW << _radius << CD << "\n"
			  << pad3 << "Slices: " << CLW << _slices << CD << "\n"
			  << pad3 << "Stacks: " << CLW << _stacks << CD << "\n";

	// Release.
	#undef CLW
	#undef CD
}

//______________________________________________________________________________
bool sphere::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	filled::stream(o, read);
		
	// Streams the cylinder properties.
	af::stream::RW(o, _radius, read);
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
void sphere::glDrawSel()
{
	/*!	Draws a the line selection skeleton. */
	
	// Set up the selection drawing style.
	filled::glDrawSel(); 	

	// Assign object color
//	glColor4fv(_selColor);
		
	// Switch off lighting in case for the stroke part of the drawing.
//	glLightSuspend();
		
	// Draw the cylinder wireframe.
//	GLUquadricObj* qObj = gluNewQuadric();
	//gluQuadricCallback(qObj, GLU_ERROR, errorCallback);
//	gluQuadricDrawStyle(qObj, GLU_LINE); /* flat shaded */
//	gluQuadricNormals(qObj, GLU_FLAT);
//	gluSphere(qObj, _Radius, _Slices, _Stacks);
//	gluDeleteQuadric(qObj);
		
	// Re-enable light in case.
//	glLightRestore();
}

//______________________________________________________________________________
void sphere::glDraw()
{
	/*!	Draws a line object with two vertices in the 3D space. */
		
	// Common drawing properties are handled by the parent GP.
	silled::glDraw();

	// If not visible, bye bye.
	if (!modeVisible()) return;
		
	// Stroke outline.
	if (_strkEnable) {
	
		// Assign object color
//		glColor4fv(_strkColor);
		
		// Switch off lighting in case for the stroke part of the drawing.
//		glLightSuspend();		
		
		// Draw the stroked wireframe.
//		GLUquadricObj* qObj = gluNewQuadric();
		//gluQuadricCallback(qObj, GLU_ERROR, errorCallback);
//		gluQuadricDrawStyle(qObj, GLU_LINE); /* flat shaded */
//		gluQuadricNormals(qObj, GLU_FLAT);
//		gluSphere(qObj, _Radius, _Slices, _Stacks);
//		gluDeleteQuadric(qObj);

		// Re-enable light in case.
//		glLightRestore();
	}

	// Solid filling.
	if (_fillEnable) {

		// Assign object color
//		glColor4fv(_fillColor);
		
		// Draw the cylinder surface fill.
//		GLUquadricObj* qObj = gluNewQuadric();
//		gluQuadricDrawStyle(qObj, GLU_FILL);
//		gluQuadricNormals(qObj, GLU_SMOOTH);
//		gluQuadricOrientation(qObj, GLU_OUTSIDE);
//		gluSphere(qObj, _Radius, _Slices, _Stacks);
//		gluDeleteQuadric(qObj);
	}
}

//______________________________________________________________________________
void sphere::glDrawEnd()
{
	// Complete drawing operations.
	filled::glDrawEnd(); 
}

// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace