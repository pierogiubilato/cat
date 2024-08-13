//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Cluster data object                          --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"cluster.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'cluster' object is a collection of 'pixels', plus a set of metric 
// properties (mass, position, etc...) derived by the pixels topology. The
// 'cluster' objects exploits the base 'data' object 'update' mechanism to
// optimize speed: when pixels are added or destroyed, by default 'cluster' 
// DOES NOT update its own properties, unless an 'update' method is invoked,
// to optimize the cluster building phase.
// In case, the 'selfUpdate' method, also inherited from the 'data' object, 
// may be used to make the 'cluster' updating at each 'pixel' operation.
//==============================================================================


#pragma once

// Overloading check
#ifndef cluster_HPP
#define cluster_HPP

// Application units.
#include "../include/pixel.hpp"

// Standard library
#include <string>
#include <vector>
#include <iostream>


//______________________________________________________________________________
namespace cat { class cluster; }
class cat::cluster : public cat::data
{

public:

	// Special members.
	cluster();					//!< Ctor.
	cluster(const pixel&);		//!< Single pixel ctor.
	cluster(const cluster&);	//!< CCtor.
	~cluster();					//!< Dtor.

	// Operators.
	cluster& operator=(const cluster&);

	// Friends.
	//friend std::ostream& operator<<(std::ostream&, cat::pixel&);
		
	// Overloaded base class methods.
	inline void update();		//!< Update the cluster properties and metrics.		

	// Cluster pixels.
	void add(const pixel&);		//!< Add a pixel to the cluster.
	
	// Cluster properties.
	inline float col() const;	//!< Retrieve x coordinate.
	inline float row() const;	//!< Retrieve y coordinate.
	inline int tsp() const;		//!< Retrieve timestamp.
	inline int mult() const;	//!< Retrieve multiplicity [px].
	inline int mass() const;	//!< Retrieve mass [px*s].
	inline int width() const;	//!< Retrieve width [px].
	inline int height() const;	//!< Retrieve height [px].
	inline int left() const;	//!< Retrieve multiplicity [px].
	inline int right() const;	//!< Retrieve width [px].
	inline int bottom() const;	//!< Retrieve height [px].
	inline int top() const;		//!< Retrieve height [px].


protected:

	// No protected at the moment

private:

	// Pixels.
	std::vector<cat::pixel> _pixel;
	
	// Cluster coordinates.
	float _col;		// x coordinate.
	float _row;		// y coordinate.
	int _tsp;		// timestamp.

	// CLuster bounding box.
	int _left;		// Leftmost pixel x coordinate.
	int _right;		// Rightmost pixel x coordinate.
	int _bottom;	// Bottom pixel y coordinate.
	int _top;		// Topmost pixel y coordinate.
	
	// Metrics.
	int _mult;		// Pixels count (multiplicity).
	int _mass;		// Mass (equal to multiplicity for digital pixels).
	int _width;		// Width in pixels.
	int _height;	// Height in pixels.
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::cluster&);

// Overloading check
#endif