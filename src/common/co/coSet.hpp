//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT objects container						  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coSet.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"23 Nov 2024"
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
			

			//! Add an object.
			//! \brief dump the  data content of the object into the console
			//! \return nothing.
			void add(cat::co::abc&);

			//! Dump the object content into the console.
			//! \brief dump the  data content of the object into the console
			//! \return nothing.
			friend std::ostream& ::operator<<(std::ostream& os, const set& c);
		
	private:

			//! The linear vector containing all the objects.
			std::vector<cat::co::abc*> _obj;

	};


// #############################################################################
}}  // Close namespaces


// Overloading check
#endif