//------------------------------------------------------------------------------
// CAT user interface View class			 								  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiView.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Overloading check
#if !defined uiView_H
#define uiView_H


// Application Components
#include "ui.h"
//#include "uiBar.h"
#include "uiMouse.h"


// #############################################################################
namespace cat { namespace ui {

// Forward declaration of a pad class
class pad;

//! Basic view descriptor
/*! A cat::ui::view is a container describing all the properties of a 3D view.
 *	
 *	\author Piero Giubilato
 *	\version 1.2
 *	\date 19 Sep 2024
 */
class view //: public UI 
{
	private:
	
		// Status and properties
		pad* _owner;				//!< The pad using the View.
		bool _needRedraw;			//!< Flag for requiring redraw.
		
		// 3D View constants
		enum class k3d : Uint32 {
			projection, 
			camera, 
			top, 
			front, 
			bottom, 
			back, 
			left, 
			right
		};
		
		// Viewport.
		struct kMatrix {
			GLdouble modelview[16];		//!< Modelview matrix.
			GLdouble projection[16];	//!< Projection matrix.
			GLint viewport[4];			//!< Viewport matrix.
		};
		

		// 3D Light
		struct kLight {
			bool on;					//!< On/off.
			float mult;					//!< Multiplier.
			float dir[3];				//!< Direction.
			float ambient[4];			//!< Ambient response.
			float diffuse[4];			//!< Diffuse response.
			float specular[4];			//!< Specular response.
		};
				
		// 3D World (model)
		struct kModel {
			float rotation[4];			//!< Model rotation.	
			float scale[3];				//!< Model scale.
			float position[3];			//!< Model position.
		};
		
		// 3D Camera
		struct kCamera {
			float focal;				//!< Lens focal.	
			float fov;					//!< Field of view (degrees).	
			float position[3];			//!< Camera position.
			float target[3];			//!< Camera target.	
			float up[3];				//!< Camera up axis.	
		};

		// 1D Axis
		struct kAxis {
			bool nn;					//!< Show axis.
			bool grid;					//!< Show Grid.
			float limit;				//!< Extension limit.
			float step;					//!< Grid stepping.			
		};

	protected:
	
	public:
	
		// 3D screen view parameter.
		float _backColor[3];			//!< Background color.
		float _zoom;					//!< Self-explaining.
		Uint64 _mode;					//!< Preset-view (top, front, ....).
		bool _lighting;					//!< Lighting is on.
		
		// View models.
		kMatrix _matrix;				//!< The view matrixes.
		kModel _model;					//!< The model.
		kCamera _camera;				//!< The camera.
		kLight _light[8];				//!< Use/Set lights.
		kAxis _axis[3];					//!< Show/Set axis.
		
		// Special members.
		view(Pad* owner);				//!< Mandatory owner ctor.
		~view();						//!< Standard dtor.
		
		// General members and status.
		bool compare(const view*) const; //!< Compares two views.
		bool needRedraw() const;	//!< Check if the view has changed.
		void needRedraw(const bool&);//!< Set if the view has changed.

		// ui Functions.
		void uiBarLoad(bar&);		//!< Load a ui::Bar.
		
		// gl/glu Functions.
		// -----------------

			//! Main functions to set a view.
			bool glSet(cat::ui::mouseBall& mb, const bool& sel = false);
			bool glReset();				//!< Reset the OpenGL view.
			bool glView();				//!< Sets the OpenGL view.
		
			//! Sets the modelview (GL_MODELVIEW).
			bool glMatrixes(cat::ui::mouseBall& mb, const bool& sel);
						
			//! Fits the OpenGL lighting.
			bool glLight();

			// Viewport<->World transformations.
			bool glViewToWorld(const double* vXYZ, double* wXYZ) const;	//!< Viewport to World transform.
			bool glWorldToView(const double* wXYZ, double* vXYZ) const;	//!< World to Viewport transform.
			double glViewZ(const int& wX, const int& wY) const;			//!< Retrieve Z component of a XY viewport.
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif