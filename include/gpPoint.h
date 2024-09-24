//------------------------------------------------------------------------------
// CAT Point Graphic Primitive class					 					  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpPoint.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpPoint_H
#define gpPoint_H

// Components
#include "gpStroked.h"


// #############################################################################
namespace cat { namespace gp {

/*! pear::gp::Point creates a Point in 3D.
 *	
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 23 Sep 2024
 */

//______________________________________________________________________________
class point: public stroked
{
	private:   
	
		// The point position and its size in pixels (fractional).
		ge::point _Vtx;
		  
	protected:
	
	public:
		
		//!< Default ctor.
		point();
	
		//! Standard Constructor with (x, y, z, r).
		point(const double& x, const double& y, const double& z, const double& r = 1);
		point(const double*, const double& = 1);
		
		// Default access public members
		CO::oType type() const;		//!< Returns GP type.
		Uint64 version() const;		//!< Returns GP version.
		std::string stem() const;	//!< Returns GP stem name.
		void dump(const Uint64& = 0) const;	//!< Dumps GP data.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		
		//! Stream the GP data (both read and write).
		bool stream(std::stringstream& o, const bool& read = false);

		// Public transformation overloads.
		point& trsf(const ge::ref& ref, const bool& inv);				//!< Transform the GP.
		point& trsfIn(const ge::ref& ref) {return trsf(ref, false);}	//!< Transform the GP into ref.	 	
		point& trsfOut(const ge::ref& ref) {return trsf(ref, true);}	//!< Transform the GP from ref.

		// Provide Access to the internal Point Components.
		ge::point vtx() const;
		//double radius() const;		
		
		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			void glDraw();		//!< Draws the GP.
			void glDrawSel();	//!< Highlight the GP.
			void glDrawEnd();	//!< Close the GP drawing. Mandatory call!
		#endif
};

// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::ge::point& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Point. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif