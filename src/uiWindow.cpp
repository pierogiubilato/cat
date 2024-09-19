//------------------------------------------------------------------------------
// CAT Graphics User Interface Window class									  --
// (C) Piero Giubilato 2013-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiWindow.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Application components
#include "uiWindow.h"


// #############################################################################
// Open namespaces
namespace cat { namespace ui {


// *****************************************************************************
// **							 Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
window::window(const char* title, const int& w, const int& h, const bool& r, 
					const int& x, const int& y)
{
	/*! Creates a SDL graphic windows of title \c title, width and height
	 *	\c w and \c h. If not specified by \c x and \c y, new windows will
	 *	appear centered on screen. This is just the basic graphic window,
	 *	which provides NO visualization. The window is open to host an OpenGL
	 *	context. The object which actually handles visualization and user 
	 *	interaction is the \c 'cat::ui::pad' object.
	 */

	// Prepares flag.
	Uint32 flag = SDL_WINDOW_OPENGL;
	if (r) flag = flag | SDL_WINDOW_RESIZABLE;

	// Check for start position.
	int pX, pY;
	if (x < 0) pX = SDL_WINDOWPOS_CENTERED;
	if (y < 0) pY = SDL_WINDOWPOS_CENTERED;

	// Set up the window.
	_window = SDL_CreateWindow(title, pX, pY, w, h, flag);	
	if (!_window) throw std::runtime_error("SDL_CreateWindow failed");

	// Enable SDL handling unicode and key-repeat.
//***	SDL_EnableUNICODE(1);
//***	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	

	// Create a renderer.
	_renderer = SDL_CreateRenderer(_window, 0, 0);

	// Create an OpenGL context.
	init_OpenGL();

	// Store values.
	_width = w;
	_height = h;
	_title = title;
	_resized = false;
}

//______________________________________________________________________________
window::~window() 
{
	/* Destroys the window and releases the allocated resources. */
	SDL_GL_DeleteContext(_GLContext);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}


//______________________________________________________________________________
bool window::initOpenGL()
{
	/*! Creates the OpenGL context to be drawn on the SDL graphic window. */ 
	
	// Delete OpenGL Context in case.
	if (_GLContext) SDL_GL_DeleteContext(_GLContext);

	// Create an OpenGL context for SDL.
	_GLContext = SDL_GL_CreateContext(_window);
	if (!_GLContext) throw std::runtime_error("SDL_GL_CreateContext failed");

	// Set refresh interval to match the monitor one
	SDL_GL_SetSwapInterval(1);

	// Initialize the GL Extention Library.
//	GLenum err = glewInit();
//	std::cout << err << "\n";
//	if (GLEW_OK != err) {
//		std::cout << COL(PEAR_COL_ERROR) 
//				  << "pear: GLEW initialization failed\n" 
//				  << COL(DEFAULT);
//		return true;
//	}

	// Everything ok.
	return false;
}


// *****************************************************************************
// **							   Public Members							  **
// *****************************************************************************

//______________________________________________________________________________
void window::swap()
{
	/* Swap the buffers of the window. */ 
	SDL_GL_SwapWindow(_window);

	// Update current window real size.
	int oldW = _width;
	int oldH = _height;
	SDL_GetWindowSize(_window, &_width, &_height);

	// Raise the resized flag in case.
	_resized = (oldW != _width || oldH != _height); 
}

//______________________________________________________________________________
void Window::title(const std::string& title)
{
	/*! Sets the window title. */
	_title = title; 
	SDL_SetWindowTitle(_window, _title.c_str());
}

//______________________________________________________________________________
std::string window::title() const
{
	/*! Returns the window title. */ 
	return _title;
}

// #############################################################################
}} // Close namespaces
