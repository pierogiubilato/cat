//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application CLIENT entry point               --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"client.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"08 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________



// SFML system/windowing library.
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// Network.
#include <SFML/Network.hpp>

// STL.
#include <iostream>
 
// Application.
#include "client.hpp"
#include "console.hpp"		// Header only. Include ONLY here to hav its method linked.
//#include "socket.hpp"




//______________________________________________________________________________
cat::client::client() : _srvPort(2000), 
						_srvAddress("localhost")//: _command(new cmd)
{
	// Create PImpl classes.
	//_command = new cat::cmd;


}

//______________________________________________________________________________
cat::client::client(int argc, char* argv[]) : client()
{
	
	// Setup the client command.
	cmdSet();
	cmdParse(argc, argv);
}

//______________________________________________________________________________
cat::client::~client()
{

}


//______________________________________________________________________________
int cat::client::cmdSet()
{
	// Setup default tokens.


	// Server address.
	_command.addOpt("address", 
					"set the server address [localhost]", 
					false, true);
	
	// Server listening port.
	_command.addOpt("port", 
					"set the server port [2000]", 
					false, true);
	
	// Verbosity level.
	_command.addOpt("v", 
					"verbosity level [critical, error, warning, message, info, debug, all]", 
					false, true);

	// Everything fine.
	return 0;
}


//______________________________________________________________________________
int cat::client::cmdParse(int argc, char* argv[])
{
	// Parse the command line.
	if (_command.parse(argc, argv) != 0) return -1;

	// Retrieve server values.
	_srvPort = std::stoi(_command.getOptionValue("port", "2000"));
	_srvAddress = _command.getOptionValue("address", "localhost");

	// Retrieve verbosity.
	cat::cl::verb::set(_command.getOptionValue("v", "message"));

	// Everything fine.
	return 0;
}


//______________________________________________________________________________
cat::client::status cat::client::connect()
{
	// Connects with the default parameters.
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(_srvAddress, _srvPort, sf::milliseconds(_timeout));

	// Check status
	if (status != sf::Socket::Done) {
		
		// Console output.
		if (cl::verb::show(cat::cl::verb::error)) {
			std::cout << cat::cl::error("Failed to connect to server at: ")
				<< cat::cl::message(_srvAddress.c_str()) << " on port "
				<< cat::cl::message(_srvPort)
				<< std::endl;
		}
		
		// Return error.
		return cat::client::status::error;
	}
	
	// Everything fine.
	return cat::client::status::connected;
}


//______________________________________________________________________________
cat::client::status cat::client::connect(const std::string& address, const unsigned short& port)
{
	// Store new variables in the class.
	_srvAddress = address;
	_srvPort = port;

	// Try to connect.
	return client::connect();
}




////______________________________________________________________________________
//int main(int argc, char* argv[])
//{
//
//    std::cout << "CAT client\n";
//
//    // Application context.
//    cat::context ctx;
//
//    // Various debug.
//    std::cout << cat::cl::warning() << "test console" << cat::cl::reset() << "\n";
//
//    // Parse command line.
//    cmd(ctx, argc, argv);
//    sf::IpAddress srvAddress(ctx.cmd.getOptionValue("address", "localhost"));
//    unsigned short srvPort(std::stoi(ctx.cmd.getOptionValue("port", "2000")));
//
//    // Get verbosity.
//    std::cout << "Verbosity flag set to: "
//        << cat::cl::message()
//        << ctx.cmd.getOptionValue("v", "message")
//        << cat::cl::reset() << "\n";
//
//    // Set verbosity.
//    ctx.cl.verb(ctx.cmd.getOptionValue("v", "message"));
//
//    // Get verbosity.
//    std::cout << "Verbosity level in class set to: "
//        << cat::cl::message()
//        << ctx.cl.verb()
//        << cat::cl::reset() << "\n";
//
//    // Connecting to the server.    
//    std::cout << "Trying to connect to the host address " << srvAddress << "\n";
//    std::cout << "Trying to connect to the server on port " << srvPort << "\n";
//        
//    sf::TcpSocket socket;
//    sf::Socket::Status status = socket.connect(srvAddress, srvPort, sf::milliseconds(5000));
//
//    if (status != sf::Socket::Done)
//    {
//        // error...
//    }
//
//    // Check what received from server
//    std::cout << "Remote address: " << socket.getRemoteAddress() << "\n";
//    std::cout << "Remote port: " << socket.getRemotePort() << "\n";
//
//
//    // In case, send a close.
//    sf::Packet pkt;
//    pkt << "Client";
//    socket.send(pkt);
//
//
//    //Bye bye.
//    return 0;
//
//}

////______________________________________________________________________________
//int cmd(cat::context& ctx, int argc, char* argv[])
//{
//    /*! Prepare and parse the command line.
//    */
//
//    // Set the arguments.
//    //app.cmd.addArg("","",)
//
//
//    // Set the options.
//    ctx.cmd.addOpt("address", "set the server address [localhost]", false, true);
//    ctx.cmd.addOpt("port", "set the server port [2000]", false, true);
//    ctx.cmd.addOpt("v", "verbosity level [critical, error, warning, message, info, debug, all]", false, true);
//
//    // Parse the command line. Return 0 if everything ok, -1 for unknown/wrong
//    // options or arguments.
//    if (ctx.cmd.parse(argc, argv)) return -1;
//
//    // Everything fine.
//    return 0;
//}