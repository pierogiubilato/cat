//------------------------------------------------------------------------------
// CAT polygon Graphic Primitive class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpPolygon.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined gpPolygon_H
#define gpPolygon_H

// Components
#include "gpStroked.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::polygon creates a Polygon (a series of connected segments) in 3D.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 18 Sep 2024
 */

//______________________________________________________________________________
class polygon: public stroked
{
	private:   
	
		//! The vertex points defining the polygon.
		std::vector<ge::point> _vtx;
		
		//! Open/close polygon.
		bool _closed;
	      
	protected:
	
	public:
		
		//!< Default ctor.
		polygon();
	
		//! Polygon Constructor with array of Vertexes.
		polygon(const ge::point* vtx, const Uint64& vtxCount, const bool& closed = false);
		
		// Default access public members
		Uint64 type() const;					//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const Uint64& ind = 0) const;	//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);

		// Public transformation overloads.
		polygon& trsf(const ge::ref& ref, const bool& inv);			//!< Transform the GP.
		polygon& trsfIn(const ge::ref& ref) {return trsf(ref, false);}	//!< Transform the GP into ref.	 	
		polygon& trsfOut(const ge::ref& ref) {return trsf(ref, true);}	//!< Transform the GP from ref.
	
		// Provide Access to the internal Vertex Components.
		inline ge::point vtx(const Uint64&) const;
		
		// Returns number of vertexes composing the polygon.
		size_t vtxCount() const;
		
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
inline std::ostream& operator << (std::ostream& o, const cat::gp::polygon& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Polygon. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif