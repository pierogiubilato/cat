//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT objects container						  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coSet.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"24 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catCoSet_HPP
#define catCoSet_HPP

// Standard library
#include <vector>
#include <string>

//#include <ostream>
#include <sstream>


// Application units.
#include "coAbc.hpp"


// #############################################################################
// Forward declarations of the class and the global friend function operator<< 
// to avoid the compiler preventing its definition within the namespaced class.
namespace cat {
	namespace co {
		class set;
	}
}
std::ostream& operator<<(std::ostream& os, const cat::co::set& c);
// #############################################################################

// #############################################################################
namespace cat { namespace co {

	//__________________________________________________________________________
	//! \brief The 'cat::coSet' is a container for cat::co objects. It provides
	//! streaming and synchronization between sets.
	class set
	{
		public:

			//! Ctor.
			set();

			//! Dtor.
			~set();
			

			// -----------------------------------------------------------------
			// --						Objects access						  --
			// -----------------------------------------------------------------


			//! Add an object.
			//! \brief add an object to the container.
			//! \return nothing.
			void add(cat::co::abc*);

			//! Delete an object.
			//! \brief delete an object from the container
			//! \argument 'ptr' is a pointer to an object.
			//! \return 0 if successful, an error code otherwise.
			int del(cat::co::abc* ptr);

			//! Delete an object.
			//! \brief delete an object from the container
			//! \argument 'id' is the object id within the container.
			//! \return 0 if successful, an error code otherwise.
			int del(const cat::co::ID_t& ptr);

			//! Gen an object.
			//! \brief get an object pointer by issuing its ID.
			//! \return a pointer to the object if it exists, a nullptr otherwise.
			abc* get(const cat::co::ID_t&) const;
			
			//! Get an object.
			//! \brief get an object ID by issuing its pointer.
			//! \return the object ID if it exists, 0 otherwise.
			ID_t get(const cat::co::abc*) const;

			//! Dump the object content into the console.
			//! \brief dump the  data content of the object into the console
			//! \return nothing.
			friend std::ostream& ::operator<<(std::ostream& os, const set& c);


			// -----------------------------------------------------------------
			// --					Container(s) operations					  --
			// -----------------------------------------------------------------

			//! Clear the container.
			//! \brief Deletes all objects from the container. If the 'del'
			//!		argument is set to true (default), also deletes the objects 
			//!		themselves.
			//! \argument the 'del' bool, if true, actually delete all the 
			//!		objects being owned by the container.
			//! \return 0 if everything right, an error code otherwise.
			int clear(const bool& del = true);

			int pushTo(set* target) const;
			
			int pullFrom(set* source);


		
	private:

			//! The linear vector containing all the objects.
			std::vector<cat::co::abc*> _obj;

			//! The list of latest modifications.
			std::vector<size_t> _objModified;


	};


// #############################################################################
}}  // Close namespaces


// Overloading check
#endif