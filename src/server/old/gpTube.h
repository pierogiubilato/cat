//------------------------------------------------------------------------------
// CAT Tube Graphic Primitive class											  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpTube.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpTube_H
#define gpTube_H

// Components
#include "gpFilled.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::tube creates a Tube in 3D. This GP can also draw a cylinder or cone
 *	or a truncated cone.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 24 Sep 2024
 */

//______________________________________________________________________________
class tube: public filled
{
	private:   
	
		// The cylinder parameters.
		double _riBase;		//!< Base inner radius.
		double _roBase;		//!< Base outer radius.
	    double _riTop;		//!< Top inner radius.
		double _roTop;		//!< Top outer radius.
  		double _height;		//!< Height.
		uint16_t _slices;	//!< Radial sectors.
		uint16_t _stacks;	//!< Height sectors.
	
	protected:
	
	public:
		
		//!< Default ctor.
		tube();
	
		//! Standard Constructor.
		tube(const double& riBase, const double& roBase,
			 const double& riTop, const double& roTop,
			 const double& height,
			 const uint_fast16_t& slices = 10, const uint_fast16_t& stacks = 1);
		
		// Default access public members.
		CO::oType type() const;					//!< Returns GP type.
		coVer_t version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const int& = 0) const;		//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);

		// Public transformation overloads.
		//Tube& Trsf(const go::Ref& ref, const bool& inv);			//!< Transform the GP.
		//Tube& TrsfIn(const go::Ref& ref) {return Trsf(ref, false);}	//!< Transform the GP into ref.	 	
		//Tube& TrsfOut(const go::Ref& ref) {return Trsf(ref, true);}	//!< Transform the GP from ref.

		// Provide Access to the internal Point Components.
		double riBase() const {return _riBase;}
		double roBase() const {return _roBase;}
		double riTop() const {return _riTop;}
		double roTop() const {return _roTop;}
		double height() const {return _height;}
		double slices() const {return _slices;}
		double stacks() const {return _stacks;}
				
		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			void glDraw();		//!< Draws the GP on the current GLcontext.
			void glDrawSel();	//!< Draws the GP in selection mode.
			void glDrawEnd();	//!< Closes the GP drawing. MAndatory call!
		#endif
};


/*! cat::gp::cylinder creates a cylinder in 3D. It actually is an ultralight 
 *	overload of the cat::gp::tube class to just provide easier constructor and
 *	different signature.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 24 Sep 2024
 */
//______________________________________________________________________________
class cylinder: public tube
{
	public:
		//! Default ctor.
		cylinder():tube(0, 1, 0, 1, 1) {;};
	
		//! Standard Constructor.
		cylinder(const double& rBase, const double& rTop, const double& height,
				 const uint_fast16_t& slices = 10, const uint_fast16_t& stacks = 1)
				 : tube(0, rBase, 0, rTop, height, slices, stacks) {;};
		
		// Default access public members.
		CO::oType type() const {return CO::oType::gpCylinder;};
		std::string stem() const {return "cylinder";};
};


/*! cat::gp::cone creates a cone in 3D. It actually is an ultralight 
 *	overload of the cat::gp::Tube class to have an easier constructor 
 *  and a different signature.
 *	
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 24 Sep 2024
 */
//______________________________________________________________________________
class cone: public tube
{
	public:
		//! Default ctor.
		cone():tube(0, 1, 0, 0, 1) {;};
	
		//! Standard Constructor.
		cone(const double& rBase, const double& height,
				 const Uint32& slices = 10, const uint_fast16_t& stacks = 1)
				 : tube(0, rBase, 0, 0, height, slices, stacks) {;};
		
		// Default access public members.
		CO::oType type() const {return CO::oType::gpCone;};
		std::string stem() const {return "cone";};
};


// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::tube& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Tube. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif