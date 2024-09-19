//------------------------------------------------------------------------------
// CAT Graphics User Interface (GUI) user interface pad class                 --
// (C) Piero Giubilato 2011-2024, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiPad.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"10 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined uiPad_H
#define uiPad_H

// Application Components
#include "uiBase.h"
//#include "uiWindow.h"
#include "gpScene.h"
//#include "uiPadGUI.h"
//#include "uiPadGL.h"
//#include "uiView.h"
//#include "afTimer.h"

// AntTweakBar
//#include "AntTweakBar/AntTweakBar.h"


// #############################################################################
namespace pear { namespace ui {

//! Basic graphic interface
/*! A pear::ui::Pad handles a graphic display, an OpenGL layer and also manages 
 *	the user interaction. It uses a pear::Window class as base window, and it 
 *	puts an OpeGL viewport on it. Events management is handled through the SDL
 *	routines.
 *	The Pad hosts a vector of gps::scene, with the number 0 used as a pivot 
 *	element made equal to the actually displayed one.
 *
 *	\author Piero Giubilato
 *	\version 1.2
 *	\date 27 Sep 2024
 */
class pad: public base 
{
	private:
	
		// The personal timer used to check speed.
		//pear::af::timer _tmrTimer;
		//pear::af::timer _tmrTimer2;
		Uint32 _tmrCycle;
		Uint32 _tmrCycleCount;

		// OpenGL status.
		//GLint _glAuxFrameBufCount;		// Available auxiliary frame buffers.
		//GLuint _glFrameBuffer[10];		// Specific frame buffers.
		//GLuint _glRenderBuffer[10];		// Specific render buffers.
		
		// Initializations functions.
		bool init_Window(const char* title, const bool& r);
		bool init_OpenGL();
		void init_Info() const;

		// Misc functions.
		void title_Draw(const double& timing = 0);
		
	protected:
	
	public:
	
		// Handles to the graphic elements.
		//Window* _Window;
		//SDL_GLContext _GLContext;
		//std::vector<TwBar*> _TwBar;
		
		// Modules
		//pad_GUI* GUI;							//!< Pad's personal user interface.
		//pad_GL* GL;								//!< Pad's personal raster drawing primitives.

		// Status and properties
		Uint64 _idx;							// Main loop assigned identifier.
		Uint64 _sHnd;							// Linked socket handle.
		Uint64 _size;							// Last "measured" memory occupation.
		std::string _title;						// Main title.
		
		// The hosted scene(s)
		Uint64 _sceneIdx;						// The current scene Idx.
		std::vector<gp::scene*> _scene;			// The scene database.		
		std::vector<view*> _view;				// The scene(s) view(s).						
		Uint64 _gpsCount;						// Number of GPs in the currently selected scene.
		Uint64 _gpsSize;						// Total size of the GPs in the currently selected scene.
	
		// Drawing/Selection status
		static const int _selBufferSize = 1024;	// Selection buffer size.
		//GLuint _selBuffer[_selBufferSize];		// Selection buffer.
		unsigned int _selHits;					// Selection hits.
		std::vector<gpHnd> _selGPHnd;			// The select primitive/s handle/s.
		bool _selForceRedraw;					// Force redraw due to selection.

		// Special members
		pad(const Uint64& Idx, const char* title, const bool& resizable = true); 
		~pad();
		
		// Loop and event handlers.
		bool evn_Handler();						//!< Events handler.
		bool evn_System(SDL_Event);				//!< Handles system events.
		bool evn_Keyboard(SDL_Event);			//!< Handles keyboard events.
		bool evn_Mouse(SDL_Event);				//!< Handles mouse events.
		
		// Selection.
		void selClear();						//!< Clear any selection.
		void selAdd(const gpHnd&);				//!< Add a GP to the selection.
		void selAdd(const std::vector<gpHnd>&);	//!< Add a list of GPs to the selection.
		void selShow();							//!< Highlight the GPS in the selection vector.

		// Scene(s) management.
		Uint64 scene_Count();					//!< The number of hosted scenes.
		gp::scene* scene_Get(gpHnd = 0);		//!< The hosted scene access.
		gpHnd scene_Add(gp::Scene*);			//!< Sets ownership over a new scene.
		void scene_Del(gpHnd);					//!< Delete a owned scene.
		void scene_Sel(gpHnd);					//!< Select the active scene.
				
		// Pad management.
		void run(const bool& openLoop = false);	//!< Runs the pad.
		void refresh();							//!< Refresh the pad.
		Uint64 size();							//!< Returns the Pad total allocated memory (bytes).
		Uint64 idx() const;						//!< Returns the pad Idx.
		void idx(const Uint64&);				//!< Resets the pad Idx.
		void info() const;						//!< Dumps pad info.

		// GL Drawing.
		virtual bool glDraw();					//!< Graphic redraw.	
		void glTime();							//!< Graphic timing.
		size_t glHits(double& minZ, const bool& add = false, const bool& all = false);	//!< Graphic selection.	
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif