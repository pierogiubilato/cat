
// STL.
#include <iostream>


// CAT headers.
#include <client.hpp>
#include "console.hpp"
#include "cmd.hpp"


////______________________________________________________________________________
int main(int argc, char* argv[])
{
    // Startup.
    std::cout << "CAT example #1: BASIC\n";

    // Initialize the CAT framework by creating a new cat::client object. Passing
    // the command line arguments (optional) allows the library to look for the
    // managed options:
    // '--address []': the address of the server, in the form "###.###.###.###" or
    //              any resolved string, like "localhost" (the default setting).  '
    // '--port []': the port the server is listening at , e.g. "2000" (the default 
    //              server setting if no other port has been set at its launch).  '
    // '--verb []': the verbosity of the library, which possible arguments are 
    //              {"critical", "error", "warning", "message", "info", "debug", 
    //              "all"}. The default value is "message".
    cat::client cat(argc, argv);
    
    
    // With the CAT library are included some very simple console formatting,
    // mostly to help debug, based on the oof library (https://github.com/s9w/oof).
    
    // The verbosity filter may be set with:
    
    
    // Once instantiated, the library must connect to the server. If the 'connect'
    // call returns 'cat::'
    if (cat.connect() != cat::client::status::connected) {

        // Here we had an error. We can try again to connect. Until the connection
        // is properly defined, the CAT library will only partially work.
        std::cout << cat::cl::error() << "CAT example #1 exit with connection error" 
                  << cat::cl::reset() << "\n";
        return -1;
    }



    
    // Use the CAT library to look for possible arguments on the command line.
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

    // Info.
    std::cout << "CAT example #1 successfully completed\n";

    // Bye bye.
    return 0;
}



