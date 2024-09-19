//------------------------------------------------------------------------------
// CAT main Graphic User Interface window pad class							  --
// (C) Piero Giubilato 2011-2013, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiPad.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Application components
#include "uiPad.h"
//#include "uiSplash.h"


// #############################################################################
namespace cat { namespace ui { 


// *****************************************************************************
// **							  Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
pad::pad(const Uint64& idx, const char* title, const bool& r): _idx(idx)
{
	/*! Creates a pad, a minimal self-running graphical pad. The \c Pad object
	 *	provides a graphic window and a main event loop to handle user inputs.
	 */
		
	// Startup presets.
	_title = title;	

	// OpenGL status.
//	_glAuxFrameBufCount = 0;
//	for (int i = 0; i < 10; i++) {
//		_glFrameBuffer[i] = 0;
//		_glRenderBuffer[i] = 0;
//	}

	// Timing.
//	_tmrTimer.Reset();
//	_tmrCycle = 0;
//	_tmrCycleCount = 10;

	// Here the pivot Scene (scene #0) is added. It is always assumed to be
	// present, as all the controls in the pad link to it.
	_sceneIdx = 0;
	
	// No scene and views present at startup.
	_scene.clear();
	_view.clear();
	_scene.push_back(NULL); 
	_view.push_back(NULL);
	
	// Scene status.
	_gpsCount = 0;
	_gpsSize = 0;

	// Selection status.
	_selForceRedraw = false;
	
	// Init the window which hosts the pad.
//	if (init_Window(title, r)) throw std::runtime_error("Window initialization failed.");
	
	// Init the OpenGL library.
//	if (init_OpenGL()) throw std::runtime_error("OpenGL initialization failed.");
	
	// Init the pad modules.
//	GUI = new pad_GUI(this);
//	GL = new pad_GL(this);

	// Show startup info if requested.
	if (cat::ag::_stupShowInfo) init_Info();
}

//______________________________________________________________________________
pad::~pad() 
{
	/*! Realeses all allocated resources. */

	// Clear all the scenes. Attention: as the scene #0, the current scene, is 
	// simply a copy of one of the other scenes pointer, it must NOT be deleted,
	// otherwise a scene would be deleted twice!
	for (Uint64 i = 1; i < _scene.size(); i++) {
		delete _scene[i];
		_scene[i] = 0;
	}
	_scene[0] = 0;
	
	// Delete the associate modules.
//	delete GUI;
//	delete GL;

	// Release OpenGL framebuffers.
//	if (GLEW_VERSION_3_0) {
//		glDeleteFramebuffers(10, _glFrameBuffer);
//		glDeleteRenderbuffers(10, _glFrameBuffer);
//	}

	// Delete the pad graphic window.
	delete _window;
}


// *****************************************************************************
// **								Private Members							  **
// *****************************************************************************

//______________________________________________________________________________
bool Pad::init_Window(const char* title, const bool& r)
{
	/*! Startup the SDL library and open the pad graphic window. */ 
	
	// Creates the window.
	_Window = new Window(title, PEAR_PAD_WIDTH, PEAR_PAD_HEIGHT, r);
	if (!_Window) return true;

	// Everything ok.
	return false;
}

//______________________________________________________________________________
bool Pad::init_OpenGL()
{
	/*! A general OpenGL initialization function.  Sets all of the initial
	 *	gl parameters. We call this right after our OpenGL window is created
	 *	or every time it is resized.
	 */

	// General Properties 	
	glViewport(0, 0, _Window->Width(), _Window->Height());		// Set Viewport to window size. 
	glDepthRange(0.0, 100.0);				// Set Depth Range (important for depth-picking). 
	glEnable(GL_DEPTH_TEST);				// Enables Depth Testing.
	glShadeModel(GL_SMOOTH);				// Enables Smooth Color Shading.
	glEnable (GL_BLEND); 					// Enables Blending (For Transparent Effects). 
	glEnable(GL_NORMALIZE); 				// Enable Automatically normalized normal vectors.   
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enables Blending w/ Alpha Value.    
	
	// Reset matrixes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	// Retrieves OpenGL status.
	glGetIntegerv(GL_AUX_BUFFERS, &_glAuxFrameBufCount);	// Available auxiliary framebuffers.

	// If OpenGL Version >= 1.5, create a support framebuffer.
	if (GLEW_VERSION_3_0) {
		
		// Kill previous in case.
		glDeleteFramebuffers(10, _glFrameBuffer);
		glDeleteRenderbuffers(10, _glFrameBuffer);
		
		// Creates the color and depth render buffers.
		glGenRenderbuffers(2, _glRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, _glRenderBuffer[0]);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, _Window->Width(), _Window->Height());
		glBindRenderbuffer(GL_RENDERBUFFER, _glRenderBuffer[1]);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, _Window->Width(), _Window->Height());

		// Creates the frame buffer.
		glGenFramebuffers(1, &_glFrameBuffer[0]);
		glBindFramebuffer(GL_FRAMEBUFFER, _glFrameBuffer[0]);
		
		// Attach the renderbuffer to the framebuffer.
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _glRenderBuffer[0]);
		glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _glRenderBuffer[1]);
		
		// By default bind the drawing buffer to the window one.	
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}
 
	// Everything ok.
	return false;
}

//______________________________________________________________________________
void Pad::init_Info() const
{
	/*! Give a little info about the graphic environment of the pad. */
	
	// Show OpenGL info.
	std::cout << COL(LWHITE) << "\nOpenGL\n" << COL(DEFAULT);
	std::cout << "   Vendor:   " << glGetString(GL_VENDOR) << "\n";
	std::cout << "   Version:  " << glGetString(GL_VERSION) << "\n";
	std::cout << "   Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "   Shading:  " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	//std::cout << "  Extens.:   " << glGetString(GL_EXTENSIONS) << "\n";

	// Retrieve names stack size.
	GLint param; 
	glGetIntegerv(GL_MAX_NAME_STACK_DEPTH, &param);
	std::cout << "   Name max stack: " << param << "\n";
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &param);
	std::cout << "   Modelview max stack: " << param << "\n";
	glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &param);
	std::cout << "   Projection max stack: " << param << "\n";
	glGetIntegerv(GL_MAX_CLIP_PLANES, &param);
	std::cout << "   Clip planes max: " << param << "\n";

	// Frambuffers.
	glGetIntegerv(GL_AUX_BUFFERS, &param);
	std::cout << "   Auxiliary Framebuffers: " << param << "\n";
}

//______________________________________________________________________________
void Pad::title_Draw(const double& timing)
{
	/*! Sets the pad window title, with eventual scene name and timing info. */
	
	// Pivot stream.
	std::stringstream title("");
	title << std::setiosflags(std::ios::fixed) << std::setprecision(2);
	
	// Adds application name.
	title << PEAR_VER_TITLE;
	
	// Adds scene name (in case).
	if (_scene[0]) title << " - " << _scene[0]->Name();
	
	// Adds timing (in case).
	if (timing > 0) title << " (" << timing << " ms/frame)";
	
	// Updates window.
	_Window->Title(title.str());
}


// *****************************************************************************
// **						Private interface events						  **
// *****************************************************************************

//______________________________________________________________________________
bool Pad::evn_Handler()
{
	/*! Processes the SDL provided events queue. This function actually handles
	 *	all the keyboard, system and mouse inputs to the program. 
	 */

	// The current event reference.
	SDL_Event evn;

	// Scan through the event queue.
	while(SDL_PollEvent(&evn)) {
			
		// Tweak Bar.
		if (GUI->evnBar(evn)) continue;
					
		// System.
		if (evn_System(evn)) return true;

		// Keyboard.
		if (evn_Keyboard(evn)) return true;
		
		// Mouse.
		if (GUI->evnMouse(evn)) return true;
		
	} // End of event queue LOOP.
	
	// Everything ok.
	return false;
}

//______________________________________________________________________________
bool Pad::evn_System(SDL_Event evn)
{
	/*! Handles system events. */
  	
	// Window events.
	if(evn.type == SDL_WINDOWEVENT) {
			
		// Close
		if (evn.window.event == SDL_WINDOWEVENT_CLOSE) return true;
		
		// Resized.
		if (evn.window.event == SDL_WINDOWEVENT_RESIZED) {
			
			// Get latest window size.
			_Window->Swap();
			
			// Reset the OpenGL context for the new size.
			init_OpenGL();
			
			// Reset the TwBar for the new size.
			GUI->updateTwBar();

			// Updates the mouse utilities
			GUI->updateMouse();
 
			// Updates the layout.
			GUI->LayoutSet();
		}

		// Minimized.
		if (evn.window.event == SDL_WINDOWEVENT_MINIMIZED) {
			// Do something here.
		}
	
	} // End of Window event
   
	// Everything ok.
	return false;	
}

//______________________________________________________________________________
bool Pad::evn_Keyboard(SDL_Event evn)
{
	/*! Handles keyboard events. */
  	if(evn.type == SDL_KEYDOWN) {
			 
		// Switch the key
		switch(evn.key.keysym.sym) {
				
			// Movements
			case SDLK_UP: break;
			case SDLK_DOWN: break;
			case SDLK_LEFT: break;
			case SDLK_RIGHT: break;
				
			// Commands
			case SDLK_q: return true;	// Quit, stop the loop.
		}
	} // End of Keyboard event
     	
	// Everything ok.
	return false;	
}


// *****************************************************************************
// **							Public Scene Management						  **
// *****************************************************************************

//______________________________________________________________________________		
gp::Scene* Pad::scene_Get(Uint64 sIdx)
{
	/*! Returns the scene identified by \c sIdx. If \c sIdx is omitted, or out of
	 *	range, the current active scene will be returned. Note that \c sIdx=0 
	 *	equals to get the currently selected scene. Scene #0 is always the
	 *	currently selected scene. 
	 */
	if (sIdx >= _scene.size()) return _scene[0];
	else return _scene[sIdx];
}

//______________________________________________________________________________
Uint64 Pad::scene_Count()
{
	/*! Return the number of scene in the Pad. This number accounts for all the
	 *	hosted scenes but not for the active scene (scene #0), so the number
	 *	returned is actually the _scene vector size -1. 
	 */
	return _scene.size() - 1;
}

//______________________________________________________________________________
Uint64 Pad::scene_Add(gp::Scene* scene)
{
	/*! Adds a scene to the Pad. Mind that Pad will take ownership over the 
	 *	scene, i.e. it will delete it or tamper with it at will. The scene 
	 *	has not to be managed by anyone else after being added to the Pad.
	 * 	A linked View is also added, so every scene keeps its own view settings. 
	 *	Returns the scene handle to recall/select it later.
	 */
	
	// Adds the scene.
	_scene.push_back(scene);
	
	// Create a view and link it to the pad.
	_View.push_back(new View(this)); 
	
	// If this is the only scene (the first one added), select it.
	if (_scene.size() == 2) {
		scene_Sel(1);
	}

	// Updates the bars.
	Refresh();
	
	// Returns the current scene.
	return _scene.size() - 1;
}

//______________________________________________________________________________
void Pad::scene_Del(Uint64 sIdx)
{
	/*! Deletes a sene. Scene #0 cannot be deleted. */
	
	// Check for boundaries.
	if (sIdx == 0 || sIdx >= _scene.size()) return; 

	// Delete scene and associated view.
	delete _scene[sIdx];
	delete _View[sIdx];
	_scene.erase(_scene.begin() + sIdx);
	_View.erase(_View.begin() + sIdx);

	// If no more scenes, reset the current scene.
	if (_scene.size() == 1) {
		_scene[0] = NULL;
		_View[0] = NULL;
		_sceneIdx = 0;
	}

	// If the deleted scene was the curretly selected one, change
	// the current selection to the first scene in the list.
	if (_sceneIdx == sIdx && _scene.size() > 1) scene_Sel(1);

	// Updates the bars.
	Refresh();
}

//______________________________________________________________________________
void Pad::scene_Sel(Uint64 sIdx)
{
	/*! Selects a scene, making it the active (displayed) one. Scene #0 cannot 
	 *	be seleted, i.e. selecting it makes nothing, as scene #0 is by default 
	 *	the currently selected scene. 
	 */
	if (sIdx > 0 && sIdx < _scene.size()) {
		_scene[0] = _scene[sIdx];
		_View[0] = _View[sIdx];
		_sceneIdx = sIdx;
	}

	// Reset current selection.
	_SelGPHnd.clear();

	// Updates the bars.
	Refresh();

}

// *****************************************************************************
// **						Public Members Pad Management					  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 Pad::Idx() const 
{
	/*! Retrieves the pad Idx. */
	return _Idx;
}

//______________________________________________________________________________
void Pad::Idx(const Uint64& Idx) 
{
	/*! Assigns the pad Idx. */
	_Idx = Idx;
}

//______________________________________________________________________________
Uint64 Pad::Size()
{
	/*! Returns the Pad's amount of allocated memory in bytes. It also stores
	 *	the result in \c _Size for internal purposes.
	 */
	
	// The pad itself size (minimal...).
	Uint64 tSize = sizeof(this);
	
	// Sums over all the scenes.
	for (Uint64 i = 0; i < _scene.size(); i++) {
		if(_scene[i]) tSize += _scene[i]->Size();
	}
	
	// Well done!
	_Size = tSize;
	return tSize;
}

//______________________________________________________________________________
void Pad::Run(const bool& openLoop) 
{
	/*! Main pad loop, handles the event and referesh the display. If 
	 *	\c openLoop is set to \c true, it just runs one loop and then exit,
	 *	but retaining the full current status ready for the next Run call.
	 *	Resize and other window events are managed by the event handler routine.
	 */
	
	// While an explicit quit is called.
	while(!evn_Handler()) {
		
		// Redraw the Scene.
		if(glDraw()) break;
		
		// Repaint the GUI. GUI is painted on the front buffer, so the back
		// color buffer always old the "clean" scene picture.
		if(GUI->glDraw()) break;
		
		// Show updated graphic in Pad window.
		_Window->Swap();
		
		// It not continuos, just exit for this time.
		if (openLoop) break;
	}
}

//______________________________________________________________________________
void Pad::Refresh() 
{
	/*! Refreshes the Pad and the bars. */
	
	// Calculate its own size
	Size();
	
	// Update current scene info
	if (_scene[0]) {
		_GPsCount = _scene[0]->gp_Count(); 
		_GPsSize = _scene[0]->Size();
	}

	// The Main bar is always refreshed
	GUI->updateBars();
}

//______________________________________________________________________________
void Pad::Info() const
{
	/*! Provide pad infos (mostly SDL and OpenGL status). */
	init_Info();
}


// *****************************************************************************
// **						  Public selection members						  **
// *****************************************************************************

//______________________________________________________________________________
void Pad::SelClear() 
{
	/*! Unselect all the selected GPS and clear the selection vector. */
	
	// Check for the scene.
	if (!_scene[0]) return;

	// Releases the selected GPs.
	for (size_t i = 0; i < _SelGPHnd.size(); i++) {
		GP* gp = _scene[0]->gp_Get(_SelGPHnd[i]);
		if(gp) gp->modeSelected(false);
	}

	// Now clear the selection vector.
	_SelGPHnd.clear();
	_SelForceRedraw = false;

	// Updates the interface.
	GUI->evnSelect(_SelGPHnd); 
}

//______________________________________________________________________________
void Pad::SelAdd(const GPHnd& gpHnd) 
{
	/*! Add to the selection vector. */
	
	// Check if already present.
	for (size_t i = 0; i < _SelGPHnd.size(); i++) {
		if (gpHnd == _SelGPHnd[i]) return;
	}

	// Add.
	_SelGPHnd.push_back(gpHnd);
}

//______________________________________________________________________________
void Pad::SelAdd(const std::vector<GPHnd>& sel) 
{
	/*! Add to the selection vector. */
	
	// Check if not already present and add.
	size_t i, j;
	for (i = 0; i < sel.size(); i++) {
		for (j = 0; j <_SelGPHnd.size(); j++) {
			if (sel[i] == _SelGPHnd[j]) break;
		}
		if (j == _SelGPHnd.size())	{
			_SelGPHnd.push_back(sel[i]); 	
			//_scene[0]->gp_Get(sel[i])->modeSelected(true);
		}
	}
}

//______________________________________________________________________________
void Pad::SelShow() 
{
	/*! Switch the selected option for all the GPs stored into the selection
	 *	vector. This allow to not highlight selected items, yet having them
	 *	stored for other purposes than direct modification.
	 */
	
	// Check if not already present and add.
	for (size_t i = 0; i < _SelGPHnd.size(); i++) {
		_scene[0]->gp_Get(_SelGPHnd[i])->modeSelected(true);
	}
	
	// We have highlighted objects potentially on modification,
	// so force the redraw to see real-time updates.
	_SelForceRedraw = true;

	// Updates the interface.
	GUI->evnSelect(_SelGPHnd); 
}


// *****************************************************************************
// **						  Private drawing members						  **
// *****************************************************************************

//______________________________________________________________________________
bool Pad::glDraw()
{
	/*! This is THE pad main DRAWING function, the one which actually manages
	 *	to continuosly redraw the selected scene. */

	// Check if there is anything to display...
	if (!_sceneIdx) return false;
	if (!_scene[0]) return false;

	// Anti-aliasing on following objects.
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);

	// Blending mode.
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Pivot reference to the view for the current scene.
	View* view = _View[0];
	
	// If OpenGL >= 3.0, enforce the auxiliary buffer as drawing target.
	if (GLEW_VERSION_3_0) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _glFrameBuffer[0]);
	}

	// Highlight selected GPs if selection is confirmed for displaying.	
	if (GUI->MousePick().StatusGet() == GUI->MousePick().kPk_Confirmed) {
		SelShow();
		GUI->MousePick().StatusStep();
	}

	// Sets the view. Perform a selection rendering if picking is active.
	if (GUI->MousePick().StatusGet() == GUI->MousePick().kPk_Started) {

		GUI->MousePick().StatusStep();	// Updates current picking status.
		glSelectBuffer(_SelBufferSize, _SelBuffer);	// Init selection buffer.
		
		// Initializes selection mode. 	
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(0);

		// Set the special picking view.
		view->glSet(GUI->MouseBall(), true);  
		view->NeedRedraw(true);		

	// Otherwise is a normal rendering.
	} else view->glSet(GUI->MouseBall()); 
		
	// Do the actual redraw. Always if no GL_3.0, when needed otherwise.
	if (!GLEW_VERSION_3_0 || view->NeedRedraw() || _scene[0]->modeNeedRedraw() || _SelForceRedraw) {
		
		// Start redraw timing.
		glTime();
	
		// Anyway clears the screen and the depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Renders non trasparent objects first. 
		for (Uint64 i = 1; i < _scene[0]->gp_Size(); i++) {
			GP* gp = _scene[0]->gp_Get(i); 
			if (gp) if (!(gp->glAlpha())) gp->glDisplay();
		}
			
		// Renders transparent objects then.
		for (Uint64 i = 1; i < _scene[0]->gp_Size(); i++) {
			GP* gp = _scene[0]->gp_Get(i); 
			if (gp) if ((gp->glAlpha())) gp->glDisplay();
		}

		// Reset the scene redrawing necessity.
		_scene[0]->modeNeedRedraw(false); 
		
		// Stop timing.
		glTime();
	}
	
	// Reset the stack matrixes. VERY important!
	view->glReset(); 

	// Returns always to render mode. Stores anyway 
	// the size of the selection buffer in _SelHits.
	_SelHits = glRenderMode(GL_RENDER);
		
	// Copy the auxiliary framebuffer into the window one.
	if (GLEW_VERSION_3_0) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, _glFrameBuffer[0]);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBlitFramebuffer(0, 0, _Window->Width(), _Window->Height(), 
						  0, 0, _Window->Width(),  _Window->Height(),
						  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	// If any picking action, process and end it.
	if (GUI->MousePick().StatusGet() == GUI->MousePick().kPk_Rendered) {
		std::cout << "glDraw: Processing picking list\n";
		
		// Processes the hits buffer. If there is an hit, stores the minZ
		// value into the mouseBall for eventual rotation/scaling.
		double zMin = 0;
		//if (glHits(zMin, false, false) > 0) GUI->MouseBall().BeginZ(zMin);
		//else GUI->MouseBall().BeginZ(0);
		glHits(zMin, false, false);

		// Updates scene redrawn and picking status. 		
		_scene[0]->modeNeedRedraw(true);
		GUI->MousePick().StatusStep();
	}		
	
	// Everything ok.
	return false;	
}

//______________________________________________________________________________
void Pad::glTime()
{
	/*! Simply timing info about the rendering time */
	
	// Stop.
	if (_tmrTimer.Running()) {
		_tmrTimer.Stop();

	// Start.
	} else {
	
		_tmrCycle++;
		if (_tmrCycle == _tmrCycleCount) {
		
			// Calculate average frame time in ms.
			double avg = std::floor(100.0f * _tmrTimer.Elapsed_ms() / (double)_tmrCycleCount) / 100.0f;
		
			// Update title.
			title_Draw(avg);

			// Reset.
			_tmrTimer.Reset();
			_tmrCycle = 0;
		}
		_tmrTimer.Start();
	}

	// Reset
	_SelHits = 0;
}

//______________________________________________________________________________
size_t Pad::glHits(double& minZ, const bool& add, const bool& all)
{
	/*! Parses the selection buffer and retrieves which object/s has/have been 
	 *	selected. Selected objects will be loaded to the _SelGPHnd vector, adding
	 *	them to the existent records if \c 'add' is set to true, or filling the
	 *	vector from scratch if \c 'add' is set to false (default).
	 *	The \c 'all' switch tells whether to include in the selection vector only
	 *	the topmost primitive found in the hit list. If false (default) only the
	 *	topomost primitive is added to the selection vector, otherwise all the 
	 *	primitives are added to the vector.
	 *	The function returns the size of the selection vector as argument, and 
	 *	loads into \c 'minZ' the viewport Z value of the closest found item.
	 */

	// Store an old vector.
	std::vector<GPHnd> oldGPHnd = _SelGPHnd;
	std::vector<GPHnd> newGPHnd;

	// Prepare to search Buffer 
	int hitHnd = 0;				// 'Picked' GP handle.
	GLuint* ptr = _SelBuffer;	// Pointer to buffer element.
	float gMin = 0;				// Global minimum for the selection.	

	// Search! Loop over each hit, and every element in the hit buffer.
	for (size_t i = 0; i < _SelHits; i++) {
			
		// How many names for this hits.
		GLuint names = *ptr; ptr++;
			
		// Minimum Z (orthogonal to the screen plane).
		float zMin = (float) *ptr/0x7fffffff; ptr++;
			
		// Maximum Z (orthogonal to the screen plane).
		/* No need to store the maximum */; ptr++;
			
		// Retrieves all the names for this hit.
		unsigned int name = 0;
		for (unsigned int j = 0; j < names; j++) {
			name = *ptr; ptr++;
			//std::cout << "Hit: " << i << ", name: " << name << ", zMin: " << zMin << "\n";
		}

		// "All what it's in view" pick mode, store every hit found.
		if (all) newGPHnd.push_back(name);  
				 
		// Single pick mode, search for the topmost primitive.
		else {
			if(i == 0 || zMin < gMin) {
				gMin = zMin;	// Set global minimum. 
				hitHnd = name;	// Store GP handle.
			}
		}		
	}

	// Store the gMin hit in case of single selection.
	if (!all && hitHnd > 0) newGPHnd.push_back(hitHnd);

	// Anyway, store the minimum Z.
	minZ = gMin;
	
	// Now, compare new and hold vector, and remove from the
	// new vector any GPs already present in the old one, so
	// accounting for swapping of selected object/s.
	size_t i = 0, o = 0;
	while (i < newGPHnd.size()) {
		
		// Kill the item if present in the old vector.
		for (o = 0; o < oldGPHnd.size(); o++) {				
			if (newGPHnd[i] == oldGPHnd[o]) {
				newGPHnd.erase(newGPHnd.begin() + i);
				break;
			}
		}
		
		// Increases i only if no kill has happened.
		if (o == oldGPHnd.size()) i++;
	}

	// DEBUG: show the sel vector.
	//std::cout << "Selection vector:\n";
	//for (size_t i = 0; i < _SelGPHnd.size(); i++) {
	//	std::cout << "Sel: " << i << ", Handle: " << _SelGPHnd[i] << "\n";
	//}

	// Reset the selection vector in case.
	if (!add) SelClear();
	SelAdd(newGPHnd);
	
	// Returns how many GP are in the selection vector.
	return newGPHnd.size();	
}


// #############################################################################
}} // Close namespaces