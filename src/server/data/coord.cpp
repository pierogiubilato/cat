﻿//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - coord geometrical object                     --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coord.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [Date]	        "13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/coord.hpp"
#include "../include/caf.hpp"



// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
cat::coord::coord() : _x(0), _y(0), _z(0)
{
    /* Default ctor. */
}

//______________________________________________________________________________
cat::coord::coord(const float& x, const float& y, const float& z)
    : _x(x), _y(y), _z(z)
{
    /*! Coordinates ctor. */
}

//______________________________________________________________________________
cat::coord::coord(const cat::coord& p)
    : _x(p._x), _y(p._y), _z(p._z)
{
    /*! Copy ctor. */
}

//______________________________________________________________________________
cat::coord::~coord()
{
    /*! Dtor. Nothing really to do, all members are managed. */
}


// *****************************************************************************
// **                            Private members                              **
// *****************************************************************************


// *****************************************************************************
// **                           Operators overload                            **
// *****************************************************************************


//______________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const cat::coord& p)
{
    // Build (x, y, z) like string.
    os << "(" 
       << cat::caf::fcol(C_GEO_X) << p.x() << cat::caf::rst() 
       << ", "
       << cat::caf::fcol(C_GEO_Y) << p.y() << cat::caf::rst() 
       << ", "
       << cat::caf::fcol(C_GEO_Z) << p.z() << cat::caf::rst() 
       << ")";
    
    // Return.
    return os;
}


//______________________________________________________________________________
cat::coord& cat::coord::operator=(const cat::coord& p)
{
    /*! Copy operator. */
    
    
    // Object data copy.
    _x = p._x;
    _y = p._y;
    _z = p._z;

    // Return.
    return *this;
}



// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************


//______________________________________________________________________________
float cat::coord::x() const
{
    /* Returns the coord x coordinate. */
    return _x;
}


//______________________________________________________________________________
void cat::coord::x(const float& x)
{
    /* Set the x coordinate. */
    _x = x;
}


//______________________________________________________________________________
float cat::coord::y() const
{
    /* Returns the y coordinate. */
    return _y;
}


//______________________________________________________________________________
void cat::coord::y(const float& y)
{
    /* Set the y coordinate. */
    _y = y;
}


//______________________________________________________________________________
float cat::coord::z() const
{
    /* Returns the z coordinate. */
    return _z;
}


//______________________________________________________________________________
void cat::coord::z(const float& z)
{
    /* Set the z coordinate. */
    _z = z;
}