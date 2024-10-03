//------------------------------------------------------------------------------
// CAT material Graphic Primitives class									  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpMaterial.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef gpMaterial_H
#define gpMaterial_H

// Application
#include "gp.h"


// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							The cat::GP::material						  **
// *****************************************************************************

/*! cat::GP::Material is describes a material used by other GPs to fill their
 *	surfaces.
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 18 Sep 2024
*/

//______________________________________________________________________________
class material: public GP
{
	private:   
		
	protected:
   
		// Material Colors.
		float _mtrlAmbient[4];		//!< Material Ambient color.
		float _mtrlDiffuse[4];		//!< Material Diffuse color.
		float _mtrlSpecular[4];		//!< Material Specular color.
		float _mtrlEmission[4];		//!< Material Emission color.		
		float _mtrlShininess;		//!< Material Shininess.
				
	public:
		
		// Special members.
		material();								//!< Default ctor.
		virtual ~material();						//!< Virtual dtor.
		
		// To be overloaded public members (already virtual from pear::GO).
		oType type() const;						//!< Returns GP type.
		coVer_t version() const;				//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const int& = 0) const;		//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);
				
		// Public specific members.
		const float* mtrlAmbient() const;	//!< Returns material ambient color.
		void mtrlAmbient(const float*);		//!< Sets material ambient color.
		const float* mtrlDiffuse() const;	//!< Returns material diffuse color.
		void mtrlDiffuse(const float*);		//!< Sets material diffuse color.
		const float* mtrlSpecular() const;	//!< Returns material specular color.
		void mtrlSpecular(const float*);	//!< Sets material specular color.
		const float* mtrlEmission() const;	//!< Returns material emission color.
		void mtrlEmission(const float*);	//!< Sets material emission color.
		const float mtrlShininess() const;	//!< Returns material shininess.
		void mtrlShininess(const float&);	//!< Sets material shininess.

		// Drawing functions and vars are ONLY defined for the SERVER side!
		// ----------------------------------------------------------------
		#ifdef CAT_SERVER
			
			// UI interaction.
			//virtual void uiBarLoad(ui::Bar&);	//!< Load a bar with the GP specific properties.
		
		#endif
};

// #############################################################################
}} // Close namespace



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::material& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
