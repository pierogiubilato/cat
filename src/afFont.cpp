//------------------------------------------------------------------------------
// CAT Application Facility font class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afFont.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application components
#include "afFont.h"
#include "afFile.h"

// #############################################################################
namespace cat { namespace af {


// *****************************************************************************
// **								Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
font::font(const std::string& path)
{
	//! Standard ctor.
	/*! Initializes the library and check for all the available fonts on the
	 *	provided path.
	 */

	// Initializes the FreeType library.	
	FT_Error err = FT_Init_FreeType(&_FLib);
	if (err) throw std::runtime_error("FreeType initialization failed.");
	
	// No current face available.
	_fFace = 0;
	
	// Initialize the lists. To get a list of the successfully loaded families
	// and styles, call the fontList() member.
	init(path);

	// Show startup info if requested.
	if (cat::ag::_stupShowFont) fontList();
}

//______________________________________________________________________________
font::~font() 
{
	/* Releases all allocated resources. */

	// Releases all the faces.
	
	// Release the Font Library.
	FT_Done_FreeType(_fLib);
}


// *****************************************************************************
// **							Private Members								  **
// *****************************************************************************

//______________________________________________________________________________
void font::init(const std::string& path)
{
	/*!	List all the available fonts on the indicated path, and compile a list 
	 *	of available families and styles.
	 *
	 */	

	// Clear the font table
	_fTable.clear();

	// Create a file list.
	std::vector<std::string> file;	
	cat::af::_file->list(path, file);
	
	// Creates the available families/styles table.
	for (Uint32 i = 0; i < file.size(); i++) {
		
		// Retrieve the face associated to the file
		FT_Face newFace;
		FT_Error err = FT_New_Face(_FLib, file[i].c_str(), 0, &newFace);
		if (err == FT_Err_Unknown_File_Format) {
			std::cout << COL(CAT_COL_WARNING) << "Error loading: " 
					  << COL(DEFAULT) << file[i] << "\n";
			continue;
		} else if (err) {
			std::cout << COL(CAT_COL_WARNING) << "Corrupted file: " 
					  << COL(DEFAULT) << file[i] << "\n";
			continue;
		
		// Face is fine, load the family/style.
		} else {
			
			// Check if the family already exist.
			Uint32 j = 0;
			for (j; j < _fTable.size(); j++) {
				if (_fTable[j].name == newFace->family_name) break;
			}
			
			// If not, creates a new slot and add it.
			if (j == _fTable.size()) {
				_fTable.push_back(fFamily()); 
				_fTable[j].name = newFace->family_name; 
			}

			// Check if the style already exist.
			Uint32 k = 0;
			for (k; k < _fTable[j].style.size(); k++) {
				if (_fTable[j].style[k].name == newFace->style_name) break;
			}
			
			// If not, creates a new one and add it!
			if (k == _fTable[j].style.size()) {
				_fTable[j].style.push_back(fStyle());
				_fTable[j].style[k].name = newFace->style_name; 
				_fTable[j].style[k].file = file[i];				
				_fTable[j].style[k].face = newFace;
			}	
		}
	}

	// Check at least one font has been loaded.
	if (_fTable.size() < 1) {
		std::cout << COL(CAT_COL_WARNING) << "No fonts found." 
				  << COL(DEFAULT) << "\n";
	
	// Ok, at least one font is available!
	}
}


// *****************************************************************************
// **							Public Members								  **
// *****************************************************************************

//______________________________________________________________________________
void font::fontList()
{
	/*! Lists all available fonts. */
	
	std::cout << COL(LWHITE) << "Available fonts by family and style" << COL(DEFAULT) << "\n";

	// Families and styles
	for (size_t i = 0; i < _fTable.size(); i++) {
		std::cout << "   [" << COL(LWHITE) << _fTable[i].name << COL(DEFAULT) << "]\n";
		for (size_t j = 0; j < _fTable[i].style.size(); j++) {
			std::cout << "   [" << _fTable[i].style[j].name << "] ("
					  << _fTable[i].style[j].file << ") {"
					  << _fTable[i].style[j].face << "}\n";
		}
	}
}

//______________________________________________________________________________
std::vector<std::string> Font::familyList()	const
{
	/*! Lists all available font families. Returns a vector containing the names
	 *	of the families. These name can be used to select the font family when
	 *	calling the textFont(...) function.
	 */
	std::vector<std::string> fList;
	for (size_t i = 0; i < _fTable.size(); i++) fList.push_back(_fTable[i].name); 
	return fList;
}

//______________________________________________________________________________
Uint64 font::familyIdx(const std::string& family) const
{
	/*! Find and check for the family index. If the family is not fount, by
	 *	default returns the index of the first family (=0). */
	Uint64 fIdx = 0;
	for (fIdx = 0; fIdx < _fTable.size(); fIdx++) {
		if (_fTable[fIdx].name == family) return fIdx;
	}
	return 0;		
}

//______________________________________________________________________________
std::string font::familyName(const Uint64& idx) const
{
	/*! Returns the family name given the index. If the index is out of range,
	 *	by default returns the name of the first family, if any, or an empty
	 *	string otherwise. */
	if (idx < _fTable.size()) return _fTable[idx].name;
	if (_fTable.size() > 0) return _fTable[0].name;
	return std::string(""); 
}

//______________________________________________________________________________
std::vector<std::string> font::styleList(const std::string& family) const
{
	/*! Lists all the available styles for a given family. Returns a vector 
	 *	containing the names of the styles. These names can be used to select 
	 *	the font family style when calling the textFont(...) function.
	 */
	std::vector<std::string> sList;
	
	// Find and check for the family.
	Uint64 fIdx = familyIdx(family);
	
	// Fill the style vector and return.
	for (size_t i = 0; i < _fTable[fIdx].style.size() ; i++) {
		sList.push_back(_fTable[fIdx].style[i].name); 
	}
	return sList;
}

//______________________________________________________________________________
Uint64 font::styleIdx(const std::string& family, const std::string& style) const
{
	/*! Find and check for the style index. If the index is not fount, by
	 *	default returns the index of the first style (=0). */
	
	// Retrieves the family index.
	Uint64 fIdx = familyIdx(family);
	
	// Retrieve the style index.
	Uint64 sIdx = 0;
	for (sIdx = 0; sIdx < _fTable.size(); sIdx++) {
		if (_fTable[sIdx].name == style) return sIdx;
	}
	return 0;		
}

//______________________________________________________________________________
std::string font::styleName(const std::string& family, const Uint64& sIdx) const
{
	/*! Returns the style name given a family name and a style index. If family
	 *	does not exist or the the index is out of range, by default returns an 
	 *	empty string.
	 */
	
	// Retrieves the family index.
	Uint64 fIdx = familyIdx(family);
	if (fIdx >= _fTable.size()) return std::string("");		

	// Checks and returns.
	if (sIdx < _fTable[fIdx].style.size()) return _fTable[fIdx].style[sIdx].name;
	if (_fTable.size() > 0) return _fTable[0].style[0].name;
	return std::string(""); 
}

//______________________________________________________________________________
void font::textParse(std::string& text, std::vector<Uint32>& color, const Uint32& defaultColor)
{
	/*!	Get the string \c text and extract from it the control characters and
	 *	corresponding arguments. The original string will hence be modified! 
	 *	\c color will be loaded with an array of RGBA codes, one for each
	 *	of the resulting string characters, reporting color and transparency
	 *	for each char. The \c defaultColor defines the default color being 
	 *	assigned to the text characters.
	 *
	 *	Managed control sequences:
	 *
	 *	"\n" -	Mimic the behaviour of the standard "\n" sequence in that cases
	 *			it is. not directly replaced by the parser (runtime setting).	 
	 *
	 *	"//c" - Set color/transparency of the following text. The "//c"	control
	 *			sequence interprets the next 10 char as an hex 4 bytes number 
	 *			describing the RGBA channels to apply to the following text.
	 *			Example: "//c0xffff00ff" tells the parser to set the color to 
	 *			bright yellow (R = ff, G = ff, B = 00) and the alpha channel to 
	 *			no transparency (A = ff).
	 */

	// Set the default RGBA code. Note that a color will be assigned even to
	// DEFAULT control characters ("\n", ...).
	color.clear();
	Uint32 RGBA = defaultColor;
	std::string sequence = "";
	for (Uint64 i = 0; i < text.size(); i++) {

		// Standard character, assign color. The alpha channel is anyway
		// modulated by the default color alpha	channel initial value.
		color.push_back(RGBA);

		// Extracts DEFAULT CONTROL sequence.
		// ----------------------------------
		sequence = text.substr(i, 2); 
		if (sequence.size() == 2 && sequence[0] == 92) {
		//std::cout << sequence << " ";

			// New line sequence [n = 110].
			if (sequence[1] == 110) {
				
				// Get rid of 1 char from the string
				//text.erase(i, 1);
				text.replace(i, 2, "\n");

				// Skip doing anything else.	
				continue;
			}
		}

		// Extracts SPECIAL CONTROL sequence.
		// ----------------------------------
		sequence = text.substr(i, 3); 

		// Color sequence.
		if (sequence == "//c") {

			std::cout << "!!!!!!" << "\n";
			
			// Update the RGBA code.
			std::string strHex = text.substr(i + 3, 10);
			cat::af::stream::value(RGBA, strHex, std::hex);   
			RGBA = (RGBA & 0xffffff00) + (((RGBA & 0xff) * (defaultColor & 0xff)) >> 8);
			//std::cout << "Extracted: [" << sequence	<<" ] and code [" << strHex << "] of value (" << RGBA << ")\n";
			
			// Get rid of 3+10 chars from the string
			text.erase(i, 13);
			i--;

			// Kills even the color.
			color.pop_back(); 
	
			// Skip doing anything else.	
			continue;
		}
	
		// Other sequences will be implemented...
		// --------------------------------------
	}
		
	// Debug.
	//std::cout << "Ending string: [" << text << "]\n";
	//for (Uint64 i = 0; i < text.size(); i++) {
	//	std::cout << "# " << i << ", " << text[i] << ", " << std::hex << color[i] << std::hex << "\n";
	//}
	//std::cout << text.size() << ", " << color.size() << "\n";
}	   

//______________________________________________________________________________
void font::textFont(const std::string& family, const std::string& style,
					const Uint32& size, const float& angle)
{
	/*! Sets the font used to draw the text. \c family and \c style must 
	 *	correspond to an existent combination of font family and style. If the
	 *	combination is not found, the font facility will set in order a style
	 *	equal to Regular and, if even the family is unknown, the first family
	 *	available.
	 *	\c size is the size of the font in pixel, and \c angle the rotation
	 *	in radians respect the baseline.
	 */ 

	// Check that at least one font is available.
	if (!_fTable.size()) return;

	// Chose the family.
	Uint32 f = 0;
	for (f; f < _fTable.size(); f++) {
		if (_fTable[f].name == family) break;
	}
	
	// If not found, by default set the first available.			
	if (f == _fTable.size()) f = 0;

	// Chose the style.
	Uint32 s = 0;
	for (s; s < _fTable[f].style.size(); s++) {
		if (_fTable[f].style[s].name == style) break;
	}
	
	// If not found, by default set the first available.			
	if (s == _fTable[f].style.size()) s = 0;

	// Set the current face.
	_fFace = _fTable[f].style[s].face;

	// Check for size standard in case.
	Uint32 _size = size;
	if (size == 0) _size = CAT_FONT_DEF_SIZE_PX; 
	
	// Set a size (pixel)
	FT_Error err = FT_Set_Pixel_Sizes(_fFace, 0, _size);

	// Derives the line height in pixel unit.
	_fLineHeight = _size;

	// Set transformation matrix.
	_fMatrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
	_fMatrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
	_fMatrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
	_fMatrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);
}


//______________________________________________________________________________
void font::textDraw(const std::string& text, const std::vector<Uint32>& color, 
					Uint32& pxmWidth, Uint32& pxmHeight, GLubyte*& pxmData)
{
 	/*! Creates a pixMap containing the text \c text rendered with the currently 
	 *	loaded face. The pixmap will be loaded into the \c pxmData pointer with
	 *	the RGBA format. The starting color for every character of the text is
	 *	passed in the \c color vector. Note that pre-allocated pxmData will be
	 *	erased. The dimensions of the generated pixmap will be loaded into the 
	 *	\c pxmWidth	and \c pxmHeight variables. The size of the resulting pixmap
	 *	is always 8 byte aligned in the pxmWidth dimension.
	 *	\c text is the array containing the characters to be displayed, and 
	 *	\c count the total number of characters.
	 */
	
	// Check if a face is available.
	if (!_fFace) return;

	// Pivots.
	FT_Error err;
	FT_GlyphSlot slot;

	// Char drawing position.
	FT_Vector charPen = {0, 0};		
	FT_Vector linePos = {0, 0};
	int lineIdx = 0;

	// Allocates a per-character map tables.
	Uint64 count = text.size();
	unsigned char** charMap = new unsigned char*[count];
	FT_Vector* charPos = new FT_Vector[count];
	FT_Vector* charDim = new FT_Vector[count];
	Uint32 charSize = 0;
	
	// Drawing boundaries.
	FT_Vector pxmMin = charPen;		
	FT_Vector pxmMax = charPen;
	
	// Loop over all the characters.  
	for (Uint64 i = 0; i < count; i++) {
    
		// Set transformation.
		FT_Set_Transform(_fFace, &_fMatrix, &charPen);
		
		// Load glyph image into the slot (erase previous one).
		err = FT_Load_Char(_fFace, text[i], FT_LOAD_RENDER);
		if (err) continue;
		slot = _fFace->glyph;
		
		// Stores the generated glyph bitmap (1 byte/pixel).
		charSize = slot->bitmap.width * slot->bitmap.rows;
		charMap[i] = new unsigned char[charSize];
		for (Uint32 p = 0; p < charSize; p++) charMap[i][p] = slot->bitmap.buffer[p];
		
		// Stores position and dimension of the glyph bitmap.
		charPos[i].x = + slot->bitmap_left;
		charPos[i].y = - slot->bitmap_top;
		charDim[i].x = slot->bitmap.width;
		charDim[i].y = slot->bitmap.rows;

		// Updates drawing boundaries.
		if (text[i] > 31) {
			if (charPos[i].x < pxmMin.x) pxmMin.x = charPos[i].x;
			if (charPos[i].y < pxmMin.y) pxmMin.y = charPos[i].y;
			if (charPos[i].x + charDim[i].x > pxmMax.x) pxmMax.x = charPos[i].x + charDim[i].x;
			if (charPos[i].y + charDim[i].y > pxmMax.y) pxmMax.y = charPos[i].y + charDim[i].y;
		}

		// Advance the charPen (next position) accordingly to what
		// it finds into the text string (normal or escape char).
		switch (text[i]) {
			
			// Line feed.
			case 10: // Get line starting position.
					lineIdx++;
					linePos.x = 0;
					linePos.y = -lineIdx * _fLineHeight;
					
					// Here: Freetype stores matrix values in 16.16 fixed format, and internal
					// font typesetting coordinates in 1/64 of unit. So to get the correct
					// conversion factor from rotation calculation we need to divide by 65536
					// and multiply by 64 the result, equal to a 10 bit bitshift to the right!
					charPen.x = (_fMatrix.xx * linePos.x + _fMatrix.xy * linePos.y) >> 10;
					charPen.y = (_fMatrix.yx * linePos.x + _fMatrix.yy * linePos.y) >> 10;
					break;
			
			// Normal text.				
			default:
				
				// Standard left to right advance.
				charPen.x += slot->advance.x;
				charPen.y += slot->advance.y;
		} // Character code SWITCH
	} // Characters LOOP.
		
	// Calculates pix map dimensions (8 bytes over 4 aligned).
	pxmWidth = pxmMax.x - pxmMin.x + 1;
	pxmWidth = pxmWidth + ((pxmWidth % 2) ? 1 : 0);
	pxmHeight = pxmMax.y - pxmMin.y + 1;
	
	// Allocates the main pixMap.
	if (pxmData) delete[] pxmData;
	pxmData = new GLubyte[pxmHeight * pxmWidth * 4];
	
	// Clean the main map.
	for (Uint32 i = 0; i < pxmWidth * pxmHeight * 4; i++) pxmData[i] = 0;

	// Stiches the single character maps into the main map. The Y axis is
	// mirrored to match the OpenGL standard which orients pix maps in the
	// Argand-Gauss way.
	Uint32 start = 0;
	Uint32 pxPos = 0;
	unsigned char alpha = 0;
  	for (Uint64 i = 0; i < count; i++) {
		
		// Skip control chars.
		if (text[i] < 32) continue;

		// Get char color.
		GLubyte colR = color[i] >> 24;
		GLubyte colG = color[i] >> 16;
		GLubyte colB = color[i] >> 8;
		GLubyte colA = color[i];

		// Stich every pixel different from 0.
		start = (pxmWidth * (pxmMax.y - charPos[i].y) + (charPos[i].x - pxmMin.x));
		for (int y = 0; y < charDim[i].y; y++)	{
			for (int x = 0; x < charDim[i].x; x++)	{
				alpha = charMap[i][y * charDim[i].x + x];
				if (alpha) {
					pxPos =  4 * (start - y * pxmWidth + x);
					pxmData[pxPos + 0] = colR;	// RGB.
					pxmData[pxPos + 1] = colG;	// Green.
					pxmData[pxPos + 2] = colB;	// Blue.
					pxmData[pxPos + 3] = (alpha * colA) >> 8; // Alpha.
				}
			}
		}
	}
	
	// Release the single character maps.
	for (Uint32 i = 0; i < count; i++) delete[] charMap[i];
	delete[] charMap;
	delete[] charPos;
	delete[] charDim;
}


// #############################################################################
}} // Close namespaces
