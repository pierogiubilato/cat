
// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
#define OOF_IMPL
#include "oof.h"


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
#include "socket.hpp"
#include "cmd.hpp"


//______________________________________________________________________________
namespace cat {
    class context
    {
        public:
            unsigned short port;
            sf::IpAddress address;
            cat::cmd cmd;
    };
}

// Local functions declaration.
int cmd(cat::context&, int argc, char* argv[]);


//______________________________________________________________________________
int main(int argc, char* argv[])
{
   
    std::cout << "CAT client\n";

    // Application context.
    cat::context ctx;

    // Parse command line.
    cmd(ctx, argc, argv);
    sf::IpAddress srvAddress(ctx.cmd.getOptionValue("address", "localhost"));
    unsigned short srvPort(std::stoi(ctx.cmd.getOptionValue("port", "2000")));
    
    std::cout << "Trying to connect to the host address " << srvAddress << "\n";
    std::cout << "Trying to connect to the server on port " << srvPort << "\n";
        
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(srvAddress, srvPort, sf::milliseconds(5000));

    if (status != sf::Socket::Done)
    {
        // error...
    }

    // Check what received from server
    std::cout << "Remote address: " << socket.getRemoteAddress() << "\n";
    std::cout << "Remote port: " << socket.getRemotePort() << "\n";


    // In case, send a close.
    sf::Packet pkt;
    pkt << "Client";
    socket.send(pkt);


    //Bye bye.
    return 0;

}


//______________________________________________________________________________
int cmd(cat::context& ctx, int argc, char* argv[])
{
    /*! Prepare and parse the command line.
    */

    // Set the arguments.
    //app.cmd.addArg("","",)


    // Set the options.
    ctx.cmd.addOpt("address", "set the server address [localhost]", false, true);
    ctx.cmd.addOpt("port", "set the server port [2000]", false, true);
    ctx.cmd.addOpt("v", "verbosity level", false, false);

    // Parse the command line. Return 0 if everything ok, -1 for unknown/wrong
    // options or arguments.
    if (ctx.cmd.parse(argc, argv)) return -1;

    // Everything fine.
    return 0;
}