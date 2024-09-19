//------------------------------------------------------------------------------
// Basic CAT object                                                           --
// (C) Piero Giubilato 2022-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"co.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef co_H
#define co_H

// Application
#include "acGlobal.h"
#include "afStream.h"


// #############################################################################
namespace cat {



// *****************************************************************************
// **							The basic cat GE							  **
// *****************************************************************************

/*! 'cat::CO' is the base class for all cat data objects, including data,
 *  geometry and graphics. This class is a very basic format container and just 
 *  provides virtual, weightless interface.
 *
 *	Objects deriving directly from the 'cat::CO' class are usually pure math 
 *  or geometrical items, like coordinate representations or transformation 
 *  frames.
 *
 *  Objects expected to be actually drawn all derives from the more specialized
 *  'cat::gp::GP' derived class, which implements all the features necessary
 *  for proper graphics display (and weights much more...).
 *
 *
 *	\author Piero Giubilato
 *	\version 1.2
 *	\date 18 Sep 2024
 */

 //______________________________________________________________________________
class CO
{
	private:

	protected:

	public:
	
		// Default interface virtual public members.
		virtual Uint64 type() const { return 0; }		//!< Returns CO type. It's a sum of all the layer!
		virtual Uint64 version() const { return 0; }	//!< Returns CO version.
		virtual std::string stem() const { return ""; }	//!< Returns CO stem name.
		virtual void dump(const Uint64 & = 0) const {};	//!< Dumps CO data.

		//! Returns the object size in bytes.
		virtual size_t size(const bool& = false) const {
			/*! Returns the complete (full static + full dynamic)
			 *	allocated space for the CO if \c dynamic = false,
			 *	which is the default call. If \c dynamic = true,
			 *	it returns only the dynamically allocated space,
			 *	without any contribution from the static part. */
			return 0;
		}

		//! Stream the CO data, the only non-const basic interface member.
		virtual bool stream(std::stringstream&, const bool&) { return false; }
};

// #############################################################################
} // Close namespaces



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::co& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
