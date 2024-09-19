//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - coord geometrical object                     --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coord.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'coord' object represents a coord in 3D space, in float precision.
// It provides standard methods to manage it as a standard data type.
//==============================================================================


#pragma once

// Overloading check
#ifndef coord_HPP
#define coord_HPP

// Standard library
#include <iostream>

//______________________________________________________________________________
namespace cat { class coord; }
class cat::coord 
{

public:

	// Special members.
	coord();				//!< Ctor.
	coord(const float&, const float&, const float&);
	coord(const coord&);	//! CCtor.
	~coord();				//!< Dtor.

	// Operators.
	coord& operator=(const coord&);

	// Friends.
	//friend std::ostream& operator<<(std::ostream&, cat::pixel&);
		
	// Methods.
	inline float x() const;			//!< Retrieve x coordinate.
	inline void x(const float&);	//!< Set x coordinate.
	inline float y() const;			//!< Retrieve y coordinate.
	inline void y(const float&);	//!< Set y coordinate.
	inline float z() const;			//!< Retrieve z coordinate.
	inline void z(const float&);	//!< Set z coordinate.

protected:

	// Data.
	float _x;		// x coordinate.
	float _y;		// y coordinate.
	float _z;		// z coordinate..
			
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::coord&);

// Overloading check
#endif