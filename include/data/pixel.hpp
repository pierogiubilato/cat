//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Pixel data object                            --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"pixel.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"14 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'pixel' object represents a sensor pixel, with its logical coordinates
// (col, row) and timestamp (tsp). It provides basic object capabilities, 
// including copy construction, assignment and ostream operators overload.
//==============================================================================


#pragma once

// Overloading check
#ifndef pixel_HPP
#define pixel_HPP

// Application units
#include "../include/data.hpp"


// Standard library
#include <iostream>


//______________________________________________________________________________
namespace cat { class pixel; }
class cat::pixel : public cat::data
{

public:

	// Special members.
	pixel();				//!< Ctor.
	pixel(const int&, const int&, const int& = 0);
	pixel(const pixel&);	//! CCtor.
	~pixel();				//!< Dtor.

	// Operators.
	pixel& operator=(const pixel&);

	// Friends.
	//friend std::ostream& operator<<(std::ostream&, cat::pixel&);
		
	// Methods.
	inline int col() const;			//!< Retrieve x coordinate.
	inline void col(const int&);	//!< Set x coordinate.
	inline int row() const;			//!< Retrieve y coordinate.
	inline void row(const int&);	//!< Set y coordinate.
	inline long tsp() const;		//!< Retrieve time.
	inline void tsp(const long&);	//!< Set time.

protected:

	// No protected at the moment

private:

	// Pivot structures.
	int _col;		// Pixel matrix x coordinate (0 to n-1).
	int _row;		// Pixel matrix y coordinate (0 to m-1).
	long _tsp;		// Pixel timestamp.
			
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::pixel&);

// Overloading check
#endif