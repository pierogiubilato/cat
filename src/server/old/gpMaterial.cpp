//------------------------------------------------------------------------------
// CAT material Graphic Primitive											  --
// (C) Piero Giubilato 2011-2013, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpMaterial.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "gpmaterial.h"

//##############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
material::material():GP()
{
	/*! Ctor. Initialize the filling properties to default. */
	
	// Colors.
	_mtrlAmbient[0] =	_mtrlAmbient[1] =	_mtrlAmbient[2] = 0.2f;		_mtrlAmbient[3] = 1.0f;
	_mtrlDiffuse[0] =	_mtrlDiffuse[1] =	_mtrlDiffuse[2] = 0.6f;		_mtrlDiffuse[3] = 1.0f;
	_mtrlSpecular[0] =	_mtrlSpecular[1] =	_mtrlSpecular[2] = 0.1f;	 _mtrlSpecular[3] = 1.0f;
	_mtrlEmission[0] =	_mtrlEmission[1] =	_mtrlEmission[2] = 0.0f;	_mtrlEmission[3] = 1.0f;
	_mtrlShininess = 0;	
}

//______________________________________________________________________________
material::~material()
{
	/*! Destructor	*/
} 

//______________________________________________________________________________
CO::oType material::type() const
{
	/*! Returns object type. This function MUST be overloaded to differentiate 
	 *	any derived class, and must also be addictive! 
	 */
   return CO::oType::gpMaterial;
}

//______________________________________________________________________________
cat::coVer_t material::version() const
{
	/*! Returns object version. This function MUST be overloaded to differentiate 
	 *	any derived class! Version numbering is made in unit of hundreds for the
	 *	major and decimal for the subversions. So version 2.0 is 200.
	 */
   return 100;
}

//______________________________________________________________________________
std::string material::stem() const
{
	/*! Returns the object stem, i.e. the class stem. MUST be overloaded */
   return "material";
}

//______________________________________________________________________________
size_t material::size(const bool& dynamic) const 
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
void material::dump(const int& ind) const
{
 	/*! Dumps on the standard output the relevant GP properties. */

	// Quich out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)
	#define CLR COL(LRED)
	#define CLG COL(LGREEN)
	#define CLB COL(LBLUE)

	// Padding string
	GP::dump(ind);
	std::string pad(ind, ' ');
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');

	// Set output formatting.
	std::cout << std::showpos << std::fixed << std::setprecision(CAT_DUMP_PREC_COLOR);
	
	// Colors.
	std::cout << pad2 << "material\n"
		<< pad3 << "Diffuse: <"	<< CLR << _mtrlDiffuse[0] << CD << ", "
						<< CLG << _mtrlDiffuse[1] << CD << ", "
						<< CLB << _mtrlDiffuse[2] << CD << ", "
						<< CLW << _mtrlDiffuse[3] << CD << ">\n"
		<< pad3 << "Ambient: <"	<< CLR << _mtrlAmbient[0] << CD << ", "
						<< CLG << _mtrlAmbient[1] << CD << ", "
						<< CLB << _mtrlAmbient[2] << CD << ", "
						<< CLW << _mtrlAmbient[3] << CD << ">\n"
		<< pad3 << "Specular: <"<< CLR << _mtrlSpecular[0] << CD << ", "
						<< CLG << _mtrlSpecular[1] << CD << ", "
						<< CLB << _mtrlSpecular[2] << CD << ", "
						<< CLW << _mtrlSpecular[3] << CD << ">\n"
		<< pad3 << "Emission: <"<< CLR << _mtrlEmission[0] << CD << ", "
						<< CLG << _mtrlEmission[1] << CD << ", "
						<< CLB << _mtrlEmission[2] << CD << ", "
						<< CLW << _mtrlEmission[3] << CD << ">\n"
		<< pad3 << "Shininess: <"<< CLW	<< _mtrlShininess << CD << "\n";
		
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
bool material::stream(std::stringstream& o, const bool& read)
{
	/*! Adds the current GP data member into the \c o stream (when \c Read = 
	 *	false) or load the GP from the \c o stream (when \c Read = true). 
	 */
	
	// Streams the parent.
	GP::stream(o, read);
		
	// Colors.
	for (auto i = 0; i < 4; i++) {
		af::stream::rw(o, _mtrlAmbient[i], read);
		af::stream::rw(o, _mtrlDiffuse[i], read);
		af::stream::rw(o, _mtrlSpecular[i], read);
		af::stream::rw(o, _mtrlEmission[i], read);
	}
	af::stream::rw(o, _mtrlShininess, read);

	// Everything fine!
	return false;
}


// *****************************************************************************
// **						  Public specific members						  **
// *****************************************************************************

//______________________________________________________________________________
const float* material::mtrlAmbient() const
{
	/*! Returns the material ambient color: pointer to a 4 elements float 
	 *	array (RGBA). */
	return _mtrlAmbient;
}

//______________________________________________________________________________
void material::mtrlAmbient(const float* col)
{
	/*! Sets material ambient color. */
	_mtrlAmbient[0] = col[0];
	_mtrlAmbient[1] = col[1];
	_mtrlAmbient[2] = col[2];
	_mtrlAmbient[3] = col[3];	
}

//______________________________________________________________________________
const float* material::mtrlDiffuse() const
{
	/*! Returns the material diffuse color: pointer to a 4 elements float 
	 *	array (RGBA). */
	return _mtrlDiffuse;
}

//______________________________________________________________________________
void material::mtrlDiffuse(const float* col)
{
	/*! Sets material diffuse color. */
	_mtrlDiffuse[0] = col[0];
	_mtrlDiffuse[1] = col[1];
	_mtrlDiffuse[2] = col[2];
	_mtrlDiffuse[3] = col[3];	
}

//______________________________________________________________________________
const float* material::mtrlSpecular() const
{	
	/*! Returns the material specular color: pointer to a 4 elements float 
	 *	array (RGBA). */
	return _mtrlSpecular;
}

//______________________________________________________________________________
void material::mtrlSpecular(const float* col)
{
	/*! Sets material specular color. */
	_mtrlEmission[0] = col[0];
	_mtrlEmission[1] = col[1];
	_mtrlEmission[2] = col[2];
	_mtrlEmission[3] = col[3];	
}

//______________________________________________________________________________
const float* material::mtrlEmission() const
{
	/*! Returns the material emission color: pointer to a 4 elements float 
	 *	array (RGBA). */
	return _mtrlEmission;
}

//______________________________________________________________________________
void material::mtrlEmission(const float* col) 
{
	/*! Sets material emission color. */
	_mtrlEmission[0] = col[0];
	_mtrlEmission[1] = col[1];
	_mtrlEmission[2] = col[2];
	_mtrlEmission[3] = col[3];	
}

//______________________________________________________________________________
const float material::mtrlShininess() const
{
	/*! Returns the material shininess. */
	return _mtrlShininess;
}

//______________________________________________________________________________
void material::mtrlShininess(const float& shine)
{
	/*! Sets the material shininess. */
	_mtrlShininess = shine;	
}



// *****************************************************************************
// **							     SERVER SIDE							  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER


// *****************************************************************************
// **							    gl Functions							  **
// *****************************************************************************

// *****************************************************************************
// **								ui Functions							  **
// *****************************************************************************

//______________________________________________________________________________
//void material::uiBarLoad(ui::Bar& bar)
//{
//	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
//	 *	the GP. This member should be overloaded to change/add the properties
//	 *	shown on the properties bar by every GP.
//	 */
//	
//	// The parent first!
//	GP::uiBarLoad(bar); 
//
//	// Retrieve the TwBarr associated with the owner uiBar.
////	TwBar* twBar = bar._TwBar;
//	
//	// material
////	bar.GroupAdd("material");
////	TwAddVarRW(twBar, "mtrlAmbient", TW_TYPE_COLOR4F, _mtrlAmbient, "label='Ambient' colororder=rgba coloralpha=true group='material'");
////	TwAddVarRW(twBar, "mtrlDiffuse", TW_TYPE_COLOR4F, _mtrlDiffuse, "label='Diffuse' colororder=rgba coloralpha=true group='material'");
////	TwAddVarRW(twBar, "mtrlSpecular", TW_TYPE_COLOR4F, _mtrlSpecular, "label='Specular' colororder=rgba coloralpha=true group='material'");
////	TwAddVarRW(twBar, "mtrlEmission", TW_TYPE_COLOR4F, _mtrlEmission, "label='Emission' colororder=rgba coloralpha=true group='material'");
////	TwAddVarRW(twBar, "mtrlShininess", TW_TYPE_FLOAT, &_mtrlShininess, "label='Shininess' min=0.1 max=128 step=0.1 group='material'");
//	
//	// Move material group under fill group.
//	//TwSetParam(twBar, "material", "group", TW_PARAM_CSTRING, 1, "Fill");
//}

// End of PEAR_SERVER if.
#endif

// #############################################################################
}} // Close Namespaces
