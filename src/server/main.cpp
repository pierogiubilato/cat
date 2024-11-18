//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER entry point               --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"main.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"09 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________

// STL.
#include <cmath>
#include <iostream>
#include <string>

// SFML system/windowing library.
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// SFML Network.
#include <SFML/Network.hpp>

// ImGui interface.
#include "imgui-SFML.h"
#include "imgui.h"

// Application.
#include "console.hpp"
//#include "global.hpp"
#include "context.hpp"
#include "cmd.hpp"
#include "socket.hpp"

//______________________________________________________________________________
// Main proprietary functions.
int appCmd(cat::context&, int argc, char* argv[]);
int appInit(cat::context&);
int srvInit(cat::context&);
int appSplash(cat::context&);
int appLoop(cat::context&);
int srvListen(cat::context&);
int appEvent(cat::context&);
int appDraw(cat::context&);
int srvClose(cat::context&);
int appClose(cat::context&);

//______________________________________________________________________________
int main(int argc, char* argv[]) {
    
    /* CAT Server entry point. The main entry point simply executes initialization
       then hands over control to the 'srvLoop' main application loop.
    */

    // Set up the application context data structure. Doing that, actually 
    // initializes the system/windows management as well through the class
    // ctor, which creates a SFML window.
    cat::context ctx;

    // Parse the command line.
    if (appCmd(ctx, argc, argv) != 0) return -1;

    // Splash.
    appSplash(ctx);

    // Init App.
    if (appInit(ctx) != 0) return -1;;

    // Init Server.
    if (srvInit(ctx) != 0) return -1;
    
    // Start the main loop.
    appLoop(ctx);
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Stop the server.
    srvClose(ctx);

    // Close the interfaces.
    appClose(ctx);
        
    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appCmd(cat::context& ctx, int argc, char* argv[])
{
    /*! Prepare and parse the command line.
    */

    // Set the arguments.
    //app.cmd.addArg("","",)


    // Set the options.
    ctx.cmd.addOpt("port", "server port", false, true);
    ctx.cmd.addOpt("v", "verbosity level", false, false);
    
    // Parse the command line. Return 0 if everything ok, -1 for unknown/wrong
    // options or arguments.
    if (ctx.cmd.parse(argc, argv)) return -1;

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appInit (cat::context& ctx)
{
    /*! Initialize the application, including the windows management,
        event management, graphics API libraries, network libraries.
    */

    // Starts the windows and event management.
    ctx.window.create(sf::VideoMode(ctx.winWidth, ctx.winHeight), ctx.winTitle);

    // Frame rate limit, to avoid system overload when not necessary.
    ctx.window.setFramerateLimit(60);
    
    // Init the GUI interface system (ImGui).
    ImGui::SFML::Init(ctx.window);

    // Graphics APIs management.

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvInit(cat::context& ctx)
{
    /*! Initialize the server, and start listening.
    */


    // Check whether a specific port was asked for (defaults to 0 if not).
    int port = std::stoi(ctx.cmd.getOptionValue("port", "2000"));

    // If no specific port requested, use the first available one.
    if (port == 0) port = sf::Socket::AnyPort;

    // Try opening the listening port.
    if (ctx.server.listen(port) != sf::Socket::Done) {
        
        // Report error.
        std::cout << cat::cl::error() << "Error"
            << cat::cl::reset() << ": failed to start the server\n";
        return -1;
    }
     
    // Set the sockets functions as non-blocking.
    //ctx.server.setBlocking(false);

    // Connection info.
    std::cout << "Server started. " 
        << cat::cl::info() << "Listening on port : "
        << cat::cl::message() << ctx.server.getLocalPort()
        << cat::cl::reset() << "\n";
    
    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appSplash(cat::context& ctx)
{
    /*! Show splash credits.
    */
    
  
    // Title.
    std::cout << "\n\n";
    std::cout << "+" << std::string(42, '-') << "+\n";
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout 
        << "|    "
        << cat::cl::lavio() << cat::cl::bold() << "C" << cat::cl::reset() << "++ "
        << cat::cl::lavio() << cat::cl::bold() << "A" << cat::cl::reset() << "cquisiiton & "
        << cat::cl::lavio() << cat::cl::bold() << "A" << cat::cl::reset() << "nalysis "
        << cat::cl::lavio() << cat::cl::bold() << "T" << cat::cl::reset() << "oolset"
        "    |\n";
    
    // Copyright.
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout << "|" 
        << "        (C)" 
        << cat::cl::lwhite() << " Padova University "
        << cat::cl::reset() << "2024        " << "|\n";

    // Closure.    
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout << "+" << std::string(42, '-') << "+\n";
    
    // Libraries.
    std::cout << "\nLibraries\n";
    std::cout << "Console..................: "
        << cat::cl::lwhite() << "Off           " << cat::cl::reset() << "("
        << cat::cl::link() << "https://github.com/s9w/oof"
        << cat::cl::reset() << ")\n";
    std::cout << "System and network.......: "
        << cat::cl::lwhite() << "SFML 2.6.1    " << cat::cl::reset() << "("
        << cat::cl::link() << "https://github.com/SFML"
        << cat::cl::reset() << ")\n";
    std::cout << "Graphics User Interface..: "
        << cat::cl::lwhite() << "Dear ImGui    " << cat::cl::reset() << "("
        << cat::cl::link() << "https://github.com/ocornut/imgui"
        << cat::cl::reset() << ")\n";
    std::cout << "3D APIs abstraction......: "
        << cat::cl::lwhite() << "Diligent Core " << cat::cl::reset() << "("
        << cat::cl::link() << "https://github.com/DiligentGraphics/DiligentCore"
        << cat::cl::reset() << ")\n";
        
    // Spacing
    std::cout << std::endl;

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvListen(cat::context& ctx)
{
    /*! Collect latest connection request, and parse new I/O data streams from 
        clients arrived since the last check.
    */


    // Listen to all connected clients.
    //for (auto i : ctx.client) {}
    
       
    // Look for a new client trying to connect.
    std::cout << "Server listening...\n";
    sf::TcpSocket client;
    //client.setBlocking(false);
    sf::Packet pkt;
    switch (ctx.server.accept(client)) {
        
        // Connection established. Save the client object in the client vector,
        // and ping it back for confirmation that the socket is now open.
        case sf::Socket::Done :
            std::cout << "Client accepted: " << client.getRemoteAddress() << "\n";

            pkt << uint32_t(cat::tcp::open);
            //ctx.client.push_back(client);
            //ctx.client.back().send(pkt);
            break;
        
        // No connection. Nothing to do, the socket object will expire at the
        // function exit.
        case sf::Socket::Error :
            break;
    
        // Unmanaged.
        default:
            break;
            
    }

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appLoop(cat::context& ctx)
{
    /*! This is the main application loop, which handles events from the user,
        calls from/to the clients, and display the outputs.
    */

    
    // Main loop.
    while (ctx.state == cat::context::runState::ongoing) {
        
        // Retrieve events from the user/system.
        appEvent(ctx);
        
        // Listen the server connections.
        srvListen(ctx);

        // Draw interface and scene(s).
        appDraw(ctx);
        
    }

    // Everything fine.
    return 0;
}

//______________________________________________________________________________
int appEvent(cat::context& ctx)
{
    /*! Retrieves and parse events from the user and the system
    */

    // Retrieve events from the user/system.
    sf::Event event;
    
    // Retrieve all the queued events from the user/system.
    while (ctx.window.pollEvent(event)) {

        // First, pass the event to the GUI.
        // ---------------------------------
        ImGui::SFML::ProcessEvent(ctx.window, event);


        // Parse the managed events.
        // -------------------------
        


        // Resize.
        
        // Quit.
        if (event.type == sf::Event::Closed) {
            ctx.state = cat::context::runState::success;
        }
    }

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appDraw(cat::context& ctx)
{
    /*! Draw the scene(s) and other interface 3Dworld elements.
    */

    // Update the GUI.
    ImGui::SFML::Update(ctx.window, ctx.clock.restart());

    // ImGui cycle.
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();
    
    // ImGui demo.
    ImGui::ShowDemoWindow();

    // Scene drawing.

    ctx.window.clear();
    //app.window.draw(shape);
    ImGui::SFML::Render(ctx.window);
    ctx.window.display();

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvClose(cat::context& ctx)
{
    /*! Stop the server from listening, and clear all the sockets to/from the 
        connected clients.
    */

    
    // Broadcast closure to all connected clients.

    // Close the server.
    ctx.server.close();


    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appClose(cat::context& ctx)
{
    /*! Stop the application, close the windows/event managers, shut down the
        graphics APIs.
    */

    // CLose main SFML window.
    ctx.window.close();

    // Close ImGui.
    ImGui::SFML::Shutdown();

    // Everything fine.
    return 0;
}