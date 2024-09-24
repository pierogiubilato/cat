//------------------------------------------------------------------------------
// Basic CAT object                                                           --
// (C) Piero Giubilato 2022-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"co.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef co_H
#define co_H

// STL.
#include<sstream>
#include<ostream>

// Application
#include "acGlobal.h"
#include "afStream.h"


// #############################################################################
namespace cat {


// *****************************************************************************
// **						The basic cat CO types							  **
// *****************************************************************************

	//! Handle representing a CO object.
	typedef uint_fast64_t coHnd_t;

	//! Handle representing a CO object.
	typedef uint_fast64_t coType_t;

	//! Version of CO object.
	typedef uint_fast16_t coVer_t;


// *****************************************************************************
// **							The basic cat CO							  **
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
 *	\date 21 Sep 2024
 */

 //______________________________________________________________________________
class CO
{
	private:

	protected:

	public:
	
		// Object types.
		enum class oType : coType_t {

			// The virtual base object
			coBase,

			// GE (Graphics Entities).
			geNull,
			geBase,
			geCoord,
			gePoint,
			geVector,
			geRef,
			geColor,

			// GP (Graphics Primitives).
			gpNull,
			gpBase,
			gpStroked,	// | These are layer GPs, i.e. GPs 
			gpFilled,	// | providing specific properties
			gpFonted,	// | to others GPS.
			gpScene,
			gpFrame,
			gpMaterial,
			gpPalette,
			gpPoint,
			gpLine,
			gpPolygon,
			gpBox,
			gpTube,
			gpCylinder,
			gpCone,
			gpSphere,
			gpLabel
			//131072,262144,524288, 1048576
			// GT (Graphics Tools).
		};

		// Default interface virtual public members.
		virtual oType type() const { return oType::coBase; }	//!< Returns CO type.
		virtual coVer_t version() const { return 0; }			//!< Returns CO version.
		virtual std::string stem() const { return ""; }			//!< Returns CO stem name.
		virtual void dump(const int & = 0) const {};			//!< Dumps CO data.

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
inline std::ostream& operator << (std::ostream& o, const cat::CO& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
