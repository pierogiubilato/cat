//------------------------------------------------------------------------------
// CAT Coordinate Graphic Data class					 			          --
// (C) Piero Giubilato 2023-2025, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"geCoord.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Overloading check
#if !defined geCoord_H
#define geCoord_H
 
// STL.
#include<iomanip>

// Application components
#include "ge.h"
#include "afConsole.h"

// The coordinate storage precision. Use the most suitable data type.
#define GECP float

// #############################################################################
namespace cat { namespace ge {

//! coordinate storage in 3D space.
/*! coord is the storing elements for coordinates in 3D space. It is basically 
 *	equivalent to the \b ROOT \c TVector3, but provides template coordinate basis
 *	and more flexibility in performing standard and vector/scalar operations. It 
 *	is not suggested to derive classes directly from coord, which is optimized 
 *	for speed and lacks many standard services. To avoid weight penalties it 
 *	inherits directly from cat::gd:base instead that from cat::gp::base. 
 *  cat::gd::coord has two derived specialized classes, cat::gd::point and 
 *  cat::gd::vector.
 * 
 *  The precision (and hence size) of the storage is set by the 'gdCP' constant
 *  definition, which defines the variable type used to store the coordinates.
 *
 *	\author Piero Giubilato
 *	\version 1.2
 *	\date 24 Sep 2024
 */
//______________________________________________________________________________
class coord: public GE
{
	private:   
		
	protected:

		// The actual coordinates!
		GECP _x;		// X coordinate.
		GECP _y;		// Y coordinate.
		GECP _z;		// Z coordinate.
      
	public:
      
		// Special members
		coord();										//!< Standard Ctor.
		coord(const coord&);							//!< Copy Ctor.
		coord(const double&);							//!< Scalar Copy Ctor.
		coord(const double& x, const double& y, const double& z);	//!< coordinate Ctor.	    
		virtual ~coord();								//!< Standard Dtor.
			
		// Default access public members.
		oType type() const;								//!< Returns GP type.
		uint32_t version() const;							//!< Returns GP version.
		std::string stem() const;						//!< Returns GP stem name.
		size_t size() const;							//!< Returns GP size in bytes.
		void dump(const int ind = 0) const;			//!< Dumps GP data.
		
		//! Stream the GP data (both read and write).
		bool stream(std::stringstream& o, const bool& read = false);
		
		// Specific support members.
		unsigned char precisionGet() const;				//!< Retrieves dump precision.

		// Operator=
		coord& operator = (const coord&);				//<! Copy operator.
		coord& operator = (const double&);				//<! Scalar copy operator.
		
		// Boolean operators <,>,<=,>=
		bool operator < (const coord&) const;			//<! Lesser operator.
		bool operator > (const coord&) const;			//<! Bigger operator.
		bool operator <= (const coord&) const;			//<! Lesser operator.
		bool operator >= (const coord&) const;			//<! Bigger operator.
		
		// Boolean operators == & !=
		bool operator == (const coord&) const;			//<! Equal operator.
		bool operator != (const coord&) const;			//<! Different operator.

		//! Boolean operator == for scalars, returns true in only two cases.
		/*! If s = 0, returns true for the null coordinates; if s = 1, returns 
			true for any unitary coordinate. */
		bool friend operator == (coord& c, const double& s) {
			if (s == 0) return (c.x() == 0) && (c.y() == 0) && (c.z() == 0);
			if (s == 1) return (c.mag() == 1); return false; }

		//! Boolean operator != for scalars, returns true in only two cases.
		/*! If s = 0, returns true for the null coordinates; if s = 1, returns 
			true for any unitary coordinate. */
		bool friend operator != (coord& c, const double& s) {
			if (s == 0) return (c.x() != 0) && (c.y() != 0) && (c.z() != 0);
			if (s == 1) return (c.mag() != 1); return false; }

		// Inversion & unary operators
		coord& operator + () {return *this;}			//<! Null operator.
		coord& operator - ();							//<! Inversion.
		
		// Unary arithmetic operators for scalars<U>
		coord& operator += (const double&);				//<! += operator on scalar.
		coord& operator -= (const double&);				//<! -= operator on scalar.
		coord& operator *= (const double&);				//<! *= operator on scalar.
		coord& operator /= (const double&);				//<! /= operator on scalar.
		
		// Unary arithmetic operators for coord<U>
		coord& operator += (const coord&);				//<! += operator on coord<U>.
		coord& operator -= (const coord&);				//<! -= operator on coord<U>.
		
		// Binary arithmetic operators for scalars
		coord friend operator + (const coord& lo, const double& ro) {return coord(lo) += ro;}	//<! coord + scalar.
		coord friend operator + (const double& lo, const coord& ro) {return coord(ro) += lo;}	//<! Scalar + coord.		
		coord friend operator - (const coord& lo, const double& ro) {return coord(lo) -= ro;}	//<! coord - scalar.
		coord friend operator - (const double& lo, const coord& ro) {return coord(ro) -= lo;}	//<! Scalar - coord.		
		coord friend operator * (const coord& lo, const double& ro) {return coord(lo) *= ro;}	//<! coord * scalar.
		coord friend operator * (const double& lo, const coord& ro) {return coord(ro) *= lo;}	//<! Scalar * coord.		
		coord friend operator / (const coord& lo, const double& ro) {return coord(lo) /= ro;}	//<! coord / scalar.
		coord friend operator / (const double& lo, const coord& ro) {return coord(ro) /= lo;}	//<! Scalar / coord.		
		
		// Binary arithmetic operators for coord<U>
		coord friend operator + (const coord& lo, const coord& ro) {return coord(lo) += ro;}	//<! + operator with coord.
		coord friend operator - (const coord& lo, const coord& ro) {return coord(lo) -= ro;}		//<! - operator with coord.
		double friend operator * (const coord& lo, const coord& ro) {return lo.dot(ro);}		//<! * Scalar products.
	
		// Magnitudes
		double mag2() const;						//!< Returns the magnitude square.
		double mag() const;							//!< Returns the magnitude.
		void mag(const double&);					//!< Sets the magnitude.
		double perp2() const;						//!< Returns the cyl. XY projection square.
		double perp() const;						//!< Returns the cyl. XY projection.

		// Polar angles
		double phi() const;							//!< Returns the azimuth angle.
		void phi(const double&);					//!< Sets Phi coordinate.
		double theta() const;						//!< Returns the polar angle.
		void theta(const double&);					//!< Sets Theta coordinate.

		// Related vectors
		coord unit() const;							//!< Returns a unit vector parallel to this one.
		
		// Geometric operations between coords.
		double dot(const coord&) const;				//!< Scalar product with another coord.
		coord cross(const coord&) const;			//!< Cross product with another coord.
		double angle(const coord&) const;			//!< Retruns the angle with another coord.

		// Operations between coords
		coord& maxize(const coord&);				//!< Maxize by coordinate with coord.
		coord& minize(const coord&);				//!< Minize by coordinate with coord.
	
		// Rotations										
		coord& rotX(const double&);					//<! Rotation around X.
		coord& rotY(const double&);					//<! Rotation around Y.
		coord& rotZ(const double&);					//<! Rotation around Z.
		coord& rotV(const double&, const coord&);	//<! Still missing rotation by V.	

		
		// Direct coordinates access
		// -------------------------
	
		// Operator [], dereference by index
		GECP operator [] (int) const;				//<! Returns coordinate by index.	
		GECP& operator [] (int);					//<! Returns coordinate reference by index.

		// Operator (), dereference by index
		GECP operator () (int) const;				//<! Returns coordinate by index.
		GECP& operator () (int);					//<! Returns coordinate reference by index.
		
		// XYZ coordinates.
		inline GECP x() const {return _x;}			//<! Returns X coordinate.	
		inline GECP& x() {return _x;}				//<! Returns X reference.
		inline void x(const double x) {_x = static_cast<GECP>(x);} //<! Sets X coordinate.
		
		inline GECP y() const {return _y;}			//<! Returns Y coordinate.	
		inline GECP& y() {return _y;}				//<! Returns Y reference.
		inline void y(const double y) {_y = static_cast<GECP>(y);} //<! Sets Y coordinate.
		
		inline GECP z() const {return _z;}			//<! Returns Z coordinate.	
		inline GECP& z() {return _z;}				//<! Returns Z reference.
		inline void z(const double z) {_z = static_cast<GECP>(z);} //<! Sets Z coordinate.

		//! Sets XYZ coordinate.
		inline void xyz(const double& x, const double& y, const double& z) {
			_x = static_cast<GECP>(x); 
			_y = static_cast<GECP>(y); 
			_z= static_cast<GECP>(z);
		}
};

//	*****************************************************************************
// **							  Class Specializations						  **
//	*****************************************************************************

//! A point in 3D space
/*! Point purpose is to make evident that the underlying cat::go:coord object 
	has to be considered a point, not a vector.

	\author Piero Giubilato
	\version 1.1
	\date 29 Sep 2024
*/
//______________________________________________________________________________
class point: public coord
{
	public:
		point():coord() {;}
		point(const double& x, const double& y, const double& z): coord(x,y,z) {;}
		point(const point& p):coord(p) {;}
		point(const coord& c):coord(c) {;}
		point(const double& s):coord(s) {;}
		oType type() const {return oType::gePoint;}
		std::string stem() const {return "Point";}
};

//! A vector in 3D space
/*! Vector purpose is to make evident that the underlying pear::gp::coords object 
	has to be considered a vector, not a vertex.

	\author Piero Giubilato
	\version 1.1
	\date 17 Sep 2024
*/
//______________________________________________________________________________
class vector: public coord 
{
	public:
		vector():coord() {;}
		vector(const double& x, const double& y, const double& z): coord(x,y,z) {;}
		vector(const point& p):coord(p) {;}
		vector(const coord& c):coord(c) {;}
		vector(const double& s):coord(s) {;}
		oType type() const {return oType::geVector;}
		std::string stem() const {return "Vector";}
};

// #############################################################################
}} // Close Namespaces.


// *****************************************************************************
// **						Global namespace overloads						  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::ge::coord& obj)
{
	/*! Overloads standard output operator << for a generic coordinate object. */ 
	
	//! Sets the output accordingly to the stored type precision.
	o << std::showpos << std::fixed << std::setprecision(CAT_DUMP_PREC_GEOMETRY);
	
	//! Dumps the data members on screen.
	o	<< "<"  << COL(RED)	  << obj.x() << COL(DEFAULT) 
		<< ", " << COL(GREEN) << obj.y() << COL(DEFAULT)
		<< ", " << COL(BLUE)  << obj.z() << COL(DEFAULT) << ">";
	
	//! Reset output formatting.
	o << std::resetiosflags(std::ios::fixed | std::ios::showpos) << std::setprecision(9);
	
	// Continue the chain
	return o;
}

// Overloading check
#endif
