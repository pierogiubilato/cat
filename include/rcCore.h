//------------------------------------------------------------------------------
// CAT client core class for the CAT remote client						      --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"rcCore.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"23 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined rcCore_H
#define rcCore_H

// Prevents windows.h including winsock.h
#if defined(_WIN32) || defined(_WIN64)
#define _WINSOCKAPI_
#endif

// SDL net for the socket controls.
#include <SDL_net.h>

// Application components.
#include "gtTools.h"
#include "gpScene.h"
#include "geRef.h"




// *****************************************************************************
// **						OS specific definitions							  **
// *****************************************************************************

// Define this to enable dll/so linking
#define CAT_EXPORTS

// Export style for dll/so
#if defined(_WIN32) || defined(_WIN64)
#   define CAT_CALL __stdcall
#   define CAT_EXPORT_API __declspec(dllexport)
#   define CAT_IMPORT_API __declspec(dllimport)
#else
#   define CAT_CALL
#   define CAT_EXPORT_API
#   define CAT_IMPORT_API
#endif

// dll/so linking
#if defined CAT_EXPORTS
#   define CAT_API   CAT_EXPORT_API
#elif defined CAT_STATIC
#   define CAT_API
#   if defined(_MSC_VER) && !defined(CAT_NO_LIB_PRAGMA)
#       pragma comment(lib, "catClientStatic")
#   endif
#else
#   define CAT_API   CAT_IMPORT_API
#   if defined(_MSC_VER) && !defined(CAT_NO_LIB_PRAGMA)
#       pragma comment(lib, "catClient")
#   endif
#endif

// #############################################################################
namespace cat { namespace rc {

	
	//! Client verbosity constants.
	enum class kVerb : Uint64 {
		null,
		error,
		warn,
		all
	};

	//! Commands constants.
	enum class kCmd : Uint64 {
		clear,
		begin,
		add,
		close,
		wait,
		dummy,
		exit
	};

	//! Connection status constants.
	enum class kStatus : Uint64 {
		null,
		close,
		open,
		error
	};



//! cat::rc::core
/*! cat::rc::core is the TCP-IP client used to communicate with a CAT server.
 *	Server host and port number must be provided at instantiation; they can be
 *	found in the splash screen of the running pear server the client wants to
 *	connect to. cat::client acts as a virtual "drawing pad" where to compose
 *	the actual drawing by using the dc* commands. A drawing is actually called
 *	scene, and a client can create multiple scenes at the same time.
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 23 Sep 2024
 */
class core 
{
	private:
	

	protected:
		
		// Client status.
		Uint64 _verbose;						// Verbosity level.
		Uint64 _status;							// Connection status.
		
		// Connection.
		//IPaddress _IP;							// Server address.
		//TCPsocket _SD;							// Socket descriptor.
 		Uint64 _OPS;							// Optimal Packet Size (bytes).

		// Drawing elements and flags.
		std::vector<gp::scene*> _scene;			// Scene vector.
		std::vector<Uint64> _flush;				// Scene flush counter vector.
		bool sceneStatus() const;				// Checks if at least a Scene is available and selected.	
		void gpLoadBrush(gp::GP* gp);			// Load current brush into a gp.
		void gpLoadFill(gp::GP* gp);			// Load current fill into a gp.
		void gpLoadInherit(gp::GP* gp);			// Load current inheritance into a gp.
		void gpLoadFont(gp::GP* gp);			// Load current font into a gp.				
		void gpLoadTrsf(gp::GP* gp, const bool& = false);	// Load current transformation into a gp.	

		// Active drawing tools settings.
		gp::GPHnd _select;						// Currently selected scene.	
		//gt::brush _brush;						// Current Brush.
		//gt::fill _fill;						// Current Fill.
		//gt::material _material;				// Current Material.
		//gt::inherit _inherit;					// Current inheritance.
		//gt::font _font;						// Current font.
		//gt::trsf _trsf;						// Current transformation.

		// Active pivot gp.
		ge::ref _ref;							// The pivot reference.	

		// Initialize the client.
		bool init(const char* host, const Uint16& port);
		
		// Stream facilities
		bool streamSend(const std::stringstream&) const;	// Send a stream.
		
		// Add a command to a stream.
		void streamCmd(std::stringstream&, const Uint64&, const Uint64&, 
										   const Uint64&, const Uint64&) const;
		
		//! Sends a command to the server.
		bool sendCommand(const Uint64&, const Uint64&, const Uint64&, const Uint64&) const;
		bool sendGP(gp::GP* gp) const;			//!< Sends a single gp to the server.
		bool sendScene(gp::scene* scene);		//!< Sends a complete scene to the server.
		bool socketStatus() const;				//!< Check if the socket status is valid.		
	
	public:

		// Exposed library members
		// -----------------------

		
		// Special members.
		CAT_API CAT_CALL core(const char* host, const Uint16& port, const Uint64& verb = 0); 
		CAT_API CAT_CALL ~core();
	 	
		//! Returns the client status.
		CAT_API Uint64 CAT_CALL status() const {return _status;}
	
		//// Drawing constants
		//// ----------------

		//	// Colors
		//			
		//	// Drawing tools.
		//	static const GPBrush dkBrushDefault;				// The default brush.
		//	static const GPFill dkFillDefault;					// The default fill.
		//	static const GPMaterial dkMaterialDefault;			// The default material.	
		//	static const GPInherit dkInheritDefault;			// The default inheritance.
		//	static const GPFont dkFontDefault;					// The default font.	
		//	static const GPTrsf dkTrsfDefault;					// The default transformation.

		//	// Stippling patterns.
		//	static const Uint16 dkStippleDefault =	0x0000;		// Continuous stroke.
		//	static const Uint16 dkStippleDashLarge = 0xff00;	// Large dashing.
		//	static const Uint16 dkStippleDashMedium = 0xf0f0;	// Medium dashing.
		//	static const Uint16 dkStippleDashFine = 0x8888;		// Fine dashing.
		//	static const Uint16 dkStippleDot = 0x7777;			// Dotting.

		// Drawing commands
		// ----------------

		// *** Scene ***
		// *************

		//! Starts a new scene.
		CAT_API gp::GPHnd CAT_CALL dcSceneBegin(const char* name = "null");
		
		//! Set active scene to draw on.
		CAT_API bool CAT_CALL dcSceneSelect(const gp::GPHnd& = 0);
		
		//! Close the active scene.
		CAT_API bool CAT_CALL dcSceneClose();
		
		//! Flush the active scene to server.
		CAT_API bool CAT_CALL dcSceneFlush();
		
		
		//// *** Brush ***
		//// *************

		//// Retrieve brush call.
		//CAT_API GPBrush CAT_CALL dcBrushGet() const;		
		//
		//// Set a brush brush call.
		//CAT_API void CAT_CALL dcBrushSet(const GPBrush& = dkBrushDefault);		

		////! Complete Brush call with single channel R, G, B, A float color.
		//CAT_API void CAT_CALL dcBrushSet(const bool& active, const double& R = 0.5, const double& G = 0.5,
		//								   const double& B = 0.5, const double& A = 1.0, 
		//								   const double& width = 1, const Uint16& pattern = 0, const Uint32& scale = 1);

		////! Complete Brush call with single RGBA unsigned int 32 color mask.
		//CAT_API void CAT_CALL dcBrushSet(const bool& active, const Uint32& color = 0xFF888888,
		//								   const double& width = 1, const Uint16& pattern = 0, const Uint32& scale = 1);
	
		////! Switch the brush On/off.
		//CAT_API void CAT_CALL dcBrushActive(const bool& Active);
		//
		////! Change the brush color and Alpha (optional).
		//CAT_API void CAT_CALL dcBrushColor(const double& R,  const double&, 
		//									 const double& B, const double& A = 1.0f);

		////! Change the brush color and Alpha with single RGBA argument.
		//CAT_API void CAT_CALL dcBrushColor(const Uint32& RGBA);

		////! Change the brush width and pattern.
		//CAT_API void CAT_CALL dcBrushStroke(const double& width = 1,  const Uint16& pattern = 0, const Uint32& scale = 1); 
		//								  
		//
		//// *** Fill ***
		//// ************

		////! Get current fill.
		//CAT_API GPFill CAT_CALL dcFillGet() const;		
 	//			
		////! Reference fill call.
		//CAT_API void CAT_CALL dcFillSet(const GPFill& = dkFillDefault);		

		////! Complete Fill call with single channel R, G, B, A float color.
		//CAT_API void CAT_CALL dcFillSet(const bool& active, const double& R = 0.5, const double& G = 0.5,
		//							   const double& B = 0.5, const double& A = 1.0, const bool& wire = false);
	
		////! Complete Fill call with single RGBA unsigned int 32 color mask.
		//CAT_API void CAT_CALL dcFillSet(const bool& active, const Uint32& color = 0xFF888888, 
		//								const bool& wire = false);

		////! Switch the fill On/off.
		//CAT_API void CAT_CALL dcFillActive(const bool& active, const bool& wire = false);
		//
		////! Change the fill color and Alpha (optional).
		//CAT_API void CAT_CALL dcFillColor(const double& R,  const double& G, 
		//									 const double& B, const double& A = 1.0);

		////! Change the brush color and Alpha with single RGBA argument.
		//CAT_API void CAT_CALL dcFillColor(const Uint32& RGBA);


		//// *** Material ***
		//// ****************
		//
		////! Get current fill.
		//CAT_API GPMaterial CAT_CALL dcMaterialGet() const;		
 
		////! Reference Material call.
		//CAT_API void CAT_CALL dcMaterialSet(const GPMaterial& = dkMaterialDefault);		

		////! Complete Material call with Active, Shininess and 16 channels float pointer.
		//CAT_API void CAT_CALL dcMaterialSet(const bool& active, const double& shininess = 1, 
		//									  const double* channel = 0);
	
		////! Complete Material call with Active, Shininess and 4 color float pointer.
		//CAT_API void CAT_CALL dcMaterialSet(const bool& active, const double& shininess = 1, 
		//									  const double* ambient = 0, const double* diffuse = 0,
		//									  const double* specular = 0, const double* emission = 0);
		////! Complete Material call with Active, Shininess and 4 color Uint32.
		//CAT_API void CAT_CALL dcMaterialSet(const bool& active, const double& shininess = 1, 
		//									  const Uint32& ambient = 0, const Uint32& diffuse = 0,
		//									  const Uint32& specular = 0, const Uint32& emission = 0);
		//
		//// *** Inheritance ***
		//// *******************

		////! Get current inheritance mode.
		//CAT_API GPInherit CAT_CALL dcInheritGet() const;		

		////! Reference Inheritance mode call.
		//CAT_API void CAT_CALL dcInheritSet(const GPInherit& = dkInheritDefault);		
		//
		////! Change the inheritance mode.
		//CAT_API void CAT_CALL dcInheritSet(const bool& enable, const bool& visibility = true,
		//									 const bool& opacity = true, const bool& wire = true);
		//														    
		//
		//// *** Font ***
		//// ************

		////! Get current font.
		//CAT_API GPFont CAT_CALL dcFontGet() const;		

		////! Set current font by reference.
		//CAT_API void CAT_CALL dcFontSet(const GPFont& = dkFontDefault);		
		//
		////! Set current font.
		//CAT_API void CAT_CALL dcFontSet(const char* family, const char* style,
		//								  const Uint32& size = 64);
		//

		//// *** Transformation ***
		//// **********************

		////! Get current transformation.
		//CAT_API GPTrsf CAT_CALL dcTrsfGet() const;		

		////! Set current font by reference.
		//CAT_API void CAT_CALL dcTrsfSet(const GPTrsf& = dkTrsfDefault);		
		//
		////! Set current transformation, full parameters.
		//CAT_API void CAT_CALL dcTrsfSet(const double& xP, const double& yP, const double& zP,
		//								  const double& a = 0, const double& b = 0, const double& g = 0,
		//								  const double& xS = 1, const double& yS = 1, const double& zS = 1);
		//
		////! Set current transformation position.
		//CAT_API void CAT_CALL dcTrsfPos(const double& x = 0, const double& y = 0, const double& z = 0);

		////! Set current transformation rotation.
		//CAT_API void CAT_CALL dcTrsfRot(const double& a = 0, const double& b = 0, const double& g = 0);
		//CAT_API void CAT_CALL dcTrsfRot(const double& x, const double& y, const double& z, const double& a);

		////! Set current transformation scale.
		//CAT_API void CAT_CALL dcTrsfScale(const double& x = 1, const double& y = 1, const double& z = 1);

		//
		//// *** Geometric Primitives ***
		//// ****************************

		////! A virtual primitive.
		//CAT_API GPHnd CAT_CALL dcVirtual(const GPHnd& parent, const char* name = "");
		//
		////! A parentless virtual primitive.
		//CAT_API GPHnd CAT_CALL dcVirtual(const char* name = "");
		//
		////! A frame defined by a point, a vector and an angle.
		//CAT_API GPHnd CAT_CALL dcFrame(const GPHnd& parent, 
		//								const double& pX, const double& pY, const double& pZ,
		//								const double& vX, const double& vY, const double& vZ,										
		//								const double& a,
		//								const char* name = "");
		//
		////! A parentless frame defined by a point, a vector and an angle.
		//CAT_API GPHnd CAT_CALL dcFrame(const double& pX, const double& pY, const double& pZ,
		//								const double& vX, const double& vY, const double& vZ,										
		//								const double& a,
		//								const char* name = "");
		//
		////! A frame defined by a point and three angles.
		//CAT_API GPHnd CAT_CALL dcFrame(const GPHnd& parent, 
		//								const double& pX, const double& pY, const double& pZ,
		//								const double& aX, const double& aY, const double& aZ,										
		//								const char* name = "");
		//
		////! A parentless frame defined by a point and three angles.
		//CAT_API GPHnd CAT_CALL dcFrame(const double& pX, const double& pY, const double& pZ,
		//								const double& aX, const double& aY, const double& aZ,										
		//								const char* name = "");
		//
		////! Point with parent.
		//CAT_API GPHnd CAT_CALL dcPoint(const GPHnd& parent, 
		//								const double& x, const double& y, const double& z,
		//								const double& r = 1.0f, const char* name = "");
		////! Parentless point.
		//CAT_API GPHnd CAT_CALL dcPoint(const double& x, const double& y, const double& z,
		//								const double& r = 1.0f, const char* name = "");

		////! Line with parent.
		//CAT_API GPHnd CAT_CALL dcLine(const GPHnd& parent,
		//								const double& x1, const double& y1, const double& z1,
		//								const double& x2, const double& y2, const double& z2,
		//								const char* name = "");
		//
		////! Parentless line.
		//CAT_API GPHnd CAT_CALL dcLine(const double& x1, const double& y1, const double& z1,
		//								const double& x2, const double& y2, const double& z2,
		//								const char* name = "");

		////! Polygon with parent.
		//CAT_API GPHnd CAT_CALL dcPolygon(const GPHnd& parent,
		//								const double* vtx, const Uint64& vtxCount,
		//								const bool& closed, const char* name = "");
		//
		////! Parentless polygon.
		//CAT_API GPHnd CAT_CALL dcPolygon(const double* vtx, const Uint64& vtxCount,
		//								const bool& closed, const char* name = "");

		////! Box with parent, 8*3 double vertex list.
		//CAT_API GPHnd CAT_CALL dcBox(const GPHnd& parent, const double* vtx,										
		//								const char* name = "");
		//
		////! Box with no parent, 8*3 double vertex list.
		//CAT_API GPHnd CAT_CALL dcBox(const double* vtx, const char* name = "");
		//
		////! Box with parent.
		//CAT_API GPHnd CAT_CALL dcBox(const GPHnd& parent,
		//								const double& cX, const double& cY, const double& cZ,
		//								const double& sX, const double& sY, const double& sZ,										
		//								const char* name = "");
		//
		////! Box with no parent.
		//CAT_API GPHnd CAT_CALL dcBox(const double& cX, const double& cY, const double& cZ,
		//								const double& sX, const double& sY, const double& sZ,										
		//								const char* name = "");
		//
		////! Tube with parent.
		//CAT_API GPHnd CAT_CALL dcTube(const GPHnd& parent,
		//								const double& riBase, const double& roBase, 
		//								const double& riTop, const double& roTop, 
		//								const double& height, const Uint32& slices = 10, 
		//								const Uint32& stacks = 1, const char* name = "");
		//
		////! Tube with no parent.
		//CAT_API GPHnd CAT_CALL dcTube(const double& riBase, const double& roBase, 
		//								const double& riTop, const double& roTop, 
		//								const double& height, const Uint32& slices = 10, 
		//								const Uint32& stacks = 1, const char* name = "");

		////! Cylinder with parent.
		//CAT_API GPHnd CAT_CALL dcCylinder(const GPHnd& parent,
		//								const double& radius, const double& height, 
		//								const Uint32& slices = 10, const Uint32& stacks = 1, 
		//								const char* name = "");
		//
		////! Cylinder with no parent.
		//CAT_API GPHnd CAT_CALL dcCylinder(const double& radius, const double& height, 
		//								const Uint32& slices = 10, const Uint32& stacks = 1, 
		//								const char* name = "");

		////! Cone with parent.
		//CAT_API GPHnd CAT_CALL dcCone(const GPHnd& parent,
		//								const double& radius, const double& height, 
		//								const Uint32& slices = 10, const Uint32& stacks = 1, 
		//								const char* name = "");
		//
		////! Cone with no parent.
		//CAT_API GPHnd CAT_CALL dcCone(const double& radius, const double& height, 
		//								const Uint32& slices = 10, const Uint32& stacks = 1, 
		//								const char* name = "");

		////! Sphere with parent.
		//CAT_API GPHnd CAT_CALL dcSphere(const GPHnd& parent,
		//								const double& radius, const Uint32& slices = 10, 
		//								const Uint32& stacks = 10, const char* name = "");
		//
		////! Sphere with no parent.
		//CAT_API GPHnd CAT_CALL dcSphere(const double& radius, const Uint32& slices = 10,
		//								const Uint32& stacks = 10, const char* name = "");
		//
		////! Label with parent.
		//CAT_API GPHnd CAT_CALL dcLabel(const GPHnd& parent, const char* text, 
		//								const double& cX, const double& cY, const double& cZ,
		//								const Uint32& alignement = 0, const double& rotation = 0, 
		//								const bool& view2D = false, const char* name = "");
		//								
		////! Label with no parent.
		//CAT_API GPHnd CAT_CALL dcLabel(const char* text, 
		//								const double& cX, const double& cY, const double& cZ,
		//								const Uint32& alignement = 0, const double& rotation = 0,
		//								const bool& view2D = false, const char* name = "");
		//
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
