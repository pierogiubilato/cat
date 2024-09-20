//------------------------------------------------------------------------------
// CAR remote client Drawing Commands class                                   --
// (C) Piero Giubilato 2021-2024, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"rcDCs.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"18 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "rcDCs.h"

// The implemented GPs not included in the H file.
#include "gpStroked.h"
#include "gpFilled.h"
#include "gpFonted.h"
#include "gpEmpty.h"
#include "gpFrame.h"
#include "gpPoint.h"
#include "gpLine.h"
#include "gpPolygon.h"
#include "gpBox.h"
#include "gpTube.h"
#include "gpSphere.h"
#include "gpLabel.h"


//##############################################################################
namespace cat { namespace rc {


// *****************************************************************************
// **							Static members								  **
// *****************************************************************************

	// Default brush.
	const gt::brush DCs::dkBrushDefault = {
		true,				// Active. 
		{0xffb2b2b2, {0.7f, 0.7f, 0.7f, 1.0f}}, // Color.
		{1.0f, 0, 1}		// Stroke
	};

	// Default fill.
	const gt::fill DCs::dkFillDefault = {
		false,						// Not active
		{0xffb2b2b2, {0.7f, 0.7f, 0.7f, 1.0f}}, // Color.		
		false						// Not wireframed.
	};
		
	// Default material.
	const gt::material DCs::dkMaterialDefault = {
		false,						// Not active.
		{0.0f, 0.0f, 0.0f, 1.0f},	// Ambient.
		{0.7f, 0.7f, 0.7f, 1.0f},	// Diffuse.
		{0.7f, 0.7f, 0.7f, 1.0f},	// Specular.
		{0.0f, 0.0f, 0.0f, 1.0f},	// Emission.
		20							// Shininess.
	};

	// Default Inheritance.
	const gt::inherit DCs::dkInheritDefault = {
		true,	// Appearance/global.
		true,	// Visibility.
		true,	// Alpha channel.
		true,	// Wireframe.
		true	// Reference.
	};

	// Default Font.
	const gt::font DCs::dkFontDefault = {
		"",		// Default Font Facility family.
		"",		// Default font Facility style.
		0		// Default Font Facility size.
	};

	// Default reference.
	const gt::trsf DCs::dkTrsfDefault = {
		{0.0f, 0.0f, 0.0f},		// Position (0,0,0), no translation.
		{0.0f, 0.0f, 0.0f},		// Angle (0,0,0), no rotation.
		{1.0f, 1.0f, 1.0f}		// Scale (1,1,1), no scaling.
	};



// *****************************************************************************
// **							  Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
DCs::DCs(const char* host, const Uint16& port, const Uint64& verb): core(host, port, verb)
{

	// Preset drawing tools to default values.
	_brush = dkBrushDefault;	
	_fill = dkFillDefault;
	_material = dkMaterialDefault;
	_inherit = dkInheritDefault;

}
	

// *****************************************************************************
// **								Drawing Tools							  **
// *****************************************************************************


// ************************************ Brush **********************************

//______________________________________________________________________________
gpBrush DCs::dcBrushGet() const
{
	/*! Returns the current brush. */
	return _brush;
}

//______________________________________________________________________________
void DCs::dcBrushSet(const gt::brush& brush)
{
	/*! Sets the drawing brush equal to the argument \c brush. If called without 
	 *	any arguments this function will assign the default brush to the current
	 *	brush, actually resetting it to default values.
	 */
	_brush = brush;
}

//______________________________________________________________________________
void DCs::dcBrushSet(const bool& active, const double& R, const double& G,
						const double& B, const double& A, const double& width,
						const Uint16& pattern, const Uint32& scale)
{
	/*! Sets the drawing brush. Calling this function affects all subsequent
	 *	drawing functions. Brush properties are:
	 *	
	 *	\c active: if false object are actually drawn as invisible, and they will
	 *			not appear by default on the server scene. It will be possible
	 *			to make them visible while browsing the scene on the server. A
	 *			non visible object is identical to a visible one, except it is 
	 *			not displayed.
	 *
	 *	\c R,G,B,A:	the drawing color components, each component in the range
	 *			[0-1]. A component is the Alpha channel, or color opacity, where
	 *			1 means a completely opaque color and 0 a completely transparent
	 *			one (which actually makes the object invisible).
	 *	
	 *	\c width:	the size of the stroke in pixels. 
	 *
	 *	\c pattern: a bitmask describing the stroke stippling. On bits are drawn,
	 *			null bits are left transparent. Use provided dkStipple* constants
	 *			to access predefined styles.
	 *
	 *	\c scale:	the scale factor for the pattern mask, can range in [1 - 256].
	 *
	 *	Note that all these properties can be changed after object drawing by
	 *	directly accessing the object by its handle	and/or on the server side
	 *	through the user interface.
	 *	Calling the function with no argument will reset the brush to default.
	 */
 
	/* Sets the brush for the currently selected scene. */
	
	// Color.
	dcBrushColor(R, G, B, A);
	
	// Status	
	_brush.active = active;
	
	// Stroke.
	_brush.stroke.width = static_cast<float>(width);
	_brush.stroke.pattern = pattern; 
	_brush.stroke.scale = scale;
}

//______________________________________________________________________________
void DCs::dcBrushSet(const bool& active, const Uint32& color, const double& width, 
						const Uint16& pattern, const Uint32& scale)
{
	/*! Same as the main dcBrushSet fuction, except the color argument is passed
	 *	as an unsigned integer of 32 bits.
	 *
	 *	\c color:	the drawing color in the RGBA format. To set a solid full red,
	 *			set 0xFF0000FF, a 50% transparent full green is 0x8800FF00, and
	 *			so on. 
	 */

	// Recall the original function after color conversion.
	dcBrushSet(active, 
				static_cast<float>((color &  0x000000FF) / 255), 
				static_cast<float>((color &  0x0000FF00) / 255), 
				static_cast<float>((color &  0x00FF0000) / 255),
				static_cast<float>((color &  0xFF000000) / 255),
				static_cast<float>(width), pattern, scale);
}

//______________________________________________________________________________
void DCs::dcBrushActive(const bool& active)
{
	/*! Turns the brush Active status. */
	_brush.active = active;
}

//______________________________________________________________________________
void DCs::dcBrushColor(const double& R, const double& G,
						  const double& B, const double& A)
{
	/*! Sets only the brush color, where \c R is the red channel, \c G the green 
	 *	channel, \c B the blue channel and \c A the alpha (transparency)
	 *	channel. EAch channel can range in the [0 - 1] interval
	 */
	
	// Color check.
	float _r = static_cast<float>(r); if (_r < 0) _r = 0; if (_r > 1) _r = 1;
	float _g = static_cast<float>(g); if (_g < 0) _g = 0; if (_g > 1) _g = 1;
	float _b = static_cast<float>(b); if (_b < 0) _b = 0; if (_b > 1) _b = 1;
	float _a = static_cast<float>(a); if (_a < 0) _a = 0; if (_a > 1) _a = 1;

	// Color assign.
	_brush.col.col[0] = _r;
	_brush.col.col[1] = _g;
	_brush.col.col[2] = _b;
	_brush.col.col[3] = _a;
	_brush.col.RGBA = (Uint32)(_r * 255 + _g * 65280 + _b * 16711680 + _a * 4278190080); 
}

//______________________________________________________________________________
void DCs::dcBrushColor(const Uint32& color)
{
	/*! Same as the dcBrushColor fuction, except the color argument is passed
	 *	as an unsigned integer of 32 bits.
	 *
	 *	Color:	the drawing color in the RGBA format. To set a solid full red,
	 *			set 0xff0000ff, a 50% transparent full green is 0x00ff0088, and
	 *			so on. 
	 */

	//std::cout << "Color: " << std::hex << color << std::dec << "\n";
	//std ::cout << "Red channel: " << std::hex << (color >> 24 & 0xff) << std::dec << ", " << (color >> 24 & 0xff) / 255.0f << "\n";
	//std ::cout << "Blue channel: " << std::hex << (color >> 8 & 0xff) << std::dec << ", " << (color >> 8 & 0xff) / 255.0f << "\n";
	dcBrushColor((color >> 24 & 0xff) / 255.0f, 
				 (color >> 16 & 0xff) / 255.0f, 
				 (color >> 8  & 0xff) / 255.0f, 
				 (color >> 0  & 0xff) / 255.0f);
}

//______________________________________________________________________________
void DCs::dcBrushStroke(const double& width, const Uint16& pattern, 
						   const Uint32& scale)
{
	/*! Sets the brush stroke. */
	_brush.stroke.width = static_cast<float>(width);
	_brush.stroke.pattern = pattern;
	_brush.stroke.scale = scale;
}


// ************************************ Fill ***********************************

//______________________________________________________________________________
gt::fill DCs::dcFillGet() const
{
	/*! Returns the curren filling. */
	return _fill;
}

//______________________________________________________________________________
void DCs::dcFillSet(const gt::fill& fill)
{
	/*! Sets the drawing fill equal to the argument \c fill. If called without 
	 *	any arguments this function will assign the default fill to the current
	 *	fill, actually resetting it to default values.
	*/
	_fill = fill;
}

//______________________________________________________________________________
void DCs::dcFillSet(const bool& active, const double& r, const double& g,
					   const double& b, const double& a, const bool& wire)
{
	/*! Sets the drawing fill. Calling this function affects all subsequent
	 *	drawing functions. Fill properties are:
	 *	
	 *	active: if false objects are drawn without any fill, otherwise with
	 *			the current fill. 
	 *
	 *	R, G, B, A:	the filling color components, each component in the range
	 *			[0-1]. A component is the Alpha channel, or color opacity, where
	 *			1 means a completely opaque color and 0 a completely transparent
	 *			one (which actually makes the object fill invisible).
	 *	
	 *	wire:	if true this setting overrides all other settings and draws
	 *			the object in wireframe mode. It is usually used in combination
	 *			with 3D objects which have no brush applied to them, otherwise
	 *			the wireframe lines will superimpose to the object brush outlines,
	 *			giving weird results.
	 *
	 *	material: assign a material to fill the object. For the material to be used,
	 *			its Active property has to be set to true. The default material
	 *			passed as default argument has its Active property set false, so
	 *			the actual filling will simply use the filling color. Material
	 *			plays a role only if lighting is enabled in the server renderer.
	 *
	 *	Note that all these properties can be changed after object drawing by
	 *	directly accessing the object by its handle	and/or on the server side
	 *	through the usr interface.
	 *	Calling the function with no argument will reset the brush to default.
	 */
 
	/* Sets the fill for the currently selected scene. */
	
	// Set Color.
	dcFillColor(r, g, b, a);

	// Set Status.	
	_fill.active = active;
	_fill.wire = wire;
}

//______________________________________________________________________________
void DCs::dcFillSet(const bool& active, const Uint32& color, const bool& wire)
{
	/*! Same as the main dcFillSet fuction, except the color argument is passed
	 *	as an unsigned integer of 32 bits.
	 *
	 *	\c color:	the filling color in the RGBA format. To set a solid full
	 *				red, set 0xFF0000FF, a 50% transparent full green is 
	 *				0x8800FF00, and so on. 
	 */

	// Recall the original function after color conversion.
	dcFillSet(active, 
			 (color >> 24 & 0xff) / 255.0f, 
			 (color >> 16 & 0xff) / 255.0f, 
			 (color >> 8  & 0xff) / 255.0f, 
			 (color >> 0  & 0xff) / 255.0f,
			  wire);
}

//______________________________________________________________________________
void DCs::dcFillActive(const bool& active, const bool& wire)
{
	/*! Turns the fill Active status. */
	_fill.active = active;
	_fill.wire = wire;
}

//______________________________________________________________________________
void DCs::dcFillColor(const double& r, const double& g,
						 const double& b, const double& a)
{
	/*! Sets only the fill color, where \c R is the red channel, \c G the green 
	 *	channel, \c B the blue channel and \c A the alpha (transparency)
	 *	channel. EAch channel can range in the [0 - 1] interval
	 */
	
	// Color check.
	float _r = static_cast<float>(r); if (_r < 0) _r = 0; if (_r > 1) _r = 1;
	float _g = static_cast<float>(g); if (_g < 0) _g = 0; if (_g > 1) _g = 1;
	float _b = static_cast<float>(b); if (_b < 0) _b = 0; if (_b > 1) _b = 1;
	float _a = static_cast<float>(a); if (_a < 0) _a = 0; if (_a > 1) _a = 1;

	// Color assign.
	_fill.col.col[0] = _r;
	_fill.col.col[1] = _g;
	_fill.col.col[2] = _b;
	_fill.col.col[3] = _a;
	_fill.col.RGBA = (Uint32)(_r * 255 + _g * 65280 + _b * 16711680 + _a * 4278190080); 
}

//______________________________________________________________________________
void DCs::dcFillColor(const Uint32& color)
{
	/*! Same as the dcFillColor fuction, except the color argument is passed
	 *	as an unsigned integer of 32 bits.
	 *
	 *	\c color:	the filling color in the RGBA format. To set a solid full 
	 *				red, set 0xFF0000FF, a 50% transparent full green is 
	 *				0x00FF0088, and so on. 
	 */
	dcFillColor((color >> 24 & 0xff) / 255.0f, 
				 (color >> 16 & 0xff) / 255.0f, 
				 (color >> 8  & 0xff) / 255.0f, 
				 (color >> 0  & 0xff) / 255.0f);
}


// ********************************* Material **********************************

//______________________________________________________________________________
gt::material DCs::dcMaterialGet() const
{
	/*! Returns the current material. */
	return _material;
}

//______________________________________________________________________________
void DCs::dcMaterialSet(const gt::material& material)
{
	/*! Set the active material by reference. If the argument is left blank,
	 *	it actually resets the material to the default one.
	 */
	_material = material;
}

//______________________________________________________________________________
void DCs::dcMaterialSet(const bool& active, const double& shininess, const double* channel)
{	
	/*! Sets the current material.
	 *
	 *	\c active:	switch the material begin active or no. If active, it will 
	 *				force the server renderer to use the material instead the 
	 *				fill color to fill the drawn object.
	 *
	 *	\c shininess: Sets how focus is it the specular reflection of an object.
	 *				Its range from 1 to 128, where 1 is completely unfocused
	 *				specular reflection (in that case the Specular color override
	 *				the Diffuse color) and 128 is maximally focused reflection.			
	 *	
	 *	\c channel: the color channel to define the color. To define a material
	 *				4 colors are required, for a total of 16 color channel. They
	 *				follow this order:
	 *				channels [0  to 3]  Ambient color  R G B A.
	 *				channels [4  to 7]  Diffuse color  R G B A.
	 *				channels [8  to 11] Specular color R G B A.
	 *				channels [12 to 15] Emission color R G B A.		
	 *
	 */
	
	// Status
	_material.active = active;
	_material.shininess = static_cast<float>(shininess);
	
	// Material colors.
	for (Uint64 i = 0; i < 4; i++) {
		_material.ambient[i] = static_cast<float>(channel[i]);
		_material.diffuse[i] = static_cast<float>(channel[4 + i]);
		_material.specular[i] = static_cast<float>(channel[8 + i]);
		_material.emission[i] = static_cast<float>(channel[12 + i]);
	}
	
}

//______________________________________________________________________________
void DCs::dcMaterialSet(const bool& active, const double& shininess, 
						   const double* ambient, const double* diffuse,
						   const double* specular, const double* emission)
{	
	/*! Same as the main dcMaterialSet fuction, except the channel color arguments
	 * are passed as 4 float pointer to 4 color arrays of 4 float each. By leaving
	 * an argument = 0 leaves the corresponding color unaffected.
	 */
	
	// Status
	_material.active = active;
	_material.shininess = static_cast<float>(shininess);
	
	// Material colors.
	for (Uint64 i = 0; i < 4; i++) {
		if (ambient) _material.ambient[i] = static_cast<float>(ambient[i]);
		if (diffuse) _material.diffuse[i] = static_cast<float>(diffuse[i]);
		if (specular) _material.specular[i] = static_cast<float>(specular[i]);
		if (emission) _material.emission[i] = static_cast<float>(emission[i]);
	}
}

//______________________________________________________________________________
void DCs::dcMaterialSet(const bool& active, const double& shininess, 
						   const Uint32& ambient, const Uint32& diffuse,
						   const Uint32& specular, const Uint32& emission)
{	
	/*! Same as the main dcMaterialSet fuction, except the channel color arguments
	 * are passed as 4 Uint32 reference containing the color in the RGBA format.
	 */
	
	// Status
	_material.active = active;
	_material.shininess = static_cast<float>(shininess);
	
	// Material colors.
	for (Uint64 i = 0; i < 4; i++) {
		_material.ambient[i] = (float)(ambient >> i * 8) / 255;
		_material.diffuse[i] = (float)(diffuse >> i * 8) / 255;
		_material.specular[i] = (float)(specular >> i * 8) / 255;
		_material.emission[i] = (float)(emission >> i * 8) / 255;
	}
}


// ********************************* Inherit ***********************************

//______________________________________________________________________________
gt::inherit DCs::dcInheritGet() const
{
	/*! Get the current inheritance mode. */
	return _inherit;
}

//______________________________________________________________________________
void DCs::dcInheritSet(const gt::inherit& inherit)
{
	/*! Set the active inheritance mode by reference. If the argument is left 
	 *	blank, it actually resets the inheritance mode to the default one.
	 */
	 _inherit = inherit;
}

//______________________________________________________________________________
void DCs::dcInheritSet(const bool& enable, const bool& visibility, 
						  const bool& alpha, const bool& wire)
{
	/*! Sets the drawing inheritance mode. Drawing inheritance defines how the 
	 * children inherit the parent object properties.
	 *	
	 *	\c enable:		its a general flag: if true, more specific inheritance 
	 *					flag will be considered, otherwise the object will stay
	 *					completely unaffected by parent appearance.
	 *
	 *	\c visibility:	if true, the object visibility is ANDed with the parent 
	 *					visibility.
	 * 
	 *	\c alpha:		if true, object alpha channel(s) will be blended with parent's 
	 *					ones. 
	 *
	 *	\c wire:		if true, object wireframe mode is inherited from the 
	 *					parent.				
	 * 
	 *	Calling the function with no argument will reset the inheritance mode
	 *	to the default values.
	 */
 
	// Sets inheritance.
	_inherit.enabled = enable;
	_inherit.alpha = alpha;
	_inherit.visibility = visibility;
	_inherit.wire = wire;
}


// *********************************** Font ************************************

//______________________________________________________________________________
gt::font DCs::dcFontGet() const
{
	/*! Get the current font. */
	return _font;
}

//______________________________________________________________________________
void DCs::dcFontSet(const gt::font& font)
{
	/*! Set the active font by reference. If the argument is left 
	 *	blank, actually resets the font to the default one.
	 */
	 _font = font;
}

//______________________________________________________________________________
void DCs::dcFontSet(const char* family, const char* style, const Uint32& size)
{
	/*! Sets the font. In case of wrong parameters/unavailable font, the
	 *	standard settings will be applied.
	 *	
	 *	\c family:	font family name: "Arial", "Calibri", "times new roman", ..
	 *				A list of the server available fonts can be printed out by 
	 *				launching the server with the -F option. 
	 *
	 *	\c style:	font style: "normal", "bold", "italic", ....
	 *				A list of the server available style for each font can be 
	 *				printed out by launching the server with the -F option. 
	 *
	 *	\c size:	font size in points. 1 point is 1/64th of inch, not to be
	 *				confused with a pixel!(wave)	 
	 * 
	 *	Calling the function with no argument will reset the inheritance mode
	 *	to the default values.
	 */
 
	// Sets inheritance.
	_font.family = family;
	_font.style = style;
	_font.size = size;
}


// ***************************** Transformation ********************************


//______________________________________________________________________________
gt::trsf DCs::dcTrsfGet() const
{
	/*! Get the current transformation. */
	return _trsf;
}

//______________________________________________________________________________
void DCs::dcTrsfSet(const gt::trsf& trsf)
{
	/*! Set the active transformation by reference. If the argument is left 
	 *	blank, actually resets the transformation to the default one (identity).
	 */
	 _trsf = trsf;
}

//______________________________________________________________________________
void DCs::dcTrsfSet(const double& xP, const double& yP, const double& zP,
					   const double& a, const double& b, const double& g,
					   const double& xS, const double& yS, const double& zS)
{
	/*! Sets the current transformation. The current transformation is the affine
	 *	transformation applied to every drawn graphical entity (GP). By default
	 *	this transformation is equal to the identity, and can be set back at any
	 *	moment to the identity simply invoking dcTrsfSet() with no arguments.
	 * 
	 *	\c xP, yP, zP:	Translation (or new frame origin).
	 *
	 *	\c a ,b ,g:		Euler angles alfa, beta and gamma defining the rotation.
	 *
	 *	\c xS, yS, zS:	Scale factor for the 3 axis.
	 * 
	 */
 
	// Set the reference pivot object.
	_ref.p0(ge::point(xP, yP, zP));
	_ref.a0(ge::vector(a, b, g));
	_ref.s0(ge::vector(xS, yS, zS));
}

//______________________________________________________________________________
void DCs::dcTrsfPos(const double& x, const double& y, const double& z)
{
	/*! Sets current transformation position. */
	_ref.p0(ge::point(x, y, z));
}

//______________________________________________________________________________
void DCs::dcTrsfRot(const double& a, const double& b, const double& g)
{
	/*! Set current transformation rotation. */
	_ref.a0(ge::vector(a, b, g));	
}

//______________________________________________________________________________
void DCs::dcTrsfRot(const double& x, const double& y, const double& z, const double& a)
{
	/*! Set current transformation rotation by defining a rotation axis and a 
	 *	rotation angle. The rotation axis is defined by its three components
	 *	\c x \c y \c z . It is not necessary to provide an unitary versor, as
	 *	the function will normalize it anyway. The rotation angle \c a is in
	 *	radians and measure counterclockwise respect the rotation axis.
	 */
	_ref.v0(ge::vector(x,y,z), a);
}

//______________________________________________________________________________
void DCs::dcTrsfScale(const double& x, const double& y, const double& z)
{
	/*! Set current transformation scale. */
	_ref.s0(ge::vector(x, y, z));
}





// *****************************************************************************
// **																		  **	
// **							Drawing Primitives							  **
// **																		  **
// *****************************************************************************


// ********************************* Virtual ***********************************

//______________________________________________________________________________
gp::GPHnd DCs::dcVirtual(const gp::GPHnd& parent, const char* name)
{
	/*! Draw a virtual object. Returns the object handle, or NULL in case
		of failure. */	

	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Draw the object and retrieve a pointer to it.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::virtual, parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);

	// Sets object specific properties.
	gp->name(name);
	gp->info("");
	
	// Sets object brush and inheritance.
	gpLoadBrush(gp);
	gpLoadInherit(gp);

	// Return the handle to that object
	return newGP; 
}

//______________________________________________________________________________
gp::GPHnd DCs::dcVirtual(const char* name) 
{
	/*! Draw a virtual object, parentless overload. */
	return dcVirtual((gp::GPHnd)0, name);
}

// ********************************** Frame ************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcFrame(const gp::GPHnd& parent, 
					  const double& pX, const double& pY, const double& pZ,
					  const double& vX, const double& vY, const double& vZ,										
					  const double& a,
					  const char* name)
{
	/*! Draw a frame. A frame is an object without graphical representation,
	 *	but which affects all its family (childrens and children's childrens
	 *	in a recursive way) drawing transformations. As the name suggests, it
	 *	sets a new reference frame which all the family objects use for
	 *	drawing. Frame objects can be encapsulated one into each other like		
	 *	all other objects: in this way transformation will be chained in the
	 *	canonical fashion.
	 *
	 *	pX, pY, pZ	are the origin coordinates of the reference frame respect
	 *				to the last reference frame (or the world if no parent			 
	 *				frames are present).
	 *	vX, vY, vZ	are the components of the frame eigenvector, i.e. the 
	 *				frame rotation axis. The frame Z axis will be aligned to
	 *				this vector. It does not need to be a normalized vector.			 
	 *	a			is the angle of rotation around the frame Z axis.
 	 */

 	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::frame(ge::point(pX, pY, pZ), ge::vector(vX, vY, vZ), a), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
	
	// Sets GP specific properties.
	gp->name(name);
	gp->info("");
	
	// Sets GP drawing properties.
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadInherit(gp);
	gpLoadTrsf(gp);

	// Return the handle to that GP.
	return newGP;
}

//______________________________________________________________________________
gp::GPHnd DCs::dcFrame(const double& pX, const double& pY, const double& pZ,
					  const double& vX, const double& vY, const double& vZ,										
					  const double& a,
					  const char* name)
{
	/*! Draw a frame object by stating its origin \c p, its eigenvector \c v
	 *	and the counterclockwise rotation \c a around this vector. Parentless 
	 *	overload. */
	return dcFrame((gp::GPHnd)0, pX, pY, pZ, vX, vY, vZ, a, name); 
}
		
//______________________________________________________________________________
gp::GPHnd DCs::dcFrame(const gp::GPHnd& parent, 
					  const double& pX, const double& pY, const double& pZ,
					  const double& aX, const double& aY, const double& aZ,										
					  const char* name)
{
	/*! Draw a frame. A frame is an object whiteout graphical representation,
	 *	but which affects all its family (childrens and children's childrens
	 *	in a recursive way) drawing transformations. As the name suggests, it
	 *	sets a new reference frame which all the family objects use for
	 *	drawing. Frame objects can be encapsulated one into each other like		
	 *	all other objects: in this way transformation will be chained in the
	 *	canonical fashion.
	 *
	 *	pX, pY, pZ	are the origin coordinates of the reference frame respect
	 *				to the last reference frame (or the world if no parent			 
	 *				frames are present).
	 *	aX, aY, aZ	are the rotation angles around the parent reference frame
	 *				main axes (X, Y and Z), using the canonical counter-clock 
	 *				orientation.
 	 */

	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::frame(ge::point(pX, pY, pZ), ge::vector(aX, aY, aZ)), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
	
	// Sets GP specific properties.
	gp->name(name);
	gp->info("");
	
	// Sets GP drawing properties.
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadInherit(gp);
	gpLoadTrsf(gp);

	// Return the handle to that GP.
	return newGP;
}
		
//______________________________________________________________________________
gp::GPHnd DCs::dcFrame(const double& pX, const double& pY, const double& pZ,
					  const double& aX, const double& aY, const double& aZ,										
					  const char* name)
{
	/*! Draw a frame object by stating its origin \c p and its three rotation
	 *	angles around the three main axes (\c aX \c aY \c aZ). Parentless 
	 *	overload. */
	return dcFrame((gp::GPHnd)0, pX, pY, pZ, aX, aY, aZ, name); 
}		


// *********************************** Point ***********************************

//______________________________________________________________________________
gp::GPHnd DCs::dcPoint(const gp::GPHnd& parent, 
					  const double& x, const double& y, const double& z,
					  const double& r, const char* name)
{
/*! Draw a point. Returns the handle to that object if successful, NULL
	 *	otherwise. \c parent is the parent for the object, \c <x,y,z> is 
	 *	the 3D position of the point and \c r is the point radius in pixel.
	 *	The point radius is invariant respect any model and view transformation.
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new ge::point(x, y, z, r), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
	
	// Sets GP specific properties.
	gp->name(name);
	gp->info("");
	
	// Sets GP drawing properties.
	gpLoadBrush(gp);
	gpLoadInherit(gp);
	gpLoadTrsf(gp);

	// Return the handle to that object
	return newGP; 
}

//______________________________________________________________________________
gp::GPHnd DCs::dcPoint(const double& x, const double& y, const double& z,
					  const double& r, const char* name)
{
	/*! Draw a point. Parentless overload. */
	return dcPoint(0, x, y, z, r, name); 
}


// *********************************** Line ************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcLine(const gp::GPHnd& parent,
					 const double& x1, const double& y1, const double& z1,
					 const double& x2, const double& y2, const double& z2,	
					 const char* name)
{
	/*! Draw a line. Returns the handle to that object if successful, NULL
	 *	otherwise. \c parent is the parent for the object, \c <x1,y1,z1> is the 
	 *	starting point and \c <x2,y2,z2> the ending point of the line. Line
	 *	color, appearance and style are defined by the current settings of the 
	 *	drawing brush. 
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::line(x1, y1, z1, x2, y2, z2), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
	
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadInherit(gp);
	gpLoadTrsf(gp);

	// Return the handle to that GP.
	return newGP;
}

//______________________________________________________________________________
gp::GPHnd DCs::dcLine(const double& x1, const double& y1, const double& z1,
					 const double& x2, const double& y2, const double& z2,	
					 const char* name)
{
	/*! Draw a line object. Parentless overload. */
	return dcLine((gp::GPHnd)0, x1, y1, z1, x2, y2, z2, name); 
}


// ********************************* Polygon ***********************************

//______________________________________________________________________________
gp::GPHnd DCs::dcPolygon(const gp::GPHnd& parent, const double* vtx, const Uint64& vtxCount,
						const bool& closed, const char* name)
{
	/*! Draw a Polygon. Returns the handle to that object if successful, NULL
	 *	otherwise. \c parent is the parent for the object, \c vtx is a pointer
	 * 	to a double array of 3 * vtxCount elements, where elements represent
	 * 	vertex coordinates in this order: x(0), y(0), z(0), x(1), y(1), z(1),
	 *	...., x(n-1), y(n-1), z(n-1).
	 *	\c closed is a boolean forcing the polygon to be closed or not.
	 *	Polygon color, appearance and style are defined by the current settings of the 
	 *	drawing brush and fill. Note that this function draws a NON-oriented 
	 *	polygon, so there is no difference between its two faces when rendered.
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Creates the polygon vertexes.
	go::point* v = new go::point[vtxCount];
	for (Uint64 i = 0; i <vtxCount; i++) {
		Uint64 p = i * 3;
		v[i].XYZ(vtx[p], vtx[p + 1], vtx[p + 2]); 
	}
	
	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::polygon(v, vtxCount, closed), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
	delete[] v;

	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadTrsf(gp);

	// Return the handle to that GP.
	return newGP;
}

//______________________________________________________________________________
gp::GPHnd DCs::dcPolygon(const double* vtx, const Uint64& vtxCount,
						const bool& closed, const char* name)
{
	/*! Draw a polygon object. Parentless overload. */
	return dcPolygon((gpHnd)0, vtx, vtxCount, closed, name); 
}


// *********************************** Box *************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcBox(const gpHnd& parent, const double* vtx, const char* name)
{
	/*! Draws a box. Returns the handle to that object if successful, NULL
	 *	otherwise. \c parent is the parent for the object, \c vtx is the pointer 
	 *	to a 24 float array describing the 8 box vertexes, arranged in the
	 *	{x0, y0, z0, x1, y1, .... , x7, y7, z7} fashion.
	 * 
	 *      4-------5
	 *     /|      /|
	 *    7-------6 |  Vertex numbering respect to a standard XYZ ref frame.
	 *    | 0-----|-1
	 *    |/      |/
	 *    3-------2
	 *
	 *	Box appearance and inheritance are defined by the current settings of 
	 *	the drawing brush and inheritance mode. 
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::box(vtx), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadTrsf(gp);

	// Return the handle to that GP.
	return newGP;
}

//______________________________________________________________________________
gp::GPHnd DCs::dcBox(const double* vtx, const char* name)
{
	/*! Draw a box object by defining its 8 vertexes. Parentless overload. */
	return dcBox((gpHnd)0, vtx, name); 
}

//______________________________________________________________________________
gp::GPHnd DCs::dcBox(const gpHnd& parent,
					const double& cX, const double& cY, const double& cZ,
					const double& sX, const double& sY, const double& sZ,										
					const char* name)
{
	/*! Draws a box. Returns the handle to that object if successful, NULL
	 *	otherwise. \c parent is the parent for the object, \c cX \c cY \c cZ 
	 *	is the center of the box while \c sX \c sY \c sZ contain the dimensions 
	 *	of the box along the three corresponding axis. Box appearance and 
	 *	inheritance are defined by the current settings of the drawing brush
	 *	and inheritance mode. 
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::box(cX, cY, cZ, sX, sY, sZ), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadTrsf(gp);

	// Return the handle to that GP.
	return newGP;
}

//______________________________________________________________________________
gp::GPHnd DCs::dcBox(const double& cX, const double& cY, const double& cZ,
					const double& sX, const double& sY, const double& sZ,										
					const char* name)
{
	/*! Draw a box object. Parentless overload. */
	return dcBox((gpHnd)0, cX, cY, cZ, sX, sY, sZ, name); 
}


// ********************************** Tube *************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcTube(const gpHnd& parent,
					 const double& riBase, const double& roBase, 
					 const double& riTop, const double& roTop, 
					 const double& height, const Uint32& slices,
					 const Uint32& stacks, const char* name)
{
	/*! Draws a tube. Returns the handle to that object if successful, NULL 
	 *	otherwise. \c parent is the parent for the object, \c riBase is the 
	 *	inner radius of the base while roBase is its outer radius. The same hold
	 *	for the top of the tube with riTop and roTop. The tube is built with its 
	 *	base lying on the XY plane and centered in Z = 0 and its top placed at 
	 *	Z = \c height position along the Z axis.
	 *	\c slices are the number of sector the tube circumference is divided 
	 *	into, while \c stacks indicates the number of sector composing its height.
	 *	Tube appearance and inheritance are defined by the current settings 
	 *	of the drawing brush and inheritance mode. To affect the tube orientation 
	 *	and position in space make it children of a frame object.
	 * 	This primitive can be used to draw cylinders and cones as well. Two
	 *	overloaded commands (dcCylinder and dcCone) are anyway provided with
	 *	simplified argument lists.
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::tube(riBase, roBase, riTop, roTop, 
													   height, slices, stacks), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	  	
	// Return the handle to that GP.
	return newGP;	
}

//______________________________________________________________________________
gp::GPHnd DCs::dcTube(const double& riBase, const double& roBase, 
					 const double& riTop, const double& roTop, 
					 const double& height, const Uint32& slices,
					 const Uint32& stacks, const char* name)
{
	/*! Draw a cylinder object. Parentless overload. */
	return dcTube((gpHnd)0, riBase, roBase, riTop, roTop, height, slices, stacks, name);
}


// ******************************** Cylinder ***********************************

//______________________________________________________________________________
gp::GPHnd DCs::dcCylinder(const gpHnd& parent,
						const double& radius, const double& height,
						const Uint32& slices, const Uint32& stacks,
						const char* name)
{
	/*! Draws a cylinder. Returns the handle to that object if successful, NULL 
	 *	otherwise. \c parent is the parent for the object, \c radius is the 
	 *	radius of the cylinder base while \c height is its height. The cylinder
	 *	is built with the base lying on the XY plane and centered in Z = 0, while
	 *	its top is placed at Z = \c height along the Z axis.
	 *	\c slices are the number of sector the tube circumference is divided 
	 *	into, while \c stacks indicates the number of sector composing its height.
	 *	Cylinder appearance and inheritance are defined by the current settings 
	 *	of the drawing brush and inheritance mode. To affect the cylinder orientation 
	 *	and position in space make it children of a frame object.
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::cylinder(radius, radius, height, 
														   slices, stacks), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	  	
	// Return the handle to that GP.
	return newGP;	
}

//______________________________________________________________________________
gp::GPHnd DCs::dcCylinder(const double& radius, const double& height, 
						 const Uint32& slices, const Uint32& stacks, 
						 const char* name)
{
	/*! Draw a cylinder object. Parentless overload. */
	return dcCylinder((gpHnd)0, radius, height, slices, stacks, name);
}


// ********************************** Cone *************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcCone(const gpHnd& parent,
					 const double& radius, const double& height,
					 const Uint32& slices, const Uint32& stacks,
					 const char* name)
{
	/*! Draws a cone. Returns the handle to that object if successful, NULL 
	 *	otherwise. \c parent is the parent for the object, \c radius is the 
	 *	radius of the cone base while \c height is its height. The cone is
	 *	built with the base lying on the XY plane and centered in Z = 0, while
	 *	its top is placed at Z = \c height along the Z axis.
	 *	\c slices are the number of sector the cone circumference is divided 
	 *	into, while \c stacks indicates the number of sector composing its height.
	 *	Cone appearance and inheritance are defined by the current settings 
	 *	of the drawing brush and inheritance mode. To affect the cone orientation 
	 *	and position in space make it children of a frame object.
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::cone(radius, height, 
														slices, stacks), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	
	// Return the handle to that GP.
	return newGP;	
}

//______________________________________________________________________________
gp::GPHnd DCs::dcCone(const double& radius, const double& height, 
					 const Uint32& slices, const Uint32& stacks, 
					 const char* name)
{
	/*! Draw a cylinder object. Parentless overload. */
	return dcCone((gpHnd)0, radius, height, slices, stacks, name);
}


// ********************************* Sphere ************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcSphere(const gpHnd& parent,
					   const double& radius, const Uint32& slices,
					   const Uint32& stacks, const char* name)
{
	/*! Draws a sphere. Returns the handle to that object if successful, 
	 *	NULL otherwise. \c parent is the parent for the object, \c radius is the 
	 *	radius of the sphere, which is centered in XYZ.
	 *	\c slices are the number of meridian sectors of the sphere, while \c 
	 *	stacks indicates the number of parallel sectors of the sphere.
	 *	Sphere appearance and inheritance are defined by the current settings 
	 *	of the drawing brush and inheritance mode. To affect the sphere position
	 *	and orientation in space make it children of a frame object. 
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::sphere(radius, slices, stacks), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets GP drawing properties.
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	
	// Return the handle to that GP.
	return newGP;	
}

//______________________________________________________________________________
gp::GPHnd DCs::dcSphere(const double& radius, const Uint32& slices, 
						const Uint32& stacks, const char* name)
{
	/*! Draw a sphere object. Parentless overload. */
	return dcSphere((gpHnd)0, radius, slices, stacks, name);
}


// ********************************** Label ************************************

//______________________________________________________________________________
gp::GPHnd DCs::dcLabel(const gpHnd& parent, const char* text,
					  const double& cX, const double& cY, const double& cZ,
					  const Uint32& alignment, const double& rotation, 
					  const bool& view2D, const char* name)
{
	/*! Draws a label. A label is a simple text string which keeps a fixed 
	 *	orientation respect the scene viewport (it stays aligned with the 
	 *	viewer reference frame (the screen!), not the actual scene one). The 
	 *	label will use the current font set by the latest dcFont(...) call.
	 *
	 *	\c text:	the label text, which is parsed the same way C parses 
	 *				strings, so some escape sequences are supported:
	 *				"\n" -> newline.
	 *				No others escape sequences supported at the moment.
 	 * 
	 *	\c cX,cY,cZ: the 3D coordinates of the label anchor point.
	 *
	 *	\c alignment: the alignment of the label respect the anchor point,
	 *				can be a bit-and of the following constants.
	 *				kal_Default:	center label on the anchor point (hor & ver).
	 *				kal_Hor_Left:	extends label right the anchor point (hor).
	 *				kal_Hor_Mid:	centers label on the anchor point (hor).
	 *				kal_Hor_Right:  extends label left the anchor point (hor).
	 *				kal_Ver_Top:    extends label down the anchor point (ver).
	 *				kal_Ver_Mid:	centers label on the anchor point (ver).
	 *				kal_Ver_Bottom: extends label up the anchor point (ver).
	 *
   	 *	\c rotation: the rotation of the label in radians, CCW  oriented 
	 *				respect the viewport (user) horizontal axis.
	 * 
	 *	\c view2D:	a boolean which sets the label as fixed respect to the viewer
	 *				reference frame (the screen). In that case, the Z coordinate
	 *				is ignored while the X and Y coordinates represents the shift 
	 *				from the center of the view screen in pixels. Use this option
	 *				to create fixed, model view independent labels.
	 */
	
	// Checks if a scene is currently selected.
	if (sceneStatus()) return 0;

	// Adds the GP to the scene.
	gp::GPHnd newGP = _scene[_select]->gpAdd(new gp::label(text, cX, cY, cZ, alignment, rotation, view2D), parent);
	gp::GP* gp = _scene[_select]->gpGet(newGP);
																		
	// Sets GP specific properties.
	gp->Name(name);
	gp->Info("");
	
	// Sets label drawing properties (fill and material not actually used).
	gpLoadInherit(gp);
	gpLoadBrush(gp);
	gpLoadFill(gp);
	gpLoadFont(gp);

	// Return the handle to that GP.
	return newGP;
}

//______________________________________________________________________________
gp::GPHnd DCs::dcLabel(const char* text,
					  const double& cX, const double& cY, const double& cZ,
					  const Uint32& alignment, const double& rotation,
					  const bool& view2D, const char* name)
{
	/*! Draw a label object. Parentless overload. */
	return dcLabel((gpHnd)0, text, cX, cY, cZ, alignment, rotation, view2D, name); 
}


//##############################################################################
}} // Close namespaces
