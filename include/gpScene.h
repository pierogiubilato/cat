//------------------------------------------------------------------------------
// CAT Graphic Primitive Scene class						                  --
// (C) Piero Giubilato 2021-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpScene.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"09 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined gpScene_H
#define gpScene_H

// Application Components
#include "gp.h"


// #############################################################################
namespace cat { namespace gp {

//! Scene graphic primitive
/*! cat::gp::scene is a special graphic primitive (GP) intended to represent
	a scene, i.e. a collection of othe GPs. It provides GP collection as well 
	as family relationships management between collected GPs.

	\author Piero Giubilato
	\version 1.3
	\date 21 Sep 2024
*/
//______________________________________________________________________________
class scene: public GP
{
	private:   
		
		// GPs management
		std::vector<GP*> _scene;				// The GP's pointers list.
		Uint64 _count;							// The actual number of active GPs.
			
	protected:
	
	public:
		
		// Special members.
		scene();			//!< Ctor.
		~scene();			//!< Dtor.
		
		// Default access public members overload.
		oType type() const;						//!< Returns GP type.
		Uint64 version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const Uint64& ind = 0) const;	//!< Dumps GP data.
		
		//! Stream the GP data (both read and write).
		bool stream(std::stringstream& o, const bool& read = false);
	   		
		// Specific scene management.
		void clear();								//!< Clear the scene from all GPs.
		
		// GPs management.
		GPHnd gpAdd(GP* gp, const GPHnd& = 0);	//!< Adds a graphic primitive.
		GPHnd gpAdd(std::stringstream&);		//!< Adds a graphic primitive by a stream.
		void gpDel(const GPHnd&);				//!< Deletes a graphic primitive.
		GPHnd gpCount() const;					//!< Count all active GPs in the scene.
		size_t gpSize() const;					//!< Returns the size of the GPs vector.	
		GP* gpGet(const GPHnd&) const;			//!< Retrieves a GP from its handle.
		GP* operator [] (const GPHnd&) const;	//!< Retrieves a GP from its handle.

		// Drawing and UI functions are ONLY defined for the SERVER side!
		// --------------------------------------------------------------
		#ifdef CAT_SERVER
			
			// UI interaction.
			virtual void uiBarLoad(ui::Bar&);	//!< Load a bar with the scene GPs list.	
		#endif
};

// #############################################################################
}} // Close namespace



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::scene& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Scene. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif