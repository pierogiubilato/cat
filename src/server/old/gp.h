//------------------------------------------------------------------------------
// Drawing primitive object for the CAT graphic display	  					  --
// (C) Piero Giubilato 2021-2025, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gp.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.3"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Overloading check
#ifndef gp_H
#define gp_H

// All GPs embody their own drawing calls, so here we include the relevant
// graphics library(es) once for all.
#include "glad.h"

// Application
#include "co.h"

// Vertex and Vector are special GEs which inherits directly from cat::ge to be
// lightweight in memory, as they are used as massive storage elements.
#include "geCoord.h"

// Reference is another "special" GE that actually just inherits from cat::go.
// Here a forward reference is used for setting it as default modifying object.
#include "geRef.h"

// Server ONLY elements, used for actual drawing and rendering of the primitives.
#ifdef CAT_SERVER
	//#include "pear_ui_Bar.h"
	//#include "pear_gp_GL.h"
#endif

// cat::go::gp::scene forward declaration
namespace cat { namespace gp {
	class scene;
}}

// #############################################################################
namespace cat { namespace gp {


// *****************************************************************************
// **							Types and Structures						  **
// *****************************************************************************

//______________________________________________________________________________
// Simple support structures.
struct GPPos { float x; float y; float z; };
struct GPAng { float a; float b; float g; };
struct GPDim { float x; float y; float z; };
struct GPColor { uint32_t RGBA; float col[4]; };
struct GPStroke { float width; uint16_t pattern; uint32_t scale; };



// *****************************************************************************
// **							Types and Structures						  **
// *****************************************************************************

//! The handle representing a GP object.
typedef uint64_t GPHnd;

// Simple support structures.
//struct GPPos {float x; float y; float z;};
//struct GPAng {float a; float b; float g;};
//struct GPDim {float x; float y; float z;};
//struct GPColor {Uint32 RGBA; float Col[4];};
//struct GPStroke {float Width; Uint16 Pattern; Uint32 Scale;};

// Key drawing tools structures.
//class GPBrush: Public GO {bool Active; GPColor Col; GPStroke Stroke;};
//class GPFill: Public GO  {bool Active; GPColor Col; bool Wire;};
//class GPMaterial: Public GO {bool Active; float Ambient[4]; float Diffuse[4]; 
//				   float Specular[4]; float Emission[4]; float Shininess;};
//struct GPInherit: Public GO {bool Enabled; bool Visibility; bool Alpha; 
//				  bool Wire; bool Ref;};
//struct GPFont: Public GO {std::string Family; std::string Style; Uint32 Size;};
//struct GPTrsf: Public GO {GPPos Position; GPAng Rotation; GPDim Scale;};


// *****************************************************************************
// **							The basic pear GP							  **
// *****************************************************************************

/*! cat::GP is the base class for all cat Graphic Primitives. A graphic
*	primitive is a basic element which can be displayed in a scene, like a
*	line, a box or text. pear::GP provides all the basic functionalities and
*	properties shared by the graphic primitives, and also manages the OpenGL
*	Display List to improve rendering performances, as well as hierarchical.
*	transformation propagation.
*
*	GP derived objects are used both on the CLIENT ans SERVER side, like all
*	the GD objects, but as they also contain their own drawing functions they
*	are compiled and linked differently on the CLIENT and on the SERVER. The
*	flag CAT_SERVER must be defined when compiling and linking on the server
*	side, as this will include the OpenGL libraries and the UI modules. All
*	OpenGL-related calls must be included into the ifdef block to avoid error
*	on the client side, which must stay OpenGL and UI free.
*
*	\author Piero Giubilato
*	\version 1.2
*	\date 24 Sep 2024	
*/

//______________________________________________________________________________
class GP : public CO
{
	public:

		//// The different GP (Graphic Primitive) types.
		//enum class ktype : Uint32 {
		//	null = 0,
		//	base = 1,
		//	stroked = 2,	// | These are layer GPs, i.e. GPs 
		//	filled = 4,		// | providing specific properties
		//	fonted = 8,		// | to others GPS.
		//	scene = 16,
		//	frame = 32,
		//	material = 64,
		//	palette = 128,
		//	point = 256,
		//	line = 512,
		//	polygon = 1024,
		//	box = 2048,
		//	tube = 4096,
		//	cylinder = 8192,
		//	cone = 16384,
		//	sphere = 32768,
		//	label = 65536
		//	//131072,262144,524288, 1048576
		//};

		//! Status mode constants.
		enum class kMode : uint_fast32_t {
			null = 0,
			visible = 1,	//! GP is visible.
			frozen = 2,		//! GP is frozen.
			wire = 4,		//! GP is in wireframe mode.
			selected = 8,	//! GP is selected.
			parsed = 16,	//! GP has been already parsed.
			expanded = 32,	//! GP is expanded.
			needRedraw = 64	//! GP is expanded.
		};

		//! Inheritance mode constants.
		enum class kInhr : uint_fast32_t {
			null = 0,
			enable = 1,		//! Inheritance On/Off.
			visible = 2,	//! Inherits visibility status.
			alpha = 4,		//! Inherits alpha channel.
			wire = 8,		//! Inherits wireframe mode.
			ref = 16		//! Inherits reference frame.
		};

		// Alignment constants.
		enum kAlign : uint_fast32_t {
			null = 0,
			horLeft = 1,
			horMid = 2,
			horRight = 4,
			verTop = 8,
			verMid = 16,
			verBottom = 32
		};

		// Static data members for selection mode appearance.
		static float _selColor[4];
		static float _selWidth;
		static uint16_t _selPattern;
		static uint32_t _selFactor;

		// Special members.
		GP();									//!< Default ctor.
		virtual ~GP();							//!< Virtual dtor.

		// Special factory Build.
		GP* build(const uint64_t&) const;		//!< Builds a new GP object.	

		// Default interface public members, overload cat::CO class.
		oType type() const;						//!< Returns GP object type.
		uint32_t version() const;				//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		void dump(const int & = 0) const;	//!< Dumps GP data.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		bool stream(std::stringstream& o, const bool& read = false);

		// Default public transformations (all near-pure virtual here, must be implemented for every derived class).		
		virtual GP& trsf(const ge::ref&, const bool&) { return *this; }	//!< Transform the GP using the ref trasnformation.	 	
		virtual GP& trsfIn(const ge::ref& r) { return trsf(r, false); }	//!< Put the GP into reference frame ref.	 	
		virtual GP& trsfOut(const ge::ref& r) { return trsf(r, true); }	//!< Get the GP out reference frame ref.

		// ---------------------------------------------------------------------------
		// The following function provides family management, and are not replicated 
		// by the derived classes.
		
		// Public family functions.
		scene* owner() const;					//!< Retrieves the owner pointer.
		void owner(scene*);						//!< Sets the owner pointer.
		GPHnd parent() const;					//!< Retrieves the parent handle.
		void parent(GPHnd);						//!< Sets the parent handle.
		bool childAdd(GPHnd);					//!< Adds a child to the GP.
		bool childDel(GPHnd cHnd);				//!< Deletes the child of handle cHnd from the GP.
		GPHnd childGet(int cIdx) const;			//!< Returns the child(cIdx) handle.
		int childCount() const;					//!< Returns the number of childs.

		// GP public basic members.
		GPHnd handle() const;					//!< Returns the GP unique Id.
		void handle(GPHnd);						//!< Sets the GP unique Id.
		const char* name() const;				//!< Return GP name.
		void name(const char*);					//!< Sets the GP name.
		const char* info() const;				//!< Return GP info.
		void info(const char*);					//!< Sets the GP info.

		// GP public mode members.
		bool modeVisible() const;				//!< Retrieves GP visible status.
		void modeVisible(const bool&);			//!< Sets the GP visible status.
		bool modeWireframe() const;				//!< Retrieves GP wireframe status.
		void modeWireframe(const bool&);		//!< Sets the GP wireframe status.	
		bool modeFrozen() const;				//!< Retrieves GP frozen status.
		void modeFrozen(const bool&);			//!< Sets the GP frozen status.
		bool modeSelected() const;				//!< Retrieves GP selected status.
		void modeSelected(const bool&);			//!< Sets the GP selected status.	
		bool modeParsed() const;				//!< Retrieves GP parsed status.
		void modeParsed(const bool&);			//!< Sets the GP parsed status.
		bool modeExpanded() const;				//!< Retrieves GP parsed status.
		void modeExpanded(const bool&);			//!< Sets the GP parsed status.	
		bool modeNeedRedraw() const;			//!< Retrieves if the GP need redraw.
		void modeNeedRedraw(const bool&);		//!< Sets the if the GP need redraw.	

		bool modeGet(const uint8_t&) const;		//!< Retrieves the GP status equivalent to flag.
		void modeSet(const uint8_t&, const bool&);//!< Sets the GP status equivalent to flag.

		// Public inheritance members.
		bool inhrAppear() const;				//!< Return appearance inheritance.
		void inhrAppear(const bool&);			//!< Set appearance inheritance.
		bool inhrVisible() const;				//!< Return visibility inheritance.
		void inhrVisible(const bool&);			//!< Set visibility inheritance.
		bool inhrAlpha() const;					//!< Return opacity inheritance.
		void inhrAlpha(const bool&);			//!< Set opacity inheritance.		
		bool inhrWire() const;					//!< Return Wireframe inheritance.
		void inhrWire(const bool&);				//!< Set wireframe inheritance.		
		bool inhrRef() const;					//!< Return reference inheritance.
		void inhrRef(const bool&);			//!< Set reference inheritance.

	protected:

		// Basic GP properties
		GPHnd _handle;							//!< GP unique Handle.
		char* _name;							//!< GP name. String are not used here to save memory.
		char* _info;							//!< GP info. String are not used here to save memory.

		// Family relationships.
		scene* _ownerPtr;						//!< The GP owner (the scene it belongs to, NOT STREAMED).
		GPHnd _parentHnd;						//!< The parent GP Handle (if any).
		GP* _parentPtr;							//!< The parent GP Pointer (if instantiated, NOT STREAMED).
		std::vector<GPHnd> _childHnd;			//!< The child(s) GP(s) pointers (if any, NOT STREAMED).

		// GP status mode.
		bool _modeVisible;						//!< GP drawn or not.
		bool _modeWire;							//!< GP wireframe mode.
		bool _modeFrozen;						//!< frozen or not.
		bool _modeSelected;						//!< GP is selected.
		bool _modeParsed;						//!< Has been already parsed or not. NOT streamed.
		bool _modeExpanded;						//!< Expanded to show children or not. NOT streamed.
		bool _modeNeedRedraw;					//!< Something has changed. NOT streamed.

		// How the family relationships affect the appearance.
		bool _inhrAppear;						//!< Inherit global.
		bool _inhrVisible;						//!< Inherit visibility.
		bool _inhrAlpha;						//!< Inherit alpha channel.
		bool _inhrWire;							//!< Inherit wireframe.
		bool _inhrRef;							//!< Inherit reference frame.

		// Status and Inheritance bitmasks:
		uint8_t _modeStore;						//!< Byte storing the current status.
		uint8_t _inhrStore;						//!< Byte storing the inheritance settings.

		// Offset a point accordingly to the alignment constants.
		GPPos offset(const GPDim&, const int& alignment) const;
	
	private:

		// Private functions.
		void init(scene* = 0, GPHnd = 0);	//!< Init the GP.



	// GL drawing and UI functions are ONLY defined for the SERVER side!
	// -----------------------------------------------------------------
	#ifdef CAT_SERVER	
		
		public:
			
			// Display and drawing.
			uint8_t _glDspListIdx;				//!< The GP associated dDisplayList.
			void glBuild();						//!< Manages the DisplayList.
			void glDisplay();					//!< Draws the DisplayList.
			virtual void glDraw();				//!< Draws the GP on the current GLcontext.
			virtual void glDrawSel();			//!< Draws the GP in selection mode.
			virtual void glDrawEnd();			//!< Closes the GP drawing. Mandatory call!
			virtual double glAlpha();			//!< Returns the gp (hierarchical) transparency.
			virtual void glTrsfApply();			//!< Apply (push) the gp Ref (hierarchical) transformation.
			virtual void glTrsfReset();			//!< Reset (pop) the gp Ref (hierarchical) transformation.

			// UI interaction.
//			virtual void uiBarLoad(ui::Bar&);	//!< Load a bar with the GP specific properties.	
//			static void TW_CALL cbkSizeGet(void*, void*);	//!< Get the GP size for TwBar.
	#endif
};

// #############################################################################
}} // Close namespaces



// *****************************************************************************
// **					Global namespace public functions					  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::GP& obj)
{
	/*! Overloads standard output operator << for a generic cake::object. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif
