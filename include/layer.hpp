//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Layer data object                           --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"layer.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'layer' object stores the informations of a specific layer (chip),
// including columns, rows, and pixel size, plus other practical data. It holds
// a 'cluster' collection of logical clusters, plus its position relative to the
// 'plane' it belongs to.
//==============================================================================


#pragma once

// Overloading check
#ifndef layer_HPP
#define layer_HPP

// Application units.
#include "../include/sensor.hpp"
#include "../include/plane.hpp"

// Standard library
#include <vector>



//______________________________________________________________________________
namespace cat { class layer; }
class cat::layer: public cat::data
{

public:

	// Special members.
	layer(const sensor&, const plane&);	//!< Ctor.
	layer(const layer&);			//!< CCtor.
	~layer();						//!< Dtor.

	// Operators.
	layer& operator=(const layer&);
		
	// layers properties.
	int cols() const;		//!< Retrieve the number of columns.
	int rows() const;		//!< Retrieve the number of rows.
	float colPitch() const;	//!< Retrieve the pixel column pitch [arb].
	float rowPitch() const;	//!< Retrieve the pixel row pitch [arb].

	// Sensors.
	cat::sensor& sensor(const int& = 0); //!< Handle to a layer sensor.	
	const std::vector<cat::sensor>& sensors() const; //!< Handle to a sensor vector (for convenience, enforced cost).	
	void srAdd(const cat::sensor&);	//!< Add a sensor to the layer.
	long srCount() const;			//!< Returns how many sensors in the layer.	

	// Plane in space.
	const cat::plane& plane() const;		//!< reference to the layer plane in space.
	
	// Hits.


	
protected:

	// No protected at the moment

private:

	// Sensor collection.
	std::vector<cat::sensor> _sensor;
	
	// Physical plane.
	cat::plane _plane;

	// Hits.
	
	
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::layer&);

// Overloading check
#endif