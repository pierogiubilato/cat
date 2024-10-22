//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - plane geometrical object                     --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"plane.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'plane' object represents a plane in 3D space, through a reference point
// given by the 'pos' method, and an orientation (normal vector) 'norm' which
// origin is in the 'pos' position.
//==============================================================================


#pragma once

// Overloading check
#ifndef plane_HPP
#define plane_HPP

// Application units
#include "../include/coord.hpp"

// Standard library
#include <iostream>

//______________________________________________________________________________
namespace cat { class plane; }
class cat::plane 
{

public:

	// Special members.
	plane();				//!< Ctor.
	plane(const coord&, const coord&);  //!< Ctor.
	plane(const plane&);	//! CCtor.
	~plane();				//!< Dtor.

	// Operators.
	plane& operator=(const plane&);

	// Methods.
	coord pos() const;		//!< Retrieve plane reference point in space.
	void pos(const coord&);	//!< Set plane position in space.
	coord norm() const;		//!< Retrieve plane normal vector.
	void norm(const coord&);//!< Set plane normal vector.
	
protected:

	// Data.
	coord _pos;				// Plane position in space.
	coord _norm;			// Plane orientation )normal vector) in space.
				
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::plane&);

// Overloading check
#endif