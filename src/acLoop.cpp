//------------------------------------------------------------------------------
// CAT application core Main Application Loop								  --
// (C) Piero Giubilato 2012-2025, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"acLoop.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________


// Application components.
#include "acLoop.h"
#include "acServer.h"


// #############################################################################
// Open namespaces
namespace cat { namespace ac {


// *****************************************************************************
// **								Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
loop::loop(): _stop(false)
{
	/* Standard ctor. */

	// Resets the pad and the CTS vectors.
//	_pad.clear();
	_client.clear();
	
	// The first pad is by default associated to the server, so it is just 
	// a non-existent virtual pad (reserved for future use).
	_pad.push_back(0);

	// This is the main Pad, the one used to display and interact.
	try {
		_pad.push_back(new ui::pad(0, CAT_VER_TITLE, true));
 	}
	catch (...) {
		std::cout << "Error instantiating the main Pad...\n";
	}
}

//______________________________________________________________________________
loop::~loop() 
{
	/* Releases all allocated resources. */

	// Kills all the pad(s).
	for (Uint64 i = 0; i < _pad.size(); i++) delete _pad[i];

}


// *****************************************************************************
// **							Private Members								  **
// *****************************************************************************



// *****************************************************************************
// **							Public Members								  **
// *****************************************************************************

//______________________________________________________________________________
void loop::cmdAppRun() 
{
	/* Runs the application main loop. */

	// This is the application main loop.
	while(!_stop) {
	
		// Pad(s) run. Give the focus once to every active pad. Note we skip
		// the server virtual pad.
		for (Uint64 i = 1; i < _pad.size(); i++) {
			if (_pad[i]) _pad[i]->run(true); // Run a single loop.
		}

		// Server run.
		cat::ac::_server->run(true);
	}
}



// *****************************************************************************
// **						 Public Application Commands					  **
// *****************************************************************************

//______________________________________________________________________________
bool loop::cmdAppQuit(const Uint64& pIdx)
{
	/*! Issues a general Exit to the whole application */
	if (cat::ag::_verbose >= CAT_VERB_FULL) {
		std::cout << "Received a QUIT command from " << pIdx << "\n";
	}

	// Actually stops the application.
	_stop = true;

	// Everything fine.
	return true;
}



// *****************************************************************************
// **						  Public Client Commands						  **
// *****************************************************************************

//______________________________________________________________________________
bool loop::cmdClientAdd(const Uint64& cHnd)
{
	/*! Adds the client \c cHnd to the client list.	*/
	
	// Add the client
	_client.push_back(CSL());
	_client.back().cHnd = cHnd;
	
	// Clear its scene list.
	_client.back().sHnd.clear();	
	
	// Info	(This kind of info is handled by the server)
	if (cat::ag::_verbose >= CAT_VERB_FULL) {
		std::cout << "Client " << COL(LGREEN) << cHnd << COL(DEFAULT) 
				  << " added. Active clients: " << COL(LCYAN) 
				  << _client.size() << COL(DEFAULT) << "\n";
	}
	
	// Everything fine.
	return false; 
}

//______________________________________________________________________________
bool loop::cmdClientDel(const Uint64& cHnd)
{
	/*! Remove the client \c cHnd from the client list.	*/
	
	// Search
	Uint64 cIdx = 0;
	for (cIdx = 0; cIdx < _client.size(); cIdx++) {
		if (_client[cIdx].cHnd == cHnd) break;
	}
	
	// If bot a valid result, return.
	if (cIdx == _client.size()) return true;

	// Delete the client from the list
	_client.erase(_client.begin() + cIdx);
	
	// Info (This kind of info is handled by the server)
	if (cat::ag::_verbose >= CAT_VERB_FULL) {
		std::cout << "Client " << COL(LGREEN) << cHnd << COL(DEFAULT) 
				  << " removed. Active clients: " << COL(LCYAN) 
				  << _client.size() << COL(DEFAULT) << "\n";
	}
		
	// Everything fine.
	return false; 
}

// *****************************************************************************
// **						  Public Scene Commands							  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 loop::cmdSceneBegin(const Uint64& cHnd, std::stringstream& cBuf)
{
	/*! Begins a new scene. \c cHnd is the caller client Handle, while
	 *	\c cBuf contains the stream which describe the scene to create.
	 *	Returns the Scene handle if everything fine, 0 on error.
	 */
	
	// Search for the client.
	Uint64 cIdx = 0;
	for (cIdx; cIdx < _client.size(); cIdx++) if (_client[cIdx].cHnd == cHnd) break;
	if (cIdx >= _client.size()) return true;
	
	// Add the scene to the main pad and load it.
	Uint64 sHnd = _pad[1]->sceneAdd(new gp::scene());
 	_pad[1]->sceneGet(sHnd)->stream(cBuf, true);
	
	// Stores the new link which associates the calling Client with this Scene.
	_client[cIdx].sHnd.push_back(sHnd);

	// If it is the only scene in the pad, select it!
	if (_pad[1]->sceneCount() == 1) _pad[1]->sceneSel(1);  

	// Info
	if (cat::ag::_verbose >= CAT_VERB_FULL) {
		std::cout << "Added scene [" << COL(LWHITE) << sHnd << COL(DEFAULT) 
				  << "] from client [" << COL(LGREEN) << cHnd << COL(DEFAULT) << "]\n";
	}
	
	// Everything fine.
	return sHnd; 
}

//______________________________________________________________________________
bool loop::cmdSceneClose(const Uint64& cHnd, const Uint64& sIdx)
{
	/*! Closes scene \c sIdx of the \c cHnd scene list. */
	if (cat::ag::_verbose >= CAT_VERB_FULL) {
		std::cout << "Received a CLOSE command from " << cHnd << "\n";
	}
	
	// Search for the client.
	Uint64 cIdx = 0;
	for (cIdx; cIdx < _client.size(); cIdx++) if (_client[cIdx].cHnd == cHnd) break;
	if (cIdx >= _client.size()) return true;
	
	// Check it the scene actually exists in the scene list. sIdx is simply the
	// index of the scene, NOT its handle which must be retrieved after.
	if (sIdx >= _client[cIdx].sHnd.size()) return true;

	// Retrieve the actual scene Handle and pointer.
	Uint64 sHnd = _client[cIdx].sHnd[sIdx];
	gp::scene* sPtr = _pad[1]->sceneGet(sHnd);
	
	// Dump the scene (debug).
	//sPtr->dump();

	// Deletes the scene from the main Pad.
	return false;
}

//______________________________________________________________________________
bool loop::cmdSceneAddGP(const Uint64& cHnd, const Uint64& sIdx, std::stringstream& buf)
{
	/*! Adds a GP to the scene \c sIdx of the \c cHnd Client scene list. \c cBuf 
		is the stream containing the GP description. Returns false if no errors 
		occur, true otherwise.
	*/

	// Search for the client.
	Uint64 cIdx = 0;
	for (cIdx; cIdx < _client.size(); cIdx++) if (_client[cIdx].cHnd == cHnd) break;
	if (cIdx >= _client.size()) return true;
	
	// Check it the scene actually exists in the scene list. sIdx is simply the
	// index of the scene, NOT its handle which must be retrieved after.
	if (sIdx >= _client[cIdx].sHnd.size()) return true;

	// Retrieve the actual scene Handle and pointer.
	Uint64 sHnd = _client[cIdx].sHnd[sIdx];
	gp::scene* sPtr = _pad[1]->sceneGet(sHnd);
	
	// Adds the GP to the selected scene and refresh it.
	sPtr->gpAdd(buf);  	
	_pad[1]->refresh();
	
	// Info
	if (cat::ag::_verbose >= CAT_VERB_FULL) {
		std::cout << "GP added to scene [" << COL(LWHITE) << sHnd << COL(DEFAULT)
				  << "] from client [" << COL(LGREEN) << cHnd << COL(DEFAULT) << "]\n";
   	}
	
	// Everything fine.
	return false;
}

//______________________________________________________________________________
ui::pad* loop::padGet(const Uint64& pIdx)
{
	/*! Returns a pointer to \c pIdx pad. At the moment the only valid
	 *	pIdx is 1 by default.
	 */
	return _pad[1];
}	

// #############################################################################
}} // Close namespaces
