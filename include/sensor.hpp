//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Sensor data object                           --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"sensor.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


//==============================================================================
// The 'sensor' object stores the informations of a specific sensor (chip),
// including columns, rows, and pixel size, plus other practical data. It holds
// a 'cluster' collection of logical clusters, plus its position relative to the
// 'plane' it belongs to.
//==============================================================================


#pragma once

// Overloading check
#ifndef sensor_HPP
#define sensor_HPP

// Application units.
#include "../include/cluster.hpp"
#include "../include/point.hpp"

// Standard library
#include <vector>



//______________________________________________________________________________
namespace cat { class sensor; }
class cat::sensor: public cat::data
{

public:

	// Special members.
	sensor(const int&, const int&, const float&, const float&);	//!< Ctor.
	sensor(const sensor&);		//!< CCtor.
	~sensor();					//!< Dtor.

	// Operators.
	sensor& operator=(const sensor&);

	
	// Sensors properties.
	inline int cols() const;		//!< Retrieve the number of columns.
	inline int rows() const;		//!< Retrieve the number of rows.
	inline float colPitch() const;	//!< Retrieve the pixel column pitch [arb].
	inline float rowPitch() const;	//!< Retrieve the pixel row pitch [arb].

protected:

	// No protected at the moment

private:

	// Logical dimensions coordinates.
	int _cols;			// Columns count.
	int _rows;			// Rows count.
	
	// Physical dimensions.
	float _colPitch;	// Columns pitch.
	float _rowPitch;	// Rows pitch.

	// Physical position.
	point _pos;			// position (matrix 0, 0 corner).
	
	// Cluster collection.
	std::vector<cluster> _cluster;
};

//______________________________________________________________________________
// Operators overload
std::ostream& operator<<(std::ostream&, const cat::sensor&);

// Overloading check
#endif