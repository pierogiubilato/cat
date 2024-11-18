//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic interface object					  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"interface.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"16 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catUiButton_HPP
#define catUiButton_HPP

// Standard library
#include <string>
//#include <deque>
//#include <iostream>
//#include <ostream>
#include <sstream>


// Application units.
#include "uiAbc.hpp"


// #############################################################################
namespace cat {

	namespace ui {
	
		//______________________________________________________________________________
		//! \brief The 'cat::co' class implements the basic CAT object traits. It is
		//!		mostly a virtual set of methods and properties, aiming at the smallest
		//!		footprint.
		class button: public cat::ui::abc
		{
		public:

			//! Ctor.
			button();

			//! Dtor.
			~button();

			//! DEBUG Callback.
			//! \brief aaaaaaaaaaaaa.
			//! \argument 'aaaa'
			//! \return 0 if everything fine, a code error otherwise.
			int callback() {
				return 0;
			}

		protected:

		};


	// #############################################################################
	}  // Close namespace

// #############################################################################
}  // Close namespace


// Overloading check
#endif