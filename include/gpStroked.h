//------------------------------------------------------------------------------
// Primitives object layer for every GP which could be stroked				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpStroked.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef gpStroked_H
#define gpStroked_H

// Application
#include "gp.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							The pear::GP::Stroked						  **
// *****************************************************************************

/*! cat::GP::stroked is a GP layer providing all the functionalities typical
 *	of a filled primitive, like color, material, etc... All the properties
 *	add-up to those already present in the pear::GP base class.	
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 17 Sep 2024
*/

//______________________________________________________________________________
class stroked: public GP
{
	private:   
		
	protected:
   		
		// Style.
		bool _strkEnable;		//!< Stroke status.
		float _strkWidth;		//!< Line width in pixels.
		Uint16 _strkPattern;	//!< The dot-dash pattern.
		Uint32 _strkFactor;		//!< Pattern strectch factor.
		
		// Color.
		float _strkColor[4];	//!< Stroke color.
		
	public:
		
		// Special members.
		stroked();								//!< Default ctor.
		virtual ~stroked();						//!< Virtual dtor.
		
		// To be overloaded public members (already virtual from pear::GO).
		Uint64 type() const;					//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		void dump(const Uint64& = 0) const;		//!< Dumps GP data.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		
		//! Streams the GP data (already virtual from pear::GO).		
		bool stream(std::stringstream& o, const bool& read = false);
				
		// Public specific members.
		bool strkEnable() const;				//!< Returns stroke status.
		void strkEnable(const bool&);			//!< Sets stroke status.	
		float strkWidth() const;				//!< Returns stroke width.
		void strkWidth(const float&);			//!< Sets stroke width.
		Uint16 strkPattern() const;				//!< Returns stroke pattern bitmask.
		void strkPattern(const Uint16&);		//!< Sets stroke pattern.
		Uint32 strkFactor() const;				//!< Returns stroke pattern scaling.
		void strkFactor(const Uint32&);			//!< Sets stroke pattern scaling.
		const float* strkColor() const;			//!< Returns stroke color.
		void strkColor(const float*);			//!< Sets the stroke color.

		// Special flagging.
		bool flagStroked() const {return true;}	//!< Signal this is a filled one.

		// Drawing functions and vars are ONLY defined for the SERVER side!
		// ----------------------------------------------------------------
		#ifdef CAT_SERVER
			
			// Display and drawing.
			void glDraw();			//!< Draws the GP on the current GLcontext.
			void glDrawSel();		//!< Draws the GP in selection mode.
			void glDrawEnd();		//!< Close the GP drawing. Mandatory call!
			double glAlpha();		//!< Return transparency status.

			// UI interaction.
			virtual void uiBarLoad(ui::Bar&);	//!< Load a bar with the GP specific properties.
		
		#endif
};

// #############################################################################
}} // Close namespace



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::stroked& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif