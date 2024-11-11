//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Example 01 - Basic console output            --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"exmp_01.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"11 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________




// STL.
#include <vector>
#include <string>
#include <iostream>

// CAT headers.
#include "client.hpp"
#include "console.hpp"
#include "cmd.hpp"


//______________________________________________________________________________
int main(int argc, char* argv[])
{
    // Startup. Show an headline.
    std::cout << cat::cl::message("CAT example #1") << std::endl;

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
    
    


    // -------------------------------------------------------------------------
    // --                    Console output formatting                        --
    // -------------------------------------------------------------------------
      


    // With the CAT library are included some very simple console formatting,
    // mostly to help debug, based on the oof library (https://github.com/s9w/oof).
    // The namespace 'cat::cl' encloses all the STATIC functions and classes 
    // used for console output formatting.
    
    // Set the console verbosity at the "message" level (the default one).
    cat::cl::verb::set(cat::cl::verb::message);

    // Show current verbosity level (it makes a temporary instantiation to pass
    // the object to the output stream).
    std::cout << "Current console verbosity set to: " << cat::cl::verb() << "\n";
       
    // Alternatively, you can call the get method.
    std::cout << "Current console verbosity set to: " << cat::cl::verb::get() << "\n";

    // Print a general message.
    std::cout << cat::cl::message("This is a message") << "\n";

    // Print something standard.
    std::cout << "A standard output line of text." << "\n";
        
    // Try printing something with higher priority level. This is the explicit way,
    // which gives more flexibility in implementing more complex output structures.
    if (cat::cl::verb::show(cat::cl::verb::warning)) {
        std::cout << cat::cl::warning() << "This is a warning" << cat::cl::reset() << "\n";
    }

    // A quicker way to print the warning message. This will achieve the same
    // result of previous lines, at the expense of less flexibility (e.g., the
    // format will automatically reverse to standard).
    std::cout << cat::cl::warning("This is a warning, quick version") << "\n";
    
    // Try printing something with lower priority level (it will not).
    std::cout << cat::cl::info("This is a general info") << "\n";

    // You can print numbers in both ways as well:
    std::cout << "This is a number in bold: " << cat::cl::bold() << 3010 
              << cat::cl::reset() << "\n";
    std::cout << "This is a number in bold: " << cat::cl::warning(3010) << "\n";





    // -------------------------------------------------------------------------
    // --                    Connect to the server                            --
    // -------------------------------------------------------------------------


    // Cosmetic output.
    std::cout << "\n\n\n" << cat::cl::lwhite(std::string(80, '=')) << "\n"
        << "Connection to the server" << "\n"
        << cat::cl::lwhite(std::string(80, '=')) << "\n";


    // Once instantiated, the library must connect to the server. If the 'connect'
    // call returns 'cat::'
    if (cat.connect() != cat::client::status::connected) {

        // Here we had an error. We can try again to connect. Until the connection
        // is properly defined, the CAT library will provide local functionalities
        // only.
        std::cout << cat::cl::error() << "CAT example #1 exit with connection error" 
                  << cat::cl::reset() << "\n";
        return -1;
    }


    // Connection has been successfull.
    //std::cout << cat::client::<< "\n";
    
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



