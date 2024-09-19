//------------------------------------------------------------------------------
// Primitives object layer for every GP which could be filled				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpFonted.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "gpFonted.h"

// Include Main (to access the font facility).
#ifdef CAT_SERVER
	#include "../include/acMain.h"
	#include "../include/afFont.h"	
#endif

//##############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
fonted::fonted(): stroked()
{
	/*! Ctor. Initialize the font properties to default. */
	
	// Font.
	_fontFamily = "";		// Uses Font Facility default.
	_fontStyle = "";		// Uses Font Facility default.
	_fontSize = 0;			// Uses Font Facility default.
}

//______________________________________________________________________________
fonted::~fonted()
{
	/*! Destructor	*/
} 

//______________________________________________________________________________
Uint64 fonted::type() const
{
	/*! Returns object type. This function MUST be overloaded to differentiate 
	 *	any derived class! 
	 */
   return stroked::type() + ktype::fonted;
}

//______________________________________________________________________________
Uint64 fonted::version() const
{
	/*! Returns object version. This function MUST be overloaded to differentiate 
	 *	any derived class! Version numbering is made in unit of hundreds for the
	 *	major and decimal for the subversions. So version 2.0 is 200.
	 */
   return 100;
}

//______________________________________________________________________________
std::string fonted::stem() const
{
	/*! Returns the object stem, i.e. the class stem. MUST be overloaded */
   return "fonted";
}

//______________________________________________________________________________
size_t fonted::size(const bool& dynamic) const 
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = stroked::size(true);
	
	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}

//______________________________________________________________________________
void fonted::dump(const Uint64& ind) const
{
 	/*! Dumps on the standard output the relevant gp::Fonted properties. */

	// Quich out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)

	// Padding string
	stroked::dump(ind);
	std::string pad(ind, ' ');
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	
	// Set output formatting.
	std::cout << std::showpos << std::fixed << std::setprecision(CAT_DUMP_PREC_COLOR);
	
	// Stroke.
	std::cout << pad2 << "Font ["
		<< "Family: " << CLW << _fontFamily << CD << ", "	
		<< "Style: " << CLW << _fontStyle << CD << ", "	
		<< "Size: " << CLW << _fontSize << CD << "]\n";

	// Reset output formatting.
	std::cout << std::resetiosflags(std::ios::fixed | std::ios::showpos) 
			  << std::setprecision(CAT_DUMP_PREC_DEFAULT);	
	
	// Clear definitions.
	#undef CLW
	#undef CD
}

//______________________________________________________________________________
bool fonted::stream(std::stringstream& o, const bool& read)
{
	/*! Adds the current GP data member into the \c o stream (when \c Read = 
	 *	false) or load the GP from the \c o stream (when \c Read = true). 
	 */
	
	// Streams the parent.
	stroked::stream(o, read);
		
	// Font.
	af::stream::RW(o, _fontFamily, read);
	af::stream::RW(o, _fontStyle, read);
	af::stream::RW(o, _fontSize, read);

	// Everything fine!
	return false;
}



// *****************************************************************************
// **						  Public specific members						  **
// *****************************************************************************

//______________________________________________________________________________
std::string fonted::fontFamily() const
{
	/*! Returns the font family. */
	return _fontFamily;
}

//______________________________________________________________________________
void fonted::fontFamily(const std::string& family)
{
	/*! Sets the font family. */
	_fontFamily = family;
}

//______________________________________________________________________________
std::string fonted::fontStyle() const
{
	/*! Returns the font style. */
	return _fontStyle;
}

//______________________________________________________________________________
void fonted::fontStyle(const std::string& style)
{
	/*! Sets the font style. */
	_fontStyle = style;
}

//______________________________________________________________________________
Uint32 fonted::fontSize() const
{
	/*! Returns the font size. */
	return _fontSize;
}

//______________________________________________________________________________
void fonted::fontSize(const Uint32& size)
{
	/*! Sets the font size. */
	_fontSize = size;	
}


// *****************************************************************************
// **							     SERVER SIDE							  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER


// *****************************************************************************
// **							     gl Functions							  **
// *****************************************************************************

//______________________________________________________________________________
double fonted::glAlpha()
{
	// A font has always total transparent areas..
	return  0;
}

//______________________________________________________________________________
void fonted::glDrawSel()
{
	/*! The glDrawSel draws a specific selection "skeleton" to highlight the 
	 *	selected object. Each GP should provide its own specialized glDrawSel 
	 *	overload, aas no basic one is implemented.
	 */

	// Get transformation chain applied.
	stroked::glDrawSel();
}

//______________________________________________________________________________
void fonted::glDraw()
{
	/*! Sets all the drawing properties common for all GPs. The _drw* variables
	 *	are class member which could be used by childrens to influence their
	 *	own appearance, so they are stored until the next call to the function.
	 */
								  
	// Common drawing properties are handled by the parent GP.
	stroked::glDraw();
}

//______________________________________________________________________________
void fonted::glDrawEnd()
{
	/*! Closes the GP drawing. */
	stroked::glDrawEnd();
}


// *****************************************************************************
// **							  ui Functions								  **
// *****************************************************************************

//______________________________________________________________________________
void TW_CALL fonted::uiFamilySet(const void *value, void *clientData)
{ 
    /*! Set the _Family value in a TWBar compatible way. */
//	static_cast<fonted*>(clientData)->_fontFamily = af::_Font->familyName(*(int*)value);

	// Updates the family styles selector in the target instance (if any).
//	static_cast<fonted*>(clientData)->uiTwEnumFtStyle(); 
}
			
//______________________________________________________________________________
void TW_CALL fonted::uiFamilyGet(void *value, void *clientData)
{ 
    /*! Put the _Text value in a TWBar compatible way. */
//	*(int*)value = static_cast<int>(af::_font->familyIdx(
//				   static_cast<Fonted*>(clientData)->_fontFamily)); 
}

//______________________________________________________________________________
void TW_CALL fonted::uiStyleSet(const void *value, void *clientData)
{ 
    /*! Set the _Text value in a TWBar compatible way. */
//	std::cout << af::_font->styleName(static_cast<Fonted*>(clientData)->_fontFamily, *(int*)value) << "\n";  
//	static_cast<Fonted*>(clientData)->_fontStyle = 
//			af::_Font->styleName(static_cast<Fonted*>(clientData)->_fontFamily, 
//								 *(int*)value);
}
			
//______________________________________________________________________________
void TW_CALL fonted::uiStyleGet(void *value, void *clientData)
{ 
    /*! Put the _Text value in a TWBar compatible way. */
//	*(int*)value = static_cast<int>(af::_Font->styleIdx(
//				   static_cast<Fonted*>(clientData)->_fontFamily,
//				   static_cast<Fonted*>(clientData)->_fontStyle)); 
}

//______________________________________________________________________________
TwType fonted::uiTwEnumFtFamily() const
{ 
    /*! Creates a TwType containing all the available font families. */

	// Get font families.
//	std::vector<std::string> list = pear::af::_font->familyList();
//	TwEnumVal* twEnum = new TwEnumVal[list.size()];
//	for (int i = 0; i < list.size(); i++) {
//		twEnum[i].Value = i;
//		twEnum[i].Label = list[i].c_str();
//	}
	
	// Build the TwType structure and free the pivot struct.
//	const TwType type = TwDefineEnum("Family", twEnum, static_cast<unsigned int>(list.size()));	
//	delete[] twEnum;
//	return type;
}

//______________________________________________________________________________
TwType fonted::uiTwEnumFtStyle() const
{ 
    /*! Creates a TwType containing all the available font styles for the 
	 *	currently selected font family. */

	// Get style list.
//	std::vector<std::string> list = pear::af::_Font->styleList(_fontFamily);
//	TwEnumVal* twEnum = new TwEnumVal[list.size()];
//	for (int i = 0; i < list.size(); i++) {
//		twEnum[i].Value = i;
//		twEnum[i].Label = list[i].c_str();
//	}
	
	// Build the TwType structure and free the pivot struct.
//	const TwType type = TwDefineEnum("Style", twEnum, static_cast<unsigned int>(list.size()));	
//	delete[] twEnum;
//	return type;
}

//______________________________________________________________________________
void fonted::uiBarLoad(ui::Bar& bar)
{
	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
	 *	the GP. This member should be overloaded to change/add the properties
	 *	shown on the properties bar by every GP.
	 */
	
	// The parent first!
//	Stroked::uiBarLoad(bar); 

	// Retrieve the TwBarr associated with the owner uiBar.
//	TwBar* twBar = bar._TwBar;
	
	// Add the font properties to the bar.
//	bar.GroupAdd("Font");
//	TwAddVarCB(twBar, "fontFamily", uiTwEnumFtFamily(), Fonted::uiFamilySet, Fonted::uiFamilyGet, this, "label='Family' group='Font'");	
//	TwAddVarCB(twBar, "fontStyle", uiTwEnumFtStyle(), Fonted::uiStyleSet, Fonted::uiStyleGet, this, "label='Style' group='Font'");
//	TwAddVarRW(twBar, "fontSize", TW_TYPE_UINT32, &_fontSize, "label='Size' group='Font' min=1.0 max=240.0 step=1");
}

// End of PEAR_SERVER if.
#endif

// #############################################################################
}} // Close Namespaces
