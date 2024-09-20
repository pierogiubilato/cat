//------------------------------------------------------------------------------
// CAT User Interface mouse classes											  --	
// (C) Piero Giubilato 2010-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiMouse.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Application Components 
#include "uiMouse.h"
#include "uiView.h"

// #############################################################################
namespace cat { namespace ui {


// *****************************************************************************
// **							 Special members	       				      **
// *****************************************************************************

mouseBall::mouseBall()
{
	/*! Default ctor. */
	_vpWidth = 0;
	_vpHeight = 0;
	_flgRotateChanged = false;
	_flgScaleChanged = false;
	_flgPanChanged = false;

	// Position (View and world).
	_posView[0] = 0;
	_posView[1] = 0;
	_posView[2] = 0;
	_posWorld[0] = 0;
	_posWorld[1] = 0;
	_posWorld[2] = 0;
}

// *****************************************************************************
// **							Mouse Managers!		       				      **
// *****************************************************************************

//______________________________________________________________________________
void mouseBall::posViewGet(double* vXYZ) const
{
	/*! Returns last registered mouse position in viewport coordinates. */

	// Retrieve viewport position.
	vXYZ[0] = _posView[0];
	vXYZ[1] = _posView[1];
	vXYZ[2] = _posView[2];
}

//______________________________________________________________________________
void mouseBall::posViewGet(Uint32* vXYZ) const
{
	/*! Returns last registered mouse position in viewport coordinates. */

	// Retrieve viewport position.
	vXYZ[0] = static_cast<Uint32>(_posView[0]);
	vXYZ[1] = static_cast<Uint32>(_posView[1]);
	vXYZ[2] = static_cast<Uint32>(_posView[2]);
}

//______________________________________________________________________________
void mouseBall::posWorldGet(double* wXYZ) const
{
	/*! Returns last registered mouse position in world coordinates. */

	// Retrieve world position.
	wXYZ[0] = _posWorld[0];
	wXYZ[1] = _posWorld[1];
	wXYZ[2] = _posWorld[2];
}

//______________________________________________________________________________
void mouseBall::posWorldGet(glm::vec3& wXYZ) const
{
	/*! Returns last registered mouse position in world coordinates. */

	// Retrieve world position.
	wXYZ.x = static_cast<float>(_posWorld[0]);
	wXYZ.y = static_cast<float>(_posWorld[0]);
	wXYZ.z = static_cast<float>(_posWorld[0]);
}

//______________________________________________________________________________
void mouseBall::begin(const int& x, const int& y, const int& mb, const bool& zp, const view* view)
{
	/*! mouseBall Tracks mouse movements to determine object rotation and zoom  
	 *	interactively. 'Begin' starts mouse tracking on left button mouse click, 
	 *	registered at (x,y). It starts a pan/zoom action in case of right click,
	 *	depending on the optional switch 'zp', which by default sets for a pan 
	 *	action.
	 *	If a \c 'ui::View' object is provided, also the world coordinates for 
	 *	current viewport position will be calculated.
	 */

	// Store position (x, y), set (z) to zero.
	_posView[0] = static_cast<double>(x);
	_posView[1] = static_cast<double>(y);
	_posView[2] = 0;

	// In case a valid view is provided, calculate the world position also.
	if (view) {
		 
		// Retrieves the viewport Z of the nearest object (if any).
		_posView[2] = view->glViewZ(x, y); 

		// Calculate world coordinates.
		view->glViewToWorld(_posView, _posWorld); 
		std::cout << "Mouse (x, y, z): " << _posView[0] << ", " << _posView[1] << ", " << _posView[2] << "\n";
		std::cout << "World (x, y, z): " << _posWorld[0] << ", " << _posWorld[1] << ", " << _posWorld[2] << "\n";
	}

	// Left Click (rotation).
	if (mb == 0) { 
		 
		_mVecRotateStart = screenToSphere(static_cast<float>(x), static_cast<float>(y));
		_mQuatDown = _mQuatNow;
		_mLDragging = true;

	// Right Click (zoom/pan). 
	} else if (mb == 1) {
				
		// Prepare for scaling.
		if (zp) {
			_mVecScaleStart = ScreenToSphere(static_cast<float>(x), static_cast<float>(y));
		
		// Prepare for panning.
		} else {		
			_mVecPanStart.x = static_cast<float>(x);
			_mVecPanStart.y = static_cast<float>(y);
		}

		// Stores Panning-Zooming mode.
		_mRDragging = true; 
		_zpMode = zp;	
	}

}

//______________________________________________________________________________
void mouseBall::end()
{
	/*! Called on mouse button release, stops mouse tracking. */
	_mLDragging = false; 	
	_mRDragging = false; 

	// Reset every change.
	_flgRotateChanged = false;	
	_flgScaleChanged = false;
	_flgPanChanged = false;
}

//______________________________________________________________________________
void mouseBall::drag(const int& x, const int& y)
{
	// TODO this factor should scale properly with current zoom settings 
	//float factor = 0.02f * g_Zoom;
	
	// Reset every change.
	_flgRotateChanged = false;	
	_flgScaleChanged = false;
	_flgPanChanged = false;

	// Left Mousing... start rotating.  
	if (_mLDragging) {
		
		// Displacement vector.
		_mVecRotateLast = ScreenToSphere(static_cast<float>(x), static_cast<float>(y));
		glm::vec3 p = glm::cross(_mVecRotateStart, _mVecRotateLast);
		
		// Derive rotation quaternions.
		if (glm::length(p) > 1e-5) {
			glm::quat q = glm::quat(glm::dot(_mVecRotateStart, _mVecRotateLast), p);
			_mQuatNow = glm::cross(glm::normalize(q), _mQuatDown);
		} else {
			_mQuatNow = glm::cross(glm::quat(), _mQuatDown);	
		}

		// Rotation has happened!
		_flgRotateChanged = true;
		
	// Right Mousing...
	} else if(_mRDragging) {

		// Scaling.
		if (_zpMode) {
		
			// Compute current vector (after mouse motion), and find the displacement. 
			_mVecScaleLast = screenToSphere(static_cast<float>(x), static_cast<float>(y));
			glm::vec3 s = _mVecScaleLast - _mVecScaleStart; 
		
			// Scale! 
			_mVecScaleNow.x = glm::length(s);
			_mVecScaleNow.y = glm::length(s);
			_mVecScaleNow.z = glm::length(s);
			
			// Scaling has happened!
			_flgScaleChanged = true;

		// Panning.
		} else {
			_mVecPanLast.x = static_cast<float>(x);
			_mVecPanLast.y = static_cast<float>(y);
			
			// Panning is linear in viewport units.
			_mVecPanNow = _mVecPanLast - _mVecPanStart;
			//_mVecPanStart = _mVecPanLast;

			// Panning has happened!
			_flgPanChanged = true;
		}
	}
}

//______________________________________________________________________________
void mouseBall::setViewportSize(const int& width, const int& height)
{
	/*! Sets current viewport width and height in screen units. These dimensions
	 *	will be used later to compute the 'screenToSphere' function)
	 */
	_vpWidth = width;
	_vpHeight = height;
}

//______________________________________________________________________________
glm::vec3 mouseBall::screenToSphere(const float& sX, const float& sY)
{
	/*! Converts screen coordinates into 3D sphere surface coordinates.
	 *	Coordinates on screen are mapped on the surface of an imaginary 3D 
	 *	sphere centered on the current viewport.
	 */
	//std::cout << sX << ", " << sY << "\n";

	glm::vec2 v;
	v.x = ((sX / ((_vpWidth - 1) / 2)) - 1);
	v.y = -((sY / ((_vpHeight - 1) / 2)) - 1);
	
	float len = glm::length(v);
	if (len > 1.0f) {
		v.x = v.x / sqrt(len);
		v.y = v.y / sqrt(len); 
		return glm::vec3(v, 0);
	}
	return glm::vec3(v, sqrt(1.0f - len));
}



// *****************************************************************************
// **							mousePicking Class		       			      **
// *****************************************************************************


//______________________________________________________________________________
mousePicker::mousePicker()
{
	/*! Default ctor. */
	_mX = 0;
	_mY = 0;
	_mPickStatus = kPk::null;
}

//______________________________________________________________________________
void mousePicker::begin(const int &pX, const int &pY)
{
	/*! The mousePicker interactively selects objects (by returning the object 
	 *	name, if any) near where the user has clicked or 'picked', at mouse input 
	 *	pX, pY. mousePicker::Select prepares gl to render in selection mode.
	 */
	_mX = pX;
	_mY = pY;
	_mPickStatus = kPk::started;
	std::cout << "mouse: Pick sequence started\n";
}	

//______________________________________________________________________________
int mousePicker::statusGet() const
{
	/*! Returns picking status. */
	return _mPickStatus;	
}

//______________________________________________________________________________
void mousePicker::statusSet(const int& status)
{
	/*! Sets if mouse Confirmed a picking action. */
	_mPickStatus = status;	
	std::cout << "mouse: Pick Status forced to " << status << "\n";
}

//______________________________________________________________________________
void mousePicker::statusStep()
{
	/*! Self-increase the picking status accordingly to the current state. */
	
	switch (_mPickStatus) {
		case kPk::null:			_mPickStatus = kPk::null; break;
		case kPk::started:		_mPickStatus = kPk::rendered; break;
		case kPk::rendered:		_mPickStatus = kPk::completed; break;
		case kPk::completed:	_mPickStatus = kPk::confirmed; break;
		case kPk::confirmed:	_mPickStatus = kPk::null; break;
		case kPk::cancelled:	_mPickStatus = kPk::null; break;
		_mPickStatus = kPk::null;
	}
	std::cout << "mouse: Pick self forced to " << _mPickStatus << "\n";
}

//______________________________________________________________________________
//bool mousePicker::Process(std::vector<unsigned int> &_pickedFlags){
bool mousePicker::process(unsigned int &_pickedFlags)
{
	/*! Restores to normal rendering mode & searches hits in the buffer to find best 
	 *  candidate for the selected object by testing depth (assumes object closest 
	 *  to viewer is 'picked') Flags this object and stores its name. 
	 *
	 *		Each hit in the buffer is allocated 4 bytes
	 * 		1) Number of selected hits (Always one if using glLoadName- 
	 * 									replaces previous name in stack) 
	 * 		2) Minimum Depth	Z
	 * 		3) Maximum Depth	Z
	 * 		4) Object Name (from glLoadName)
	 */ 
	
	///* Restore normal rendering mode */
	//glMatrixMode(GL_PROJECTION); 
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW); // Return to model view 
	//glFlush();
	//hits = glRenderMode(GL_RENDER); // Return to render mode 
	//
	//// Prepare to search Buffer 
	//float Zmin; 			// Minimum Depth  
	//int Name; int Flag = 0; // 'Picked' Name and Flags   
	//GLuint names, *ptr;		// Name and buffer elements
	//ptr = (GLuint *) buffer;
	//
	//// Search! Loop over each hit, and every element in the hit buffer.
	//unsigned int i, j;
	//for (i = 0; i < hits; i++) { // Each hit   
	//		names = *ptr; ptr++; 						// Get first Buffer element: Hit Number
	//		float z1 = (float) *ptr/0x7fffffff; ptr++; 	// Second Buffer Element: minZ
	//		ptr++; 										// Third Buffer Element: maxZ
	//		
	//		for (j = 0; j < names; j++) {  // Loop over each name 
	//			int nm = (int)*ptr; ptr++; // Fourth Buffer Element: Object Name
	//			
	//			// Check which hit is minimum, discarding last name in the stack
	//			if((i == 0 || z1 < Zmin) && i != fabs((float)hits - 1) ){
	//				Zmin = z1;	// Set the new Minimum 
	//				Name = nm;	// Store name of the object
	//				Flag = 1; 	// Flag object as 'selected'			
	//			}		
	//		}
	//}
	//
	//// If an object was identified  
	//if (Flag) {
	//	_pickedFlags = Name; 
	//	return 1; // Return successful find! 
	//
	//// No object was found 
	//} else {
	//	_pickedFlags = 0; 
	//	return 0; // Return Null result 
	//}
	return 0;
}	

// #############################################################################
}} // Close namespaces