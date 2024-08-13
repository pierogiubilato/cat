//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Cluster data object                          --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"cluster.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [Date]	        "13 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/cluster.hpp"
#include "../include/caf.hpp"


// Use standard namespace:
//using namespace std;


// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
cat::cluster::cluster() : 
    data(), 
    _col(0), _row(0), _tsp(0),
    _mult(0), _mass(0),
    _left(0), _right(0), _bottom(0), _top(0),
    _width(0), _height(0)
{
    /* Default ctor. */
}



//______________________________________________________________________________
cat::cluster::cluster(const cat::pixel& px) : 
    data(),
    _col((float)px.col() + 0.5f), _row((float)px.row() + 0.5f),  _tsp(px.tsp()),
    _mult(1), _mass(1), 
    _left(px.col()), _right(px.col()), _bottom(px.row()), _top(px.row()),
    _width(1), _height(1)
{
    /*! Single pixel ctor. */
    _pixel.push_back(px);
}


//______________________________________________________________________________
cat::cluster::cluster(const cluster& cl) : 
    data(cl), 
    _col(cl._col), _row(cl._row), _tsp(cl._tsp),
    _mult(cl._mult), _mass(cl._mass),
    _left(cl._left), _right(cl._right), _bottom(cl._bottom), _top(cl._top),
    _width(cl._width), _height(cl._height)
{
    /*! Copy ctor. */
}


//______________________________________________________________________________
cat::cluster::~cluster()
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
cat::cluster& cat::cluster::operator=(const cat::cluster& cl)
{
    /*! Copy operator. */


    // Object data copy.
    _col = cl._col;
    _row = cl._row;
    _tsp = cl._tsp;
    
    _mult = cl._mult;
    _mass = cl._mass;
    
    _left = cl._left;
    _right = cl._right;
    _bottom = cl._bottom;
    _top = cl._top;

    _width = cl._width;
    _height = cl._height;


    // Return.
    return *this;
}


//______________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const cat::cluster& cl)
{
    // Build (x, y, z, t) like string.
    os << "(";
    if (!cl.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_COL) << cl.col() << cat::caf::rst() << ", ";
    if (!cl.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_ROW) << cl.row() << cat::caf::rst() << ", ";
    if (!cl.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << cat::caf::fcol(C_CL_TSP) << cl.tsp() << cat::caf::rst() << ")";

    // Return.
    return os;
}




// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************

//______________________________________________________________________________
void cat::cluster::update()
{
    /* Update the cluster properties and metrics. */
    if (_pixel.empty()) return;

    // Calculate the cluster position, width and height.
    _col = 0;
    _row = 0;
    _mass = 0;
    _mult = (int)_pixel.size();
    
    _tsp = _pixel[0].tsp();
    
    _width = 0;
    _height = 0;
    _left = _pixel[0].col();
    _right = _pixel[0].col();
    _bottom = _pixel[0].row();
    _top = _pixel[0].row();

    // Loop over all the cluster pixels.
    for (auto& px : _pixel) {
        
        // Position.
        _col += px.col();
        _row += px.row();
        _mass++;

        // Timestamp.
        if (px.tsp() < _tsp) _tsp = px.tsp() < _tsp;
        
        // Bounding box.
        if (px.col() < _left) _left = px.col();
        if (px.col() > _right) _right = px.col();
        if (px.row() < _bottom) _bottom = px.row();
        if (px.row() > _top) _top = px.row();
    }

    // Derives cluster x,y position, in matrix floating coordinates.
    // Here it a single pixel of matrix coordinates (x, y) is considered to
    // have (x + 0.5, y + 0.5) matrix coordinates.
    _col = (float)(_col / _mass) + 0.5f;
    _row = (float)(_row / _mass) + 0.5f;

    // Width and height.
    _width = _right - _left + 1;
    _height = _top - _bottom + 1;

    // Confirm update.
    data::_updated = true;
}


//______________________________________________________________________________
void cat::cluster::add(const pixel& px)
{
    /* Add a pixel to the cluster. */
    _pixel.push_back(cat::pixel(px));

    // Now the cluster has changed.
    if (data::_autoUpdate) {
        update();
    } else {
        data::_updated = false;
    }
}


//______________________________________________________________________________
float cat::cluster::col() const
{
    /* Returns the cluster column (floating) coordinate. */
    return _col;
}


//______________________________________________________________________________
float cat::cluster::row() const
{
    /* Returns the cluster row (floating) coordinate. */
    return _row;
}

//______________________________________________________________________________
int cat::cluster::tsp() const
{
    /* Returns cluster timestamp. */
    return _tsp;
}

//______________________________________________________________________________
int cat::cluster::mult() const
{
    /* Returns cluster multiplicity. */
    return _mult;
}

//______________________________________________________________________________
int cat::cluster::mass() const
{
    /* Returns cluster width [px]. */
    return _mass;
}

//______________________________________________________________________________
int cat::cluster::left() const
{
    /* Returns cluster leftmost matrix coordinate [px]. */
    return _left;
}

//______________________________________________________________________________
int cat::cluster::right() const
{
    /* Returns cluster rightmost matrix coordinate [px]. */
    return _right;
}

//______________________________________________________________________________
int cat::cluster::bottom() const
{
    /* Returns cluster bottom  matrix coordinate [px]. */
    return _bottom;
}

//______________________________________________________________________________
int cat::cluster::top() const
{
    /* Returns cluster top matrix coordinate [px]. */
    return _top;
}

//______________________________________________________________________________
int cat::cluster::width() const
{
    /* Returns cluster width [px]. */
    return _width;
}

//______________________________________________________________________________
int cat::cluster::height() const
{
    /* Returns cluster height [px]. */
    return _height;
}