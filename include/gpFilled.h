//------------------------------------------------------------------------------
// Primitives object layer for every GP which could be filled				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpFilled.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef gpFilled_H
#define gpFilled_H

// Application
#include "gpStroked.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							The cat::GP::filled						  **
// *****************************************************************************

/*! cat::GP::filled is a GP layer providing all the functionalities typical
 *	of a filled primitive, like color, material, etc... All the properties
 *	add-up to those already present in the pear::GP base class.	
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 17 Sep 2024
*/

//______________________________________________________________________________
class filled: public stroked
{
	private:   
		
	protected:
   
		// Style.
		bool _fillEnable;			//!< Fill enabled.
		GPHnd _fillMaterial;		//!< Material filling enabled.

		// Colors.
		float _fillColor[4];		//!< Fill color.
				
	public:
		
		// Special members.
		filled();								//!< Default ctor.
		virtual ~filled();						//!< Virtual dtor.
		
		// To be overloaded public members (already virtual from pear::CO).
		CO::oType type() const;					//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		void dump(const Uint64& = 0) const;		//!< Dumps GP data.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		bool stream(std::stringstream& o, const bool& read = false);
				
		// Public specific members.
		bool fillEnable() const;				//!< Returns fill status.
		void fillEnable(const bool&);			//!< Sets fill status.	
		GPHnd fillMaterial() const;				//!< Returns filling material.
		void fillMaterial(const GPHnd&);		//!< Sets filling material.
		const float* fillColor() const;			//!< Returns fill color.
		void fillColor(const float*);			//!< Sets the fill color.
		
		// Drawing functions and vars are ONLY defined for the SERVER side!
		// ----------------------------------------------------------------
		#ifdef CAT_SERVER
			
			// Display and drawing.
			void glDraw();				//!< Draws the GP on the current GLcontext.
			void glDrawSel();			//!< Draws the GP in selection mode.
			void glDrawEnd();			//!< Close the GP drawing. Mandatory call!
			double glAlpha();			//!< Return transparency status.

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
inline std::ostream& operator << (std::ostream& o, const cat::gp::filled& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
