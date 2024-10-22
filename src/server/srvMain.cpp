// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
#define OOF_IMPL
#include<oof.h>

// SFML system/windowing library.
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// GUI interface.
#include "imgui-SFML.h"
#include "imgui.h"

// STL.
#include <cmath>
#include <iostream>
#include <string>

// Application.
#include "srvGlobal.hpp"

//______________________________________________________________________________
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

    // SFML window.
    sf::RenderWindow window;
    sf::Clock deltaClock;

    // SFML Network.

    // ImGUI User Interface

    // Diligent Core Graphics APIs.
    
    // Running status.
    runState state;

    // Ctor.
    appCtx() : state(runState::ongoing),
               window(sf::RenderWindow(sf::VideoMode(winWidth, winHeight), winTitle))
               {}
    
    // Dtor.
    ~appCtx() {}
};


//______________________________________________________________________________
// Main proprietary functions.
int appInit(appCtx&);
int srvInit(appCtx&);
int appSplash(appCtx&);
int appLoop(appCtx&);
int srvListen(appCtx&);
int appEvent(appCtx&);
int appDraw(appCtx&);
int srvClose(appCtx&);
int appClose(appCtx&);

//______________________________________________________________________________
int main() {
    
    /* CAT Server entry point. The main entry point simply executes initialization
       then hands over control to the 'srvLoop' main application loop.
    */

    // Set up the application context data structure. Doing that, actually 
    // initializes the system/windows management as well through the class
    // ctor, which creates a SFML window.
    appCtx app;

    // Init App.
    appInit(app);

    // Init Server.
    srvInit(app);

    // Splash.
    appSplash(app);
    
    // STart the main loop.
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
int appInit (appCtx& app)
{
    /*! Initialize the application, including the windows management,
        event management, graphics API libraries, network libraries.
    */

    // Windows and event management.
    

    // Frame rate limit, to avoid system overload when not necessary.
    app.window.setFramerateLimit(60);
    
    // Init the GUI interface system (ImGui).
    ImGui::SFML::Init(app.window);

    // Graphics APIs management.

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvInit(appCtx& app)
{
    /*! Initialize the server, and start listening.
    */



    // Splash info.
    std::cout << "[ CAT ] " << CCO_LWHITE << "Server started" << CCO_RESET << "\n";

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appSplash(appCtx& app)
{
    /*! Show splash credits.
    */
    
    // Quick OOF definitions.
    //#define CCO_LBLUE oof::fg_color({0, 0, 255})


    // CAT.
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
int srvListen(appCtx& app)
{
    /*! Collect latest connection request, and parse new I/O data streams from 
        clients arrived since the last check.
    */


    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appLoop(appCtx& app)
{
    /*! This is the main application loop, which handles events from the user,
        calls from/to the clients, and display the outputs.
    */

    
    // Main loop.
    while (app.state == appCtx::runState::ongoing) {
        
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
int appEvent(appCtx& app)
{
    /*! Retrieves and parse events from the user and the system
    */

    // Retrieve events from the user/system.
    sf::Event event;
    
    // Retrieve all the queued events from the user/system.
    while (app.window.pollEvent(event)) {

        // First, pass the event to the GUI.
        ImGui::SFML::ProcessEvent(app.window, event);

        // Parse the managed events.
        // -------------------------
        
        // Resize.
        
        // Quit.
        if (event.type == sf::Event::Closed) {
            app.state = appCtx::runState::success;
        }
    }

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appDraw(appCtx& app)
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
int srvClose(appCtx& app)
{
    /*! Stop the server from listening, and clear all the sockets to/from the 
        connected clients.
    */



    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appClose(appCtx& app)
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



//
//
//


//
//// SDL functions
//SDL_AppResult sdlInit(appContext*);
//SDL_AppResult sdlEvent(appContext*);
//SDL_AppResult sdlIterate(appContext*);
//SDL_AppResult sdlClose(appContext*);
//SDL_AppResult sdlFail(appContext*);
//
//
////______________________________________________________________________________
//int main(int argc, char* argv[])
//{
//    /* CAT Server entry point. The main entry point simply executes initialization
//       then hands over control to the 'srvLoop' main application loop.
//    */
//
//    // Set up the application context data structure.
//    appContext* app = new appContext;
//
//    // Init App.
//    appInit(app);
//
//    // Init Server.
//    srvInit(app);
//
//    // Splash.
//    appSplash(app);
//
//    // Application main loop.
//    while (app->sdlQuit == SDL_APP_CONTINUE) {
//
//        // Parse window interaction events.
//        sdlEvent(app);
//
//        // Listen/answers to clients.
//        srvListen(app);
//
//        // Update the user interface.
//        //
//
//        // Wait.
//        SDL_Delay(100);
//
//        // Update the scene(s) drawing.
//        sdlIterate(app);
//    }
//
//    // Bye Bye.
//    appClose(app);
//
//    // Check closure.
//    if (app->sdlQuit == SDL_APP_SUCCESS) {
//        std::cout << "CAT server execution terminated with no error" << std::endl;
//        return 0;
//    } else {
//        std::cout << "CAT server execution terminated with ERROR" << std::endl;
//        return -1;
//    }
//}
//
//
//
//
//
//
////==============================================================================
////==============================================================================
////==============================================================================
////==============================================================================
//
////______________________________________________________________________________
//SDL_AppResult sdlFail(appContext* app)
//{
//    // log the SDL error.
//    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
//    
//    // set the application state as to be terminated.
//    app->sdlQuit = SDL_APP_FAILURE;
//
//    // Application encountered an error.
//    return SDL_APP_FAILURE;
//}
//
//
////______________________________________________________________________________
//SDL_AppResult sdlInit(appContext* app)
//{
//    
//    // Init the SDL library, make a window so we only need the Video capabilities.
//    if (not SDL_Init(SDL_INIT_VIDEO)) {
//        return sdlFail(app);
//    }
//
//    // Setup which types of events to handle.
//    //SDL_SetEventEnabled(SDL_EVENT_POLL_SENTINEL, false);
//
//
//    // Create the main window.
//    SDL_Window* window = SDL_CreateWindow("Window", 352, 430, SDL_WINDOW_RESIZABLE);
//    if (not window) {
//        return sdlFail(app);
//    }
//
//    // Create the SDL renderer.
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
//    if (not renderer) {
//        return sdlFail(app);
//    }
//
//    // Update application context.
//    app->sdlWindow = window;
//    app->sdlRenderer = renderer;
//
//
//    // DEBUG: print some information about the window
//    SDL_ShowWindow(window);
//    {
//        int width, height, bbwidth, bbheight;
//        SDL_GetWindowSize(window, &width, &height);
//        SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
//        SDL_Log("Window size: %ix%i", width, height);
//        SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
//        if (width != bbwidth) {
//            SDL_Log("This is a highdpi environment.");
//        }
//    }
//        
//    // Splash info.
//    std::cout << "[ CAT ] " << CCO_LWHITE << "Windows manager started" << CCO_RESET << "\n";
//    
//    // Everything fine.
//    return SDL_APP_CONTINUE;
//}
//
//
////______________________________________________________________________________
//SDL_AppResult sdlEvent(appContext* app)
//{
//    
//    // Retrieve user event queue.
//    SDL_Event event;
//    while (SDL_PollEvent(&event)) {
//        
//        // Quit.    
//        if (event.type == SDL_EVENT_QUIT) {
//            app->sdlQuit = SDL_APP_SUCCESS;
//            break;
//        }
//    
//        // Exit event queue safety check. This is an extra check to avoid what 
//        // it seems an SDL instability (as far as 3.0 version, at least on 
//        // Windows 11+) in cleaning the poll events queue, which results in 
//        // non exiting thw while loop even if there are no more events.
//        if (SDL_PollEvent(NULL) == SDL_FALSE) break;
//    }
//    
//    // Returns accordingly to eventual quit request.
//    if (app->sdlQuit == SDL_APP_CONTINUE)
//        return SDL_APP_CONTINUE;
//    else {
//        return SDL_APP_SUCCESS;
//    }
//}
//
//
////______________________________________________________________________________
//SDL_AppResult sdlIterate(appContext* app)
//{
//    
//    // draw a color
//    auto time = SDL_GetTicks() / 1000.f;
//    auto red = (std::sin(time) + 1) / 2.0 * 255;
//    auto green = (std::sin(time / 2) + 1) / 2.0 * 255;
//    auto blue = (std::sin(time) * 2 + 1) / 2.0 * 255;
//
//    SDL_SetRenderDrawColor(app->sdlRenderer, red, green, blue, SDL_ALPHA_OPAQUE);
//    SDL_RenderClear(app->sdlRenderer);
//    SDL_RenderPresent(app->sdlRenderer);
//
//    return app->sdlQuit;
//}
//
//
////______________________________________________________________________________
//void sdlQuit(appContext* app, SDL_AppResult result)
//{
//    if (app) {
//        SDL_DestroyRenderer(app->sdlRenderer);
//        SDL_DestroyWindow(app->sdlWindow);
//        delete app;
//    }
//
//    SDL_Log("Application quit successfully!");
//}
//
//
