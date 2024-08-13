//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Basic data object                            --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"data.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'data' object is the base class for data objects. It embeds the update
// trait only, to check whether an object is up-tp-date or not. It also carries
// the autoUpdate properties, which enables childs to implement self-update 
// behaviors if needed.
//==============================================================================

#pragma once

// Overloading check
#ifndef data_HPP
#define data_HPP

// Standard library
#include <string>
#include <iostream>


//______________________________________________________________________________
namespace cat { class data; }
class cat::data
{

public:

	// Special members.
	data();				//!< Ctor.
	data(const data&);	//! CCtor.
	~data();				//!< Dtor.

	// Operators.
	data& operator=(const data&);

	// Friends.
	//friend std::ostream& operator<<(std::ostream&, cat::pixel&);
		
	// Methods.
	void update();				//!< Se the object as updated.
	void setAuto(const bool&);	//!< Se the object self-updating status.
	bool isUp() const;			//!< Retrieve updated status.
	bool isAuto() const;		//!< Retrieve updated status.



protected:

	// Object status.
	bool _updated;
	bool _autoUpdate;
};


// Overloading check
#endif