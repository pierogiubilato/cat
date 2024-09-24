//------------------------------------------------------------------------------
// Primitives object layer for every GP which could be filled				  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpFilled.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "gpFilled.h"

//##############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
filled::filled(): stroked()
{
	/*! Ctor. Initialize the filling properties to default. */
	
	// Style.
	_fillEnable = true;
	_fillMaterial = 0;
	//_mtrlEnable = false;
		
	// Colors.
	_fillColor[0] =	_fillColor[1] =	_fillColor[2] = 0.5f;
	_fillColor[3] = 1.0f;
}

//______________________________________________________________________________
filled::~filled()
{
	/*! Destructor	*/
} 

//______________________________________________________________________________
CO::oType filled::type() const
{
	/*! Returns object type. This function MUST be overloaded to differentiate 
	 *	any derived class, and must also be addictive! 
	 */
   return CO::oType::gpFilled;
}

//______________________________________________________________________________
Uint64 filled::version() const
{
	/*! Returns object version. This function MUST be overloaded to differentiate 
	 *	any derived class! Version numbering is made in unit of hundreds for the
	 *	major and decimal for the subversions. So version 2.0 is 200.
	 */
   return 100;
}

//______________________________________________________________________________
std::string filled::stem() const
{
	/*! Returns the object stem, i.e. the class stem. MUST be overloaded */
   return "filled";
}

//______________________________________________________________________________
size_t filled::size(const bool& dynamic) const 
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
void filled::dump(const Uint64& ind) const
{
 	/*! Dumps on the standard output the relevant GP properties. */

	// Quich out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)
	#define CLR COL(LRED)
	#define CLG COL(LGREEN)
	#define CLB COL(LBLUE)

	// Padding string
	stroked::dump(ind);
	std::string pad(ind, ' ');
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');

	// Set output formatting.
	std::cout << std::showpos << std::fixed << std::setprecision(CAT_DUMP_PREC_COLOR);
	
	// Fill.
	std::cout << pad2 << "Fill ["
		<< "Enable: " << CLW << _fillEnable << CD << ", "
		<< "Color: <" << CLR << _fillColor[0] << CD << ", "
					  << CLG << _fillColor[1] << CD << ", "
					  << CLB << _fillColor[2] << CD << ", "
					  << CLW << _fillColor[3] << CD << ">, "
		<< "Material: " << CLW << _fillMaterial << CD << "]\n";
	
	// Reset output formatting.
	std::cout << std::resetiosflags(std::ios::fixed | std::ios::showpos) 
			  << std::setprecision(CAT_DUMP_PREC_DEFAULT);	
	
	// Clear definitions.
	#undef CLW
	#undef CLR
	#undef CLG
	#undef CLB
	#undef CD	
}

//______________________________________________________________________________
bool filled::stream(std::stringstream& o, const bool& read)
{
	/*! Adds the current GP data member into the \c o stream (when \c Read = 
	 *	false) or load the GP from the \c o stream (when \c Read = true). 
	 */
	
	// Streams the parent.
	stroked::stream(o, read);
		
	// Style.
	af::stream::RW(o, _fillEnable, read);
	af::stream::RW(o, _fillMaterial, read);
	
	// Colors.
	af::stream::RW(o, _fillColor[0], read);
	af::stream::RW(o, _fillColor[1], read);
	af::stream::RW(o, _fillColor[2], read);
	af::stream::RW(o, _fillColor[3], read);
	
	// Everything fine!
	return false;
}



// *****************************************************************************
// **						  Public specific members						  **
// *****************************************************************************

//______________________________________________________________________________
bool filled::fillEnable() const
{
	/*! Returns fill status. */
	return _fillEnable;
}

//______________________________________________________________________________
void filled::fillEnable(const bool& enable)
{		
	/*! Sets fill status. */
	_fillEnable = enable;
}

//______________________________________________________________________________
GPHnd filled::fillMaterial() const
{
	/*! Returns filling material. */
	return _fillEnable;
}

//______________________________________________________________________________
void filled::fillMaterial(const GPHnd& gpHnd)
{
	/*! Sets material status. */
	_fillMaterial = gpHnd;
}

//______________________________________________________________________________
const float* filled::fillColor() const
{
	/*! Returns the fill color: pointer to a 4 elements float array (RGBA). */
	return _fillColor;
}

//______________________________________________________________________________
void filled::fillColor(const float* col)
{
	/*! Sets the fill color: pointer to a 4 elements float array (RGBA). */
	_fillColor[0] = col[0];
	_fillColor[1] = col[1];
	_fillColor[2] = col[2];
	_fillColor[3] = col[3];
}



// *****************************************************************************
// **							     SERVER SIDE							  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER


// *****************************************************************************
// **							    gl Functions							  **
// *****************************************************************************

//______________________________________________________________________________
double filled::glAlpha()
{
	/*! Returns if the gp has any kind of transparency in its constituent
	 *	elements (color, material, brush, ...). THe function is hierarchical:
	 *	it digs through all the parents chain to sum up the whole result.
	 */
	
	// Get basic (hierarchical) alpha.
	double pAlpha = GP::glAlpha();

	// Consider filling for alpha.
	double mAlpha = 1;
	if (_fillMaterial) {
		//mAlpha = _mtrlDiffuse[3];
	} else {
		mAlpha = _fillColor[3];
	}

	// Returns the convolution of the two.
	return  pAlpha * mAlpha;
}

//______________________________________________________________________________
void filled::glDrawSel()
{
	/*! The glDrawSel draws a specific selection "skeleton" to highlight the 
	 *	selected object. Each GP should provide its own specialized glDrawSel 
	 *	overload, aas no basic one is implemented.
	 */

	// Get transformation chain applied.
	stroked::glDrawSel();
}

//______________________________________________________________________________
void filled::glDraw()
{
	/*! Sets all the drawing properties common for all GPs. The _drw* variables
	 *	are class member which could be used by childrens to influence their
	 *	own appearance, so they are stored until the next call to the function.
	 */
								  
	// Common drawing properties are handled by the parent GP.
	stroked::glDraw();
	
	// Material/lighting properties.
	if (_fillMaterial) {
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _mtrlAmbient);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _mtrlDiffuse);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _mtrlSpecular);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, _mtrlEmission);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &_mtrlShininess);
	} else {
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _fillColor);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _fillColor);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, _fillColor);
		//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	}
}

//______________________________________________________________________________
void filled::glDrawEnd()
{
	/*! Closes the GP drawing. */
	stroked::glDrawEnd();
}


// *****************************************************************************
// **								ui Functions							  **
// *****************************************************************************

//______________________________________________________________________________
void filled::uiBarLoad(ui::Bar& bar)
{
	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
	 *	the GP. This member should be overloaded to change/add the properties
	 *	shown on the properties bar by every GP.
	 */
	
	// The parent first!
	stroked::uiBarLoad(bar); 

	// Retrieve the TwBarr associated with the owner uiBar.
//	TwBar* twBar = bar._TwBar;
	
	// Fill
//	bar.GroupAdd("Fill");
//	TwAddVarRW(twBar, "fillEnable", TW_TYPE_BOOLCPP, &_fillEnable, "label='Enable' group='Fill'");	
//	TwAddVarRW(twBar, "fillMaterial", TW_TYPE_UINT32, &_fillMaterial, "label='Use material' group='Fill'");
//	TwAddVarRW(twBar, "fillColor", TW_TYPE_COLOR4F, _fillColor, "label='Color' colororder=rgba coloralpha=true group='Fill'");

	// Move material group under fill group.
	//TwSetParam(twBar, "Material", "group", TW_PARAM_CSTRING, 1, "Fill");
}

// End of PEAR_SERVER if.
#endif

// #############################################################################
}} // Close Namespaces
