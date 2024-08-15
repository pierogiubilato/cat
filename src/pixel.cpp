//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Pixel data object                            --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [Date]	        "13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/pixel.hpp"
#include "../include/caf.hpp"


// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
cat::pixel::pixel() 
    : cat::data(), 
    _col(0), _row(0), _tsp(0)
{
    /* Default ctor. */
}

//______________________________________________________________________________
cat::pixel::pixel(const int& c, const int& r, const int& t) 
    : cat::data(), 
    _col(c), _row(r), _tsp(t)
{
    /*! Coordinates and time ctor. */
}

//______________________________________________________________________________
cat::pixel::pixel(const cat::pixel& px)
    : cat::data(px),
    _col(px._col), _row(px._row), _tsp(px._tsp)
{
    /*! Copy ctor. */
}

//______________________________________________________________________________
cat::pixel::~pixel()
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
std::ostream& operator<<(std::ostream& os, const cat::pixel& px)
{
    // Build (x, y, t) like string.
    os << "(" 
       << cat::caf::fcol(C_PX_COL) << px.col() << cat::caf::rst() 
       << ", "
       << cat::caf::fcol(C_PX_ROW) << px.row() << cat::caf::rst() 
       << ", "
       << cat::caf::fcol(C_PX_TSP) << px.tsp() << cat::caf::rst() 
       << ")";
    
    // Return.
    return os;
}


//______________________________________________________________________________
cat::pixel& cat::pixel::operator=(const cat::pixel& px)
{
    /*! Copy operator. */
    data::operator=(px);
    
    // Object data copy.
    _col = px._col;
    _row = px._row;
    _tsp = px._tsp;

    // Return.
    return *this;
}



// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************


//______________________________________________________________________________
int cat::pixel::col() const
{
    /* Returns the column coordinates.
       Matrix coordinates are integer, starting from (0,0) to the sensor
       matrix size (n-1, m-1).
    */
    return _col;
}


//______________________________________________________________________________
void cat::pixel::col(const int& c)
{
    /* Set the column coordinate.
       Matrix coordinates are integer, starting from (0,0) to the sensor
       matrix size (n-1, m-1).
    */
    _col = c;
}


//______________________________________________________________________________
int cat::pixel::row() const
{
    /* Returns the row coordinate.
       Matrix coordinates are integer, starting from (0,0) to the sensor
       matrix size (n-1, m-1).
    */
    return _row;
}


//______________________________________________________________________________
void cat::pixel::row(const int& row)
{
    /* Set the row coordinate.
       Matrix coordinates are integer, starting from (0,0) to the sensor
       matrix size (n-1, m-1).
    */
    _row = row;
}


//______________________________________________________________________________
long cat::pixel::tsp() const
{
    /* Returns timestamp. */
    return _tsp;
}


//______________________________________________________________________________
void cat::pixel::tsp(const long& t)
{
    /* Set the timestamp. */
    _tsp = t;
}
