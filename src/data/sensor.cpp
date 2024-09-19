//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Sensor data object                          --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"cluster.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [Date]	        "13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/sensor.hpp"
#include "../include/caf.hpp"


// Use standard namespace:
//using namespace std;


// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
cat::sensor::sensor(const int& cs, const int& rs, const float& cp, const float& rp) : 
    data(), 
    _cols(cs), _rows(rs),
    _colPitch(cp), _rowPitch(rp),
    _pos(0, 0, 0)
{
    /* Default ctor. Makes mandatory to initialize the sensor columns and rows 
       count, as well as the pixel width and height.
    */
}



//______________________________________________________________________________
cat::sensor::sensor(const sensor& sr) : 
    data(sr), 
    _cols(sr._cols), _rows(sr._rows),
    _colPitch(sr._colPitch), _rowPitch(sr._rowPitch),
    _pos(sr._pos)
{
    /*! Copy ctor. */
}


//______________________________________________________________________________
cat::sensor::~sensor()
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
cat::sensor& cat::sensor::operator=(const cat::sensor& sr)
{
    /*! Copy operator. */

    // properties.
    _cols = sr._cols;
    _rows = sr._rows;
    _colPitch= sr._colPitch;
    _rowPitch = sr._rowPitch;
    
    // Position.
    _pos = sr._pos;

    // Clusters collection.
    _cluster = sr._cluster;

    // Return.
    return *this;
}


//______________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const cat::sensor& sr)
{
    // Build (x, y, z, t) like string.
    os << "[(";
    if (!sr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_COL) << sr.cols() << cat::caf::rst() << ", ";
    if (!sr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_ROW) << sr.rows() << cat::caf::rst() << ") - <";
    if (!sr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_COL) << sr.colPitch() << cat::caf::rst() << ",";
    if (!sr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_ROW) << sr.rowPitch() << cat::caf::rst() << "> - ";
    if (!sr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << sr.pos() << cat::caf::rst() << "> - ";

    // Return.
    return os;
}




// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************


//______________________________________________________________________________
int cat::sensor::cols() const
{
    /* Returns the sensor columns count. */
    return _cols;
}


//______________________________________________________________________________
int cat::sensor::rows() const
{
    /* Returns the sensor columns rows. */
    return _rows;
}


//______________________________________________________________________________
float cat::sensor::colPitch() const
{
    /* Returns the sensor column pitch (pixel width). */
    return _colPitch;
}


//______________________________________________________________________________
float cat::sensor::rowPitch() const
{
    /* Returns the sensor row pitch (pixel height). */
    return _rowPitch;
}


// _____________________________________________________________________________
cat::coord cat::sensor::pos() const
{
    /* Returns the sensor posiiton in a plane. */
    return _pos;
}


// _____________________________________________________________________________
void cat::sensor::pos(const cat::coord& p)
{
    /* Set the sensor position in a plane. */
    _pos = p;
}


// _____________________________________________________________________________
void cat::sensor::clAdd(const cat::cluster& cl)
{
    /* Add a cluster to the sensor. */
    _cluster.push_back(cl);
}

// _____________________________________________________________________________
long cat::sensor::clCount() const
{
    /* Retrieve how many cluster into a sensor. */
    return (long) _cluster.size();
}