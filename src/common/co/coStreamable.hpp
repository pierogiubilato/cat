//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - CAT basic streamable object				  --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coStreamable.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"21 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once

// Overloading check
#ifndef catCoStreamable_HPP
#define catCoStreamable_HPP

// Standard library
#include <string>
//#include <deque>
//#include <iostream>
//#include <ostream>
#include <sstream>


// Application units.
#include "coAbc.hpp"


// #############################################################################
namespace cat { namespace co {

	//______________________________________________________________________________
	//! \brief The 'cat::co' class implements the basic CAT object traits. It is
	//!		mostly a virtual set of methods and properties, aiming at the smallest
	//!		footprint.
	class streamable : public abc
	{
		public:

			//! Dtor.
			streamable();
			
			//! Dtor.
			~streamable();


			//! Stream the object data.
			//! \brief Stream the object data to (write) / from (read) a stream.
			//! \argument 'read' is a boolean (default false) setting the stream
			//!		direction: write to the stream when false, read from the
			//!		stream when true.
			//! \return 0 if everything fine, a code error otherwise.
			//virtual int stream(std::stringstream& ss, const bool& read = false);

		protected:

	};


// #############################################################################
}}  // Close namespaces


// Overloading check
#endif