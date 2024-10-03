//------------------------------------------------------------------------------
// CAT Box Graphic Primitive class					 						  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpBox.h"
// [Author]			"Sarah Zalusky"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpBox_H
#define gpBox_H

// Components
#include "gpFilled.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::Box creates a Box in 3D.
 *	
 *	\author Sarah Zalusky
 *	\version 1.0
 *	\date 24 Sep 2024
 */

//______________________________________________________________________________
class box: public filled
{
	private:   
	
		// The 8 vertex points defining the volume.
		ge::point _vtx[8];
	      
	protected:
	
	public:
		
		// Special Members.
		box(); //!< Default ctor.
	
		//! Standard Constructor with (Required: xWidth, yLength, zHeight. 
		box(const double& cX, const double& cY, const double& cZ,
			const double& sX, const double& sY, const double& sZ);
		
		//! Standard Constructor with (Required: xWidth, yLength, zHeight. 
		box(const double& xW, const double& yL, const double& zH);
	
		//! Box Constructor with vector containing (24 points).
		box(const double* vtx);
	
		// Default access public members
		CO::oType type() const;					//!< Returns GP type.
		coVer_t version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const int& = 0) const;		//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);
		
		// Public transformation overloads.
		box& trsf(const ge::ref& ref, const bool& inv);			//!< Transform the GP.
		box& trsfIn(const ge::ref& ref) {return trsf(ref, false);}	//!< Transform the GP into ref.	 	
		box& trsfOut(const ge::ref& ref) {return trsf(ref, true);}	//!< Transform the GP from ref.

		// Provide Access to the internal Vertex Components.
		ge::point vtx(const int& idx) const;	// Return Idxth vertex.

		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			void glDraw();		//!< Draws the GP on the current GLContext.
			void glDrawSel();	//!< Draws the GP in selection mode.
			void glDrawEnd();	//!< Closes the GP drawing. Mandatory call!
		#endif
};

// #############################################################################
}} // Close namespace


// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::box& obj)
{
	/*! Overloads standard output operator << for a generic pear::GP:Box. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif