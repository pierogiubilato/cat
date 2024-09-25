//------------------------------------------------------------------------------
// CAT graphics entity coordinate class										  --
// (C) Piero Giubilato 2023-2025, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"geCoord.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Application components
#include "../include/geCoord.h"


// #############################################################################
namespace cat { namespace ge {


// *****************************************************************************
// **							Special Members								  **
// *****************************************************************************

//______________________________________________________________________________
coord::coord(): GE(),
	_x(0),
	_y(0),
	_z(0)
{
	/*! Default constructor. */
	
}

//______________________________________________________________________________
coord::coord(const double& x, const double& y, const double& z): GE(), 
	_x(static_cast<GECP>(x)), 
	_y(static_cast<GECP>(y)), 
	_z(static_cast<GECP>(z))
{
	/*! ge::coord<T> constructor. */
	
}

//______________________________________________________________________________
coord::coord(const coord& ref): GE(), 
	_x(ref.x()), 
	_y(ref.y()),
	_z(ref.z())
{
	/*! Casting<U> Copy constructor. */
	
}

//______________________________________________________________________________
coord::coord(const double& s): GE(), 
	_x(static_cast<GECP>(s)), 
	_y(static_cast<GECP>(s)), 
	_z(static_cast<GECP>(s))
{
	/*! Scalar<U> copy constructor. */
	
}

//______________________________________________________________________________
coord::~coord ()
{
	/*! Standard destructor. */
		
	// Actually nothing to do...
}

//______________________________________________________________________________
coord& coord::operator = (const coord& c)
{
	/*! Standard copy operator = */
	if (this == (coord*)&c) return *this;
	
	// Parent copy in case
	// Not copying Object on purpose!

	// Copy
	_x = c.x();
	_y = c.y();
	_z = c.z();

	// Return
	return *this;
}

//______________________________________________________________________________
coord& coord::operator = (const double& s)
{
	/*! Scalar copy operator = */
	
	// Copy.
	_x = static_cast<GECP>(s);
	_y = static_cast<GECP>(s);
	_z = static_cast<GECP>(s);

	// Return.
	return *this;
}



// *****************************************************************************
// **							cake::Object Overloaded						  **
// *****************************************************************************

//______________________________________________________________________________
CO::oType coord::type() const
{
	/*! Returns the entity type (the class type itself). */
	return oType::geCoord; 
}

//______________________________________________________________________________
size_t coord::size() const
{
	/*! Returns the coordinate size in bytes. */
	return sizeof(_x) * 3;
}

//______________________________________________________________________________
std::string coord::stem() const
{
	/*! Returns a string identification. */
	return "ge::coord";
}

//______________________________________________________________________________
uint32_t coord::version() const
{
	/*! Returns the GP version. */
	return 100;
}

//______________________________________________________________________________
bool coord::stream(std::stringstream& o, const bool& read)
{
	/*! Stream the coordinates. */
	
	// This class has no parent, so just stream itself.
	
	// Reads from stream.
	if (read) {
		o.read((char*)&_x, sizeof(_x));
		o.read((char*)&_y, sizeof(_y));
		o.read((char*)&_z, sizeof(_z));

	// Writes to stream.
	} else {
		o.write((char*)&_x, sizeof(_x));
		o.write((char*)&_y, sizeof(_y));
		o.write((char*)&_z, sizeof(_z));										
	}

	// Everything fine.
	return false;
}

//______________________________________________________________________________
void coord::dump(const int& ind) const
{
	/*! Outputs the coordinates. */
	std::cout << std::string(ind, ' ') << *this;
	//std::string pad(ind, ' ');
	//std::cout << pad << "(p0: )" << _x << ", " << _y << ", " << _z << ")";
}



// *****************************************************************************
// **								Operators								  **
// *****************************************************************************

//______________________________________________________________________________
GECP coord::operator[] (int i) const
{   
	/*! Dereferencing operator [] const */
	switch(i) {
		case 0: return _x;
		case 1: return _y;
		case 2: return _z;
		default:;
	}
	return _x;
}

//______________________________________________________________________________
GECP& coord::operator[] (int i)
{
	/*! Dereferencing operator [] */
	switch(i) {
		case 0: return _x;
		case 1: return _y;
		case 2: return _z;
		default:;
	}
	return _x;
}

//______________________________________________________________________________
GECP coord::operator () (int i) const
{
	/*! Dereferencing operator () */
	return operator[](i);
}
//______________________________________________________________________________
GECP& coord::operator () (int i)
{
	/*! Dereferencing operator () */
	return operator[](i);
}

//______________________________________________________________________________
bool coord::operator == (const coord& c) const
{
	/*! Boolean operator == on coordinates, returns true only if
		all coordinates match. */
	return (_x == c.x()) && (_y == c.y()) && (_z == c.z());
}

//______________________________________________________________________________
bool coord::operator != (const coord& c) const
{
	/*! Boolean operator != on coordinates, return false if at least one
		coordinate does not match the corresponding one. */
	return (_x != c.x() || _y != c.y() || _z != c.z());
}

//______________________________________________________________________________
bool coord::operator < (const coord& c) const
{
	/*! Boolean operator <	on coordinates. Returns true only if all
		coordinates are ordered by the < relation. */
	return (_x < c.x() && _y < c.y() && _z < c.z());
}

//______________________________________________________________________________
bool coord::operator <= (const coord& c) const
{
	/*! Boolean operator <=	on coordinates. Returns true only if all
		coordinates are ordered by the <= relation. */
	return (_x <= c.x() && _y <= c.y() && _z <= c.z());
}

//______________________________________________________________________________
bool coord::operator > (const coord& c) const
{
	/*! Boolean operator >	on coordinates. Returns true only if all
		coordinates are ordered by the > relation. */
	return (_x > c.x() && _y > c.y() && _z > c.z());
}

//______________________________________________________________________________
bool coord::operator >= (const coord& c) const
{
	/*! Boolean operator >=	on coordinates. Returns true only if all
		coordinates are ordered by the >= relation. */
	return (_x >= c.x() && _y >= c.y() && _z >= c.z());
}

//______________________________________________________________________________
coord& coord::operator - ()
{
	/*! Inversion operator - inverts the sign for each coordinate. */
	_x = -_x; _y = -_y; _z = -_z;	return *this;
}

//______________________________________________________________________________
coord& coord::operator += (const coord& c)
{
	/*! Operator += ge::coord */
	_x += c.x(); _y += c.y(); _z += c.z();
	return *this;
}

//______________________________________________________________________________
coord& coord::operator -= (const coord& c)
{
	/* Operator -= gd::coord */
	_x -= c.x(); _y -= c.y(); _z -= c.z();
	return *this;
}

//______________________________________________________________________________
coord& coord::operator += (const double& s)
{
	/*! Operator += scalar<U> */
	_x += static_cast<GECP>(s);
	_y += static_cast<GECP>(s);
	_z += static_cast<GECP>(s);
	return *this;
}

//______________________________________________________________________________
coord& coord::operator -= (const double& s)
{
	/*! Operator -= scalar<U> */
	_x -= static_cast<GECP>(s);
	_y -= static_cast<GECP>(s);
	_z -= static_cast<GECP>(s);
	return *this;
}

//______________________________________________________________________________
coord& coord::operator*= (const double& s)
{
	/*! Operator *= scalar<U> */
	_x *= static_cast<GECP>(s);
	_y *= static_cast<GECP>(s);
	_z *= static_cast<GECP>(s);
	return *this;
}

//______________________________________________________________________________
coord& coord::operator /= (const double& s)
{
	/*! Operator /= scalar<U> */
	_x /= static_cast<GECP>(s);
	_y /= static_cast<GECP>(s);
	_z /= static_cast<GECP>(s);
	return *this;
}



// *****************************************************************************
// **					  gd::coordinates access public members					  **
// *****************************************************************************

//______________________________________________________________________________
double coord::mag2() const
{
	/*! Retrieves the magnitude of the coordinate set as measured from 
		the origin of the reference frame, leaving it squared. */
	return _x*_x + _y*_y + _z*_z;
}

//______________________________________________________________________________
double coord::mag() const
{
	/*! Retrieves the magnitude of the coordinate set as measured from 
		the origin of the reference frame. */
	return sqrt(mag2());
}

//______________________________________________________________________________
void coord::mag(const double& ma)
{
	/*! Sets the magnitude of the coordinate vector. */
	double factor = mag();
	(factor != 0) ? factor = ma / factor : factor = 1;
      
	// Scales the coordinates.
	_x = static_cast<GECP>(_x * factor);
	_y = static_cast<GECP>(_y * factor);
	_z = static_cast<GECP>(_z * factor);
}

//______________________________________________________________________________
double coord::perp2() const
{ 
	/*! Returns the cylindrical XY projection squared. */
	return _x*_x + _y*_y;
}

//______________________________________________________________________________
double coord::perp() const
{ 
	/*! Returns the cylindrical XY projection. */
	return sqrt(perp2());
}

//______________________________________________________________________________
double coord::phi() const 
{
   /*! Returns the azimuth angle Phi from -pi to pi. */
   return _x == 0.0 && _y == 0.0 ? 0.0 : atan2(_y, _x);
}

//______________________________________________________________________________
void coord::phi(const double& ph) 
{
   /*! Sets the azimuth angle Phi keeping Mag and Theta constant. */
   double xy = perp();
   _x = static_cast<GECP>(xy * cos(ph));
   _y = static_cast<GECP>(xy * sin(ph));
}

//______________________________________________________________________________
double coord::theta() const 
{
   /*! Returns the polar angle. */
   return _x == 0.0 && _y == 0.0 && _z == 0.0 ? 0.0 : atan2(perp(), (double)_z);
}

//______________________________________________________________________________
void coord::theta(const double& th) 
{
   /*! Sets the polar angle Theta keeping Mag and Phi constant. */
   double ma = mag();
   double ph = phi();
   _x = static_cast<GECP>(ma * sin(th) * cos(ph));
   _y = static_cast<GECP>(ma * sin(th) * sin(ph));
   _z = static_cast<GECP>(ma * cos(th));
}

//______________________________________________________________________________
coord coord::unit() const
{
   /*! Returns a unit vector parallel to the caller. */
   double tot = mag2();
   ge::coord p(_x, _y, _z);
   return (tot > 0.0) ? p *= (1.0 / sqrt(tot)) : p;
}

//______________________________________________________________________________
double coord::dot(const coord& c) const
{
	/*! Calculates the dot product between the caller and the argument. */
	return _x * c.x() + _y * c.y() + _z * c.z();
}

//______________________________________________________________________________
coord coord::cross(const coord& c) const
{
	/*! Calculates the cross product between the caller and the argument. */
	return ge::coord(_y * c.z() - c.y() * _z, 
					_z * c.x() - c.z() * _x, 
					_x * c.y() - c.x() * _y);
}

//______________________________________________________________________________
double coord::angle(const coord& c) const 
{
   /*! Returns the angle w.r.t. to another coord. */
   double ptot2 = mag2() * c.mag2();
   if(ptot2 <= 0) {
      return 0.0;
   } else {
      double arg = dot(c)/sqrt(ptot2);
      if(arg >  1.0) arg =  1.0;
      if(arg < -1.0) arg = -1.0;
      return acos(arg);
   }
}

//______________________________________________________________________________
coord& coord::maxize(const coord& c) 
{
	/*! Set every coordinate of the caller as the maximum between the caller
		coordinate and the argument one. */
	if (c.x() > _x) _x = c.x();	
	if (c.y() > _y) _y = c.y();
	if (c.z() > _z) _z = c.z();

	// Returns result.
	return *this;
}

//______________________________________________________________________________
coord& coord::minize(const coord& c) 
{
	/*! Set every coordinate of the caller as the minimum between the caller
		coordinate and the argument one. */
	if (c.x() < _x) _x = c.x();	
	if (c.y() < _y) _y = c.y();
	if (c.z() < _z) _z = c.z();

	// Returns result.
	return *this;
}

//______________________________________________________________________________
coord& coord::rotX(const double& a)
{
	/*! Rotates coordinates around X axis. */
	double s = sin(a);
	double c = cos(a);
	double yy = _y;
	_y = static_cast<GECP>(c*yy - s*_z);
	_z = static_cast<GECP>(s*yy + c*_z);

	// Result.
	return *this;
}

//______________________________________________________________________________
coord& coord::rotY(const double& a)
{
	/*! Rotates coordinates around Y axis. */
	double s = sin(a);
	double c = cos(a);
	double zz = _z;
	_z = static_cast<GECP>(c*zz - s*_x);
	_x = static_cast<GECP>(s*zz + c*_x);
	
	// Result.
	return *this;
}

//______________________________________________________________________________
coord& coord::rotZ(const double& a)
{
	/*! Rotates coordinates around Z axis. */
	double s = sin(a);
	double c = cos(a);
	double xx = _x;
	_x = static_cast<GECP>(c*xx - s*_y);
	_y = static_cast<GECP>(s*xx + c*_y);

	// Result
	return *this;
}

//______________________________________________________________________________
coord& coord::rotV(const double&, const coord& v)
{
	/*! To be implemented. */
   std::cout << COL(LRED) << "ge::coord::rotV is NOT IMPLEMENTED yet!" << COL(DEFAULT) << "\n";

	// Result
	return *this;
}



// *****************************************************************************
// **						  Public static members							  **
// *****************************************************************************

//______________________________________________________________________________
unsigned char coord::precisionGet() const
{
	/*! Gets the number of digit displayed after the decimal point to fit the
		actual precision required by the chosen data type. */
	#ifdef CAT_GEO_COORD_DIGITS
		return CAT_GEO_COORD_DIGITS;
	#else
		switch (sizeof(GECP)) {
			case 1:	return 2; break;
			case 2:	return 4; break;
			case 4:	return 8; break;
			case 8:	return 16; break;
			case 16: return 32; break;
			default: return 2;
		}
	#endif 
}

// #############################################################################
// Close Namespaces
}}
