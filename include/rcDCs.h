//------------------------------------------------------------------------------
// CAT remote client class, Drawing Commands								  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"rcDCs.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined rcDCs_H
#define rcDCs_H

// STL.
#include<cstdint>

// Application
#include "rcCore.h"

// #############################################################################
namespace cat { namespace rc {

//! CAT DCs (Drawing Commands)
/*! cat::rc::DCs is a layer over the cat::rc::core class which implements
 *	all the basic drawing commands issued by the client side.
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 23 Sep 2024
 */
class DCs: public core 
{
	
	private:

		// Client-side Drawing constants
		// -----------------------------

		// Colors

		// Drawing tools.
		static const gt::brush dkBrushDefault;				// The default brush.
		static const gt::fill dkFillDefault;				// The default fill.
		static const gt::material dkMaterialDefault;		// The default material.	
		static const gt::inherit dkInheritDefault;			// The default inheritance.
		static const gt::font dkFontDefault;				// The default font.	
		static const gt::trsf dkTrsfDefault;				// The default transformation.

		// Stippling patterns.
		static const Uint16 dkStippleDefault = 0x0000;		// Continuous stroke.
		static const Uint16 dkStippleDashLarge = 0xff00;	// Large dashing.
		static const Uint16 dkStippleDashMedium = 0xf0f0;	// Medium dashing.
		static const Uint16 dkStippleDashFine = 0x8888;		// Fine dashing.
		static const Uint16 dkStippleDot = 0x7777;			// Dotting.


		// Internal state variables.
		gt::brush _brush;			// The current brush.
		gt::fill _fill;				// The current  fill.
		gt::material _material;		// The current material.	
		gt::inherit _inherit;		// The current inheritance.
		gt::font _font;				// The current font.	
		gt::trsf _trsf;				// The current transformation.



	public:

	// Special members.
	CAT_API CAT_CALL DCs(const char* host, const int& port, const int& verb = 0);
	//DCs(const char* host, const int& port, const int& verb = 0);
		
	
	// Client-side Drawing commands
	// ----------------------------

		// *** Brush ***
		// *************

		// Retrieve brush call.
		CAT_API gt::brush CAT_CALL dcBrushGet() const;		
		
		// Set a brush brush call.
		CAT_API void CAT_CALL dcBrushSet(const gt::brush& = dkBrushDefault);		

		//! Complete Brush call with single channel R, G, B, A float color.
		CAT_API void CAT_CALL dcBrushSet(const bool& active, const double& R = 0.5, const double& G = 0.5,
										   const double& B = 0.5, const double& A = 1.0, 
										   const double& width = 1, const Uint16& pattern = 0, const Uint32& scale = 1);

		//! Complete Brush call with single RGBA unsigned int 32 color mask.
		CAT_API void CAT_CALL dcBrushSet(const bool& active, const Uint32& color = 0xFF888888,
										   const double& width = 1, const Uint16& pattern = 0, const Uint32& scale = 1);
	
		//! Switch the brush On/off.
		CAT_API void CAT_CALL dcBrushActive(const bool& active);
		
		//! Change the brush color and Alpha (optional).
		CAT_API void CAT_CALL dcBrushColor(const double& R,  const double&, 
											 const double& B, const double& A = 1.0f);

		//! Change the brush color and Alpha with single RGBA argument.
		CAT_API void CAT_CALL dcBrushColor(const Uint32& RGBA);

		//! Change the brush width and pattern.
		CAT_API void CAT_CALL dcBrushStroke(const double& width = 1,  const Uint16& pattern = 0, const Uint32& scale = 1); 
										  
		
		// *** Fill ***
		// ************

		//! Get current fill.
		CAT_API gt::fill CAT_CALL dcFillGet() const;		
 				
		//! Reference fill call.
		CAT_API void CAT_CALL dcFillSet(const gt::fill& = dkFillDefault);		

		//! Complete Fill call with single channel R, G, B, A float color.
		CAT_API void CAT_CALL dcFillSet(const bool& active, const double& R = 0.5, const double& G = 0.5,
									   const double& B = 0.5, const double& A = 1.0, const bool& wire = false);
	
		//! Complete Fill call with single RGBA unsigned int 32 color mask.
		CAT_API void CAT_CALL dcFillSet(const bool& active, const Uint32& color = 0xFF888888, 
										const bool& wire = false);

		//! Switch the fill On/off.
		CAT_API void CAT_CALL dcFillActive(const bool& active, const bool& wire = false);
		
		//! Change the fill color and Alpha (optional).
		CAT_API void CAT_CALL dcFillColor(const double& R,  const double& G, 
											 const double& B, const double& A = 1.0);

		//! Change the brush color and Alpha with single RGBA argument.
		CAT_API void CAT_CALL dcFillColor(const Uint32& rgba);


		// *** Material ***
		// ****************
		
		//! Get current fill.
		CAT_API gt::material CAT_CALL dcMaterialGet() const;		
 
		//! Reference Material call.
		CAT_API void CAT_CALL dcMaterialSet(const gt::material& = dkMaterialDefault);

		//! Complete Material call with Active, Shininess and 16 channels float pointer.
		CAT_API void CAT_CALL dcMaterialSet(const bool& active, const double& shininess = 1, 
											  const double* channel = 0);
	
		//! Complete Material call with Active, Shininess and 4 color float pointer.
		CAT_API void CAT_CALL dcMaterialSet(const bool& active, const double& shininess = 1, 
											  const double* ambient = 0, const double* diffuse = 0,
											  const double* specular = 0, const double* emission = 0);
		//! Complete Material call with Active, Shininess and 4 color Uint32.
		CAT_API void CAT_CALL dcMaterialSet(const bool& active, const double& shininess = 1, 
											  const Uint32& ambient = 0, const Uint32& diffuse = 0,
											  const Uint32& specular = 0, const Uint32& emission = 0);
		
		// *** Inheritance ***
		// *******************

		//! Get current inheritance mode.
		CAT_API gt::inherit CAT_CALL dcInheritGet() const;		

		//! Reference Inheritance mode call.
		CAT_API void CAT_CALL dcInheritSet(const gt::inherit& = dkInheritDefault);		
		
		//! Change the inheritance mode.
		CAT_API void CAT_CALL dcInheritSet(const bool& enable, const bool& visibility = true,
											 const bool& opacity = true, const bool& wire = true);
																    
		
		// *** Font ***
		// ************

		//! Get current font.
		CAT_API gt::font CAT_CALL dcFontGet() const;		

		//! Set current font by reference.
		CAT_API void CAT_CALL dcFontSet(const gt::font& = dkFontDefault);		
		
		//! Set current font.
		CAT_API void CAT_CALL dcFontSet(const char* family, const char* style,
										  const Uint32& size = 64);
		

		// *** Transformation ***
		// **********************

		//! Get current transformation.
		CAT_API gt::trsf CAT_CALL dcTrsfGet() const;		

		//! Set current font by reference.
		CAT_API void CAT_CALL dcTrsfSet(const gt::trsf& = dkTrsfDefault);		
		
		//! Set current transformation, full parameters.
		CAT_API void CAT_CALL dcTrsfSet(const double& xP, const double& yP, const double& zP,
										  const double& a = 0, const double& b = 0, const double& g = 0,
										  const double& xS = 1, const double& yS = 1, const double& zS = 1);
		
		//! Set current transformation position.
		CAT_API void CAT_CALL dcTrsfPos(const double& x = 0, const double& y = 0, const double& z = 0);

		//! Set current transformation rotation.
		CAT_API void CAT_CALL dcTrsfRot(const double& a = 0, const double& b = 0, const double& g = 0);
		CAT_API void CAT_CALL dcTrsfRot(const double& x, const double& y, const double& z, const double& a);

		//! Set current transformation scale.
		CAT_API void CAT_CALL dcTrsfScale(const double& x = 1, const double& y = 1, const double& z = 1);

		
		// *** Geometric Primitives ***
		// ****************************

		//! A virtual primitive.
		CAT_API gp::GPHnd CAT_CALL dcVirtual(const gp::GPHnd& parent, const char* name = "");
		
		//! A parentless virtual primitive.
		CAT_API gp::GPHnd CAT_CALL dcVirtual(const char* name = "");
		
		//! A frame defined by a point, a vector and an angle.
		CAT_API gp::GPHnd CAT_CALL dcFrame(const gp::GPHnd& parent,
										const double& pX, const double& pY, const double& pZ,
										const double& vX, const double& vY, const double& vZ,										
										const double& a,
										const char* name = "");
		
		//! A parentless frame defined by a point, a vector and an angle.
		CAT_API gp::GPHnd CAT_CALL dcFrame(const double& pX, const double& pY, const double& pZ,
										const double& vX, const double& vY, const double& vZ,										
										const double& a,
										const char* name = "");
		
		//! A frame defined by a point and three angles.
		CAT_API gp::GPHnd CAT_CALL dcFrame(const gp::GPHnd& parent,
										const double& pX, const double& pY, const double& pZ,
										const double& aX, const double& aY, const double& aZ,										
										const char* name = "");
		
		//! A parentless frame defined by a point and three angles.
		CAT_API gp::GPHnd CAT_CALL dcFrame(const double& pX, const double& pY, const double& pZ,
										const double& aX, const double& aY, const double& aZ,										
										const char* name = "");
		
		//! Point with parent.
		CAT_API gp::GPHnd CAT_CALL dcPoint(const gp::GPHnd& parent,
										const double& x, const double& y, const double& z,
										const double& r = 1.0f, const char* name = "");
		//! Parentless point.
		CAT_API gp::GPHnd CAT_CALL dcPoint(const double& x, const double& y, const double& z,
										const double& r = 1.0f, const char* name = "");

		//! Line with parent.
		CAT_API gp::GPHnd CAT_CALL dcLine(const gp::GPHnd& parent,
										const double& x1, const double& y1, const double& z1,
										const double& x2, const double& y2, const double& z2,
										const char* name = "");
		
		//! Parentless line.
		CAT_API gp::GPHnd CAT_CALL dcLine(const double& x1, const double& y1, const double& z1,
										const double& x2, const double& y2, const double& z2,
										const char* name = "");

		//! Polygon with parent.
		CAT_API gp::GPHnd CAT_CALL dcPolygon(const gp::GPHnd& parent,
										const double* vtx, const Uint64& vtxCount,
										const bool& closed, const char* name = "");
		
		//! Parentless polygon.
		CAT_API gp::GPHnd CAT_CALL dcPolygon(const double* vtx, const Uint64& vtxCount,
										const bool& closed, const char* name = "");

		//! Box with parent, 8*3 double vertex list.
		CAT_API gp::GPHnd CAT_CALL dcBox(const gp::GPHnd& parent, const double* vtx,
										const char* name = "");
		
		//! Box with no parent, 8*3 double vertex list.
		CAT_API gp::GPHnd CAT_CALL dcBox(const double* vtx, const char* name = "");
		
		//! Box with parent.
		CAT_API gp::GPHnd CAT_CALL dcBox(const gp::GPHnd& parent,
										const double& cX, const double& cY, const double& cZ,
										const double& sX, const double& sY, const double& sZ,										
										const char* name = "");
		
		//! Box with no parent.
		CAT_API gp::GPHnd CAT_CALL dcBox(const double& cX, const double& cY, const double& cZ,
										const double& sX, const double& sY, const double& sZ,										
										const char* name = "");
		
		//! Tube with parent.
		CAT_API gp::GPHnd CAT_CALL dcTube(const gp::GPHnd& parent,
										const double& riBase, const double& roBase, 
										const double& riTop, const double& roTop, 
										const double& height, const Uint32& slices = 10, 
										const Uint32& stacks = 1, const char* name = "");
		
		//! Tube with no parent.
		CAT_API gp::GPHnd CAT_CALL dcTube(const double& riBase, const double& roBase,
										const double& riTop, const double& roTop, 
										const double& height, const Uint32& slices = 10, 
										const Uint32& stacks = 1, const char* name = "");

		//! Cylinder with parent.
		CAT_API gp::GPHnd CAT_CALL dcCylinder(const gp::GPHnd& parent,
										const double& radius, const double& height, 
										const Uint32& slices = 10, const Uint32& stacks = 1, 
										const char* name = "");
		
		//! Cylinder with no parent.
		CAT_API gp::GPHnd CAT_CALL dcCylinder(const double& radius, const double& height,
										const Uint32& slices = 10, const Uint32& stacks = 1, 
										const char* name = "");

		//! Cone with parent.
		CAT_API gp::GPHnd CAT_CALL dcCone(const gp::GPHnd& parent,
										const double& radius, const double& height, 
										const Uint32& slices = 10, const Uint32& stacks = 1, 
										const char* name = "");
		
		//! Cone with no parent.
		CAT_API gp::GPHnd CAT_CALL dcCone(const double& radius, const double& height,
										const Uint32& slices = 10, const Uint32& stacks = 1, 
										const char* name = "");

		//! Sphere with parent.
		CAT_API gp::GPHnd CAT_CALL dcSphere(const gp::GPHnd& parent,
										const double& radius, const Uint32& slices = 10, 
										const Uint32& stacks = 10, const char* name = "");
		
		//! Sphere with no parent.
		CAT_API gp::GPHnd CAT_CALL dcSphere(const double& radius, const Uint32& slices = 10,
										const Uint32& stacks = 10, const char* name = "");
		
		//! Label with parent.
		CAT_API gp::GPHnd CAT_CALL dcLabel(const gp::GPHnd& parent, const char* text,
										const double& cX, const double& cY, const double& cZ,
										const Uint32& alignement = 0, const double& rotation = 0, 
										const bool& view2D = false, const char* name = "");
										
		//! Label with no parent.
		CAT_API gp::GPHnd CAT_CALL dcLabel(const char* text,
										const double& cX, const double& cY, const double& cZ,
										const Uint32& alignement = 0, const double& rotation = 0,
										const bool& view2D = false, const char* name = "");
		
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
