//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic drawable object					  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coDrawable.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"21 Nov 2024"
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
			
			
			// -----------------------------------------------------------------
			// From cat::co::streamable
			// -----------------------------------------------------------------
			
			//! Stream the object data.
			//! \brief Stream the object data to (write) / from (read) a stream.
			//! \argument 'read' is a boolean (default false) setting the stream
			//!		direction: write to the stream when false, read from the
			//!		stream when true.
			//! \return 0 if everything fine, a code error otherwise.
			virtual int stream(std::stringstream& ss, const bool& read = false);




			//! Draw the object on the current viewport.
			//! \brief draw the object in the current viewport with the current
			//!		display settings.
			virtual void draw() const {}

			
		protected:

			

	};


// #############################################################################
}}  // Close namespaces


// Overloading check
#endif