//------------------------------------------------------------------------------
// Primitives object layer for every GP which could handle text				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpFonted.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef gpFonted_H
#define gpFonted_H

// Application
#include "gpStroked.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							The cat::GP::fonted						  **
// *****************************************************************************

/*! cat::GP::fonted is a GP layer providing all the functionalities typical
 *	of a primitive which uses fonts, such labels, text, ... All the properties
 *	add-up to those already present in the cat::GP base class.	
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 17 Sep 2024
*/

//______________________________________________________________________________
class fonted: public stroked
{
	private:   
		
	protected:
   
		// Font.
		std::string _fontFamily;		//!< Font family (calibri, arial, ...).
		std::string _fontStyle;			//!< Font style (normal, italic, ...).
		Uint32 _fontSize;				//!< Font size in points (1/64 of inch).
						
	public:
		
		// Special members.
		fonted();								//!< Default ctor.
		virtual ~fonted();						//!< Virtual dtor.
		
		// To be overloaded public members (already virtual from pear::GO).
		Uint64 type() const;					//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		void dump(const Uint64& = 0) const;		//!< Dumps GP data.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		
		//! Streams the GP data (already virtual from pear::GO).		
		bool stream(std::stringstream& o, const bool& read = false);
				
		// Public specific members.
		std::string fontFamily() const;			//!< Returns the font family.
		void fontFamily(const std::string&);	//!< Sets the font family.
		std::string fontStyle() const;			//!< Returns the font style.
		void fontStyle(const std::string&);		//!< Sets the font style.
		Uint32 fontSize() const;				//!< Returns the font size.
		void fontSize(const Uint32&);			//!< Sets the font size.

		// Special flagging.
		bool flagFonted() const {return true;}	//!< Signal this is a fonted one.

		// Drawing functions and vars are ONLY defined for the SERVER side!
		// ----------------------------------------------------------------
		#ifdef CAT_SERVER
			
			// Display and drawing.
			void glDraw();				//!< Draws the GP on the current GLcontext.
			void glDrawSel();			//!< Draws the GP in selection mode.
			void glDrawEnd();			//!< Close the GP drawing. Mandatory call!
			double glAlpha();			//!< Return transparency status.

			// UI interaction.
			//virtual void uiBarLoad(ui::Bar&);	//!< Load a bar with the GP specific properties.
			//TwType uiTwEnumFtFamily() const;	//!< Creates a TwEnum for the Font Families.
			//TwType uiTwEnumFtStyle() const;		//!< Creates a TwEnum for the Family's Font Styles.
			//static void TW_CALL uiFamilySet(const void *value, void *clientData);
			//static void TW_CALL uiFamilyGet(void *value, void *clientData);
			//static void TW_CALL uiStyleSet(const void *value, void *clientData);
			//static void TW_CALL uiStyleGet(void *value, void *clientData);
		#endif
};

// #############################################################################
}} // Close namespace



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::fonted& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
