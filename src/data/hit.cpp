//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - hit data object                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [Date]	        "14 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/hit.hpp"
#include "../include/caf.hpp"



// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
cat::hit::hit() :
    cat::data(), 
    cat::coord(),
    _t(0),
    _cluster(NULL)
{
    /* Default ctor. */
}

//______________________________________________________________________________
cat::hit::hit(const coord& p, const long& t) :
    cat::data(), 
    cat::coord(p),
    _t(t),
    _cluster(NULL)
{
    /*! Coordinates and time ctor. */
}

//______________________________________________________________________________
cat::hit::hit(const cat::cluster& cl) :
    cat::data(), 
    cat::coord(cl.col(), cl.row(), 0),
    _t(cl.tsp()),
    _cluster(&cl)
{
    /*! Cluster ctor. */
}

//______________________________________________________________________________
cat::hit::hit(const cat::hit& h) :
    cat::data(h),
    cat::coord(h),
    _t(h._t),
    _cluster(h._cluster)
{
    /*! Copy ctor. */
}

//______________________________________________________________________________
cat::hit::~hit()
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
std::ostream& operator<<(std::ostream& os, const cat::hit& h)
{
    // Build (x, y, t) like string.
    os << "["
       << static_cast<cat::coord>(h) << cat::caf::rst() 
       << ", "
       << cat::caf::fcol(C_HIT_T) << h.t() << cat::caf::rst() 
       << ", *"
       << cat::caf::fcol(C_HIT_CL) << h.cluster() << cat::caf::rst() 
       << "]";
    
    // Return.
    return os;
}


//______________________________________________________________________________
cat::hit& cat::hit::operator=(const cat::hit& h)
{
    /*! Copy operator. */
    data::operator=(h);
    coord::operator=(h);
    
    // Object data copy.
    _t = h._t;
    _cluster = h._cluster;
    
    // Return.
    return *this;
}



// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************


//______________________________________________________________________________
long cat::hit::t() const
{
    /* Returns timestamp. */
    return _t;
}


//______________________________________________________________________________
void cat::hit::t(const long& t)
{
    /* Set the timestamp. */
    _t = t;
}


//______________________________________________________________________________
const cat::cluster* cat::hit::cluster() const
{
    /* Returns linked cluster pointer. The pointer is made const, as an hit 
       may derive from a real cluster, but cannot modify it in any way. If no
       cluster is linked, returns a void pointer.
       MIND: there is NO GUARANTEE the pointer is valid, this is left to 
       correct usage of the hit/cluster objects.
    */
    return _cluster;
}


//______________________________________________________________________________
void cat::hit::cluster(const cat::cluster& cl)
{
    /* Set the cluster pointer. */
    _cluster = &cl;
}
