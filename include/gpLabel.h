//------------------------------------------------------------------------------
// PEAR Label GP class					 									  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"pear_gp_Label.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"04 Sep 2011"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined pear_gp_Label_H
#define pear_gp_Label_H

// Components
#include "pear_gp_Fonted.h"


// #############################################################################
namespace pear { namespace gp {

/*! pear::gp::Label creates a Label.
 *	
 *	\author Piero Giubilato, Sarah Zalusky
 *	\version 1.0
 *	\date 04 Sep 2011
 */
//______________________________________________________________________________
class Label: public Fonted
{
	private:   
	
		// The 5 vertex points defining the label space (1 anchor + 1 quad).
		go::Point _Vtx[5];
		Uint32 _Alignment;		// Label alignement respect _Vtx[0].
		float _Rotation;		// Label rotation respect the horizontal viewport axis.
		bool _View2D;			// Project the label into the 2D viewport.

		// The plain text.
		std::string _Text;		// Text contained into the label.
		
		// The generated pixMap.
		#ifdef PEAR_SERVER
			GLubyte* _pxmData;	// The actual data (an RGBA array).
			Uint32 _pxmWidth;	// Width of the array (pixels).
			Uint32 _pxmHeight;	// Height of the array (pixels).
		#endif

	protected:
					
	public:
		
		// Special members.		
		Label();					//! Default ctor.
		virtual ~Label();			//!< Virtual dtor.

		//! Standard Constructor with (text, position and font).
		Label(const std::string& text, 
			  const double& x = 0, const double& y = 0, const double& z = 0, 
			  const Uint32& alignement = 0, const double& rotation = 0,
			  const bool& view2D = false);
		
		
		// Default access public members
		Uint64 Type() const;					//!< Returns GP type.
		Uint64 Version() const;					//!< Returns GP version.
		std::string Stem() const;				//!< Returns GP stem name.
		size_t Size(const bool& = false) const;	//!< Returns GP size in bytes.
		void Dump(const Uint64& = 0) const;		//!< Dumps GP data.
		
		//! Stream the GP data (both read and write).
		bool Stream(std::stringstream& o, const bool& read = false);

		// Public transformation ovelorads.
		Label& Trsf(const go::Ref& ref, const bool& inv);		//!< Transform the GP.
		Label& TrsfIn(const go::Ref& ref) {return Trsf(ref, false);}	//!< Transform the GP into ref.	 	
		Label& TrsfOut(const go::Ref& ref) {return Trsf(ref, true);}	//!< Transform the GP from ref.

		// Text and relate properties access.
		std::string& Text() {return _Text;}
		Uint32& Alignment() {return _Alignment;}
		float& Rotation() {return _Rotation;}
		bool& View2D() {return _View2D;}

		// Access to the internal go::Point Components.
		go::Point Vtx(const Uint64&) const;
		
		// Drawing functions are ONLY defined for the SERVER side!
		#ifdef PEAR_SERVER
			
			// Drawing.			
			void glDraw();		//!< Draws the GP.
			void glDrawSel();	//!< Highlight the GP.
			void glDrawEnd();	//!< Close the GP drawing. Mandatory call!
			double glAlpha();	//!< Overloaded from GP.

			// UI interaction.	
			void uiBarLoad(ui::Bar&);			//!< Load the GP properties bar.
			//TwType uiTwEnumFtFamily() const;	//!< Creates a TwEnum for the Font Families.
			//TwType uiTwEnumFtStyle() const;		//!< Creates a TwEnum for the Family's Font Styles.
			TwType uiTwEnumTxAlign() const;		//!< Creates a TwEnum for the Text's alignment mode.
			static void TW_CALL uiTextSet(const void *value, void *clientData);
			static void TW_CALL uiTextGet(void *value, void *clientData);
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
inline std::ostream& operator << (std::ostream& o, const pear::gp::Label& obj)
{
	/*! Overloads standard output operator << for a generic pear::gp::Label. */ 
	obj.Dump();
	return o;
}

// Overloading check
#endif