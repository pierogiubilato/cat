//------------------------------------------------------------------------------
// CAT sphere Graphic Primitive class					 					  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpSphere.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpSphere_H
#define gpSphere_H

// Components
#include "gpFilled.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::sphere creates a Sphere in 3D. This GP can also draw a cone 
 *	or a truncated cone.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 24 Sep 2024
 */

//______________________________________________________________________________
class sphere: public filled
{
	private:   
	
		// The cylinder parameters.
		double _radius;
		uint16_t _slices;
		uint16_t _stacks;
	
	protected:
	
	public:
		
		//!< Default ctor.
		sphere();
	
		//! Standard Constructor.
		sphere(const double& radius, const Uint32& slices = 10, 
			   const Uint32& stacks = 10);
		
		// Default access public members.
		CO::oType type() const;					//!< Returns GP type.
		coVer_t version() const;				//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const int& ind = 0) const;	//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);

		// Provide Access to the internal Point Components.
		double radius() const {return _radius;}
		double slices() const {return _slices;}
		double stacks() const {return _stacks;}
				
		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			void glDraw();		//!< Draws the GP on the current GLcontext.
			void glDrawSel();	//!< Draws the GP in selection mode.
			void glDrawEnd();	//!< Closes the GP drawing. MAndatory call!
			
		#endif
};

// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::sphere& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Sphere. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif