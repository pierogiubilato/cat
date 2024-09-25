//------------------------------------------------------------------------------
// CAT User Interface Pad OpenGL support class		 						  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiPadGL.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined uiPadGL_H
#define uiPadGL_H

// Components
//#include <ui.h>

// #############################################################################
namespace cat { namespace ui {

// Forward declaration of a pad class
class pad;

//! Basic pad GL
/*! cat::ui::padGL provides some very basic primitives to help using the 
 *	OpenGL current viewport as a classic raster bitmap 2D screen.
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 24 Sep 2024
 */

class padGL //: public UI 
{
	private:
		
		// Status and properties
		static pad* _owner;				// The pad using the GUI.
			
	protected:
	
	public:

		// Special members
		padGL(pad* owner); 
		~padGL();

		//!< Setup the gl context for raster-style operations.
		void glSet();	
		
		//!< Reset the gl context for raster-style operations.
		void glReset();	
		
		//! Draws a line.
		void glLine(const int& x1, const int& y1, const int& x2, const int& y2, 
					const int& c1, const int& c2, const bool& alias = false);
		
		//! Draws a circle.		
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif