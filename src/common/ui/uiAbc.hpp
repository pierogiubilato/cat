//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic user interface abstract class	  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiAbstract.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catUiAbc_HPP
#define catUiAbc_HPP

// Standard library
#include <string>
//#include <deque>
//#include <iostream>
//#include <ostream>
#include <sstream>


// Application units.
#include "coDrawable.hpp"


// #############################################################################
namespace cat {

	namespace ui {
	
	//__________________________________________________________________________
	//! \brief The 'cat::ui::abc' is the abstract base class for the basic CAT 
	//!		user interface object traits. It is	mostly a virtual set of methods 
	//!		and properties.
	class abc : public cat::co::drawable
	{
		public:

			// Ctor.
			abc();

			//! Dtor.
			~abc();

			//! DEBUG Callback.
			//! \brief aaaaaaaaaaaaa.
			//! \argument 'aaaa'
			//! \return 0 if everything fine, a code error otherwise.
			virtual int callback() {
				return 0;
			}

		protected:

	};


	// #########################################################################
	}  // Close namespace

// #############################################################################
}  // Close namespace


// Overloading check
#endif