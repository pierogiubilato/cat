//------------------------------------------------------------------------------
// Primitives object layer for every GP which could be stroked				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpStroked.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "gpStroked.h"

//##############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
stroked::stroked(): GP()
{
	/*! Ctor. Initialize the stroke properties to default. */
	
	// General.
	_strkEnable = true;	

	// Style.
	_strkWidth = 1;
	_strkPattern = 0;
	_strkFactor = 1;

	// Color.
	_strkColor[0] =	_strkColor[1] =	_strkColor[2] = 0.7f; _strkColor[3] = 1.0f;
}

//______________________________________________________________________________
stroked::~stroked()
{
	/*! Destructor	*/
} 

//______________________________________________________________________________
CO::oType stroked::type() const
{
	/*! Returns object type. This function MUST be overloaded to differentiate 
	 *	any derived class, and must also be addictive! 
	 */
   return CO::oType::gpStroked;
}

//______________________________________________________________________________
cat::coVer_t stroked::version() const
{
	/*! Returns object version. This function MUST be overloaded to differentiate 
	 *	any derived class! Version numbering is made in unit of hundreds for the
	 *	major and decimal for the subversions. So version 2.0 is 200.
	 */
   return 100;
}

//______________________________________________________________________________
std::string stroked::stem() const
{
	/*! Returns the object stem, i.e. the class stem. MUST be overloaded */
   return "stroked";
}

//______________________________________________________________________________
size_t stroked::size(const bool& dynamic) const 
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = GP::size(true);
	
	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}

//______________________________________________________________________________
void stroked::dump(const int& ind) const
{
 	/*! Dumps on the standard output the relevant gp::Stroke properties. */

	// Quick out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)

	// Padding string
	GP::dump(ind);
	std::string pad(ind, ' ');
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	
	// Set output formatting.
	std::cout << std::showpos << std::fixed << std::setprecision(CAT_DUMP_PREC_COLOR);
	
	// Stroke.
	std::cout << pad2 << "Stroke ["
		<< "Enable: " << CLW << _strkEnable << CD << ", "
		<< "Width: " << CLW << _strkWidth << CD << ", "
		<< "Pattern: " << CLW << _strkPattern << CD << ", "
		<< "Scaling: " << CLW << _strkFactor << CD << ", "
		<< "Color: <" << COL(LRED)  << _strkColor[0] << CD << ", "
						<< COL(LGREEN) << _strkColor[1]  << CD << ", "
						<< COL(LBLUE)  << _strkColor[2]  << CD << ", "
						<< COL(LWHITE) << _strkColor[3]  << CD << ">]\n";

	// Reset output formatting.
	std::cout << std::resetiosflags(std::ios::fixed | std::ios::showpos) 
			  << std::setprecision(CAT_DUMP_PREC_DEFAULT);	
	
	// Clear definitions.
	#undef CLW
	#undef CD
}

//______________________________________________________________________________
bool stroked::stream(std::stringstream& o, const bool& read)
{
	/*! Adds the current GP data member into the \c o stream (when \c Read = 
	 *	false) or load the GP from the \c o stream (when \c Read = true). 
	 */
	
	// Streams the parent.
	GP::stream(o, read);

	// Style.
	af::stream::rw(o, _strkEnable, read);
	af::stream::rw(o, _strkWidth, read);
	af::stream::rw(o, _strkPattern, read);
	af::stream::rw(o, _strkFactor, read);

	// Color.
	af::stream::rw(o, _strkColor[0], read);
	af::stream::rw(o, _strkColor[1], read);
	af::stream::rw(o, _strkColor[2], read);
	af::stream::rw(o, _strkColor[3], read);
	
	// Everything fine!
	return false;
}

// *****************************************************************************
// **						  Public specific members						  **
// *****************************************************************************

//______________________________________________________________________________
bool stroked::strkEnable() const
{
	/*! Returns stroke status. */
	return _strkEnable;
}

//______________________________________________________________________________
void stroked::strkEnable(const bool& enable)
{
	/*! Sets stroke status. */
	_strkEnable = enable;
}

//______________________________________________________________________________
float stroked::strkWidth() const
{
	/*! Returns stroke width. */
	return _strkWidth;
}

//______________________________________________________________________________
void stroked::strkWidth(const float& width)
{
	/*! Sets stroke width. */
	_strkWidth = width;
}

//______________________________________________________________________________
uint16_t stroked::strkPattern() const
{
	/*! Returns stroke pattern bitmask. */
	return _strkPattern;
}

//______________________________________________________________________________
void stroked::strkPattern(const uint16_t& pattern)
{
	/*! Sets stroke pattern. */
	_strkPattern = pattern;
}

//______________________________________________________________________________
uint32_t stroked::strkFactor() const
{
	/*! Returns stroke pattern scaling. */
	return _strkFactor;
}

//______________________________________________________________________________
void stroked::strkFactor(const uint32_t& factor)
{
	/*! Sets stroke pattern scaling. */
	_strkFactor = factor;
}

//______________________________________________________________________________
const float* stroked::strkColor() const
{
	/*! Returns stroke color (4 floats components RGBA). */
	return _strkColor;
}

//______________________________________________________________________________
void stroked::strkColor(const float* col)
{		
	/*! Sets the stroke color. It assumes a pointer to a 4 elements float 
	 *	representing the RGBA components of the color. */
	_strkColor[0] = col[0];
	_strkColor[1] = col[1];
	_strkColor[2] = col[2];
	_strkColor[3] = col[3];		
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
double stroked::glAlpha()
{
	/*! Returns if the gp has any kind of transparency in its constituent
	 *	elements (color, material, brush, ...). THe function is hierarchical:
	 *	it digs through all the parents chain to sum up the whole result.
	 */
	
	// Returns the convolution of me and parent.
	return  GP::glAlpha() * _strkColor[3];
}


//______________________________________________________________________________
void stroked::glDrawSel()
{
	/*! The glDrawSel draws a specific selection "skeleton" to highlight the 
	 *	selected object. Each GP should provide its own specialized glDrawSel 
	 *	overload, aas no basic one is implemented.
	 */

	// Get transformation chain applied.
	GP::glDrawSel();

	// Line style for selected objects is set into the base GP object. So every
	// object will uniform to that selection style.
}

//______________________________________________________________________________
void stroked::glDraw()
{
	/*! Sets all the drawing properties common for all GPs. The _drw* variables
	 *	are class member which could be used by childrens to influence their
	 *	own appearance, so they are stored until the next call to the function.
	 */
								  
	// Hierarchical drawing properties.
	GP::glDraw();
	
	// Stroke width.
//	glLineWidth(_strkWidth);
	
	// Stroke stippling.
	if (_strkPattern) {
//		glLineStipple(_strkFactor, _strkPattern);
//		glEnable(GL_LINE_STIPPLE);
	} else {
//		glDisable(GL_LINE_STIPPLE);
	}
}

//______________________________________________________________________________
void stroked::glDrawEnd()
{
	/*! Closes the GP drawing. */
//	GP::glDrawEnd();
}

// *****************************************************************************
// **								ui Functions							  **
// *****************************************************************************

//______________________________________________________________________________
//void stroked::uiBarLoad(ui::Bar& bar)
//{
//	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
//	 *	the GP. This member should be overloaded to change/add the properties
//	 *	shown on the properties bar by every GP.
//	 */
//	
//	// The parent first!
//	//GP::uiBarLoad(bar); 
//
//	//// Retrieve the TwBarr associated with the owner uiBar.
//	//TwBar* twBar = bar._TwBar;
//	//
//	//// General.
//	//bar.GroupAdd("Stroke");
//	//TwAddVarRW(twBar, "strkActive", TW_TYPE_BOOLCPP, &_strkEnable, "label='Active' group='Stroke'");	
//	//
//	//// Style.
//	//TwAddVarRW(twBar, "strkWidth", TW_TYPE_FLOAT, &_strkWidth, "label='Width' min=0.1 max=100 step=0.1 group='Stroke'");
//	//TwAddVarRW(twBar, "strkPattern", TW_TYPE_UINT16, &_strkPattern, "label='Pattern' group='Stroke'");
//	//TwAddVarRW(twBar, "strkScale", TW_TYPE_UINT32, &_strkFactor, "label='Scale' min=1 max=256 step=1 group='Stroke'");
//	//
//	//// Color.	
//	//TwAddVarRW(twBar, "strkColor", TW_TYPE_COLOR4F, _strkColor, "label='Color' colororder=rgba coloralpha=true group='Stroke'");
//}

// End of PEAR_SERVER if.
#endif

// #############################################################################
}} // Close Namespaces
