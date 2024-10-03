//------------------------------------------------------------------------------
// CAT application core class for the remote client 						  --
// (C) Piero Giubilato 2011-2024, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"rcCore.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "../include/rcCore.h"
#include "../include/gpStroked.h"
//#include "../include/gpFilled.h"
//#include "../include/gpFonted.h"

//##############################################################################
namespace cat { namespace rc {


// *****************************************************************************
// **							Special members								  **
// *****************************************************************************

//______________________________________________________________________________
core::core(const char* host, const int& port, const int& verb): 
		_status(kStatus::close), 
		_verbose(verb)
{
	/*! Default Ctor. Initializes the connection with the host \c host on the
	 *	port \c port. \c verb set the verbosity level: 0 (default) means no
	 *	messages, 1 warning/error messages, 2 all messages.
	 */
	
	// Searches for a server, warn in case of errors.
	if (init(host, port)) {
		
		// Core is not working
		_status = kStatus::error;

		// In case of verbosity.
		if (_verbose) std::cout << "cat::rc:core " << COL(CAT_COL_ERROR) <<
								   "Connection failed" << COL(DEFAULT) << "\n";
	}	
}

//______________________________________________________________________________
core::~core()
{
	/*! Dtor. Clears everything if we close before end.  */
	
	// Close the connection and reset the library.
	if (_status == kStatus::open) {
		sendCommand(kCmd::exit, 0, 0, 0); // Exit command to the server.		
		std::cout << "cat::rc:core Closing Core socket\n";
//		SDLNet_TCP_Close(_SD);	// CLoses the socket.
	}

	// Closes SDL NET interface.
	SDLNet_Quit();

	// Delete all pending scenes.
	for (auto i = 0; i < _scene.size(); i++) delete _scene[i];
}



// *****************************************************************************
// **						  Socket Private members						  **
// *****************************************************************************

//______________________________________________________________________________
bool core::init(const char* host, const Uint16& port)
{
	/*! Mandatory ctor. Initializes the connection with the server. \c host is
	 *	the name of the server host and \c port is the port number for the TCP-IP
	 *	connection. Both parameters are shown at server startup.
	 */
	
	// Resets the scene and flush counter vectors.
	_scene.clear();
	_flush.clear();
	_select = 0;
	
	// Starts SDL_net.
	if (SDLNet_Init() < 0) {
		if (_verbose >= kVerb::error) {
			std::cout << "cat::rc::core: " << COL(CAT_COL_ERROR) 
					  << SDL_GetError() << COL(DEFAULT) << "\n"; 
		}
		return true;
	}
 
	// Resolve the host we are connecting to.
//	if (SDLNet_ResolveHost(&_IP, host, port) < 0) {
//		if (_verbose >= kVerb::error) {
//			std::cout << "cat::rc::core: " << COL(CAT_COL_ERROR)
//					  << SDL_GetError() << COL(DEFAULT) << "\n"; 
//		}
//		return true;
//	}
 
	// Open a connection with the IP provided (listen on the host's port).
//	_SD = SDLNet_TCP_Open(&_IP);
//	if (!_SD) {
//		if (_verbose >= kv::error) {
//			std::cout << "cat::rc::core: " << COL(CAT_COL_ERROR)
//					  << SDLNet_GetError() << COL(DEFAULT) << "\n"; 
//		}
//		return true;
//	}

	// Gives info in case of verbosity
//	if (_verbose > kVerb::null) {
//		std::cout << "TCP client successfully connected to:\n";
//		std::cout << "TCP ip.host:   " << COL(LWHITE) << _IP.host << COL(DEFAULT) << "\n";
//		std::cout << "TCP ip.port:   " << COL(LWHITE) << _IP.port << COL(DEFAULT) << "\n";
//	}

	// Sets client status.
	_status = kStatus::open;

	// Sets optimal packet size (an hardcoded guess!);
	_OPS = 0;

	// Everything fine.
	return false;
}

//______________________________________________________________________________
bool core::socketStatus() const
{
	/*! Checks if the status is \c kss_Open. Warns in case. Pay attention: this 
	 *	function returns false if the status is \c Kss_Open, true otherwise.
	 */
	if (_status != kStatus::open) {
		if (_verbose >= kVerb::warn) std::cout << "cat::rc::Core: " << COL(CAT_COL_WARNING) 
										   << "No server connected\n" << COL(DEFAULT);
		return true;
	} else return false;
}



// *****************************************************************************
// **						  Streaming Private members						  **
// *****************************************************************************

//______________________________________________________________________________
void core::streamCmd(std::stringstream& stream, const kCmd& cmd, const uint64_t& arg1,
					const uint64_t& arg2, const uint64_t& arg3) const
{
	/*! Adds a command and argument to the stringstream \c stream. */
	stream.write((char*)&cmd, sizeof(cmd));
	stream.write((char*)&arg1, sizeof(arg1));
	stream.write((char*)&arg2, sizeof(arg2));
	stream.write((char*)&arg3, sizeof(arg3));
}

//______________________________________________________________________________
bool core::streamSend(const std::stringstream& stream) const
{
	/*! Sends a stream object through the current socket */

	// Check if communication is ok
	if (_status != kStatus::open) {
		if (_verbose) std::cout << "cat::rc::core: " << COL(CAT_COL_WARNING) <<
								   "No open socket!" << COL(DEFAULT) << "\n";
		return true;	
	}

	// Try sending the stream.
	std::string strbuf = stream.str();
//	if (SDLNet_TCP_Send(_SD, (void *)strbuf.data(), (int)strbuf.size()) < (int)strbuf.size()) {
//		if (_verbose) std::cout << "cat::rc::core: " << COL(CAT_COL_ERROR) << 
//									SDL_GetError() << COL(DEFAULT) << "\n";
//		return true;
//	}
		
	// Info in case
	if (_verbose >= kVerb::all) {
		std::cout << "cat::rc::core: sent: (" << COL(LCYAN) << strbuf.size() <<
					COL(DEFAULT) << ") [" << COL(LPURPLE) << strbuf << COL(DEFAULT) << "]\n";
	}

	// Everything fine.
	return false;
}

//______________________________________________________________________________
bool core::sendCommand(const kCmd& cmd, const uint64_t& arg1, const uint64_t& arg2, const uint64_t& arg3) const
{
	/*! Sends a command (\c cmd) and its argument (\c arg) to the server. */

	// Initializes a stream.
	std::stringstream buffer(std::ios::binary | std::ios::out | std::ios::in);
					  
	// Sets the start command.
	streamCmd(buffer, cmd, arg1, arg2, arg3);

	// Sends the stream.
	return streamSend(buffer);
}


//______________________________________________________________________________
bool core::sendGP(gp::GP* gp) const
{
	/*! Sends a GP the server. The second argument of the command tells the 
	 *	server which scene (of the client) is the GP from.
	 */

	// Initializes a stream
	std::stringstream command(std::ios::binary | std::ios::out | std::ios::in);
	std::stringstream buffer(std::ios::binary | std::ios::out | std::ios::in);

	// Creates the GP buffer stream
	gp->stream(buffer);
	
	// Add command with the size of the buffer as argument.
	streamCmd(command, kCmd::add, _select, 0, buffer.str().size());
	
	// Sends the GP.
	if(streamSend(command)) return true;
	return streamSend(buffer);
}


////______________________________________________________________________________
//bool Core::sendScene(pear::gp::Scene* scene)
//{
//	/*! Send a complete scene through the socket. */
//
//	// Creates the stream buffer.
//	std::stringstream buffer = streamBegin();
//	
//	// Set the new scene command.
//
//	// Set the first two slot as command (add primitive)
//	uint32_t num = kc_Add;
//	buffer.write((char*)&num, sizeof(num));
//  
//	// Fill the buffer with the primitive.
//	gp->Stream(buffer); 
//
//	// Try actually sending the buffer
//	std::string strbuf = buffer.str();
//	
//	if (SDLNet_TCP_Send(_SD, (void *)strbuf.data(), strbuf.size()) < strbuf.size()) {
//		if (_verbose) std::cout << "pear::Core: SDLNet_TCP_Send: " << SDLNet_GetError() << "\n";
//		exit(EXIT_FAILURE);
//		return true;
//	}
//
//	// Everything fine.
//	return false;
//}



// *****************************************************************************
// **						  Drawing private members		   				  **
// *****************************************************************************

//______________________________________________________________________________
bool core::sceneStatus() const
{
	/*! Checks if at least one scene is available and selected for drawing 
	 *	operations. Mind that this function returns false if a scene is available,
	 *	true otherwise. Scene #0 is the default scene and it is not used for 
	 *	actual drawing
	 */
	if (_scene.size() < 1) {
		if (_verbose >= kVerb::warn) std::cout << "cat::rc::core: " << COL(CAT_COL_WARNING) 
										   << "No scene selected\n" << COL(DEFAULT);
		return true;
	} else return false;
}

//______________________________________________________________________________
void core::gpLoadBrush(gp::GP* gp)
{
	/*! Loads a brush into a gp, i.e. uses the current brush settings to define
	 *	the gp properties. */
	
	// Check if the GP exists and if it does support a stroke.
	if (!gp) return;	
	//if (!gp->flagStroked())	return;
	//gp::Stroked* strk = (gp::Stroked*)gp; 

	// Stroke style. 
//	gp->strkEnable(_brush.active);  
//	gp->strkWidth(_brush.stroke.width); 
//	gp->strkPattern(_brush.stroke.pattern);
//	gp->strkFactor(_brush.stroke.scale);
	
	// Stroke color.
//	gp->strkColor(_brush.col.col);
}

//______________________________________________________________________________
void core::gpLoadFill(gp::GP* gp)
{
	/*! Loads current fill into a GP, i.e. uses the current fill settings to 
	 *	define the gp properties. */
	
	// Check.
	if (!gp) return;
//	if (!gp->flagStroked())	return;
//	gp::Filled* fill = (gp::filled*)gp;

	// Status.
//	fill->fillEnable(_fill.active);
//	fill->fillColor(_fill.col.col);

	// Material.
//	fill->mtrlEnable(_material.active);
//	fill->mtrlAmbient(_material.ambient);
//	fill->mtrlDiffuse(_material.diffuse);
//	fill->mtrlSpecular(_material.specular);
//	fill->mtrlEmission(_material.emission);
//	fill->mtrlShininess(_material.shininess);
}

//______________________________________________________________________________
void core::gpLoadInherit(gp::GP* gp)
{
	/*! Loads the current inheritance settings into a gp. */
	
	// Check.
	if (!gp) return;	

	// Sets GP inheritance.
//	gp->inhrAppear(_inherit.enabled);
//	gp->inhrVisible(_inherit.visibility);
//	gp->inhrAlpha(_inherit.alpha);
//	gp->inhrWire(_inherit.wire);
//	gp->inhrRef(_inherit.ref);
}

//______________________________________________________________________________
void core::gpLoadFont(gp::GP* gp)
{
	/*! Loads the current font settings into a gp. */
	
	// Check.
	if (!gp) return;
//	if (!gp->flagStroked())	return;
//	gp::fonted* font = (gp::fonted*)gp;

	// Sets GP font.
//	font->fontFamily(_font.family);
//	font->fontStyle(_font.style);
//	font->fontSize(_font.size);
}

//______________________________________________________________________________
void core::gpLoadTrsf(gp::GP* gp, const bool& inv)
{
	/*! Loads (applies) the current transformation into a gp. Load the inverse
	 *	one if \c inv is set to true. */
	
	// Check
	if (!gp) return;	

	// Sets GP transformation.
	gp->trsf(_ref, inv);  
}



// *****************************************************************************
// **						  Public Drawing management		    			  **
// *****************************************************************************

//______________________________________________________________________________
gp::GPHnd core::dcSceneBegin(const char* name)
{
	/*! Start a new Scene. Returns the scene handle. The current active Scene 
	 *	is automatically switched to the new one.
	 */
	
	// Check if a connection is available.
	if (socketStatus()) return true;
	
	// Adds a new scene to the vector.
	_scene.push_back(new gp::scene());
	_flush.push_back(1);	// The first real element of a scene is the #1.
	_select = _scene.size() - 1;
	
	// Sets new scene name.
	_scene[_select]->name(name);

	// Initializes a stream
	std::stringstream command(std::ios::binary | std::ios::out | std::ios::in);
	std::stringstream buffer(std::ios::binary | std::ios::out | std::ios::in);

	// Creates the Scene buffer stream
	_scene[_select]->stream(buffer);
	
	// Add command with the size of the buffer as argument.
	streamCmd(command, kCmd::begin, _select, 0, buffer.str().size());
	
	// Send the begin command and the buffer to the server.
	if(streamSend(command)) return true;
	return streamSend(buffer);
	
	// Returns scene handle.
	return _select;
}

//______________________________________________________________________________
bool core::dcSceneSelect(const gp::GPHnd& dHnd)
{
	/*! Select the current active scene. Returns true if \c dHnd does not
		represent an actual scene. */
	
	// Check and select.
	if (sceneStatus()) return true;
	if (dHnd >= _scene.size()) return true;
	_select = dHnd;

	// Send the close command for this scene to the server.
	return false; 
}

//______________________________________________________________________________
bool core::dcSceneClose()
{
	/*! Closes the currently selected scene. The scene will be no longer 
	 * available, but it will stay in the server memory until closed there. 
	 */
	
	// Safety flush.
	dcSceneFlush();

	// Check if a connection is available.
	if (socketStatus()) return true;
	if (sceneStatus()) return true;
 
	// Clear.
	delete _scene[_select];
	_scene[_select] = NULL;

	// Send the close command for this scene to the server.
	return sendCommand(kCmd::close, _select, 0, 0); 
}

//______________________________________________________________________________
bool core::dcSceneFlush()
{
	/*! Flush undrawn scene primitives to the server. */
	
	// This is the packet pivot stream.
	std::stringstream packet;
	std::stringstream buffer;

	// Check if a connection and a scene are available.
	if (socketStatus()) return true;
	if (sceneStatus()) return true;

	// Sends all the pending GPs in the scene.
	for (gp::GPHnd i = _flush[_select]; i < _scene[_select]->gpSize(); i++) {
		
		// If the GP(i) is ok (no one deleted it)
		if(_scene[_select]->gpGet(i)) {
			
			std::cout << "Flush: processing GP: " << i << "\n";
			
			// Adds command and GP buffer to the stream.
			buffer.str("");
			_scene[_select]->gpGet(i)->stream(buffer);
			streamCmd(packet, kCmd::add, _select, 0, buffer.str().size());
			packet << buffer.str();			

			// Send and reset the packet in case.
			if (packet.str().size() >= _OPS) {
				streamSend(packet);
				packet.str("");
			}
		}
	}	
	
	// Send the last packet whatever the size!
	if (packet.str().size()) streamSend(packet);

	// Update the flush status.
	_flush[_select] = _scene[_select]->gpCount();

	// Everything ok.
	return false; 
}

// *****************************************************************************
// **								Drawing Tools							  **
// *****************************************************************************
//
// Provided by the derived pear::rc::DCs class.


//##############################################################################
}} // Close namespaces
