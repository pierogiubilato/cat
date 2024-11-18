//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER entry point               --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"server.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________

// STL.
#include <cmath>
#include <iostream>
#include <string>

// SFML system/windowing library.
//#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// SFML Network.
#include <SFML/Network.hpp>

// ImGui interface.
#include "imgui-SFML.h"
#include "imgui.h"

// Application - shared with end User.
#include "console.hpp"
#include "cmd.hpp"

// Application - shared between Server and Client.
#include "socket.hpp"
//#include "coStreamable.hpp"
//#include "coDrawable.hpp"
#include "coSet.hpp"
#include "uiButton.hpp"

// Application - Server only.
#include "context.hpp"
#include "window.hpp"
#include "gui.hpp"


//______________________________________________________________________________
// Main proprietary functions.
int appCmd(cat::context&, int argc, char* argv[]);

int appInit(cat::context&);
int srvInit(cat::context&);
int guiInit(cat::context&);

int appSplash(cat::context&);
int appLoop(cat::context&);
int srvListen(cat::context&);
////int appEvent(cat::context&);
////int appDraw(cat::context&);

int guiClose(cat::context&);
int srvClose(cat::context&);
int appClose(cat::context&);


int doTest(cat::context&);


//______________________________________________________________________________
int main(int argc, char* argv[]) {
    
    //! CAT Server entry point. The main entry point simply executes initialization
    //! then hands over control to the 'srvLoop' main application loop.
std::cout << "[1]\n";
    // Set up the application context data structure. Doing that, actually 
    // initializes the system/windows management as well through the class
    // ctor, which creates a SFML window.
    cat::context ctx;
std::cout << "[2]\n";

    // Parse the command line.
    if (appCmd(ctx, argc, argv) != 0) return -1;
std::cout << "[3]\n";

    // Splash.
    appSplash(ctx);
std::cout << "[4]\n";

    // Init App.
    if (appInit(ctx) != 0) return -1;;
std::cout << "[5]\n";

    // Init GUI.
    if (guiInit(ctx) != 0) return -1;
std::cout << "[6]\n";

    // Init Server.
    if (srvInit(ctx) != 0) return -1;
std::cout << "[7]\n";
    
    // Do tests with objects.
    if (doTest(ctx) != 0) return -1;
std::cout << "[8]\n";



    // Start the main loop.
    appLoop(ctx);
std::cout << "[9]\n";

    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    // Stop the server.
    srvClose(ctx);
std::cout << "[10]\n";
    
// Stop the GUI.
    guiClose(ctx);
std::cout << "[11]\n";

    // Close the interfaces.
    appClose(ctx);
std::cout << "[12]\n";
    
// Everything fine.
    return 0;
}


 
//______________________________________________________________________________
int appCmd(cat::context& ctx, int argc, char* argv[])
{
    //! Prepare and parse the command line.
    
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
    //! Initialize the application, including the windows management,
    //! event management, graphics API libraries, network libraries.
    

    // Starts the windows and event management.
    //ctx.window.create(sf::VideoMode(ctx.winWidth, ctx.winHeight), ctx.winTitle);

    // Frame rate limit, to avoid system overload when not necessary.
    //ctx.window.setFramerateLimit(60);
    
   
    // Graphics APIs management.

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int guiInit(cat::context& ctx)
{
    //! Initialize GUI interface


    // Init the GUI interface system (ImGui).
    //ImGui::SFML::Init(ctx.window);

    // Init the server main GUI interface. This will start the SFML system and 
    // create the main application window.

    //ctx._gui = cat::gui::getInstance();



    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvInit(cat::context& ctx)
{
    //! Initialize the server, and start listening.
    


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
    //! Show splash credits.
        
  
    // Title.
    std::cout << "\n\n";
    std::cout << "+" << std::string(42, '-') << "+\n";
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout 
        << "|    "
        << cat::cl::lavio("C") << "++ "
        << cat::cl::lavio("A") << "cquisiiton & "
        << cat::cl::lavio("A") << "nalysis "
        << cat::cl::lavio("T") << "oolset"
        "    |\n";
    
    // Copyright.
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout << "|" 
        << "        (C)" 
        << cat::cl::lwhite(" Padova University ") << "2024        " << "|\n";

    // Closure.    
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout << "+" << std::string(42, '-') << "+\n";
    
    // Libraries.
    std::cout << "\nLibraries\n";
    std::cout << "Console..................: " << cat::cl::lwhite("Off           ") 
        << "(" << cat::cl::link("https://github.com/s9w/oof") << ")\n";
    std::cout << "System and network.......: "<< cat::cl::lwhite("SFML 2.6.1    ") 
        << "(" << cat::cl::link("https://github.com/SFML") << ")\n";
    std::cout << "Graphics User Interface..: " << cat::cl::lwhite("Dear ImGui    ") 
        << "(" << cat::cl::link("https://github.com/ocornut/imgui") << ")\n";
    std::cout << "3D APIs abstraction......: " << cat::cl::lwhite("Diligent Core ")
        << "(" << cat::cl::link("https://github.com/DiligentGraphics/DiligentCore") << ")\n";
        
    // Spacing
    std::cout << std::endl;

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvListen(cat::context& ctx)
{
    //! Collect latest connection request, and parse new I/O data streams from 
    //! clients arrived since the last check.
    


    // Listen to all connected clients.
    //for (auto i : ctx.client) {}
    
       
    // Look for a new client trying to connect.
    // std::cout << "Server listening...\n";
    
    // Create a new (non blocking) temporary socket to listen for.
    sf::TcpSocket* socket = new sf::TcpSocket();
    //socket->setBlocking(false);
    sf::Packet pkt;


    // Check for any answer.
    switch (ctx.server.accept(*socket)) {
        
        // Connection established. Save the client object in the client vector,
        // and ping it back for confirmation that the socket is now open.
        case sf::Socket::Done :
            if (cat::cl::verb::show(cat::cl::verb::message)) {
                std::cout << cat::cl::white("Client accepted: ")
                    << cat::cl::uline() << socket->getRemoteAddress() 
                    << "\n";
            }

            // Store the socket.
            ctx.client.push_back(socket);

            // Test message.
            pkt << uint32_t(cat::tcp::open);
            ctx.client.back()->send(pkt);
            
            break;
        
        // No connection. Nothing to do, the socket object will expire at the
        // function exit.
        case sf::Socket::Error :
            delete socket;
            break;
    
        // Unmanaged.
        default:
            delete socket;
            break;
            
    }
    

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appLoop(cat::context& ctx)
{
    //! This is the main application loop, which handles events from the user,
    //! calls from/to the clients, and display the outputs.
    

    /*
    // Main loop.
    while (ctx.state == cat::context::runState::ongoing) {
        
        // Listen the server connections.
        srvListen(ctx);



        // Retrieve events from the user/system.
        //ctx._gui->event(ctx);
        
        // Draw interface and scene(s).
        //ctx._gui->draw(ctx);
        


    }
    */

    // Everything fine.
    return 0;
}

//______________________________________________________________________________
int doTest(cat::context& ctx)
{
    //! This is the main application loop, which handles events from the user,
    //! calls from/to the clients, and display the outputs.

    
    std::cout << cat::cl::message("Building a cat::co:abstract base object") << "\n";
    cat::co::abc myCo;
    std::cout << "Dumping my first object: " << myCo << "\n";

    std::cout << cat::cl::message("Building a cat::co:set container") << "\n";
    cat::co::set mySet;
    std::cout << "Dumping my first object: " << mySet << "\n";


    // Everything fine.
    return 0;
}



////______________________________________________________________________________
//int appEvent(cat::context& ctx)
//{
//    //! Retrieves and parse events from the user and the system
//   
//
//    // Retrieve events from the user/system.
//    sf::Event event;
//    
//    // Retrieve all the queued events from the user/system.
//    while (ctx.window.pollEvent(event)) {
//
//        // First, pass the event to the GUI.
//        // ---------------------------------
//        ImGui::SFML::ProcessEvent(ctx.window, event);
//
//
//        // Parse the managed events.
//        // -------------------------
//        
//
//
//        // Resize.
//        
//        // Quit.
//        if (event.type == sf::Event::Closed) {
//            ctx.state = cat::context::runState::success;
//        }
//    }
//
//    // Everything fine.
//    return 0;
//}


//______________________________________________________________________________
//int appDraw(cat::context& ctx)
//{
    ///*! Draw the scene(s) and other interface 3Dworld elements.
    

    //// Update the GUI.
    //ImGui::SFML::Update(ctx.window, ctx.clock.restart());

    //// ImGui cycle.
    //ImGui::Begin("Hello, world!");
    //ImGui::Button("Look at this pretty button");
    //ImGui::End();
    //
    //// ImGui demo.
    //ImGui::ShowDemoWindow();

    //// Scene drawing.

    //ctx.window.clear();
    ////app.window.draw(shape);
    //ImGui::SFML::Render(ctx.window);
    //ctx.window.display();

    //// Everything fine.
    //return 0;
//}


//______________________________________________________________________________
int srvClose(cat::context& ctx)
{
    //! Stop the server from listening, and clear all the sockets to/from the 
    //! connected clients.
   

    
    // Broadcast closure to all connected clients.

    // Close the server.
    ctx.server.close();


    // Everything fine.
    return 0;
}

//______________________________________________________________________________
int guiClose(cat::context& ctx)
{
    //! Stop the application, close the windows/event managers, shut down the
    //! graphics APIs.
   
    // Close the GUI interface.
    //delete ctx._gui;

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appClose(cat::context& ctx)
{
    //! Stop the application, close the windows/event managers, shut down the
    //! graphics APIs.
   
    
    // Everything fine.
    return 0;
}
