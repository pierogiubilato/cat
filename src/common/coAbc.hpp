//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic object abstract class			  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coAbc.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catCoAbc_HPP
#define catCoAbc_HPP

// Standard library
#include <vector>
#include <string>
#include <iostream>
//#include <ostream>
//#include <sstream>


// Application units.
//#include "../include/caf.hpp"    // Console IO formatting.




// #############################################################################
// Forward declarations of the class and the global friend function operator<< 
// to avoid the compiler preventing its definition within the namespaced class.
namespace cat {
	namespace co { 
		class abc;
	}
}
std::ostream& operator<<(std::ostream& os, const cat::co::abc& c);
// #############################################################################




// #############################################################################
namespace cat { namespace co {

	//! Simply define a name for a cat::co::ABc object ID within a set. The
	//! object ID is the index within the vector holding a family of object
	//! which identifies the objects, and can be replicated among different 
	//! trees (e.g. the client and server one).
	//! The cat::co::ID is consistent only within a family tree.
	typedef uint32_t ID;
	
	//__________________________________________________________________________
	//! \brief The 'cat::co::abc' class implements the basic CAT object traits. 
	//!		It is partiallya virtual set of methods and properties, aiming at 
	//!		the smallest footprint.
	class abc
	{
		public:

			//! Ctor.
			abc();

			//! Dtor.
			~abc();
			
			// -----------------------------------------------------------------
			// --						Basic properties					  --
			// -----------------------------------------------------------------

			//! Returns the object unique stem.
			//! \brief the state of the object
			enum class state : uint16_t {
				uninitialized = 0,
				modified = 1,
				abandoned = 2
			};

			//! Returns the object unique type.
				//! \brief Return the object tye, an unique integer identifying it 
				//!		among all the 'co' objects.
				//! \return a std::string containing the object unique stem.
			virtual uint32_t type() const {
				return (0);
			}

			//! Returns the object unique stem.
			//! \brief Return the object stem, i.e. an unique string identifying it 
			//!		among all the 'co' objects.
			//! \return a std::string containing the object unique stem.
			virtual std::string stem() const {
				return ("co");
			}

			//! Returns the object version.
			//! \brief Return the object stem, i.e. an unique string identifying it 
			//!		among all the 'co' objects.
			//! \return a uint16_t containing the object version.
			virtual uint16_t version() const {
				return (0);
			}
		
			//! Returns the object size in bytes.
			//! \brief Returns the complete (full static + full dynamic) allocated 
			//!		space for the object if \c dynamicOnly = false, which is the 
			//!		default call. If \c dynamic = true, it returns only the 
			//!		dynamically allocated space, without any contribution from the 
			//!		static part.
			//! \argument dynamicOnly is a bool (default false) which restrict the 
			//!		returned object size to the dynamically allocated part only.
			virtual size_t size(const bool& dynamicOnly = false) const {
				if (dynamicOnly) {
					return 0;
				} else {
					return sizeof(*this);
				}
			}

			//! Dump the object content into the console.
			//! \brief dump the  data content of the object into the console
			//! \return nothing.
			friend std::ostream& ::operator<<(std::ostream& os, const abc& c);
			
			//! Returns the object status.
			//! \brief Return the object stem, i.e. an unique string identifying it 
			//!		among all the 'co' objects.
			//! \return a uint16_t containing the object version.
			virtual state status() const {
				return _status;
			}


			// -----------------------------------------------------------------
			// --						Family tree							  --
			// -----------------------------------------------------------------

			//co* owner() const;					//!< Retrieves the owner pointer.
			//void owner(scene*);					//!< Sets the owner pointer.
			
			//! Retrieves the parent coID.
			//! \brief returns the parent of the object, if any.
			//! \return the cat::coID of the parent object within the family 
			//!		tree, 0 if there is no parent.
			ID parent() const;
			
			//! Sets the parent coID.
			//! \brief sets the object parent.
			//! \argument parent is a cat::coID of the parent object. the coID 
			//!		always refers to the current object family.
			//!	\return nothing.
			void parent(const ID& pID);
			
			//! Adds a child to the GP.
			int childAdd(const ID& cId);
			
			//! Deletes the child of handle cHnd from the GP.
			int childDel(const ID& cId);				
			
			//! Returns the object childs.
			std::vector<ID> childGet() const;
			
			//! Returns the number of childs.
			size_t childCount() const;

			// Return the self-ID.
			ID myID() const;

			// Return the self-pointer.
			abc* myPtr();


		protected:

			state _status;			//!< Current status.
			ID _parent;				//!< Parent (if any) within the same set.
			ID _ID;					//!< ID within the set it is included in.
			std::vector<ID> _child;	//!< Child(s) (if any).

	};


// #############################################################################
}} // Close namespaces


// Overloading check
#endif