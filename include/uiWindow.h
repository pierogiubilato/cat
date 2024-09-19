//------------------------------------------------------------------------------
// CAT Graphic User Interface window class				 					  --
// (C) Piero Giubilato 2011-2013, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiWindow.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"16 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined uiWindow_H
#define uiWindow_H

// Application components
#include <ui.h>


// #############################################################################
// Open namespaces
namespace cat { namespace ui {

//! Basic graphic window
/*! cat::ui::Window handles a graphic window interface, providing the actual 
 *	window and an handle to it. It is just a basic container, used by higher 
 *	level entities to actually provide an usable interface.
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 16 Sep 2024
 */
//______________________________________________________________________________
class window: public ui 
{
	private:
		
		// General window properties
		int _width;
		int _H
			height;
		bool _resized;
		std::string _title;
		SDL_Window* _window;
		SDL_Renderer* _renderer;

		// OpenGL context
		SDL_GLContext _GLContext;
		bool initOpenGL();

	protected:
	public:

		// Special members
		window(const char* title, const int& w, const int& h, const bool& resizable = true, 
				const int& x = -1, const int& y = -1); 
		~window();

		// Window properties
		SDL_Window* handle() const {return _window; }		//!< Returns window handle.
		SDL_Renderer* renderer() const {return _renderer;}	//!< Returns window handle.
		SDL_GLContext GLContext() const {return _GLContext;}//!< Returns window handle.
		int width() const	{return _width;}				//!< Returns window width. 
		int height() const	{return _height;}				//!< Returns window height.
		bool resized() const {return _resized;}				//!< Check id window has been resized.

		// Window methods
		void swap();										//!< Swaps the window buffer.
		void title(const std::string& title);				//!< Set window title.
		std::string title() const;							//!< Get window title.
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
