// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
#define OOF_IMPL
#include<oof.h>

// SFML system/windowing library.
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// SFML Network.
#include <SFML/Network.hpp>

// GUI interface.
#include "imgui-SFML.h"
#include "imgui.h"

// STL.
#include <cmath>
#include <iostream>
#include <string>

// Application.
#include "srvGlobal.hpp"
#include "cmd.hpp"

//______________________________________________________________________________
namespace cat {
    class appCtx {
        /* This structure contains all the running parameters of the application
           and it is passed through the various steps of the (many) running
           processes.
           Note that the class start the windows management system (SFML library)
           through the constructor itself, to ensure more c++ object management
           with respect to a pointer-based one.
        */
    public:

        // Application running status.
        enum class runState : int { ongoing, success, failure };

        // General.
        std::string winTitle = "CAT";
        int winWidth = 1280;
        int winHeight = 720;

        // Command line.
        cat::cmd cmd;

        // SFML window.
        sf::RenderWindow window;
        sf::Clock deltaClock;

        // SFML network server.
        sf::TcpListener server;

        // ImGUI User Interface

        // Diligent Core Graphics APIs.

        // Running status.
        runState state;

        // Ctor.
        appCtx() : state(runState::ongoing)
            //window(sf::RenderWindow(sf::VideoMode(winWidth, winHeight), winTitle))
        {}

        // Dtor.
        ~appCtx() {}
    };
}

//______________________________________________________________________________
// Main proprietary functions.
int appCmd(cat::appCtx&, int argc, char* argv[]);
int appInit(cat::appCtx&);
int srvInit(cat::appCtx&);
int appSplash(cat::appCtx&);
int appLoop(cat::appCtx&);
int srvListen(cat::appCtx&);
int appEvent(cat::appCtx&);
int appDraw(cat::appCtx&);
int srvClose(cat::appCtx&);
int appClose(cat::appCtx&);

//______________________________________________________________________________
int main(int argc, char* argv[]) {
    
    /* CAT Server entry point. The main entry point simply executes initialization
       then hands over control to the 'srvLoop' main application loop.
    */

    // Set up the application context data structure. Doing that, actually 
    // initializes the system/windows management as well through the class
    // ctor, which creates a SFML window.
    cat::appCtx app;

    // Parse the command line.
    if (appCmd(app, argc, argv)) return -1;

    // Splash.
    appSplash(app);

    // Init App.
    if (appInit(app)) return -1;;

    // Init Server.
    if (srvInit(app)) return -1;
    
    // Start the main loop.
    appLoop(app);
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Stop the server.
    srvClose(app);

    // Close the interfaces.
    appClose(app);
        
    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appCmd(cat::appCtx& app, int argc, char* argv[])
{
    /*! Prepare and parse the command line.
    */

    // Set the arguments.
    //app.cmd.addArg("","",)


    // Set the options.
    app.cmd.addOpt("p", "server port", true, true);
    app.cmd.addOpt("v", "verbosity level", false, false);

    // Parse the command line. Return 0 if everything ok, -1 for unknown/wrong
    // options or arguments.
    return app.cmd.parse(argc, argv);
}


//______________________________________________________________________________
int appInit (cat::appCtx& app)
{
    /*! Initialize the application, including the windows management,
        event management, graphics API libraries, network libraries.
    */

    // Starts the windows and event management.
    app.window.create(sf::VideoMode(app.winWidth, app.winHeight), app.winTitle);

    // Frame rate limit, to avoid system overload when not necessary.
    app.window.setFramerateLimit(60);
    
    // Init the GUI interface system (ImGui).
    ImGui::SFML::Init(app.window);

    // Graphics APIs management.

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvInit(cat::appCtx& app)
{
    /*! Initialize the server, and start listening.
    */



    // Splash info.
    std::cout << "Server started. Listening on port: " << 33 << CCO_RESET << "\n";

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appSplash(cat::appCtx& app)
{
    /*! Show splash credits.
    */
    
  
    // Title.
    std::cout << "\n\n";
    std::cout << "+" << std::string(42, '-') << "+\n";
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout 
        << "|    "
        << CCO_LAVIO << CCO_BOLD << "C" << CCO_RESET << "++ "
        << CCO_LAVIO << CCO_BOLD << "A" << CCO_RESET << "cquisiiton & "
        << CCO_LAVIO << CCO_BOLD << "A" << CCO_RESET << "nalysis "
        << CCO_LAVIO << CCO_BOLD << "T" << CCO_RESET << "oolset"
        "    |\n";
    
    // Copyright.
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout << "|" 
        << "        (C)" 
        << CCO_LWHITE << " Padova University " 
        << CCO_RESET << "2024        " << "|\n";

    // Closure.    
    std::cout << "|" << std::string(42, ' ') << "|\n";
    std::cout << "+" << std::string(42, '-') << "+\n";
    
    // Libraries.
    std::cout << "\nLibraries\n";
    std::cout << "Console..................: "
        << CCO_LWHITE << "Off           " << CCO_RESET << "("
        << CCO_ULINE << CCO_CYAN << "https://github.com/s9w/oof"
        << CCO_RESET << ")\n";
    std::cout << "System and network.......: "
        << CCO_LWHITE << "SFML 2.6.1    " << CCO_RESET << "("
        << CCO_ULINE << CCO_CYAN << "https://github.com/SFML"
        << CCO_RESET << ")\n";
    std::cout << "Graphics User Interface..: "
        << CCO_LWHITE << "Dear ImGui    " << CCO_RESET << "("
        << CCO_ULINE << CCO_CYAN << "https://github.com/ocornut/imgui"
        << CCO_RESET << ")\n";
    std::cout << "3D APIs abstraction......: "
        << CCO_LWHITE << "Diligent Core " << CCO_RESET << "("
        << CCO_ULINE << CCO_CYAN << "https://github.com/DiligentGraphics/DiligentCore"
        << CCO_RESET << ")\n";
        
    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvListen(cat::appCtx& app)
{
    /*! Collect latest connection request, and parse new I/O data streams from 
        clients arrived since the last check.
    */


    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appLoop(cat::appCtx& app)
{
    /*! This is the main application loop, which handles events from the user,
        calls from/to the clients, and display the outputs.
    */

    
    // Main loop.
    while (app.state == cat::appCtx::runState::ongoing) {
        
        // Retrieve events from the user/system.
        appEvent(app);
        
        // Listen the server connections.
        srvListen(app);

        // Draw interface and scene(s).
        appDraw(app);
        
    }

    // Everything fine.
    return 0;
}

//______________________________________________________________________________
int appEvent(cat::appCtx& app)
{
    /*! Retrieves and parse events from the user and the system
    */

    // Retrieve events from the user/system.
    sf::Event event;
    
    // Retrieve all the queued events from the user/system.
    while (app.window.pollEvent(event)) {

        // First, pass the event to the GUI.
        // ---------------------------------
        ImGui::SFML::ProcessEvent(app.window, event);


        // Parse the managed events.
        // -------------------------
        


        // Resize.
        
        // Quit.
        if (event.type == sf::Event::Closed) {
            app.state = cat::appCtx::runState::success;
        }
    }

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appDraw(cat::appCtx& app)
{
    /*! Draw the scene(s) and other interface 3Dworld elements.
    */

    // Update the GUI.
    ImGui::SFML::Update(app.window, app.deltaClock.restart());

    // ImGui cycle.
    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();
    
    // ImGui demo.
    ImGui::ShowDemoWindow();

    // Scene drawing.

    app.window.clear();
    //app.window.draw(shape);
    ImGui::SFML::Render(app.window);
    app.window.display();

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvClose(cat::appCtx& app)
{
    /*! Stop the server from listening, and clear all the sockets to/from the 
        connected clients.
    */

    
    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appClose(cat::appCtx& app)
{
    /*! Stop the application, close the windows/event managers, shut down the
        graphics APIs.
    */

    // CLose main SFML window.
    app.window.close();

    // Close ImGui.
    ImGui::SFML::Shutdown();

    // Everything fine.
    return 0;
}