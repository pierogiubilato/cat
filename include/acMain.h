//------------------------------------------------------------------------------
// CAT application core entry point											  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"acMain.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined acMain_H
#define acMain_H

// STL.
#include <string>

// SDL (used also for numeric types).
//#include "SDL.h"
//#include "SDL_opengl.h"

// Application globals
#include "acGlobal.h"



// Personalized streams are spread through all the application.
//#include "afStream.h"


// #############################################################################
namespace cat {

	// Application global status and switches.
	namespace ag {

		// Miscellanea.
		extern int _verbose;			//!< Verbosity level.
	
		// Startup switches.
		extern bool _stupShowInfo;		//!< Show general info.
		extern bool _stupShowFont;		//!< Show installed fonts.
		extern bool _stupShowHelp;		//!< Show quick help.

		// Paths.
		extern std::string _pathMain;	//!< The application path.
		extern std::string _pathFonts;	//!< The font directory path.
	
		// Screen.
		extern int _screenDPIX;		//!< The screen resolution.
		extern int _screenDPIY;		//!< The screen resolution.
	} 
	
	// Application Core (AC) services.
	namespace ac {
		class loop;
		extern loop*	_loop;		//!< Main application handler.
		class server;
		extern server*	_server;	//!< Main application server.
	}
	
	// Application Facilities (AF) services.
	namespace af {
		class font;
		extern font*	_font;		//!< Font Facility.
		class file;
		extern file*	_file;		//!< File Facility.
	}

// #############################################################################
} // Close namespaces
	
// Overloading check
#endif
