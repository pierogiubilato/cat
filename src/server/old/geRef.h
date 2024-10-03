//------------------------------------------------------------------------------
// CAT Graphics Data Reference class				                          --
// (C) Piero Giubilato 2021-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"geRef.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.3"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined geRef_H
#define geRef_H

// Application components.
#include "geCoord.h"

// #############################################################################
namespace cat { namespace ge {

/*! cat::ge::ref creates a reference frame in 3D.
 *	
 *	\author Piero Giubilato
 *	\version 1.3
 *	\date 24 Sep 2024
 */
//______________________________________________________________________________
class ref: public GE
{
	private:
		
		// Data containers
		point _p0;			// UVW Displacement respect to XYZ.
		vector _s0;			// UVW Scaling respect to XYZ.
		vector _a0;			// Euler's angles rotation.
		vector _v0;			// UVW Rotation axis respect to XYZ.
		double _vA;			// UVW Rotation angle around the v0 axis.	
		double _trsf[9];	// Transformation matrix.
		
		// Private checks.
		bool check();		//!< Checks if a matrix is a rotation one.
		bool getAxisAngle();//!< Derives the rotation axis and angle.

	public:
	   
		//! Special members.
		ref();				//!< Default ctor.		
		
		//! Displacement + Euler angles XYZ ctor.		
		// ref(const point& p, const vector& a);
		
		//! Displacement + UVW base ctor.
		ref(const point& p, const vector& u, const vector& v); 
		
		//! Displacement + V axis and A rotation ctor.
		ref(const point& p, const vector& v, const double& a); 
		
		// Public members overloaded from cake::Object
		oType type() const;						//!< Returns the GP type id.
		uint32_t version() const;				//!< Return the GP version
		size_t size() const;					//!< Returns the entity memory size in bytes.
		void dump(const int& = 0) const;		//!< Dump entity elements.
		std::string stem() const;				//!< Returns GP stem.
		
	 	//! Stream the GP data (both read and write).
		bool stream(std::stringstream& o, const bool& read = false);

		// Direct data access		
		point p0() const;						//!< Returns reference origin.
		//vector a0() const;					//!< Returns reference orientation Euler angles.
		vector v0() const;						//!< Returns reference rotation axis.
		double vA() const;						//!< Returns rotation angle around the v0 axis.		
		vector s0() const;						//!< Returns reference scaling factors.
		vector eU() const;						//!< Returns eU expressed in the XYZ base.
		vector eV() const;						//!< Returns eV expressed in the XYZ base
		vector eW() const;						//!< Returns eW expressed in the XYZ base
		vector eX() const;						//!< Returns eX expressed in the UVW base.
		vector eY() const;						//!< Returns eY expressed in the UVW base
		vector eZ() const;						//!< Returns eZ expressed in the UVW base

		// Transformation settings
		void p0(const point& p);					//!< Sets reference frame origin.
		void a0(const vector& a);					//!< Sets frame orientation by Euler angles in the ZX'Z'' fashion.
		void v0(const vector& v, const double& a);	//!< Sets frame orientation by rotation axis and angle.
		void v0(const double& x, const double& y,	
				const double& z, const double& a);	//!< Sets frame orientation by rotation axis XYZ and angle.
		void s0(const vector& s);					//!< Sets frame scaling (U, V, W ordered).
		
		//! Sets the representation of the UVW base in the XYZ parent base. 
		void uvw(const vector& u, const vector& v);

		// Base coordinate transformation
		point toUVW(const point& p) const;		//!< Returns a point p in this (UVW) frame reference coordinates. 
		point toXYZ(const point& p) const;		//!< Returns a point p in parent (XYZ) frame reference coordinates.
		point& trsf(point& p, const bool& inv = false) const; //!< Apply the transformation to p, the inverse one if inv = true.
		vector toUVW(const vector& v) const;	//!< Returns a vector v in this (UVW) frame reference coordinates. 
		vector toXYZ(const vector& v) const;	//!< Returns a vector v in parent (XYZ) frame reference coordinates.
		vector& trsf(vector& v, const bool& inv = false) const; //!< Apply the transformation to v, the inverse one if inv = true.
};

// #############################################################################
}} // Close Namespaces


// *****************************************************************************
// **						Global namespace public functions				  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator<<(std::ostream& o, const cat::ge::ref& obj)
{
	/*! Overloads the standard output operator << for a cake::geo::Ref object. */
	o << "[Ref: ";
	
	// Displacement point and Euler angles.
	o << ", p0 " << obj.p0() << ", v0 " << obj.v0() 
	  << ", a " << obj.vA() << ", s0 " << obj.s0();
	
	// The rotation matrix.
	o << " u " <<  obj.eU() << ", v " << obj.eV() << ", w " << obj.eW() << "]";
	
	// Returns the stream
	return o;
}

// Overloading check
#endif