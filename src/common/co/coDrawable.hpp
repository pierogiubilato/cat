//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic drawable object					  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coDrawable.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catCoDrawable_HPP
#define catCoDrawable_HPP

// Standard library
#include <string>
//#include <deque>
//#include <iostream>
//#include <ostream>
#include <sstream>


// Application units.
#include "coStreamable.hpp"


// #############################################################################
namespace cat { namespace co {

	//______________________________________________________________________________
	//! \brief The 'cat::drawable' class implements the basic CAT drawable object
	//!		traits. It is a virtual set of methods and properties.
	class drawable : public streamable
	{
		public:

			//! Ctor.
			drawable();

			//! Dtor.
			~drawable();
			
			//! Draw the object on the current viewport.
			//! \brief draw the object in the current viewport with the current
			//!		display settings.
			virtual void draw() const {
			
			}

			
		protected:

			

	};


// #############################################################################
}}  // Close namespaces


// Overloading check
#endif