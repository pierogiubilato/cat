//------------------------------------------------------------------------------
// CAT label Graphic Primitive class					 					  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpLabel.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined gpLabel_H
#define gpLabel_H

// Components
#include "gpFonted.h"


// #############################################################################
namespace cat { namespace gp {

/*! cat::gp::Label creates a Label.
 *	
 *	\author Piero Giubilato, Sarah Zalusky
 *	\version 1.0
 *	\date 24 Sep 2024
 */
//______________________________________________________________________________
class label: public fonted
{
	private:   
	
		// The 5 vertex points defining the label space (1 anchor + 1 quad).
		ge::point _vtx[5];
		uint16_t _alignment;		// Label alignment respect _Vtx[0].
		float _rotation;			// Label rotation respect the horizontal viewport axis.
		bool _view2D;				// Project the label into the 2D viewport.

		// The plain text.
		std::string _text;			// Text contained into the label.
		
		// The generated pixMap.
		#ifdef CAT_SERVER
			uint8_t* _pxmData;		// The actual data (an RGBA array).
			uint32_t _pxmWidth;		// Width of the array (pixels).
			uint32_t _pxmHeight;	// Height of the array (pixels).
		#endif

	protected:
					
	public:
		
		// Special members.		
		label();					//! Default ctor.
		virtual ~label();			//!< Virtual dtor.

		//! Standard Constructor with (text, position and font).
		label(const std::string& text, 
			  const double& x = 0, const double& y = 0, const double& z = 0, 
			  const uint16_t& alignment = 0, const double& rotation = 0,
			  const bool& view2D = false);
				
		// Default access public members
		CO::oType type() const;					//!< Returns GP type.
		coVer_t version() const;					//!< Returns GP version.
		std::string stem() const;				//!< Returns GP stem name.
		size_t size(const bool& = false) const;	//!< Returns GP size in bytes.
		void dump(const int& = 0) const;		//!< Dumps GP data.
		bool stream(std::stringstream& o, const bool& read = false);

		// Public transformation overloads.
		label& trsf(const ge::ref& ref, const bool& inv);		//!< Transform the GP.
		label& trsfIn(const ge::ref& ref) {return trsf(ref, false);}	//!< Transform the GP into ref.	 	
		label& trsfOut(const ge::ref& ref) {return trsf(ref, true);}	//!< Transform the GP from ref.

		// Text and relate properties access.
		std::string& text() {return _text;}
		uint16_t& alignment() {return _alignment;}
		float& rotation() {return _rotation;}
		bool& view2D() {return _view2D;}

		// Access to the internal ge::point Components.
		ge::point vtx(const int&) const;
		
		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef CAT_SERVER
			
			// Drawing.			
			void glDraw();		//!< Draws the GP.
			void glDrawSel();	//!< Highlight the GP.
			void glDrawEnd();	//!< Close the GP drawing. Mandatory call!
			double glAlpha();	//!< Overloaded from GP.

			// UI interaction.	
//			void uiBarLoad(ui::Bar&);			//!< Load the GP properties bar.
			//TwType uiTwEnumFtFamily() const;	//!< Creates a TwEnum for the Font Families.
			//TwType uiTwEnumFtStyle() const;		//!< Creates a TwEnum for the Family's Font Styles.
//			TwType uiTwEnumTxAlign() const;		//!< Creates a TwEnum for the Text's alignment mode.
//			static void TW_CALL uiTextSet(const void *value, void *clientData);
//			static void TW_CALL uiTextGet(void *value, void *clientData);
			//static void TW_CALL uiFamilySet(const void *value, void *clientData);
			//static void TW_CALL uiFamilyGet(void *value, void *clientData);
			//static void TW_CALL uiStyleSet(const void *value, void *clientData);
			//static void TW_CALL uiStyleGet(void *value, void *clientData);
		#endif
};

// #############################################################################
}} // Close namespace



//	*****************************************************************************
// **					Global namespace public functions					   **
//	*****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator << (std::ostream& o, const cat::gp::label& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Label. */ 
	obj.dump();
	return o;
}

// Overloading check
#endif