//______________________________________________________________________________	
/*!
*  	Utility Classes for the CAT User Interface:
*	These classes provide support for the drawing pad (i.e. manage 
*	object rotation, zooming, camera panning, and any project 
*	dependencies of CAT on the math glm library.)   
*	
*  \author (C) Sarah Zalusky 2010-2013, CERN										  
*/
//______________________________________________________________________________	

//______________________________________________________________________________
// [File name]		"uiMouse.h"
// [Author]			"Sarah Zalusky"
// [Version]		"1.2"
// [Modified by]	"Sarah Zalusky, Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined uiMouse_H
#define uiMouse_H

// Application components.
#include "ui.h"


// #############################################################################
namespace cat { namespace ui {


// Forward declaration of a view class
class view;

//______________________________________________________________________________	
/*! cat::ui::mouseBall interprets mouse translations (click + tracking the 
 *	mouse 'ball') as the rotation of an object in 3-D space. It generates the 
 *	(4x4) transformation matrix derived from the mouse movement, also handling 
 *	//---scaling, or zoom factor, on right-click + mouse 
 *	//---dragging.  
 * 
 *	\author Piero Giubilato, Sarah Zalusky
 *	\version 1.2
 *	\date 19 Sep 2024
 */
class mouseBall  //: public UI
{
	private:
		int _vpWidth, _vpHeight;	// Current viewport width and height.
		bool _mLDragging, _mRDragging;
		
		glm::vec3 _mVecRotateStart, _mVecRotateLast; 
		glm::vec3 _mVecScaleStart, _mVecScaleLast;
		glm::vec2 _mVecPanStart, _mVecPanLast;

		glm::quat _mQuatNow, _mQuatDown;
		glm::vec3 _mVecScaleNow;		// Current scale.	
		glm::vec2 _mVecPanNow;			// Current pan.

		// Z reference in viewport coordinates.
		double _posView[3];				// Mouse position in viewport space.	
		double _posWorld[3];			// Mouse position in world space.	

		// Flags.
		bool _flgRotateChanged;			// Rotate changed flag.
		bool _flgScaleChanged;			// Scale changed flag.
		bool _flgPanChanged;			// Pan changed flag.
		bool _zpMode;					// Panning-Zooming mode.

		/*! Converts a mouse screen position into a 3 components vector
		laying down into a sphere surface */
		glm::vec3 screenToSphere(const float& sX, const float& sY);
				
	public:
		
		//! Default constructor.
		mouseBall();
		
		//! Store original position vector on (left-or-right) mouse click (x, y). 
		void begin(const int& x, const int& y, const int& mb, const bool& zp = false, const View* view = 0);
		
		//! Compute new quaternion, scale or pan based on current mouse position.
		void drag(const int& x, const int& y);
		
		//! Stop computations when mouse button released. 
		void end();
		
		// Position.
		void posViewGet(double* vXYZ) const;		//!< Retrieve mouse View position (double*).
		void posViewGet(Uint32* vXYZ) const;		//!< Retrieve mouse View position (UInt32*).
		void posWorldGet(double* wXYZ) const;		//!< Retrieve mouse World position (double*).
		void posWorldGet(glm::vec3& wXYZ) const;	//!< Retrieve mouse World position (glm::vec3&).
		
		//! Set current window size (for computing position vector). 
		void setViewportSize(const int& width, const int& height);
		
		//! Sets the inner quaternion by a float array. 
		void quaternionSet(const float* quat)  {
			_mQuatNow.x  = quat[0];
			_mQuatNow.y  = quat[1];
			_mQuatNow.z  = quat[2];
			_mQuatNow.w  = quat[3];
		}
		
		//! Load the inner quaternion into the float array.
		void quaternionGet(float* quat) const {
			quat[0] = _mQuatNow.x;
			quat[1] = _mQuatNow.y;
			quat[2] = _mQuatNow.z;
			quat[3] = _mQuatNow.w;
		}
				
		//! Converts quaternion to 4x4 matrix. 
		const glm::mat4 rotation() const {return glm::mat4_cast(_mQuatNow);}

		//! Sets current scale factor.
		void scaleSet(const float* scale) {
			_mVecScaleNow.x = scale[0];
			_mVecScaleNow.y = scale[1];
			_mVecScaleNow.z = scale[2];
		}

		//! Gets current scale factor.
		void scaleGet(float* scale) const {
			scale[0] = _mVecScaleNow.x;
			scale[1] = _mVecScaleNow.y;
			scale[2] = _mVecScaleNow.z;
		}

		//! Change current scale factor.
		void scaleChange(const float& step) {
			_mVecScaleNow.x += step;
			_mVecScaleNow.y += step;
			_mVecScaleNow.z += step;
			_flgScaleChanged = true;
			std::cout << "scaling: " << _mVecScaleNow.x << "\n";
		}

		//! Sets current pan.
		void panSet(const float* pan) {
			_mVecPanNow.x = pan[0];
			_mVecPanNow.y = pan[1];
		}

		//! Gets current pan.
		void panGet(float* pan) const {
			pan[0] = _mVecPanNow.x;
			pan[1] = _mVecPanNow.y;
		}

		//! Sets current scale factor.

		//! Returns if there has been a change.
		bool changed() const {return _flgRotateChanged;}
		bool flagRotate() const {return _flgRotateChanged;}
		bool flagScale() const {return _flgScaleChanged;}
		bool flagPan() const {return _flgPanChanged;}
		bool flagAny() const {return _flgPanChanged || _flgRotateChanged || _flgScaleChanged;}
};


//______________________________________________________________________________	
/*! Interprets Mouse click (left-click) as object picking 
 *	
 *	\author Piero Giubilato, Sarah Zalusky
 *	\version 1.0
 *	\date 26 Jul 2012 
 */
class mousePicker // : public UI
{
	private:

		// Mouse viewport coordinates.
		int _mX, _mY;
		int _mPickStatus;
		
	public:
		
		// Picking action status constants.
		enum class kPk : Uint32 {
			null, 
			started, 
			rendered, 
			completed, 
			confirmed, 
			cancelled   
		};
		
		//! Default constructor.
		mousePicker();

		//! Store original position vector on (left-or-right) mouse click x, y. 
		void begin(const int &pX, const int &pY);
		
		//! Stop picking and get Buffer. 
		//bool Process(std::vector<unsigned int> &_pickedFlags);	// Stop Picking and get Buffer 
		bool process(unsigned int &_pickedFlags);		
		int statusGet() const;		//!< Get current picking status.
		void statusSet(const int&);	//!< Force current picking status.
		void statusStep();			//!< Self increase picking status.
		int x() const {return _mX;}
		int y() const {return _mY;}

		GLuint buffer[64];
		GLuint hits; 
		//GLint view[4];
		
		//std::vector<int> _pickedFlags;
	 
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
