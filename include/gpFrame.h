//------------------------------------------------------------------------------
// CAT Frame Graphic Primitive class					 					  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpFrame.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpFrame_H
#define gpFrame_H

// Components
#include "gp.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::frame creates a frame in 3D. A gp::frame is a draw-less gp which
 *	holds a ge::ref object which affects all the frame family members. In this
 *	way the transformation set on the ge:rRef object is applied to all the
 *	family hierarchy of the parent frame object.
 *	
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 24 Sep 2024
 */

//______________________________________________________________________________
class frame: public GP
{
	private:   
	
		// The reference.
		ge::ref _ref;
	      
	protected:
	
	public:
		
		//! Default ctor.
		frame();	
	
		//! Ctor with displacement (p0) and rotation around XYZ (a0). 
		frame(const ge::point& p0, const ge::vector& a0);
		
		//! Ctor with displacement (p0), rotation axis (v0) and rotation angle.
		frame(const ge::point& p0, const ge::vector& v0, const double& a);
	
		// Default access public members
		CO::oType type() const;					//!< Returns GP type.
		coVer_t version() const;				//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const int& = 0) const;		//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);
		
		// Public transformation overloads.
		frame& trsf(const ge::ref& ref, const bool& inv);				//!< Transform the GP.
		frame& trsfIn(const ge::ref& ref) {return trsf(ref, false);}	//!< Transform the GP into ref.	 	
		frame& trsfOut(const ge::ref& ref) {return trsf(ref, true);}	//!< Transform the GP from ref.

		// Provide Access to the internal Reference Components.
		ge::ref ref() const;	// Returns the internal reference.

		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			void glDraw();			//!< Draws the GP on the current GLContext.
			void glDrawSel();		//!< Draws the GP in selection mode.
			void glDrawEnd();		//!< Closes the GP drawing. Mandatory call!
			void glTrsfApply();		//!< Apply (push) the gp Ref (hierarchical) transformation.
			void glTrsfReset();		//!< Reset (pop) the gp Ref (hierarchical) transformation.
		#endif
};

// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::frame& obj)
{
	/*! Overloads standard output operator << for a generic pear::GP:Frame. */ 
	obj.dump();
	return o;
}


// Overloading check
#endif