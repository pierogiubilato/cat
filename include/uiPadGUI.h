//------------------------------------------------------------------------------
// CAT User Interface pad_GUI class					 						  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiPadGUI.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"21 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined uiPadGUI_H
#define uiPadGUI_H

// Application components.
#include "ui.h"
#include "uiMouse.h"
#include "uiBar.h"
#include "uiSplash.h"
#include "gp.h"

// AntTweakBar
//#include "AntTweakBar/AntTweakBar.h"


// #############################################################################
namespace cat { namespace ui {

// Forward declaration of a pad class
class pad;

//______________________________________________________________________________
//! Basic pad GUI
/*! cat::ui::padGUI provides user interaction by using the AntTweakBar 
 *	library and some others SDL facilities to handle mouse and keyboard events. 
 *	It also implements some basic layout management of the interface elements. 
 *	This class is instantiated as a public member of the owner pad, which passes 
 *	its own pointer as constructor argument. This way also the class can read and
 *	manipulate all the public members of the owner pad through the _owner pointer.
 *
 *	\author Piero Giubilato
 *	\version 1.2
 *	\date 24 Aug 2024
 */
class padGUI //: public UI 
{
	private:
		
		//! Tweak bars buttons constants.
		enum ktbb {	ktbb_main_Quit, ktbb_main_Dump, ktbb_main_Save, ktbb_main_Test, ktbb_main_Test1000, ktbb_main_Close, ktbb_main_About,
					ktbb_spot_pan_Origin, ktbb_spot_pan_Selected, 
					ktbb_spot_zoom_All, 
					ktbb_spot_view_Top, ktbb_spot_view_Bottom, ktbb_spot_view_Left, ktbb_spot_view_Right, ktbb_spot_view_Front, ktbb_spot_view_Back
				   };
		
		//! Layout constants.
		enum kl {kl_Null, kl_Free, kl_Side};
		
		//! 3D View constants.
		enum k3d {k3d_Projection, k3d_Camera, k3d_Top, k3d_Front, k3d_Bottom, k3d_Back, k3d_Left, k3d_Right};
		
		// Handles to the different bars, with status and other support info.
		std::vector<bar> _bar;
		
		// Status and properties
		static pad* _owner;					//!< The pad using the GUI.
		Uint32 _layout;						//!< Pad elements layout.				
		Uint32 _barMove;					//!< Bar moving status.

		// Mouse/Drawing utilities
		int _mWheelPos;						//!< Mouse wheel cumulative position.
		bool _mDrag;						//!< Mouse has dragged.
		cat::ui::mouseBall _mArcBall; 		//!< Initialize a Mouse Ball (for mouse rotations).
		cat::ui::mousePicker _mPick;		//!< Initialize a Picker (for mouse picking). 
		
		// Initializations
		bool initTwBar();
		
	protected:
	
	public:

		// Special members
		padGUI(pad* owner);							//!< Mandatory owner ctor. 
		~padGUI();										//!< Default dtor.

		// Updates interface elements/status.
		void updateTwBar();								//!< Update the TwBar system.
		void updateBars();								//!< Updates all the GUI bars.
		void updateBarMain();							//!< Updates the main bar.
		void updateBarView();							//!< Updates the view bar.
		void updateBarSpot(const bool&);				//!< Updates the popup view bar.
		void updateBarScene();							//!< Updates the scene bar.
		void updateBarGP(gp::GPHnd gpHnd = 0);			//!< Updates the GP bar.
		void updateBarHelp();							//!< Updates the help bar.
		void updateMouse();								//!< Updates the mouse.	

		// Layout functions.
		Uint32 layoutGet() const;						//!< Get current layout mode.
		void layoutSet(const Uint32& mode = 0);			//!< Set/Update layout/mode.
		void layoutSet2(const Uint32& snap = 10);		//!< Set/Update layout/mode.

		// Events handlers.
		bool evnBar(SDL_Event evn);						//!< Handles Bar events.
		bool evnMouse(SDL_Event);						//!< Handles mouse events.
		bool evnSelect(const std::vector<gp::GPHnd>&);	//!< External selection events.

		//! Reference to mouse arc ball status.
		cat::ui::mouseBall& mouseBall() {return _mArcBall;}

		//! Reference to mouse pick status.
		cat::ui::mousePicker& mousePick() {return _mPick;}		

		// Main TwBar callbacks
//		static void TW_CALL cbkMain(void*);				//!< Main bar callback.
//		static void TW_CALL cbkMainScene(void*);		//!< Main bar Scene callback.
//		static void TW_CALL cbkSceneGP(void*);			//!< Scene bar GP callback.
//		static void TW_CALL cbkGP(void*);				//!< GP bar callback.
//		static void TW_CALL cbkSizeGet(void*, void*);	//!< Get the current scene size.
//		static void TW_CALL cbkLayoutGet(void*, void*);
//		static void TW_CALL cbkLayoutSet(const void*, void*);
//	   	static void TW_CALL cbkSpot(void*);				//!< Spot view bar callback.

		// Specific OpenGL draw calls.
		bool glDraw();								//!< Draw the GUI.
};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif