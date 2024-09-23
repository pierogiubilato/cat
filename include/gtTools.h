//------------------------------------------------------------------------------
// Graphic tools to manipulate the Graphic Primitives                         --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpTools.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef gtTools_H
#define gtTools_H

// Application
#include "gp.h"

// #############################################################################
namespace cat { namespace gt {

// *****************************************************************************
// **							Types and Structures						  **
// *****************************************************************************


// *****************************************************************************
// **							The basic pear GT							  **
// *****************************************************************************

/*! cat::gt::GT is the base class for all pear graphic tools. A graphic tool 
 *  is anything which perform actions or affect the properties of a graphic 
 *	primitive, like a brush, a pen, a font, etc... This class is a very basic 
 *	container and just provides virtual interface.
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 23 Sep 2024
*/

//______________________________________________________________________________
class GT : public CO
{
	private:   
		
		// Basic GT properties
		
		// Family relationships.
		
		
   protected:
	
		
	
	public:
	
		// Default interface public members.
		//virtual bool Stream(std::stringstream& o, bool read = false);	//!< Stream GO data.		
		
};

// #############################################################################
}} // Close namespaces



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gt::GT& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}


// *****************************************************************************
// **							  Graphic Tools								  **
// *****************************************************************************



// #############################################################################
namespace cat { namespace gt {

//______________________________________________________________________________
//! Brush.
class brush: public GT
{
	/*! Brush GT. Holds the stroking parameters. */
	bool active; 
	float color[4]; 
	float width;
	Uint16 pattern;
	Uint32 scale;

	//! Default ctor.
	brush() {
		active = true;
		color[0] = color[1] = color[2] = 0.7f; color[3] = 1;
		width = 1;
		pattern = 0;
		scale = 1;
	}
};

//______________________________________________________________________________
class fill: public GT 
{
	/*! Fill GT. Holds the filling parameters. */
	bool active; 
	float color[4]; 
	
	//! Default ctor.
	fill() {
		active = true;
		color[0] = color[1] = color[2] = 0.5f; color[3] = 1;
	}
};

//______________________________________________________________________________
class material: public GT
{
	/*! Material GT. Holds the material settings. */ 
	bool active; 
	float ambient[4]; 
	float diffuse[4]; 
	float specular[4];
	float emission[4];
	float shininess;

	//! Default ctor.
	material() {
		active = false;
		ambient[0] =  ambient[1] =  ambient[2] = 0.7f;  ambient[3] = 1;
		diffuse[0] =  diffuse[1] =  diffuse[2] = 0.7f;  diffuse[3] = 1;
		specular[0] = specular[1] = specular[2] = 0.7f; specular[3] = 1;
		emission[0] = emission[1] = emission[2] = 0.7f; emission[3] = 1;
		shininess = 20;
	}
};

//______________________________________________________________________________
class inherit: public GT
{
	/*! Inherit GT. Holds the inheritance settings. */ 
	bool enabled;
	bool visibility;
	bool alpha;
	bool wire;
	bool ref;

	//! Default ctor.
	inherit() {
		enabled = true;
		visibility = true;
		alpha = true;
		wire = true;
		ref = true;
	}
};

//______________________________________________________________________________
class font: public GT
{
	/*! Font GT. Hold the properties of a font. */
	std::string family;		//!< Font family (arial, ...).
	std::string style;		//!< Font style (bold, ...).
	Uint32 size;			//!< Font size.

	//! Default ctor.
	font() {
		family = "";		//!< Use default font.
		style = "";			//!< Use default style.
		size = 0;			//!< Use default size.
	}
};

//______________________________________________________________________________
class trsf: public GT
{
	/*! Trsf GT. Hold the properties of a 3D transformation. */
	gp::GPPos pos;			//!< Translation.
	gp::GPAng rot;			//!< Rotation.
	gp::GPDim scale;		//!< Scale.

	//! Default ctor.
	trsf() {
		pos.x = pos.y = pos.z = 0;
		rot.a = rot.b = rot.g = 0;
		scale.x = scale.y = scale.z = 1;
	}
};


// #############################################################################
}} // Close namespaces


// Overloading check
#endif
