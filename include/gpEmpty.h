//------------------------------------------------------------------------------
// CAT empty Graphic Primitive												  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpEmpty.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined gpEmpty_H
#define gpEmpty_H

// Components
#include "gp.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::Virtual is a virtual graphic primitive with no actual properties.
 *	It is used for testing/padding.
 *	
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 18 Sep 2024
 */

//______________________________________________________________________________
class empty: public GP
{
	private:   
	      
	protected:
	
	public:
		
		// Default access public members
		Uint64 type() const;			//!< Returns GP type.
		Uint64 version() const;			//!< Returns GP version.
		std::string stem() const;		//!< Returns GP stem name.
		//size_t Size() const;			//!< Returns GP size in bytes.
		void dump(const Uint64& ind = 0) const;			//!< Dumps GP data.
		
		//! Stream the GP data (both read and write).
		bool stream(std::stringstream& o, const bool& read = false);

		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			//! Draws the GP on the current GLcontext.			
			void glDraw();
			void glDrawSel();
		#endif
};

// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const pear::gp::empty& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Virtual. */ 
	obj.dump();
	return o;
}


// Overloading check
#endif