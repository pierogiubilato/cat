//------------------------------------------------------------------------------
// CAT Graphics Data object reference system class                            --
// (C) Piero Giubilato 2021-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gdRef.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Application components.
#include "../include/geRef.h"


// #############################################################################
namespace cat { namespace ge {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
ref::ref(): GE(), 
	_p0(point(0, 0, 0)),
	_v0(0, 0, 1, 0),
	_s0(vector(1, 1, 1))
{
	/*! Only the default and coordinate ctor are provided, as the default copy 
	 *	ctor, dtor and operator= are fine with the shallow data copy required.
	 *	The default initialization for a reference objects sets an origin equal 
	 *	to (0,0,0) and a rotation equal to (0,0,0), making it superimposed to the
	 *	parent reference frame. 
	 */
		
	// Preset displacement and rotation matrix to 0.

}

//______________________________________________________________________________
ref::ref(const point& p, const vector& a): GE(),
	_p0(p),
	_a0(a),
	_s0(gd::vector(1, 1, 1))
{
	/*! Initialize the reference frame with displacement \c p0 respect to the XYZ
	 *	parent frame and Euler angles equal to \c a. \c p is expressed in XYZ frame
	 *	coordinates, while \c a expresses Euler angles following the ZX'Z'' rule,
	 *	so actually mixing the two reference frames.
	 */
		
	// Sets displacement and rotation matrix.
}

//______________________________________________________________________________
ref::ref(const point& p, const vector& u, const vector& v): GE(),
	_p0(p),
	_UVW(u, v),
	_s0(vector(1, 1, 1))
{
	/*! Initialize the reference frame with displacement \c p respect to the XYZ
	 *	parent frame and rotation defined by the UVW base vectors respect the XYZ 
	 *	frame using \c u(x,y,z),, \c v(x,y,z) to determine the UVW base.
	 */
		
	// Sets displacement and basis representation.
}

//______________________________________________________________________________
ref::ref(const point& p, const vector& v, const double& a): GE(),
	_p0(p),
	_v0(v, a),
	_s0(vector(1, 1, 1)),
{
	/*! Initialize the reference frame with displacement \c p respect to the XYZ
	 *	parent frame and rotation defined by the \c v vector (rotation axis) and
	 *	\c a angle around that axis (counterclockwise).
	 */
}
	
// *****************************************************************************
// **					    Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 ref::type() const
{
	/*! Returns a numeric identification. */
	return GE::ktype::ref;
}

//______________________________________________________________________________
Uint64 ref::version() const
{
	/*! Returns a numeric identification. */
	return 100;
}

//______________________________________________________________________________
std::string ref::stem() const
{
	/*! Returns a string identification. */
	return "ref";
}

//______________________________________________________________________________
size_t ref::size() const
{
	/*! Returns the size of the GP in bytes. */
	size_t total = GE::size();
	total += (sizeof(double) * (3 + 4 + 3 + 9));
	return total;
}
//______________________________________________________________________________
void ref::dump(const Uint32& ind) const
{
	/*! Send out all the refrence data. */
	std::string pad(ind, ' ');
	std::cout << pad << "p0: " << _p0[0] << " " << _p0[1] << " " << _p0[2] << "\n";
	std::cout << pad << "v0: " << _v0[0] << " " << _v0[1] << " " << _v0[2] << " " << _vA << "\n";
	std::cout << pad << "s0: " << _s0[0] << " " << _s0[1] << " " << _s0[2] << "\n";
}

//______________________________________________________________________________
bool ref::stream(std::stringstream& o, const bool& read)
{
	/*! Streams the primitive. */

	// This class has no parent, so just stream itself.
	
	
	// Origin.
	af::stream::RW(o, _p0[0], read);
	af::stream::RW(o, _p0[1], read);
	af::stream::RW(o, _p0[2], read);
	
	// Axis and angle.
	af::stream::RW(o, _v0[0], read);
	af::stream::RW(o, _v0[1], read);
	af::stream::RW(o, _v0[2], read);
	af::stream::RW(o, _vA, read);
	
	// Scale.
	af::stream::RW(o, _s0[0], read);
	af::stream::RW(o, _s0[1], read);
	af::stream::RW(o, _s0[2], read);
	
	// If read, recalculate the transformation matrix!
	if (read) v0(_v0[0], _v0[1], _v0[2], _vA);
	
	// Everything fine.
	return false;
}



// *****************************************************************************
// **					    GP data access public members					  **
// *****************************************************************************

//______________________________________________________________________________
bool ref::check()
{
	/*! Check the stored transformation matrix for orthogonality. */
	
	// Those vectors should form an orthonormal basis
	vector u(_trsf[0], _trsf[1], _trsf[2]);
	vector v(_trsf[3], _trsf[4], _trsf[5]);
	vector w(_trsf[6], _trsf[7], _trsf[8]);

	// Unary vectors
	if (u.unit() != u) return false;
	if (v.unit() != v) return false;
	if (w.unit() != w) return false;

	// Orthogonality
	if (u.dot(v) != 0) return false;
	if (u.dot(w) != 0) return false;
	if (v.dot(w) != 0) return false;

	// It seems ok!
	return true;
}


//______________________________________________________________________________
point ref::p0() const
{
	/* Returns the reference origin. */
	return point(_p0[0], _p0[1], _p0[2]);
}

//______________________________________________________________________________
void ref::p0(const point& p)
{
	/*! Defines the reference frame origin point in the XYZ parent frame 
		coordinates base. */
	_p0[0] = p[0];
	_p0[1] = p[1];
	_p0[2] = p[2];
}

//______________________________________________________________________________
vector ref::v0() const
{
	/* Returns the reference rotation axis versor. */
	return vector(_v0[0], _v0[1], _v0[2]);
}

//______________________________________________________________________________
double ref::vA() const
{
	/* Returns the reference rotation angle. */
	return _vA;
}

//______________________________________________________________________________
vector ref::s0() const
{
	/* Returns the reference scaling for each axis. */
	return vector(_s0[0], _s0[1], _s0[2]);
}

//______________________________________________________________________________
void ref::s0(const vector& s)
{
	/*! Defines the reference frame scaling respect the XYZ parent frame 
		coordinates base. */
	_s0[0] = s[0];
	_s0[1] = s[1];
	_s0[2] = s[2];
}

//______________________________________________________________________________
void ref::UVW(const vector& u, const vector& v)
{
	/*! Defines the reference frame orientation by describing its UVW base with
	 *	the parent frame XYZ base.	\c u , \c v  must be orthogonal coordinate 
	 *	vectors.
	 */
	
	// Builds the UVW base vectors;
	vector _u = u.Unit();
	vector _v = v.Unit();
	vector _w = _u.Cross(_v);

	// Fills transformation matrix. How that works: transformation matrix is 
	// fully defined by the new base, so assuming u v w being orthonormal base 
	// vectors, it is enough to write them as ROWS of the matrix to get the
	// XYZ to UVW transformation matrix. Use it transposed to get the UVW to
	// XYZ transformation.
	_trsf[0] = _u.X(); _trsf[1] = _u.Y(); _trsf[2] = _u.Z();
	_trsf[3] = _v.X(); _trsf[4] = _v.Y(); _trsf[5] = _v.Z();
	_trsf[6] = _w.X(); _trsf[7] = _w.Y(); _trsf[8] = _w.Z();

	// Check it, warns in case
	if (!check()) {
		std::cout << *this << "\n" << COL(YELLOW) << 
		"Impossible reference frame set!\n" << COL(DEFAULT) << "\n";
	}
}

//______________________________________________________________________________
bool ref::getAxisAngle()
{
	/*!	Derives the rotation axis and angle from the current rotation matrix
	 *	coefficients. Correctly locates the angle in the right quadrant.
	 */

	// First step, we determine the rotation axis. This is done by finding
	// the eigevector of eigenvalue 1. There are two possible solutions
	// for this eigenvalue (+-1), we will disambiguate them in the next 
	// step	by using the rotation angle cosine and sine.
	_v0[0] = (_trsf[4] - 1) * (_trsf[8] - 1) - _trsf[5] * _trsf[7];
	_v0[1] = (_trsf[8] - 1) * (_trsf[0] - 1) - _trsf[6] * _trsf[2];
	_v0[2] = (_trsf[0] - 1) * (_trsf[4] - 1) - _trsf[1] * _trsf[3];

	// Normalize it.
	double mag = sqrt(_v0[0] * _v0[0] + _v0[1] * _v0[1] + _v0[2] * _v0[2]);
	if (mag > 0) {
		_v0[0] /= mag;
		_v0[1] /= mag;
		_v0[2] /= mag;
	}

	// The cosine of the rotation angle cos(a) is simply related to the
	// trace of the rotation matrix, so we get:
	double cosA = (_trsf[0] + _trsf[4] + _trsf[8] - 1) / 2;
	
	// Now, if A is the trasformation matrix, we exploit the fact that
	// the A - Trsp(A) matrix is equivalent (calling x, y, z the axis
	// components and a the rotation angle around this axis):
	//
	//	 /		0			 2 z sin(a)		-2 y sin(a)	 \
	//	 |	-2 z sin(a)			 0			 2 x sin(a)	 |
	//	 \	 2 y sin(a)		-2 x sin (a)		 0		 /
	//
	//	 /		  0			_A[1] - _A[3]	_A[2] - _A[6]	\					
	//	 | _A[3] - _A[1]			0		_A[5] - _A[7]	|
	//	 \ _A[6] - _A[2]	_A[7] - _A[5]		  0			/

	// Hence we calculate three components of such matrix to account
	// for every possible rotation axis. To enhance precision, carry
	// the calculation on the biggest component of the axis.	
	
	// Here we get which is the biggest component.
	int idx = 0;
	if (_v0[0] > _v0[1]) {
		(_v0[0] > _v0[2]) ? idx = 0 : idx = 2;
	} else {
		(_v0[1] > _v0[2]) ? idx = 1 : idx = 2;
	}
	
	// And eventually calculate the sin(a) value.
	double sinA = 0;
	if (_v0[idx] != 0) {
		switch (idx) {
			case 0:	sinA = (_trsf[5] - _trsf[7]) / (2 * _v0[0]); break;
			case 1:	sinA = (_trsf[6] - _trsf[2]) / (2 * _v0[1]); break;
			case 2:	sinA = (_trsf[1] - _trsf[3]) / (2 * _v0[2]);
		}
	}
	
	// Derive the rotation angle!
	_vA = -atan2(sinA, cosA);
	
	// Math debug.
	//std::cout << "       " << _trsf[0] << " " << _trsf[1] << " " << _trsf[2] << "\n";
	//std::cout << "Trsf:  " << _trsf[3] << " " << _trsf[4] << " " << _trsf[5] << "\n";
	//std::cout << "       " << _trsf[6] << " " << _trsf[7] << " " << _trsf[8] << "\n";
	//std::cout << "axis:  " << _v0[0] << " " << _v0[1] << " " << _v0[2] << "\n";
	//std::cout << "idx:   " << idx << "\n";
	//std::cout << "cos:   " << cosA << "\n";
	//std::cout << "sin:   " << sinA << "\n";
	//std::cout << "A5-A7: " << _trsf[5] << " " << _trsf[7] << " " << _trsf[5] - _trsf[7] << "\n";
	//std::cout << "angle: " << _vA << "\n";

	// All ok.
	return false;
}

//______________________________________________________________________________
void ref::a0(const vector& a)
{
   /*!	Defines the reference frame orientation by describing its Euler angles
	*	rotation respect to the parent frame XYZ base. Adopted convention for \a 
	*	is the XYZ, where the first component of \c a (alpha) represent the 
	*	rotation along the X axis, the second component \c a (beta) the rotation
	*	around the Y axis and the third \c a component (gamma) the rotation 
	*	along the Z axis.
	*/
	
	// Pivot sines/cosines.
	double sX = sin(a[0]);
	double cX = cos(a[0]);
	double sY = sin(a[1]);
	double cY = cos(a[1]);
	double sZ = sin(a[2]);
	double cZ = cos(a[2]);
		
	// Fills transformation matrix. How that works: transformation matrix is 
	// fully defined by the euler angles and here created to describe the XYZ
	// to UVW transformation; use it transposed to get the UVW to XYZ one.
	//
	//	/  cZ cY	cZ sY sX - sZ cX	cZ sY cX + sZ sX  \
	//	|  sZ cY	sZ sY sX + cZ cX	sZ sY cX - cZ sX   |
	//	\	-sY			 cY sX				  cY cX		  /
	//
	//		 1				0					0
	//		 0			   cX				   -sX
	//		 0			   sX				   cX
	//
	_trsf[0] = cY * cZ;  
	_trsf[1] = sX * sY * cZ - cX * sZ;
	_trsf[2] = cX * sY * cZ + sX * sZ;
	_trsf[3] = cY * sZ;
	_trsf[4] = sX * sY * sZ + cX * cZ;
	_trsf[5] = cX * sY * sZ - sX * cZ;
	_trsf[6] = -sY;
	_trsf[7] = sX * cY;
	_trsf[8] = cX * cY;

	// Debug.
	//std::cout << a << "\n";
	
	// Derives the rotation axis and angle.
	getAxisAngle();	
}

//______________________________________________________________________________
void ref::v0(const double& x, const double& y, const double& z, const double& a)
{
   /*!	Defines the reference frame orientation by describing its eigenvector
	*	\c v and the rotation angle \c a around this vector.
	*/

	// Builds the unit versor.
	double mag = sqrt(x*x + y*y + z*z);
	double u[3] = {x / mag, y / mag, z / mag};

	// Basic elements for the transformation matrix.
	double sA = sin(a);
	double cA = cos(a);

	// Fills transformation matrix.
	_trsf[0] = cA + u[0] * u[0] * (1 - cA);
	_trsf[1] = u[0] * u[1] * (1 - cA) - u[2] * sA;
	_trsf[2] = u[0] * u[2] * (1 - cA) + u[1] * sA;
	_trsf[3] = u[1] * u[0] * (1 - cA) + u[2] * sA;
	_trsf[4] = cA + u[1] * u[1] * (1 - cA);
	_trsf[5] = u[1] * u[2] * (1 - cA) - u[0] * sA;
	_trsf[6] = u[2] * u[0] * (1 - cA) - u[1] * sA;
	_trsf[7] = u[2] * u[1] * (1 - cA) + u[0] * sA;
	_trsf[8] = cA + u[2] * u[2] * (1 - cA);
}

//______________________________________________________________________________
void ref::v0(const vector& v, const double& a)
{
   /*!	Defines the reference frame orientation by describing its eigenvector
	*	\c v and the rotation angle \c a around this vector.
	*/
	_v0(v[0], v[1], v[2], a);
}

//______________________________________________________________________________
vector ref::eU() const
{
	/*! Returns the base vector U expressed in the XYZ parent reference frame 
	 *	coordinate base. */
	return vector(_trsf[0], _trsf[1], _trsf[2]);
}

//______________________________________________________________________________
vector ref::eV() const
{
	/*! Returns the base vector V expressed in the XYZ parent reference frame 
	 *	coordinate base. */
	return vector(_trsf[3], _trsf[4], _trsf[5]);
}
//______________________________________________________________________________
vector ref::eW() const
{
	/*! Returns the base vector W expressed in the XYZ parent reference frame 
	 *	coordinate base. */
	return vector(_trsf[6], _trsf[7], _trsf[8]);
}

//______________________________________________________________________________
vector ref::eX() const
{
	/*! Returns the parent frame base vector X expressed in the UVW reference frame 
	 *	coordinate base. */
	return vector(_trsf[0], _trsf[3], _trsf[6]);
}

//______________________________________________________________________________
vector ref::eY() const
{
	/*! Returns the parent frame base vector Y expressed in the UVW reference frame 
	 *	coordinate base. */
	return vector(_trsf[1], _trsf[4], _trsf[7]);
}
//______________________________________________________________________________
vector ref::eZ() const
{
	/*! Returns the parent frame base vector W expressed in the UVW reference frame 
	 *	coordinate base. */
	return vector(_trsf[2], _trsf[5], _trsf[8]);
}

//______________________________________________________________________________
vector gd::ref::toUVW(const vector& v) const
{
	/*! Transforms the vector \c v coordinates from parent space reference 
	 *	frame XYZ to the container reference frame coordinates UVW. */
	return vector(_trsf[0] * v[0] + _trsf[1] * v[1] + _trsf[2] * v[2],
				  _trsf[3] * v[0] + _trsf[4] * v[1] + _trsf[5] * v[2],
				  _trsf[6] * v[0] + _trsf[7] * v[1] + _trsf[8] * v[2]);
}

//______________________________________________________________________________
vector ref::toXYZ(const vector& v) const
{
	/*! Transforms the vector \c v coordinates from this reference frame UVW base
	 *	to the parent frame XYZ base. */
	return vector(_trsf[0] * v[0] + _trsf[3] * v[1] + _trsf[6] * v[2],
				  _trsf[1] * v[0] + _trsf[4] * v[1] + _trsf[7] * v[2],
				  _trsf[2] * v[0] + _trsf[5] * v[1] + _trsf[8] * v[2]);
}

//______________________________________________________________________________
point ref::toUVW(const point& p) const
{
	/*! Transforms the point \c p coordinates from parent space reference 
	 *	frame XYZ to the container reference frame coordinates UVW. */
	
	// Translate the point (displacement is in XYZ base), then rotate it
	return ToUVW(vector(p[0] - _p0[0], p[1] - _p0[1], p[2] - _p0[2]));
}

//______________________________________________________________________________
point ref::toXYZ(const point& p) const
{
	/*! Transforms the point \c p coordinates from this reference frame UVW base
	 *	to the parent frame XYZ base. */
	
	// Rotates  the vector component
	point q = toXYZ((vector)p);
	
	// Then traslates, as displacement is expressed in XYZ base
	return point(q[0] + _p0[0], q[1] + _p0[1], q[2] + _p0[2]);
}

//______________________________________________________________________________
vector& ref::trsf(vector& v, const bool& inverse) const
{
	/*! Transforms the vector \c v coordinates with a direct (to UVW) or inverse
	 *	(to XYZ) transformation.
	 */
	
	// A (fast) pivot.
	static double w[3];

	// To XYZ (inverse) rotation.
	if (inverse) {
		w[0] = _trsf[0] * v[0] + _trsf[3] * v[1] + _trsf[6] * v[2];
		w[1] = _trsf[1] * v[0] + _trsf[4] * v[1] + _trsf[7] * v[2];
		w[2] = _trsf[2] * v[0] + _trsf[5] * v[1] + _trsf[8] * v[2];
	
	// To UVW (direct) rotation.
	} else {
		w[0] = _trsf[0] * v[0] + _trsf[1] * v[1] + _trsf[2] * v[2];
		w[1] = _trsf[3] * v[0] + _trsf[4] * v[1] + _trsf[5] * v[2];
		w[2] = _trsf[6] * v[0] + _trsf[7] * v[1] + _trsf[8] * v[2];
	}

	// Updates the vector.
	v.xyz(w[0], w[1], w[2]);

	// Return the modified vector in case of chaining.
	return v;
}

//______________________________________________________________________________
point& ref::trsf(point& p, const bool& inverse) const
{
	/*! Transforms the point \c p coordinates with a direct (to UVW) or inverse
	 *	(to XYZ) transformation.
	 */
		
	// Rotates the point as a vector.
	trsf((vector&)p, inverse);
		
	// Then traslates, as displacement is expressed in XYZ base
	if (inverse) {
		p[0] -= static_cast<float>(_p0[0]);
		p[1] -= static_cast<float>(_p0[1]);
		p[2] -= static_cast<float>(_p0[2]);
	} else {
		p[0] += static_cast<float>(_p0[0]);
		p[1] += static_cast<float>(_p0[1]);
		p[2] += static_cast<float>(_p0[2]);
	}
	//(inverse) ? p -= _p0 : p += _p0; 
	
	// Return the modified point in case of chaining.
	return p;
}


// #############################################################################
}} // Close namespaces.