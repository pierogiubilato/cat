//------------------------------------------------------------------------------
// CAT Tube Graphic Primitive class											  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpTube.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"C++"
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
 *	\date 18 Sep 2024
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
		Uint32 _slices;		//!< Radial sectors.
		Uint32 _stacks;		//!< Height sectors.
	
	protected:
	
	public:
		
		//!< Default ctor.
		tube();
	
		//! Standard Constructor.
		tube(const double& riBase, const double& roBase,
			 const double& riTop, const double& roTop,
			 const double& height,
			 const Uint32& slices = 10, const Uint32& stacks = 1);
		
		// Default access public members.
		Uint64 type() const;					//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const Uint64& = 0) const;		//!< Dumps GP data.
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
		double height() const {return _Height;}
		double slices() const {return _Slices;}
		double stacks() const {return _Stacks;}
				
		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			void glDraw();		//!< Draws the GP on the current GLcontext.
			void glDrawSel();	//!< Draws the GP in selection mode.
			void glDrawEnd();	//!< Closes the GP drawing. MAndatory call!
		#endif
};


/*! pear::gp::Cylinder creates a cylinder in 3D. It actually is an ultralight 
 *	overload of the gp::Tube class to just provide easier constructor and
 *	different signature.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 30 Aug 2011
 */
//______________________________________________________________________________
class Cylinder: public Tube
{
	public:
		//! Default ctor.
		Cylinder():Tube(0, 1, 0, 1, 1) {;};
	
		//! Standard Constructor.
		Cylinder(const double& rBase, const double& rTop, const double& height,
				 const Uint32& slices = 10, const Uint32& stacks = 1)
				 :Tube(0, rBase, 0, rTop, height, slices, stacks) {;};
		
		// Default access public members.
		Uint64 Type() const {return Filled::Type() + kgp_Cylinder;};
		std::string Stem() const {return "Cylinder";};
};


/*! pear::gp::Cone creates a cone in 3D. It actually is an ultralight 
 *	overload of the gp::Tube class to just provide easier constructor and
 *	different signature.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 30 Aug 2011
 */
//______________________________________________________________________________
class Cone: public Tube
{
	public:
		//! Default ctor.
		Cone():Tube(0, 1, 0, 0, 1) {;};
	
		//! Standard Constructor.
		Cone(const double& rBase, const double& height,
				 const Uint32& slices = 10, const Uint32& stacks = 1)
				 :Tube(0, rBase, 0, 0, height, slices, stacks) {;};
		
		// Default access public members.
		Uint64 Type() const {return Filled::Type() + kgp_Cone;};
		std::string Stem() const {return "Cone";};
};


// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const pear::gp::Tube& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Tube. */ 
	obj.Dump();
	return o;
}

// Overloading check
#endif