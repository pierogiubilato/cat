//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Hit data object                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"hit.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"14 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'hit' object represents a particle hit position in space (x, y, t) and
// time (t). It provides a reference link to the originating cluster, to be
// used if needed.
//==============================================================================


#pragma once

// Overloading check
#ifndef hit_HPP
#define hit_HPP

// Application units
#include "../include/data.hpp"
#include "../include/coord.hpp"
#include "../include/cluster.hpp"

// Standard library
#include <iostream>


//______________________________________________________________________________
namespace cat { class hit; }
class cat::hit : public cat::data, public cat::coord
{

public:

	// Special members.
	hit();					//!< Ctor.
	hit(const coord&, const long&);
	hit(const cluster&);	//!< Cluster Ctor.
	hit(const hit&);		//!< CCtor.
	~hit();					//!< Dtor.

	// Operators.
	hit& operator=(const hit&);

	// Inherited overloaded methods.
	//bool isUp() const;
	

	// Methods.
	const cluster* cluster() const;		//!< Pointer to the originating cluster. MAY BE VOID, CHECK!.
	void cluster(const cat::cluster&);	//!< Set a cluster reference for the hit.
	long t() const;					//!< Retrieve the hit time.
	void t(const long&);			//!< Set the hit time.

protected:

	// No protected at the moment

private:

	// Pivot structures.
	long _t;						// Hit time.
	const cat::cluster* _cluster;	// Possible link to the originating cluster.
				
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::pixel&);

// Overloading check
#endif