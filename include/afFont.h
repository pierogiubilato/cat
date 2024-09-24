//------------------------------------------------------------------------------
// CAT Font facility class													  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afFont.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined afFont_H
#define afFont_H

// STL.
#include <vector>

// OpenGL data types are used for pxMap management.
// #include "glad.h" // <-- Used only for 'GLByte', which is an 'uint8_t'

// FreeType	(font management C library).
extern "C" {
	#include <ft2build.h>
	#include FT_FREETYPE_H
}

// Application components.
//#include "acMain.h"


// #############################################################################
namespace cat { namespace af {

//! CAT font
/*! cat::af::font provides fonts management. It uses the freetype library to 
 *	build OpenGL textures embedded font sets as well as single textures for one
 *	time use of types.
 *	Library constructor wants for a path where to search for recognized font
 *	files (*.ttf, *.ott, ...): provide a path containing all the fonts you want 
 *	to be available.
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 24 Sep 2024
 */
//______________________________________________________________________________
class font //: public AF
{
	private:
		
		// Font style structure.
		struct fStyle{
			std::string name; 
			std::string file; 
			FT_Face face;
		};
		
		// Font family  structure.
		struct fFamily{
			std::string name; 
			std::vector<fStyle> style;
		};
		
		// Available fonts (families and styles) table.
		std::vector<fFamily> _fTable;	// Table of available families and styles.

		// FreeType elements.
		FT_Library	_fLib;			// The freetype library instance in use.	
		FT_Face		_fFace;			// The current face in in use.	
		FT_Matrix	_fMatrix;		// The current transformation matrix.
		
		// Paragraph elements.
		uint32_t	_fLineHeight;	// Line height calculated from the font size.

		// Init library.
		void init(const std::string& path);
		
	protected:
	
	public:

		// Special members
		font(const std::string& path);	//!< Mandatory ctor.	
		~font();						//!< Default dtor.

		// Support functions.			  
		void fontList(); //!< Printout a list of all available family/style combinations.
		std::vector<std::string> familyList() const;	//!< Returns all available font families.
		uint64_t familyIdx(const std::string&) const;		//!< Returns the family Idx by Name.
		std::string familyName(const uint64_t&) const;	//!< Returns the family Name by Idx.
		std::vector<std::string> styleList(const std::string&) const;	//!< Returns all available font family styles.
		uint64_t styleIdx(const std::string&, const std::string&) const;	//!< Returns the style Idx.
		std::string styleName(const std::string&, const uint64_t&) const;	//!< Returns the style Name by Idx.

		//!	Checks, parses and removes a text string from the control characters.
		void textParse(std::string& text, std::vector<uint32_t>& color, 
					   const uint32_t& defaultColor);
	   
		//! Sets the text font.
		void textFont(const std::string& family, const std::string& style,
					  const uint32_t& size, const float& angle);
		
		//! Draws the text on a pixmap.
		void textDraw(const std::string& text, const std::vector<uint32_t>& color, 
					  uint32_t& pxmWidth, uint32_t& pxmHeight, uint8_t*& pxmData);
		
		// Debug.
		//void Test();
		//void faceLoad(const char* family = "", const char* style ="");
		//void faceSetPoint(const uint32_t& size, const float& angle);
		//void faceSetPixel(const uint32_t& size, const float& angle);
};


// #############################################################################
}} // Close namespaces

// Overloading check
#endif