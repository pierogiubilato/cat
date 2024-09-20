//------------------------------------------------------------------------------
// CAT Bar user interface for pad_GUI class									  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiBar.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined uiBar_H
#define uiBar_H

// Application components.
#include "ui.h"

// AntTweakBar
//#include "AntTweakBar/AntTweakBar.h"


// #############################################################################
namespace cat { namespace ui {

//______________________________________________________________________________
//! Bars group status class.
class barGroup: public UI
{
	/*! pear::ui::BarGroup is a structure which contains the description of a Bar 
	 *	Group, an expandable. */
	
	// Public members.
	public:
		
		std::string name; 
		int enable; 
		int open;													 
	
	//! Name ctor.
	BarGroup(const std::string& s): name(s), enable(1), open(1) {};
	
	//! Name and enable ctor.
	BarGroup(const std::string& s, const int& e): name(s), enable(e), open(1) {};
	
	//! Name, enable and open ctor.
	BarGroup(const std::string& s, const int& e, const int& o): name(s), enable(e), open(o) {};
};

//______________________________________________________________________________
//! The standard 
/*! pear::ui::Bar is a support class wich holds the properties of a TwBar plus
 *	offering misc utility routines.
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 09 Aug 2011
 */
class bar: public UI 
{
	private:

		std::vector<BarGroup> _GroupOld;	// Old groups container.

	public:
		
		// Storage elements.
//		TwBar* _TwBar; 
		std::vector<BarGroup> _Group;		// Bar groups container.
	
		// Special members.
		bar();
//		Bar(TwBar* bar);
		~bar();

		// Bar commands.
		void Clear();					//!< Clear the bars from all components.

		// Status commands.
		void StatusSave();				//!< Saves the current status.
		void StatusLoad();				//!< Makes the saved status current.
		void StatusGet();				//!< Get the current TwBar status.
		void StatusSet();				//!< Set the current status to the TwBar.
		void StatusDump();				//!< Dump the current bar status.
		void StatusMatch();				//!< Match the bar status with the saved one.
		void StatusMatch(const Bar&);	//!< Match the bar status with a reference.

		//! Adds a group (name only).
		void GroupAdd(const std::string& name);
		
		//! Adds a group (name and enable status). 
		void GroupAdd(const std::string& name, const int& enable);
		
		//! Adds a group (name plus enable and open status). 
		void GroupAdd(const std::string& name, const int& enable, const int& open);	

		// GUI utilities.
		static void SortByXY(const std::vector<Bar>&, std::vector<Bar>&);
//		static TwBar* PickTop();

};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif