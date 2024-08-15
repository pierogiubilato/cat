//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - layer data object                          --
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
#include "../include/layer.hpp"
#include "../include/caf.hpp"


// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************


//______________________________________________________________________________
cat::layer::layer(const cat::sensor& sr, const cat::plane& pl) : 
    data(), 
    _plane(pl)
{
    /* Default ctor. Makes mandatory to initialize the layer sensor and plane. */
    _sensor.push_back(sr);
}



//______________________________________________________________________________
cat::layer::layer(const layer& lr) : 
    data(lr), 
    _sensor(lr._sensor),
    _plane(lr._plane)
{
    /*! Copy ctor. */
}


//______________________________________________________________________________
cat::layer::~layer()
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
cat::layer& cat::layer::operator=(const cat::layer& lr)
{
    /*! Copy operator. */
    data::operator=(lr);

    // Sensor.
    _sensor= lr._sensor;
    
    // Plane.
    _plane = lr._plane;

    // Hits.
    

    // Return.
    return *this;
}


//______________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const cat::layer& lr)
{
    // Build (x, y, z, t) like string.
    os << "[";
    if (!lr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    os << lr.plane() << cat::caf::rst() << ", ";
    if (!lr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    for (auto sr : lr.sensors()) {
        os << sr << ", ";
    }
     
    // if (!lr.isUp()) os << cat::caf::font(cat::caf::BLINK);
    //os << cat::caf::fcol(C_CL_COL) << sr.colPitch() << cat::caf::rst() << ",";
    os << "]";


    // Return.
    return os;
}




// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************


//______________________________________________________________________________
const std::vector<cat::sensor>& cat::layer::sensors() const
{
    /* Returns a const handle to the sensors vector. */

    // Return the sensor.
    return _sensor;
}


//______________________________________________________________________________
cat::sensor& cat::layer::sensor(const int& i)
{
    /* Returns the sensor. */
    
    // Check for error.
    if (i < 0 || (i >= _sensor.size())) {
        throw std::runtime_error{ "Object not found" };
    }
            
    // Return the sensor.
    return _sensor[i];
}


// _____________________________________________________________________________
void cat::layer::srAdd(const cat::sensor& sr)
{
    /* Add a sensor to the layer. */
    _sensor.push_back(sr);
}


// _____________________________________________________________________________
long cat::layer::srCount() const
{
    /* Retrieve how many sensors are into the layer. */
    return (long) _sensor.size();
}


// _____________________________________________________________________________
const cat::plane& cat::layer::plane() const
{
    /* Handle to the layer plane. */
    return _plane;
}


