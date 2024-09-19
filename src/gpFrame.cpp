//------------------------------------------------------------------------------
// PEAR Frame GP class														  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"pear_gp_Frame.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"04 Sep 2011"
// [Language]		"C++"
//______________________________________________________________________________


// Application components.
#include "pear_gp_Frame.h"


// #############################################################################
namespace pear { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
Frame::Frame()
{
	/*! Frame constructor with the provided dimensions width (\c xW ), 
	 *	length (\c yL ) and height (\c zH ). By default the box is 
	 *	(0,0,0) centered, XYZ aligned and of dimension (2,2,2). 
	 */
	
	// Reset the reference.
	_Ref;
}

//______________________________________________________________________________
Frame::Frame(const go::Point& p0, const go::Vector& a0)
{
	/*! Frame constructor with the frame reference origin set at \c p0 and the
	 *	frame rotateb by \c a0 around the XYZ axis in this order. */
	
	// Set inner reference.
	_Ref.p0(p0);
	_Ref.a0(a0); 
}

//______________________________________________________________________________
Frame::Frame(const go::Point& p0, const go::Vector& v0, const double& a)
{
	/*! Frame constructor with the frame reference origin set at \c p0 and the
	 *	frame rotateb along the \c v0 axis of \c a angle counterclockwise. */
	
	// Set inner reference.
	_Ref.p0(p0);
	_Ref.v0(v0, a); 
}

	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 Frame::Type() const
{
	/*! Returns a numeric identification. */
	return GP::Type() + GP::kgp_Frame;
}

//______________________________________________________________________________
Uint64 Frame::Version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string Frame::Stem() const
{
	/*! Returns a string identification. */
	return "Frame";
}

//______________________________________________________________________________
size_t Frame::Size(const bool& dynamic) const
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = GP::Size(true);
	
	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}
//______________________________________________________________________________
void Frame::Dump(const Uint64& ind) const
{
	/*! Send out all the box data. */
	std::string pad(ind, ' ');
	std::cout << pad << "[";
	GP::Dump();
	std::cout << " ]\n";
	pad.append(ind, ' ');
	_Ref.Dump();
	std::cout << "\n";
}

//______________________________________________________________________________
bool Frame::Stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// Streams the parent.
	if(GP::Stream(o, read)) return true;
		
	// Streams the vertexes
	_Ref.Stream(o, read);
	
	// Everythig fine.
	return false;
}

//______________________________________________________________________________
Frame& Frame::Trsf(const go::Ref& rf, const bool& inv)
{
	/*! Transforms the frame coordinates applying the rf transformation directly
	 *	if inv = false, and by applying the inverse transformation if inv = true. 
	 */
	//for (unsigned int i = 0; i < 8; i++) rf.Trsf(_Vtx[i], inv);
	
	return *this;
}	


// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
go::Ref Frame::Ref() const
{
	/*! Returns the inner reference. */
	return _Ref;
}

// *****************************************************************************
// **							  Drawing functions							  **
// *****************************************************************************

// Drawing function are available only for the SERVER. Note that the glDraw() 
// function, which must be defined for every GP, is in turn called by the parent
// GP object glBuild() function every time the object is updated. As well every
// specific gp update must call the glBuild() function provided by the parent GP
// object to make the changes effective. The object is actually drawn through 
// the GP::glDisplay() function, which uses the faster display list made by the 
// GP::gpBuild() every time it is called.
#ifdef PEAR_SERVER

//______________________________________________________________________________
void Frame::glTrsfApply()
{
	/*! The gp::Frame purpose is THIS member! It sets the OpenGL model view
	 *	matrix to make effective on the present drawing pipeline the embedded 
	 *	go::Ref object transformation. The base GP class call transfers and make
	 *	the call effective through all the family chain.
	 */

	// Family call.
	GP::glTrsfApply(); 

	// Push the current model matrix.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Apply the transformations.
	glScalef(_Ref.s0().X(), _Ref.s0().Y(), _Ref.s0().Z());
	glTranslatef(_Ref.p0().X(), _Ref.p0().Y(), _Ref.p0().Z());
	glRotated(_Ref.vA() * 57.295779513, _Ref.v0().X(), _Ref.v0().Y(), _Ref.v0().Z());	
	
	//std::cout << _Ref.vA() << ", " << _Ref.v0() << "\n";
	//std::cout << "APPLYING Frame Trsf:  " << Name() << "\n";
}

//______________________________________________________________________________
void Frame::glTrsfReset()
{
	/*! Reset the model matrix transformation applied by glTrsfApply. These two
	 *	member function must always be called in tandem to avoid messing up the
	 *	OpenGL drawing pipeline model transformation matrix. Note how calling
	 *	order is inverted respect to the Apply function, to match the push-pop
	 *	OpenGL mechanism. 
	 */

	// Restore the previous model matrix.
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//std::cout << "RESETTING Frame Trsf: " << Name() << "\n";

	// Family call.
	GP::glTrsfReset();
}

//______________________________________________________________________________
void Frame::glDrawSel()
{
	/*! Draws the selection skeleton. */

	// Common drawing properties are handled by the parent.
	GP::glDrawSel();
}

//______________________________________________________________________________
void Frame::glDraw()
{
	/*! Basically here we draw nothing, but we affect the OpenGL model transform
	 *	matrix! */
	 
	// Common drawing properties are handled by the parent.
	GP::glDraw();
}

//______________________________________________________________________________
void Frame::glDrawEnd()
{
	// Complete drawing operations.
	GP::glDrawEnd(); 
}


// End of PEAR_SERVER if
#endif

// #############################################################################
}} // Close namespace