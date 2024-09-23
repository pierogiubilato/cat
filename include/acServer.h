//------------------------------------------------------------------------------
// CAT application core Server class										  --
// (C) Piero Giubilato 2011-2013, University of Padova						  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"acServer.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined acServer_H
#define acServer_H

// Application components
//#include "ac.h"

// Standard components.
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

// SDL tcp/ip services. 
#include "SDL_net.h"


// #############################################################################
namespace cat { namespace ac {

//! CAT server
/*! cat::ac::server is the TCP-IP server used to collect drawing commands from
 *	the client(s). If a port number is not provided at instantiation, the 
 *  default value 2000 will be used.
 *	Once started the server checks for incoming connection request every time
 *	the Run() member is called: if no incoming connections are available the
 *	server returns, otherwise handle the connection and returns when the client
 *	sends the CLOSE or WAIT command. All available commands are listed in the \c
 *	cat_Client.h file.   
 *
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 20 Sep 2024
 */
//______________________________________________________________________________
class server 
{
	private:
		
		// Socket info structure.
		struct clientInfo {
			Uint32 SD;				// DUMMY <- Socket descriptor.	 
			Uint32 IP;				// DUMMY <- Resolved IP.
			Uint32 status;			// Socket status.
			Uint32 cHnd;			// The socket personal Handle.
		};

		// Sockets list.
		std::vector<clientInfo> _client;	// Sockets list
		
		// Buffers.
		std::vector<char> _buffer;	// Actual data buffer.
		Uint64 _timeout;			// Connection timeout in ms.
						
		// Server actions.
		bool init(const Uint32&, const Uint64& tOut);	//!< Init the server.
		bool close();				//!< Close the server.
		bool listen();				//!< Listen for new clients.
		bool clean();				//!< Clean closed clients.
		bool parse(const Uint64&, const char*, const Uint64&);		//!< Parse a command.
		bool read(const Uint64&, std::stringstream&, const Uint64&);	//!< Load a buffer.
				
	protected:
	
	public:

		// Special members
		server(const Uint32& port = 0, const Uint64& tOut = 100);
		~server();

		// Server
		bool run(bool openLoop = false);	//!< Run the server.
};


// *****************************************************************************
// **						Global namespace overloads						  **
// *****************************************************************************

//______________________________________________________________________________
inline std::ostream& operator<<(std::ostream& o, const Uint32& ip)
{
	/*! Overloads the standard output operator << for an IPaddress object. */
	
	// The IP
//	o << COL(LGREEN) << ((ip.host >> 0) & 255) << COL(DEFAULT) << ".";
//	o << COL(LGREEN) << ((ip.host >> 8) & 255) << COL(DEFAULT) << ".";
//	o << COL(LGREEN) << ((ip.host >> 16) & 255)	<< COL(DEFAULT) << ".";
//	o << COL(LGREEN) << ((ip.host >> 24) & 255) << COL(DEFAULT); 
	
	// The port
	o << ", ";
//	o << COL(LGREEN) << ip.port << COL(DEFAULT); 

	// Done!
	return o;
}

// #############################################################################
}} // Close namespaces

// Overloading check
#endif