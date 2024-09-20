//------------------------------------------------------------------------------
// CAT user interface View class											  --
// (C) Piero Giubilato 2011-2013, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiView.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Application components
#include "uiView.h"
#include "uiPad.h"

// #############################################################################
namespace cat { namespace ui { 


// *****************************************************************************
// **							  Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
view::view(pad* owner)
{
	/*! Instantiate a standard view. */
	 		
	// Owner.
	_owner = owner;
	_needRedraw = false;
	
	// View
	_zoom = 1;
	_mode = k3d::projection;
		
	// Back Color.
	_backColor[0] = 0.0f;	// Red.
	_backColor[1] = 0.0f;	// Green.
	_backColor[2] = 0.0f;	// Blue.
	_backColor[3] = 1.0f;	// Alpha.
	
	// Matrixes.
	_matrix.viewport[0] = 0;	// Bottom left corner X. 
	_matrix.viewport[1] = 0;	// Bottom left corler Y.
	_matrix.viewport[2] = 0;	// Width.
	_matrix.viewport[3] = 0;	// Height.
	for (Uint32 i = 0; i < 16; i++) {	
		_matrix.modelview[i] = 0;
		_matrix.projection[i] = 0; 
	}
	
	// Lighting.
	_lighting = true;	// Lighting on.
		
	// Here the presets for the standard view lighting.
	for (Uint32 i = 0; i < 8; i++) {
			
		// Status.
		_light[i].on = false;			// On/Off.
		_light[i].mult = 1.0f;			// Intensity.
			
		// Direction.
		_light[i].dir[0] = -0.577355f;	// X axis.
		_light[i].dir[1] = -0.577355f;	// Y axis.
		_light[i].dir[2] = -0.577355f;	// Z axis.

		// Ambient color.	
		_light[i].ambient[0] = 0.0f;	// Red.
		_light[i].ambient[1] = 0.0f;	// Green.
		_light[i].ambient[2] = 0.0f;	// Blue.
		_light[i].ambient[3] = 1.0f;	// Alpha.
			
		// Diffuse color.
		_light[i].diffuse[0] = 0.8f;	// Red.
		_light[i].diffuse[1] = 0.8f;	// Green.
		_light[i].diffuse[2] = 0.8f;	// Blue.
		_light[i].diffuse[3] = 1.0f;	// Alpha.

		// Specular color.
		_light[i].specular[0] = 0.8f;	// Red.
		_light[i].specular[1] = 0.8f;	// Green.
		_light[i].specular[2] = 0.8f;	// Blue.
		_light[i].specular[3] = 1.0f;	// Alpha.
	}
	
	// Switch on just light #1 (light are computationally heavy...)
	_light[0].On = true;		

	// Model.
	_model.position[0] = 0.0f;	// Offset X.
	_model.position[1] = 0.0f;	// Offset Y.
	_model.position[2] = 0.0f;	// Offset Z.
	_model.rotation[0] = 0.0f;	// rotation quat 0.
	_model.rotation[1] = 0.0f;	// rotation quat 1.
	_model.rotation[2] = 0.0f;	// rotation quat 2.
	_model.rotation[3] = 0.0f;	// rotation quat 3.
	_model.scale[0] = 1.0f;		// scale X.
	_model.scale[1] = 1.0f;		// scale Y.
	_model.scale[2] = 1.0f;		// scale Z.
	
	// Camera.
	_camera.focal = 5.0f;		// Lens focal (mm).		
	_camera.fov = 45.0f;		// Lens fov (degree).		
	_camera.position[0] = 0.0f;	// Pos X.
	_camera.position[1] = 0.0f;	// Pos Y.
	_camera.position[2] = 9.0f;	// Pos Z.
	_camera.target[0] = 0.0f;	// Dir X. 
	_camera.target[1] = 0.0f;	// Dir Y. 
	_camera.target[2] = -1.0f;	// Dir Z. 
	_camera.up[0] = 0.0f;		// Up X. 
	_camera.up[1] = 1.0f;		// Up Y. 
	_camera.up[2] = 0.0f;		// Up Z. 

}

//______________________________________________________________________________
view::~view() 
{
	/*! Releases all allocated resources. */

}


// *****************************************************************************
// **							  Public Members							  **
// *****************************************************************************

//______________________________________________________________________________
bool view::compare(const view* cView) const
{
	/*! Compare the current view with the \c cView. Returns true if the two 
	 *	views are identical, false otherwise. */
	
	// Check.
	if(!cView) return false;

	// Compares.
	bool equal = true;
	
	// General.
	equal &= (_zoom == cView->_zoom);
	for (int i = 0; i < 3; i++) equal &= (_backColor[i] == cView->_backColor[i]);
	equal &= (_mode == cView->_mode);
	equal &= (_lighting == cView->_lighting);
	
	// Model.
	for (int i = 0; i < 4; i++) {
		equal &= (_model.rotation[i] == cView->_model.rotation[i]);
	}
	for (int i = 0; i < 3; i++) {
		equal &= (_model.position[i] == cView->_model.position[i]);
		equal &= (_model.scale[i] == cView->_model.scale[i]);
	}	

	// Camera.
	equal &= (_camera.focal == cView->_camera.focal);
	equal &= (_camera.fov == cView->_camera.fov);
	for (int i = 0; i < 3; i++) {
		equal &= (_camera.position[i] == cView->_camera.position[i]);
		equal &= (_camera.target[i] == cView->_camera.target[i]);
		equal &= (_camera.up[i] == cView->_camera.up[i]);
	}	
	
	// Lights.
	for (int l = 0; l < 8; l++) {
		equal &= (_light[l].on == cView->_light[l].on);
		equal &= (_light[l].mult == cView->_light[l].mult);
		for (int i = 0; i < 3; i++) {
			equal &= (_light[l].dir[i] == cView->_Light[l].Dir[i]);
		}
		for (int i = 0; i < 4; i++) {
			equal &= (_light[l].ambient[i] == cView->_light[l].ambient[i]);
			equal &= (_light[l].diffuse[i] == cView->_light[l].diffuse[i]);
			equal &= (_light[l].specular[i] == cView->_light[l].specular[i]);
		}
	}

	// Axis.
	for (int a = 0; a < 3; a++) {
		equal &= (_axis[a].on == cView->_axis[a].on);
		equal &= (_axis[a].grid == cView->_axis[a].grid);
		equal &= (_axis[a].limit == cView->_axis[a].limit);
		equal &= (_axis[a].step == cView->_axis[a].step);
	}

	//std::cout << "Zooms: " << _Zoom << ", " << cView->_Zoom << "\n";
	//if (!equal) std::cout << "Some differences!\n";

	// Done.
	return equal;
}

//______________________________________________________________________________
bool view::needRedraw() const
{
	/*! Returns if the view has changed. To reset or force the status, call 
	 *	the NeedRedraw(status) function. */
	return _needRedraw;
}

//______________________________________________________________________________
void view::needRedraw(bool const& status)
{
	/*! Set the need for redraw status. */
	_needRedraw = status;
}


// *****************************************************************************
// **								ui Members								  **
// *****************************************************************************

//______________________________________________________________________________
void view::uiBarLoad(bar& bar) 
{
	/*! Load an ui Bar with the view settings. */
/*
	// Gets the linked TwBar.
	TwBar* twBar = bar._TwBar; 	

	// View mode enum.
	const TwEnumVal viewMode[] = {
		{k3d_camera, "Camera"}, {k3d_Projection, "Projection"}, {k3d_Top,	"Top"},
		{k3d_Bottom,"Bottom"}, {k3d_Front, "Front"}, {k3d_Back, "Back"},
		{k3d_Left,	"Left"}, {k3d_Right, "Right"},
    };
	const TwType type = TwDefineEnum("ViewMode", viewMode, SDL_arraysize(viewMode));

	// Global.
	bar.GroupAdd("Global"); 
	TwAddVarRW(twBar, "View mode", type, &_Mode, "group='Global'");
	TwAddVarRW(twBar, "Back color", TW_TYPE_COLOR3F, &_BackColor, "group='Global'");
	TwAddVarRW(twBar, "Zoom", TW_TYPE_FLOAT, &_Zoom, "min=0.01 max=100 step=0.01 keyIncr=z keyDecr=Z group='Global'");

	// Model.
	bar.GroupAdd("Model");
	TwAddVarRW(twBar, "Offset X", TW_TYPE_FLOAT, &_model.position[0], "group='Model' step=0.01");
	TwAddVarRW(twBar, "Offset Y", TW_TYPE_FLOAT, &_model.position[1], "group='Model' step=0.01");
	TwAddVarRW(twBar, "Offset Z", TW_TYPE_FLOAT, &_model.position[2], "group='Model' step=0.01");
	TwAddVarRW(twBar, "rotation", TW_TYPE_QUAT4F, &_model.rotation, "group='Model'");
	TwAddVarRW(twBar, "scale X", TW_TYPE_FLOAT, &_model.scale[0], "group='Model' min=0.01 max=100 step=0.01");
	TwAddVarRW(twBar, "scale Y", TW_TYPE_FLOAT, &_model.scale[1], "group='Model' min=0.01 max=100 step=0.01");
	TwAddVarRW(twBar, "scale Z", TW_TYPE_FLOAT, &_model.scale[2], "group='Model' min=0.01 max=100 step=0.01");
				
	// Camera.
	bar.GroupAdd("Camera");
	TwAddVarRW(twBar, "fov", TW_TYPE_FLOAT, &_camera.fov, "group='Camera' min='1' max='180' step=0.1");
	TwAddVarRW(twBar, "Camera X", TW_TYPE_FLOAT, &_camera.position[0], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Camera Y", TW_TYPE_FLOAT, &_camera.position[1], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Camera Z", TW_TYPE_FLOAT, &_camera.position[2], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Target X", TW_TYPE_FLOAT, &_camera.Target[0], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Target Y", TW_TYPE_FLOAT, &_camera.Target[1], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Target Z", TW_TYPE_FLOAT, &_camera.Target[2], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Up axis X", TW_TYPE_FLOAT, &_camera.Up[0], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Up axis Y", TW_TYPE_FLOAT, &_camera.Up[1], "group='Camera' step=0.1");
	TwAddVarRW(twBar, "Up axis Z", TW_TYPE_FLOAT, &_camera.Up[2], "group='Camera' step=0.1");
	
	// Lighting.
	bar.GroupAdd("Light");
	TwAddVarRW(twBar, "_Lighting", TW_TYPE_BOOLCPP, &_Lighting, "group='Light' label='Lighting'");
	TwSetParam(twBar, "Light", "opened", TW_PARAM_CSTRING, 1, "false");

	// Lights
	for (Uint64 i = 0; i < 8; i++) {

		// Naming.
		std::stringstream varName;
		std::stringstream varNameRoot;
		std::stringstream varParam;
		std::stringstream varParamRoot;
		varNameRoot << "Light_" << i;	
		varParamRoot << "group='" << varNameRoot.str() << "' ";
		bar.GroupAdd(varNameRoot.str()); 		

		// On/Off.
		varName << varNameRoot.str() << "_On";
		varParam << varParamRoot.str() << "label='Active'";
		TwAddVarRW(twBar, varName.str().c_str(), TW_TYPE_BOOLCPP, &_Light[i].On, varParam.str().c_str());
	
		// Intensity
		varName << varNameRoot.str() << "_Multiplier";
		varParam << varParamRoot.str() << "label='Multiplier'";
		TwAddVarRW(twBar, varName.str().c_str(), TW_TYPE_FLOAT, &_Light[i].Mult, varParam.str().c_str());
		TwSetParam(twBar, varName.str().c_str(), "min", TW_PARAM_CSTRING, 1, "0.0");	
		TwSetParam(twBar, varName.str().c_str(), "max", TW_PARAM_CSTRING, 1, "1.0");
		TwSetParam(twBar, varName.str().c_str(), "step", TW_PARAM_CSTRING, 1, "0.01");
		
		// Direction
		varName << varNameRoot.str() << "_Dir";
		varParam << varParamRoot.str() << "label='Direction'";
		TwAddVarRW(twBar, varName.str().c_str(), TW_TYPE_DIR3F, &_Light[i].Dir, varParam.str().c_str());
		TwSetParam(twBar, varName.str().c_str(), "opened", TW_PARAM_CSTRING, 1, "false");

		// Ambient.
		varName << varNameRoot.str() << "_Ambient";
		varParam << varParamRoot.str() << "label='Ambient'";
		TwAddVarRW(twBar, varName.str().c_str(), TW_TYPE_COLOR4F, &_Light[i].Ambient, varParam.str().c_str());
		TwSetParam(twBar, varName.str().c_str(), "opened", TW_PARAM_CSTRING, 1, "false");	

		// Diffuse.
		varName << varNameRoot.str() << "_Diffuse";
		varParam << varParamRoot.str() << "label='Diffuse'";
		TwAddVarRW(twBar, varName.str().c_str(), TW_TYPE_COLOR4F, &_Light[i].Diffuse, varParam.str().c_str());
		TwSetParam(twBar, varName.str().c_str(), "opened", TW_PARAM_CSTRING, 1, "false");	

		// Specular.
		varName << varNameRoot.str() << "_Specular";
		varParam << varParamRoot.str() << "label='Specular'";
		TwAddVarRW(twBar, varName.str().c_str(), TW_TYPE_COLOR4F, &_Light[i].Specular, varParam.str().c_str());
		TwSetParam(twBar, varName.str().c_str(), "opened", TW_PARAM_CSTRING, 1, "false");	
		
		// Set group 'Light_#' as part of the general group light.
		TwSetParam(twBar, varNameRoot.str().c_str(), "group", TW_PARAM_CSTRING, 1, "Light");
	}
*/
}


// *****************************************************************************
// **								gl Members								  **
// *****************************************************************************

//______________________________________________________________________________
bool view::glSet(cat::ui::mouseBall& mb, const bool& sel) 
{
	/*! Set the OpenGL view to match this object view parameters. It sets
	 *	general parameters, geometry and lighting. If \c 'sel' is set to true
	 *	set up only the features needed for a selection view.
	 *	\c 'mb' is a mouseBall object used to check for mouse-induced
	 *	rotation, scaling and panning, and cursor pointing position.
	 * 	This function has to be called before drawing any object, and after
	 *	drawing all the objects \c glReset() has to be called to restore the
	 *	previous OpenGL settings.
	 */

	// Store current settings, they will be recalled by the
	// glReset() call after drawing the full scene.	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	// Updates selection color/pattern accordingly to the view properties.
	cat::gp::GP::_selColor[0] = 1 - _backColor[0];  
	cat::gp::GP::_selColor[1] = 1 - _backColor[1];
	cat::gp::GP::_selColor[2] = 1 - _backColor[2];
	cat::gp::GP::_selColor[3] = 1;
	cat::gp::GP::_selWidth = 3;
	cat::gp::GP::_selFactor = (int)(_zoom / 4);
		
	// Set the appearance and projection.
	if (!sel) {
		glView();		// General parameters.
		glLight();		// Lighting.
	}
		
	// Transform the model (MODELVIEW).

	// Set the camera view and lens (PROJECTION).

	// Camera is always set.
	//glCamera(mb, sel);

	// Model view is always set.
	glMatrixes(mb, sel);
	
	// Compare and save current view settings for the taskbar
	// refresh in case of multiple views/scenes.m
	static view oldView(0);
	_NeedRedraw = !compare(&oldView);
	oldView = *this;

	// Stores current view matrixes. These will be used for
	// world<->viewport coordinate transformations once the
	// rendering is completed and the matrixes reset to their 
	// previous values from the glReset() call.
	if (!mb.flagAny()) {  
		glGetDoublev(GL_MODELVIEW_MATRIX, _matrix.modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, _matrix.projection);
		glGetIntegerv(GL_VIEWPORT, _matrix.viewport);
	}

	// Everything fine.
	return false;
}

//______________________________________________________________________________
bool view::glReset() 
{
	/*! Restore OpenGL view setting as before calling glSet. It is MANDATORY
	 *	to call this function after glSet(), otherwise a stack-error will be
	 *	raised by the OpenGL matrix manager.
	 */
	 
	// Background color.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	// Everything fine.
	return false;
}

//______________________________________________________________________________
bool view::glView() 
{
	/*! Set general parameter for the OpenGL view. Returns false if no error 
	 *	occurred, true otherwise.
	 */

	// Background color.
	glClearColor(_backColor[0], _backColor[1], _backColor[2], _backColor[3]);

	// Everything fine.
	return false;
}

////______________________________________________________________________________
//bool View::glCamera(pear::ui::mouseBall& mb, const bool& sel)
//{
//	/*! Fits the current OpenGL PROJECTION matrix to match the camera settings,
//	 *	focal length, fov, etc... Returns false if no error occurred, true 
//	 *	otherwise.
//	 */
//
//	//// Apply panning to the viewport in case.
//	//if (mb.flagPan()) {
//	//	//std::cout << "*** PANNING " << _Matrix.Viewport[0] << "\n";
//	//	float pan[2];
//	//	mb.PanGet(pan); 
//	//	glViewport(_Matrix.Viewport[0] + static_cast<int>(pan[0]), 
//	//			   _Matrix.Viewport[1] - static_cast<int>(pan[1]), 
//	//			   _Matrix.Viewport[2], 
//	//			   _Matrix.Viewport[3]);	
//	//} else {
//	//	//_Matrix.Viewport[0] = viewport[0];	
//	//	//_Matrix.Viewport[1] = viewport[1];
//	//	//_Matrix.Viewport[2] = viewport[2];
//	//	//_Matrix.Viewport[3] = viewport[3];
//	//}
//	
//	// Go into PROJECTION matrix stack.
////	glMatrixMode(GL_PROJECTION);
////	glLoadIdentity();
//	
//	// Retrieves viewport aspect ratio.
////	GLint viewport[4];
////	glGetIntegerv(GL_VIEWPORT, viewport);
////	float aspect = (float)viewport[2] / (float)viewport[3];
//		
//	// Establish new clipping volume to be unit cube around
//	// mouse cursor point (x, y) and extending two pixels
//	// in the vertical and horizontal direction
//	Uint32 mPosView[3];
//	mb.posViewGet(mPosView);
//	if (sel) gluPickMatrix(mPosView[0], viewport[3] - mPosView[1] + viewport[1], 3, 3, viewport);
////	gluPerspective(_camera.fov, aspect, 0.5, 100);			 
//	
//	
//	// Everything fine.
//	return false;
//}

//______________________________________________________________________________
bool view::glMatrixes(cat::ui::mouseBall& mb, const bool& sel)
{
	/*! Fits the current OpenGL MODELVIEW matrix to match the camera settings.
	 *	Returns false if no error occurred, true otherwise. \c 'mb' is a
	 *	mouseBall object used to download/load position, scaling and panning 
	 *	parameters to the view.
	 */

	// Support identity matrix.
	const glm::mat4 uniMtx(1.0f);
	
	// Retrieves current viewport aspect ratio (used for projective calculations).
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float viewAspect = (float)viewport[2] / (float)viewport[3];

	// Mouse induced rotation, scaling and panning. If mouse has changes,
	// then mouse "numbers" will be moved into the view, while in the other
	// case view "numbers" will update mouse references, keeping them synched.
	// -----------------------------------------------------------------------
	
		// rotation.
		glm::vec3 rotOff(0, 0, 0);				// rotation offset (0 if no object).
		if (mb.flagRotate()) {
			mb.quaternionGet(_model.rotation);	// Retrieves mouse rotation.
			mb.posWorldGet(rotOff); 			// Retrieves eventual object 3D position.
		}
		else mb.quaternionSet(_model.rotation);

		// scale.
		if (mb.flagscale()) mb.scaleGet(_model.scale); 
		else mb.scaleSet(_model.scale);
	

	

// GLU camera, perspective and pick.
//glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
//gluLookAt(_camera.position[0], _camera.position[1], _camera.position[2],
//		  _camera.Target[0], _camera.Target[1], _camera.Target[2],
//		  _camera.Up[0], _camera.Up[1], _camera.Up[2]);

	// MODELVIEW MATRIX building..
//	glLoadIdentity();
	
	// Camera transformations come first, in the "ideal" clean world provided
	// by the glLoadIdentity() call. Here the camera is placed and oriented.
	 

	// View matrix (mimicking camera positioning).
	glm::mat4 camMtx = glm::lookAt(glm::vec3(_camera.position[0], _camera.position[1], _camera.position[2]), 
									glm::vec3(_camera.target[0], _camera.target[1], _camera.target[2]), 
									glm::vec3(_camera.up[0], _camera.up[1], _camera.up[2]));
   
	// Translation matrix.
	glm::mat4 trlMtx = glm::translate(uniMtx, glm::vec3(_model.position[0], _model.position[1], _model.position[2]));

	// scale matrix.
	glm::mat4 sclMtx = glm::scale(uniMtx, glm::vec3(_model.scale[0], _model.scale[1], _model.scale[2]));

	// rotation matrix.
	glm::mat4 rotMtx = mb.rotation();
	
	// Computes the full modelview matrix and load it into OpenGL.
	glm::mat4 mdlMtx = camMtx * trlMtx * rotMtx * sclMtx;
	//glm::mat4 mdlMtx = camMtx * pckMtx * trlMtx * rotMtx * sclMtx;

	// Load the view matrix.
	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//glMultMatrixf(glm::value_ptr(mdlMtx));	
	glLoadMatrixf(glm::value_ptr(mdlMtx));

	// This allow to center the ArcBall action over the point
	// of interest.
	//glm::mat4 mdlMtx = glm::translate(rotMtx, rotOff);
	//std::cout << "rotation Off: " << rotOff.x << ", " << rotOff.y << ", " << rotOff.z << "\n";
	//std::cout << "rotation Mtx: " << rotMtx.x << ", " << rotMtx.y << ", " << rotMtx.z << "\n";
	//std::cout << "model Matrix: " << mdlMtx.x << ", " << mdlMtx.y << ", " << mdlMtx.z << "\n";
		
	

		// Picking matrix: in case of selection, resize the scene to fit the 
Uint32 mPosView[3]; mb.posViewGet(mPosView);	
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
//if (sel) gluPickMatrix(mPosView[0], viewport[3] - mPosView[1] + viewport[1], 3, 3, viewport);
//gluPerspective(_camera.fov, viewAspect, 0.5, 100);	


		

	// Lens matrix: in case of selection, use special settings to narrow the view 
	// down to few pixels around the mouse cursor point (x, y) and extending few 
	// pixels in the vertical and horizontal direction.
	// viewport around the mouse picking position.
	glm::mat4 pckMtx(1.0f);
	if (sel) {
		
		// Grab current viewport mouse position.
		//Uint32 mPosView[3]; mb.posViewGet(mPosView);
		
		/* Translate and scale the picked region to the entire window */
		Uint32 x = mPosView[0];
		Uint32 y = mPosView[1];
		Uint32 deltax = 3;
		Uint32 deltay = 3;

		//glTranslatef((viewport[2] - 2 * (x - viewport[0])) / deltax, (viewport[3] - 2 * (y - viewport[1])) / deltay, 0);
		glm::mat4 pckTrlMtx = glm::translate(uniMtx, glm::vec3((viewport[2] - 2 * (x - viewport[0])) / deltax, (viewport[3] - 2 * (y - viewport[1])) / deltay, 0));
		glMultMatrixf(glm::value_ptr(pckTrlMtx));

		//glscalef(viewport[2] / deltax, viewport[3] / deltay, 1.0);
		glm::mat4 pckSclMtx = glm::scale(uniMtx, glm::vec3(viewport[2] / deltax, viewport[3] / deltay, 1.0));
		glMultMatrixf(glm::value_ptr(pckSclMtx));

		pckMtx = pckSclMtx * pckTrlMtx;
	}
  
	// Camera matrix: emulates the positioning of the camera.
	glm::mat4 prjMtx = (glm::perspective<float>(_camera.fov, viewAspect, 0.5, 100));
	//prjMtx *= pckMtx;

		// Load the projection matrix.	
	glMultMatrixf(glm::value_ptr(prjMtx));
//	glMatrixMode(GL_PROJECTION);
//	glLoadMatrixf(glm::value_ptr(prjMtx));
	glMatrixMode(GL_MODELVIEW);


	// In case of selection, narrows the view down to few pixels around the mouse 
	// cursor point (x, y) and extending two pixels in the vertical and horizontal 
	// direction.
	//if (sel) {
	//	Uint32 mPosView[3]; mb.posViewGet(mPosView);
	//	//gluPickMatrix(mPosView[0], viewport[3] - mPosView[1] + viewport[1], 3, 3, viewport);
	//

	//	/* Translate and scale the picked region to the entire window */
	//	Uint32 x = mPosView[0];
	//	Uint32 y = mPosView[1];
	//	Uint32 deltax = 3;
	//	Uint32 deltay = 3;

	//	glTranslatef((viewport[2] - 2 * (x - viewport[0])) / deltax, (viewport[3] - 2 * (y - viewport[1])) / deltay, 0);
	//	glscalef(viewport[2] / deltax, viewport[3] / deltay, 1.0);
	//}
  
		
	// Everything fine.
	return false;		 
}

//______________________________________________________________________________
bool View::glLight()
{
	/*! Fits the current OpenGL lighting to match the view settings. Returns
	 *	false if no error occurred, true otherwise.
	 */
	 
	// Enable lighting in case.
	if(_Lighting) {
		glEnable(GL_LIGHTING);

	// Normal mode without lightining.
	} else {
		glDisable(GL_LIGHTING);
		return false;
	}

	// For all the active lights.
	for (Uint64 l = 0; l < 8; l++) {	

		// Generate a GL_LIGHT_ID which identifies the current light.
		Uint16 GL_LIGHT_ID = 0x4000 + (Uint16)l;
			
		// If the light is ON enable it, otherwise turn off.
		if (_Light[l].On) glEnable(GL_LIGHT_ID);
		else {glDisable(GL_LIGHT_ID); continue;}

		// Pivots
		float v[4];					// Color vector.
		float lm = _Light[l].Mult;	// Multiplier.

		// Set Light Ambient.
		v[0] = _Light[l].Ambient[0] * lm; 
		v[1] = _Light[l].Ambient[1] * lm;
		v[2] = _Light[l].Ambient[2] * lm; 
		v[3] = _Light[l].Ambient[3];
		glLightfv(GL_LIGHT_ID, GL_AMBIENT, v);
		
		// Set light Diffuse.	
		v[0] = _Light[l].Diffuse[0] * lm; 
		v[1] = _Light[l].Diffuse[1] * lm;
		v[2] = _Light[l].Diffuse[2] * lm; 
		v[3] = _Light[l].Diffuse[3];
		glLightfv(GL_LIGHT_ID, GL_DIFFUSE, v);
		
		// Set light Specular.	
		v[0] = _Light[l].Specular[0] * lm; 
		v[1] = _Light[l].Specular[1] * lm;
		v[2] = _Light[l].Specular[2] * lm;
		v[3] = _Light[l].Specular[3];
		glLightfv(GL_LIGHT_ID, GL_SPECULAR, v);
		
		// Set light direction (being at infinite distance, position==direction).
		v[0] = -_Light[l].Dir[0]; 
		v[1] = -_Light[l].Dir[1]; 
		v[2] = -_Light[l].Dir[2]; 
		v[3] = 0.0f;
		glLightfv(GL_LIGHT_ID, GL_POSITION, v);
	}

	// Everything fine;
	return false;
}


// *****************************************************************************
// **								gl Utils								  **
// *****************************************************************************

//______________________________________________________________________________
double View::glViewZ(const int& vX, const int& vY) const
{
	/*! VGet the depth of the first visible object at the viewport \c 'vX' and
	 *	\c 'vY' location. */

	float vZ = 0;
	glReadPixels(vX, _Matrix.Viewport[3] - vY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &vZ);
	return vZ;
}

//______________________________________________________________________________
bool View::glViewToWorld(const double* vXYZ, double* wXYZ) const
{
	/*! Viewport to World transform. Transform the \c 'vXYZ' viewport 
	 *	coordinate into an object world coordinate \c 'wXYZ'. For the
	 *	viewport coordinate, the Z value is the depth value, ranging
	 *	[0 - 1]: Setting it to 0 means scratching the screen. 
	 */

	// Retrieve the transformed coordinates.
	gluUnProject(vXYZ[0], _Matrix.Viewport[3] - vXYZ[1], vXYZ[2], _Matrix.Modelview, _Matrix.Projection, _Matrix.Viewport, &wXYZ[0], &wXYZ[1], &wXYZ[2]);

	// Everything fine.
	return false;
}	

//______________________________________________________________________________
bool View::glWorldToView(const double* wXYZ, double* vXYZ) const
{
	/*! World to Viewport transform. Transform the \c 'wXYZ' world
	 *	coordinate into a viewport world coordinate \c 'vXYZ'. For the
	 *	viewport coordinate, the Z value is the depth value, ranging
	 *	[0 - 1]: 0 means scratching the screen, 1 being at infinite. 
	 */

	// Retrieve the transformed coordinates.
	gluProject(wXYZ[0], wXYZ[1], wXYZ[2], _Matrix.Modelview, _Matrix.Projection, _Matrix.Viewport, &vXYZ[0], &vXYZ[1], &vXYZ[2]);

	// Everything fine.
	return false;
}


// #############################################################################
}} // Close namespaces

