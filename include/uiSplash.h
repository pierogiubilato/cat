//------------------------------------------------------------------------------
// CAT user interface splash window											  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiSplash.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Overloading check
#if !defined uiSplash_H
#define uiSplash_H

// Application components.
#include "ui.h"
	
// #############################################################################
namespace cat { namespace ui {

//! CAT splash window
/*! cat::ui:splash is a simple splash-window manager.
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 20 Sep 2024
 */
//______________________________________________________________________________	
class splash //: public UI
{
	private:	
		
		// SDL elements.
		SDL_Window* _window;		// Window.
		SDL_Renderer* _renderer;	// Renderer.
		SDL_Texture* _tImage;		// Texture to be rendered
		
		// Self elements.
		unsigned int _timeout;
	
	public:
		
		// Special members.
		splash(const unsigned int& tOut = 10000);	//!< Default ctor.
		~splash();	//!< Default dtor.

		// Commands.
		void run(const unsigned int& tOut = 10000);		// Run the splash.
		void quit();	// Close the splash.
		void save();	// Save the image to a file.
		
		// Settings.
		SDL_Window* window() const {return _window;}	// Returns Window*.
		unsigned int timeout() const {return _timeout;}	// Returns Timeout.
};

// #############################################################################
}} // Close namespace


// Overloading check
#endif
