//------------------------------------------------------------------------------
// Primitives object for the CAT graphic entity                               --
// (C) Piero Giubilato 2022-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"ge.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"21 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef ge_H
#define ge_H

// Application
#include "co.h"


// #############################################################################
namespace cat { namespace ge {



// *****************************************************************************
// **							The basic cat GE							  **
// *****************************************************************************

/*! 'cat::ge::GE' is the base class for all cat graphic data entities. A graphic 
 *  entity is anything abstract involved in the representation of 3D geometry, 
 *  and in the manipulation of such data. This class is a very basic container 
 *  and just provides virtual, weightless interface.
 *
 *	Objects deriving directly from the 'cat::ge::GE' class are usually pure math 
 *  or geometrical items, like coordinate representations or transformation frames.
 *
 *  Objects expected to be actually drawn all derives from the more specialized
 *  'cat::gp::GP' ""DERIVED"" class, which implements all the features necessary
 *  for proper graphics display (and weights much more...).
 *
 *
 *	\author Piero Giubilato
 *	\version 1.2
 *	\date 21 Sep 2024
 */

 //______________________________________________________________________________
class GE : public cat::CO
{
	private:

	protected:

	public:

		// Default interface public members, overload cat::CO class.
		oType type() const { return oType::geBase; }	//!< Returns GE type. It's a sum of all the layer!
		Uint64 version() const { return 0; }			//!< Returns GE version.
		std::string stem() const { return ""; }			//!< Returns GE stem name.
		void dump(const Uint64 & = 0) const {};			//!< Dumps GE data.
		size_t size(const bool& = false) const { return 0;}
		bool stream(std::stringstream&, const bool&) { return false; }
};

// #############################################################################
}} // Close namespaces



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::ge::GE& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
