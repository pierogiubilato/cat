//------------------------------------------------------------------------------
// CAT Graphics User Interface (GUI) user interface pad class                 --
// (C) Piero Giubilato 2011-2024, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiPad.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined uiPad_H
#define uiPad_H

// Application Components
#include "ui.h"
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
class pad
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
		bool initWindow(const char* title, const bool& r);
		bool initOpenGL();
		void initInfo() const;

		// Misc functions.
		void titleDraw(const double& timing = 0);
		
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
		std::vector<cat::gp::scene*> _scene;	// The scene database.		
//		std::vector<view*> _view;				// The scene(s) view(s).						
		Uint64 _gpsCount;						// Number of GPs in the currently selected scene.
		Uint64 _gpsSize;						// Total size of the GPs in the currently selected scene.
	
		// Drawing/Selection status
		static const int _selBufferSize = 1024;	// Selection buffer size.
		//GLuint _selBuffer[_selBufferSize];	// Selection buffer.
		unsigned int _selHits;					// Selection hits.
		std::vector<cat::gp::GPHnd> _selGPHnd;	// The select primitive/s handle/s.
		bool _selForceRedraw;					// Force redraw due to selection.

		// Special members
		pad(const Uint64& Idx, const char* title, const bool& resizable = true); 
		~pad();
		
		// Loop and event handlers.
		bool evnHandler();						//!< Events handler.
		bool evnSystem(SDL_Event);					//!< Handles system events.
		bool evnKeyboard(SDL_Event);				//!< Handles keyboard events.
		bool evnMouse(SDL_Event);					//!< Handles mouse events.
		
		// Selection.
		void selClear();							//!< Clear any selection.
		void selAdd(const cat::gp::GPHnd&);			//!< Add a GP to the selection.
		void selAdd(const std::vector<cat::gp::GPHnd>&);	//!< Add a list of GPs to the selection.
		void selShow();								//!< Highlight the GPS in the selection vector.

		// Scene(s) management.
		Uint64 sceneCount();						//!< The number of hosted scenes.
		cat::gp::scene* sceneGet(cat::gp::GPHnd = 0);	//!< The hosted scene access.
		cat::gp::GPHnd sceneAdd(cat::gp::scene*);	//!< Sets ownership over a new scene.
		void sceneDel(cat::gp::GPHnd);				//!< Delete a owned scene.
		void sceneSel(cat::gp::GPHnd);				//!< Select the active scene.
				
		// Pad management.
		void run(const bool& openLoop = false);		//!< Runs the pad.
		void refresh();								//!< Refresh the pad.
		Uint64 size();								//!< Returns the Pad total allocated memory (bytes).
		Uint64 idx() const;							//!< Returns the pad Idx.
		void idx(const Uint64&);					//!< Resets the pad Idx.
		void info() const;							//!< Dumps pad info.

		// GL Drawing.
		virtual bool glDraw();						//!< Graphic redraw.	
		void glTime();								//!< Graphic timing.
		size_t glHits(double& minZ, const bool& add = false, const bool& all = false);	//!< Graphic selection.	
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif