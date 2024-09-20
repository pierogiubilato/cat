//------------------------------------------------------------------------------
// CAT application core Main Application Loop class							  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"acLoop.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if !defined acLoop_H
#define acLoop_H

// Application components.
#include "ac.h"
#include "uiPad.h"


// #############################################################################
namespace cat { namespace ac {

//! Cat loop
/*! cat::ac::Loop is the manager of the whole application behaviour. It handles
 *	all the direct interactions arriving from the Pad(s) and the system. It 
 *	also manages the commands received from the server and connects them to the 
 *	appropriate scene(s) instantiated on the main Pad.  
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 19 Sep 2024
 */
//______________________________________________________________________________
class loop  //: public ac
{
	private:
		
		// Loop status.
		bool _stop;		// Main loop flag.
				
		// Managed Pad(s).
		std::vector<cat::ui::pad*> _pad; // Pads list.	
		
		//! Clients-Scenes-Links (CSL). Lists all scenes created by a client.
		struct CSL {
			Uint64 cHnd;				//!< Client handle.   
			std::vector<Uint64>	sHnd;	//!< Handle of the iTh scene.
		};

		//! Client list.
		std::vector<CSL> _client;
		
	protected:
	
	public:

		// Special members
		loop(); 
		~loop();

		// Application Commands.
		void cmdApp_Run();					//!< Starts the main application loop.
		bool cmdApp_Quit(const Uint64&);	//!< Application Exit.

		// Client Commands.
		bool cmdClient_Add(const Uint64&);	//!< Add a new connected client.
		bool cmdClient_Del(const Uint64&);	//!< Remove a client.
		
		// Scene Commands.
		Uint64 cmdScene_Begin(const Uint64&, std::stringstream&);				//!< Starts a new scene.
		bool cmdScene_Close(const Uint64&, const Uint64&);						//!< Closes an existing scene.
		bool cmdScene_AddGP(const Uint64&, const Uint64&, std::stringstream&);	//!< Adds a GP to a scene.

		// Application elements access.
		ui::pad* padGet(const Uint64& = 1);	//!< Returns pointer to pIdx pad.	 
				
};

// *****************************************************************************
// **						Global namespace overloads						  **
// *****************************************************************************

// #############################################################################
}} // Close namespaces

// Overloading check
#endif