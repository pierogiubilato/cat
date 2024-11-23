//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic object abstract class			  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coAbc.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"23 Nov 2024"
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
#include <typeinfo>
#include <typeindex>
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
// Forward declarations of the container class cat::co::set, which is given as
// reference to any new object for the ownership.
namespace cat {
	namespace co {
		class set;
	}
}
// #############################################################################


// #############################################################################
namespace cat { namespace co {

	//! Simply define a name for a cat::co::ABc object ID within a set. The
	//! object ID is the index within the vector holding a family of objects,
	//! which identifies the objects, and can be replicated among different 
	//! containers (e.g. the client and server one).
	//! The cat::co::ID_t is consistent only within synchronized containers.
	typedef uint32_t ID_t;
	
	//! Object type unique identifier. Used mostly for object creation. This
	//! is used instead of a more modern std::type_info and/or std::type_index
	//! to ensure consistent width between different system/compilers when 
	//! streaming the object across different domains.
	typedef uint32_t type_t;

	//! Object version. Used mostly for streams verification when loading
	//! data from another object of the same type.
	typedef uint32_t version_t;


	//__________________________________________________________________________
	//! \brief The 'cat::co::abc' class implements the basic CAT object traits. 
	//!		It is partially a virtual set of methods and properties, aiming at 
	//!		the smallest footprint.
	class abc
	{
		public:

			//! Friend classes
			friend cat::co::set;
			
			//! Default Ctor.
			//! \brief containerless constructor. Used only for stand-alone
			//!		objects.
			abc();
			
			//! Container Ctor.
			//! \brief Creates a new cat::co::abc object with information 
			//!		about the container it has been stored into. The new object 
			//!		will communicate to the owner container its state changes, 
			//!		and other events as well.
			//! \argument 'set' is the reference to a cat::co:set container 
			//!		object, which the new object will become an element.
			//! \argument 'id' is the unique index of the object within the 
			//!		'set' container, guaranteed to not change for the entire
			//!		life of the object.
			//abc(set* set, const ID_t& id);

			//! Dtor.
			~abc();
			
			// -----------------------------------------------------------------
			// --						Basic properties					  --
			// -----------------------------------------------------------------

			//! Returns the object unique stem.
			//! \brief the state of the object
			enum class state : uint16_t {
				uninitialized = 0,
				unchanged = 1,
				modified = 2,
				abandoned = 3
			};

			//! Returns the object unique type.
			//! \brief Return the object tye, an unique integer identifying it 
			//!		among all the 'co' objects.
			//! \return a std::string containing the object unique stem.
			virtual type_t type() const {
				return (0);
			}

			//! Returns the object version.
			//! \brief Return the object stem, i.e. an unique string identifying it 
			//!		among all the 'co' objects.
			//! \return a uint16_t containing the object version.
			virtual version_t version() const {
				return (1);
			}

			//! Returns the object unique stem.
			//! \brief Return the object stem, i.e. an unique string identifying it 
			//!		among all the 'co' objects.
			//! \return a std::string containing the object unique stem.
			//virtual std::string stem() const {
			//	return ("co");
			//}

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

			//! Stream the object data.
			//! \brief Stream the object data to (write) / from (read) a stream.
			//! \argument 'read' is a boolean (default false) setting the stream
			//!		direction: write to the stream when false, read from the
			//!		stream when true.
			//! \return 0 if everything fine, a code error otherwise.
			virtual int stream(std::stringstream& ss, const bool& read = false);


			// -----------------------------------------------------------------
			// --						Family tree							  --
			// -----------------------------------------------------------------

			//co* owner() const;					//!< Retrieves the owner pointer.
			//void owner(scene*);					//!< Sets the owner pointer.
			
			//! Retrieves the parent coID.
			//! \brief returns the parent of the object, if any.
			//! \return the cat::coID of the parent object within the family 
			//!		tree, 0 if there is no parent.
			ID_t parent() const;
			
			//! Sets the parent coID.
			//! \brief sets the object parent.
			//! \argument parent is a cat::coID of the parent object. the coID 
			//!		always refers to the current object family.
			//!	\return nothing.
			void parent(const ID_t& pId);
			
			//! Adds a child to the GP.
			int childAdd(const ID_t& cId);
			
			//! Deletes the child of handle cHnd from the GP.
			int childDel(const ID_t& cId);				
			
			//! Returns the object childs.
			std::vector<ID_t> childList() const;
			
			//! Returns the number of childs.
			size_t childCount() const;

			// Return the self-pointer.
			abc* ptr();

			// Return the self-pointer, constant version.
			const abc* ptrConst() const;

		protected:

			// Owner-related.
			set* _owner;				//!< Pointer to the owner container.
			ID_t _oId;					//!< ID within the owner the object is included in.
			state _status;				//!< Current status.
			
			// Family tree.
			ID_t _parent;				//!< Parent (if any) within the same set.
			std::vector<ID_t> _child;	//!< Child(s) (if any).

		private:

			// -----------------------------------------------------------------
			// --						Container related					  --
			// -----------------------------------------------------------------

			//! Return the owner.
			//! \brief returns a pointer to the containe owning the object, if 
			//!		any. If there is no owner container, returns a nullptr.
			//! \return	the pointer to the owner if any, a nullptr if there is 
			//!		no owner.
			set* owner() const;

			//! Return the container-referred ID.
			//! \brief reurn the ID used by the container to identify the object.
			//!		if there is no owner container, returns 0.
			//! \return	the owner container ID, 0 if there is no owner.
			ID_t id() const;

	};


// #############################################################################
}} // Close namespaces


// Overloading check
#endif