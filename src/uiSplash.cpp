//------------------------------------------------------------------------------
// CAT splash window point				 									  --
// (C) Piero Giubilato 2011-2013, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiSplash.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Components
#include "uiSplash.h"
#include "afTimer.h"

// #############################################################################
namespace cat { namespace ui {

//______________________________________________________________________________
splash::splash(const unsigned int& tOut): _timeout(tOut)
{
	/*! Default ctor. \c tOut sets the time after that the splash window will
	 *	self-close; setting \c tOut to zero will keep the splash open until
	 *	a mouse left-click on its surface.
	 */
	
	// Prepares flag.
	unsigned int flag = SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_SHOWN;
	
	// Preset no SDL elements.
	_window = NULL;
	_renderer = NULL;
	_tImage = NULL;
	
	// Set up the window.
	_window = SDL_CreateWindow("PEAR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 480, flag);	
	if (!_window) throw std::runtime_error("SDL_CreateWindow failed");

	// SetUp a renderer for this window.
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer) throw std::runtime_error("SDL_CreateRenderer failed");	

	// Loads the splash image and creates a texture.
	SDL_Surface* _sImage = NULL;
	std::stringstream fileName;
	fileName << cat::ag::_pathMain << "/pear.spl"; 
	_sImage = SDL_LoadBMP(fileName.str().c_str());
	if (_SImage) {
		_tImage = SDL_CreateTextureFromSurface(_renderer, _sImage);
		SDL_FreeSurface(_sImage);
	}

	// Run the renderer.
	run(tOut);
}
 
//______________________________________________________________________________
splash::~splash()
{
	/*! Default dtor. */
	quit();
}


// *****************************************************************************
// **								Public Members							  **
// *****************************************************************************

//______________________________________________________________________________
void splash::run(const unsigned int& tOut)
{
	/*! Loop until the mouse click or a button is pressed */
	
	// Timing
	cat::af::timer tmr;
	tmr.start();  
	
	// Small event loop.
	while (true) {

		// Scan through the event queue for stop click.
		SDL_Event evn;
		if (SDL_PollEvent(&evn)) {
			if (evn.type == SDL_KEYDOWN) break;
			if (evn.type == SDL_MOUSEBUTTONDOWN) break;
		}

		// Here simply check for timeout.
		if (tOut > 0 && tmr.elapsed_ms() > tOut) break; 				
		
		// Refresh the picture.
		SDL_RenderClear(_renderer);
		SDL_RenderCopy(_renderer, _tImage, NULL, NULL);
		SDL_RenderPresent(_renderer);

		// Wait (so freeing resources).
		SDL_Delay(100);
	}

	// Self kill.
	delete this;
}

//______________________________________________________________________________
void splash::quit()
{
	/*! Close the splash. */
	SDL_DestroyTexture(_tImage);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

//______________________________________________________________________________
void splash::save()
{
	/*! Close the splash. */
	
	// Save the texture.
//	SDL_RWops* rw = SDL_RWFromFile("C:/Develop_Files/Projects/Pear/pear_Develop/pear.bs", "wb");
	

	//SDL_RWwrite(rw, _TImage, 1, 30);
	SDL_RWclose(rw);
}

// #############################################################################
}} // Close namespace
