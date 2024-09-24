//------------------------------------------------------------------------------
// CAT line Graphic Primitive class					 						  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpLine.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpLine_H
#define gpLine_H

// Components
#include "gpStroked.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::Line creates a Line (better segment) in 3D.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 23 Sep 2024
 */

//______________________________________________________________________________
class line: public stroked
{
	private:   
	
		// The 2 vertex points defining the line.
		ge::point _vtx[2];
	      
	protected:
	
	public:
		
		//!< Default ctor.
		line();
	
		//! Standard Constructor with (x1, y1, z1, x2, y2, z2).
		line(const double& x1, const double& y1, const double& z1,
			 const double& x2, const double& y2, const double& z2);
		
		//! Line Constructor with array of vertexes (6 point)
		line(const double* vtx);
	
		// Default access public members
		CO::oType type() const;					//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const Uint64& ind = 0) const;	//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);

		// Public transformation overloads.
		line& trsf(const ge::ref& ref, const bool& inv);		//!< Transform the GP.
		line& trsfIn(const ge::ref& ref) {return trsf(ref, false);}	//!< Transform the GP into ref.	 	
		line& trsfOut(const ge::ref& ref) {return trsf(ref, true);}	//!< Transform the GP from ref.

		// Provide Access to the internal Point Components.
		ge::point vtx(const Uint64&) const;
		ge::point v0() const {return _vtx[0];}
		ge::point v1() const {return _vtx[1];}
		
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
inline std::ostream& operator << (std::ostream& o, const cat::gp::line& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Line. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif