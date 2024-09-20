//------------------------------------------------------------------------------
// CAT application core Server class										  --
// (C) Piero Giubilato 2021-2024, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"ac_Server.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"19 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Application components
#include "acServer.h"
#include "acLoop.h"
#include "rcCore.h"


// #############################################################################
namespace cat { namespace ac {


// *****************************************************************************
// **							Special Members								  **
// *****************************************************************************

//______________________________________________________________________________
server::server(const Uint32& port, const Uint64& tOut)
{
	/* Standard ctor. Initializes the TCP-IP server. 
	 *	If \c port is not provided it is set by default at 2000. \c tOut if the 
	 *	allowed time with no calls before a Client is automatically put in WAIT 
	 *	mode. Its default is 100 ms.
	 */
	init(port, tOut);
}

//______________________________________________________________________________
server::~server() 
{
	/* Releases all allocated resources. */
	close();
}


// *****************************************************************************
// **							Private Members								  **
// *****************************************************************************

//______________________________________________________________________________
bool server::init(const Uint32& port, const Uint64& tOut)
{
	/*! Starts a TCP-IP server. If \c port is not provided it is set by default
	 *	at 2000. \c tOut if the allowed time with no calls before a Client is 
	 *	automatically put in WAIT mode. Its default is 1000 ms.
	 */
   
	// Remember: element [0] of the _client list is ALWAYS the server itself!
	_client.clear();
	_client.push_back(clientInfo()); 

	// Init the SDL_net
	if (SDLNet_Init() < 0) {
		std::cout << COL(CAT_COL_ERROR) << "SDLNet_Init: " << SDL_GetError() << COL(DEFAULT) << "\n";
		throw std::runtime_error("SDL_net init failed");
		return false;
	}
 
	// Opening the server for listening.
	//SDLNet_Server* server = SDLNet_CreateServer(&_client[0].address, port);
	
	
	// Resolving the host using NULL make network interface to listen.
	//SDLNet_Address* addr = SDLNet_ResolveHostname(port.c_str());
	//if (SDLNet_WaitUntilResolved(addr, -1) == -1) {
	//	SDL_Log("Failed to lookup %s: %s", port.c_str(), SDL_GetError());
	//	return true;
	//}
		
	// Resolving the host using NULL make network interface to listen.
	//if (SDLNet_ResolveHost(&_client[0].IP, NULL, port) < 0) {
	//	std::cout << COL(CAT_COL_ERROR) <<  "SDLNet_ResolveHost: " << SDL_GetError() << COL(DEFAULT) << "\n";
	//	throw std::runtime_error("SDL_net ResolveHost failed");
	//	return true;
	//}
 
	// Open a connection with the IP provided (listen on the host's port).
	//_client[0].SD = SDLNet_TCP_Open(&_client[0].IP);
	//if (!_client[0].SD) {
	//	std::cout << COL(CAT_COL_ERROR) << "SDLNet_TCP_Open: " << SDL_GetError() << COL(DEFAULT) << "\n";
	//	throw std::runtime_error("SDL_net TCP_Open failed");
	//	return true;
	//}

	// Set the server socket as open.
//	_client[0].status = rc::core::kss::open;
	
	// Set the data timeout (ms).
	_timeout = tOut;

	// Give infos.
	std::cout << COL(LWHITE) << "\nServer running\n" << COL(DEFAULT);
//	std::cout << "   Host full name: " << COL(LGREEN) << SDLNet_ResolveIP(&_client[0].IP) << COL(DEFAULT) << "\n";
//	std::cout << "   Listening port: " << COL(LGREEN) << port << COL(DEFAULT) << "\n";
//	std::cout << "   Server address: " << _client[0].IP << "\n";

	// Everything fine!
	return false;
}

//______________________________________________________________________________
bool server::close()
{
	/*! Closes the Server. */

	// Closes the library.
//	SDLNet_TCP_Close(_client[0].SD);
//	SDLNet_Quit();
	std::cout << "Server successfully closed\n";

	// Everything fine.
	return false;
}

//______________________________________________________________________________
bool server::clean()
{
	/*! Removes all no longer connected clients. */
  	
	// Kills inactive connections.
	for (Uint64 i = 1; i < _client.size(); i++) {

		// If a socket is no more active, close it and free the slot.
		if (_client[i].status == rc::core::kss::close) {
			
			// Tell the loop this client is no more active.
			cat::ac::_loop->cmdClientDel(_client[i].cHnd); 
			
			// Info on the killed connection.
			if (cat::ag::_verbose >= CAT_VERB_DEF) {
				std::cout << "Client [" << _client[i].IP << "] has exited\n";
			}

			// Close and then erase the socket.
//			SDLNet_TCP_Close(_client[i].SD);
			_client.erase(_client.begin() + i);
		}
	}

	// Everything fine!
	return false;	
}

//______________________________________________________________________________
bool server::listen()
{
	/*! Listen for clients awaiting connection. */
	
	// Pivots.
	clientInfo tmpClient;
	
	// Searches for pending connections.
	while(true) {
		
		// Yes, there is a pending connection
		if (tmpClient.SD = SDLNet_TCP_Accept(_client[0].SD)) {

			// Add the new socket to the socket list.
			_client.push_back(clientInfo()); 
		
			// Set up the new socket.
//			_client.back().SD = tmpClient.SD;
//			_client.back().IP = *(SDLNet_TCP_GetPeerAddress(tmpClient.SD));
			_client.back().Status = rc::core::kss_Open; 									
			_client.back().cHnd = _client.back().IP.port;			
			
			// Makes the application loop aware of the new connection. An
			// univoque Id is passed here, to make the client identification
			// independent from its position in the socket lists.
			cat::ac::_Loop->cmdClientAdd(_client.back().cHnd);  

			// Info on the new connection.
			if (cat::ag::_verbose >= CAT_VERB_DEF) {
				std::cout << "Client [" << _client.back().IP << "] has connected\n";
			}
		
		// No more pending connections, exits the loop.		
		} else break;
	}
	
	// Everything fine.
	return false;
}

//______________________________________________________________________________
bool server::read(const Uint64& cIdx, std::stringstream& cBuf, const Uint64& cLen)
{
	/*! Loads \c cLen bytes from the \c cIdx client and happend them to the
	 *	\c cBuf buffer.
	 */

	// Sets swap buffer.
	char* swapBuf = new char[cLen];
 
	// Fills the buffer.
	if (SDLNet_TCP_Recv(_client[cIdx].SD, swapBuf, (int)cLen) > 0) {
			
		// Load the data buffer.
		cBuf.write(swapBuf, cLen);
			
		// Info in case.
		if (cat::ag::_Verbose >= CAT_VERB_FULL) {
			std::cout << "Packet (" << COL(LCYAN) << cLen << COL(DEFAULT) << ") "
					  << "[" << COL(LPURPLE) << cBuf.str() << COL(DEFAULT) << "]\n";
		}
	} else return true;
	
	// Releases swap buffer.
	delete swapBuf;

	// Everything fine
	return false;
}	

//______________________________________________________________________________
bool server::parse(const Uint64& cIdx, const char* cBuf, const Uint64& cLen)
{
	/*! Parses a command from the client \c cIdx. \c cBuf is the associated
	 *	buffer and \c cLen is the length of the associated buffer.
	 */
	
	// Retrieves all necessary data
	// ----------------------------

	// Grabs command and arguments.
	Uint64 cmd = *(Uint64*)(&cBuf[0]);		// Byte 0, the command
	Uint64 cArg1 = *(Uint64*)(&cBuf[8]);	// Byte 1, first argument, usually sHnd.
	Uint64 cArg2 = *(Uint64*)(&cBuf[16]);	// Byte 2, second argument.
	Uint64 cArg3 = *(Uint64*)(&cBuf[24]);	// Byte 3, third argument, usually buffer length.	
					
	// Show command by command.
	if (cat::ag::_Verbose >= CAT_VERB_FULL) {
		std::cout << "server: raw command: [" << COL(LPURPLE);
		for (Uint64 i = 0; i < cLen; i++) std::cout << cBuf[i];
		std::cout << COL(DEFAULT) << "]\n";
	}
	
	// Retrieves the data buffer for BEGIN and ADD commands.
	std::stringstream dataBuf(std::ios::binary | std::ios::out | std::ios::in);	
	if (cmd == rc::core::kc::begin || Cmd == rc::core::kc::add) {
		read(cIdx, dataBuf, cArg3);
	}

	// Issues the commands
	// -------------------
	
	// The EXIT command. Socket end will be make effective by the next call
	// of the clean function, which happens at first at every server runs.
	if (cmd == rc::core::kc::exit) _client[cIdx].status = rc::core::kss::close;
	
	// The BEGIN command.
	if (cmd == rc::core::kc::begin) {
		Uint64 sHnd;
			
		// Pass the command to the loop.
		if ((sHnd = cat::ac::_loop->cmdSceneBegin(_client[cIdx].cHnd, dataBuf)) == 0) {
			if (cat::ag::_verbose >= CAT_VERB_WARN) {
				std::cout << "Client [" << COL(LGREEN) << _client[cIdx].cHnd << COL(DEFAULT) << "]"
						  << COL(CAT_COL_WARNING) << " could not star a scene!" 
						  << COL(DEFAULT) << "\n";				
			}
			return true;
		
		// A scene has been successfully added.
		} else {
			if (cat::ag::_Verbose >= CAT_VERB_FULL) {
				std::cout << "Client [" << COL(LGREEN) << _client[cIdx].cHnd << COL(DEFAULT) << "]"
						  << " started a new scene [" << COL(LWHITE)
						  << sHnd << COL(DEFAULT) << "]\n";			
			}
			return false;
		}
	}

	// The ADD GP command.
	if (cmd == rc::core::kc::add) {
		return cat::ac::_loop->cmdSceneAddGP(_client[cIdx].cHnd, cArg1, dataBuf);
	}

	// The CLOSE command.
	if (cmd == rc::core::kc::close) return cat::ac::_loop->cmdSceneClose(_client[cIdx].cHnd, cArg1);

	// Dummy
	return false;
}

// *****************************************************************************
// **							Public Members								  **
// *****************************************************************************

//______________________________________________________________________________
bool Server::run(bool openLoop)
{
	/*! Run once the TCP-IP server. The call will search for any waiting client:
	 *	if no one will be found, it will return if openLoop = true, or continue
	 *	waiting if openLoop = false. Otherwise, it will process all the client 
	 *	calls until a CLOSE or WAIT command is received. The EXIT command will 
	 *	trigger an exit from the main application loop.
	 */
		
	// Pivots.
	char cBuf[32];	// That's to fit the 4 Uint64 command length.
	Uint64 cLen = 32;
	Uint64 cCount = _client.size();

	// Clear closed connections.
	if (clean()) return true;

	// Listen for connections.
	if (listen()) return true;
	
	// Info	on changes in the number of connected clients.
	if (cCount != _client.size() && cat::ag::_verbose >= CAT_VERB_DEF) {
		std::cout << "Connected clients: " << COL(LCYAN) 
				  << _client.size() - 1 << COL(DEFAULT) << "\n";		
	}

	// Search for incoming commands on all available clients (remember, 
	// socket #0 is the server itself!).
	for (Uint64 cIdx = 1; cIdx < _client.size(); cIdx++) {
		
		// Waiting for commands loop.
		Uint64 dataCount = 0;
		while (true) {
		
			// Reads 4 double words (8 bytes each) as 1 command and 3 parameters, and parse them. 
			if (SDLNet_TCP_Recv(_client[cIdx].SD, cBuf, (int)cLen) > 0) {
				
				// Parse the command.
				if (parse(cIdx, cBuf, cLen)) break;
				
				// Command has been transferred, increase transfer count.
				dataCount += cLen;

				// Increase transfer count by the buffer size associated to 
				// the command, which is stored into the 4th double word.
				dataCount += *(Uint64*)(&cBuf[cLen * 3]);
											  
			// If no more data to read, exit this client loop.
			} else break;
		}

		// Some info about the reception.
		if (dataCount && cat::ag::_verbose >= CAT_VERB_DEF) {
			std::cout << "Parsed data from ["<< COL(LGREEN) << cIdx << COL(DEFAULT) 
					  << "] [" << COL(LCYAN) << dataCount << COL(DEFAULT) << " bytes]\n";
		}
	}
	
	// Everything fine!
	return false;
}


// #############################################################################
}} // Close namespaces
