#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        ImGui::ShowDemoWindow();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}




////#define SDL_MAIN_USE_CALLBACKS 1
//
//// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
//#define OOF_IMPL
//#include<oof.h>
//
//// SDL windows/events management.
//#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
//
//// SDL Network.
//#include <SDL3_net/SDL_net.h>
//
//// STL.
//#include <cmath>
//#include <iostream>
//
//// Application.
//#include "srvGlobal.hpp"
//
//
///* This structure contains all the running parameters of the application
//   and it is passed through the various steps of the running process
//*/
//class appContext {
//    
//    // The class is more a container for fundamental application properties.
//    public:
//
//    
//    // Diligent Engine Graphics API.
//    
//    // SDL System Interface.
//    SDL_Window* sdlWindow;
//    SDL_Renderer* sdlRenderer;
//    SDL_AppResult sdlQuit = SDL_APP_CONTINUE;
//
//    // SDL Network.
//
//
//    // ImGUI User Interface
//
//
//    // Special members.
//    appContext() : sdlWindow(NULL), sdlRenderer(NULL), sdlQuit(SDL_APP_CONTINUE) {}
//    ~appContext() {}
//};
//
//// Main proprietary functions.
//int appInit(appContext*);
//int srvInit(appContext*);
//int appSplash(appContext*);
//int srvListen(appContext*);
//int evnListen(appContext*);
//int appLoop(appContext*);
//int srvClose(appContext*);
//int appClose(appContext*);
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
////______________________________________________________________________________
//int appInit (appContext* app)
//{
//    /*! Initialize the application, including the windows management,
//        event management, graphics API libraries, network libraries.
//    */
//
//    // Windows and event management.
//    sdlInit(app);
//
//    // Graphics APIs management.
//
//    // Everything fine.
//    return 0;
//}
//
//
////______________________________________________________________________________
//int srvInit(appContext* app)
//{
//    /*! Initialize the server, and start listening.
//    */
//
//    // Initialize the SDL_net library.
//    if (SDLNet_Init()) {
//        app->sdlQuit = SDL_APP_CONTINUE;
//    } else {
//        return sdlFail(app);
//        app->sdlQuit = SDL_APP_FAILURE;
//    };
//
//    // Splash info.
//    std::cout << "[ CAT ] " << CCO_LWHITE << "Server started" << CCO_RESET << "\n";
//
//    // Everything fine.
//    return SDL_APP_CONTINUE;
//}
//
//
////______________________________________________________________________________
//int appSplash(appContext* app)
//{
//    /*! Show splash credits.
//    */
//    
//    // Quick OOF definitions.
//    //#define CCO_LBLUE oof::fg_color({0, 0, 255})
//
//
//    // CAT.
//    std::cout << "\n\n";
//    std::cout << "+" << std::string(42, '-') << "+\n";
//    std::cout << "|" << std::string(42, ' ') << "|\n";
//    std::cout 
//        << "|    "
//        << CCO_LAVIO << CCO_BOLD << "C" << CCO_RESET << "++ "
//        << CCO_LAVIO << CCO_BOLD << "A" << CCO_RESET << "cquisiiton & "
//        << CCO_LAVIO << CCO_BOLD << "A" << CCO_RESET << "nalysis "
//        << CCO_LAVIO << CCO_BOLD << "T" << CCO_RESET << "oolset"
//        "    |\n";
//    
//    // Copyright.
//    std::cout << "|" << std::string(42, ' ') << "|\n";
//    std::cout << "|" 
//        << "        (C)" 
//        << CCO_LWHITE << " Padova University " 
//        << CCO_RESET << "2024        " << "|\n";
//
//    // Closure.    
//    std::cout << "|" << std::string(42, ' ') << "|\n";
//    std::cout << "+" << std::string(42, '-') << "+\n";
//    
//    // Libraries.
//    std::cout << "\nLibraries\n";
//    std::cout << "Console..................: "
//        << CCO_LWHITE << "Off           " << CCO_RESET << "("
//        << CCO_ULINE << CCO_CYAN << "https://github.com/s9w/oof"
//        << CCO_RESET << ")\n";
//    std::cout << "Windows management.......: "
//        << CCO_LWHITE << "SDL 3.0       " << CCO_RESET << "("
//        << CCO_ULINE << CCO_CYAN << "https://github.com/libsdl-org/SDL"
//        << CCO_RESET << ")\n";
//    std::cout << "Network sockets..........: "
//        << CCO_LWHITE << "SDL_Net 3.0   " << CCO_RESET << "("
//        << CCO_ULINE << CCO_CYAN << "https://github.com/libsdl-org/SDL_net"
//        << CCO_RESET << ")\n";
//    std::cout << "Graphics User Interface..: "
//        << CCO_LWHITE << "Dear ImGui    " << CCO_RESET << "("
//        << CCO_ULINE << CCO_CYAN << "https://github.com/ocornut/imgui"
//        << CCO_RESET << ")\n";
//    std::cout << "3D APIs abstraction......: "
//        << CCO_LWHITE << "Diligent Core " << CCO_RESET << "("
//        << CCO_ULINE << CCO_CYAN << "https://github.com/DiligentGraphics/DiligentCore"
//        << CCO_RESET << ")\n";
//        
//    // Everything fine.
//    return 0;
//}
//
//
////______________________________________________________________________________
//int srvListen(appContext* app)
//{
//    /*! Collect latest connection request, and parse new I/O data streams from 
//        clients arrived since the last check.
//    */
//
//
//    // Everything fine.
//    return 0;
//}
//
//
////______________________________________________________________________________
//int appLoop(appContext* app)
//{
//    /*! This is the main application loop, which handles events from the user,
//        calls from/to the clients, and display the outputs.
//    */
//
//
//    // Everything fine.
//    return 0;
//}
//
//
////______________________________________________________________________________
//int srvClose(appContext* app)
//{
//    /*! Stop the server from listening, and clear all the sockets to/from the 
//        connected clients.
//    */
//
//
//
//    // Everything fine.
//    return 0;
//}
//
//
////______________________________________________________________________________
//int appClose(appContext* app)
//{
//    /*! Stop the application, close the windows/event managers, shut down the
//        graphics APIs.
//    */
//
//
//    // Everything fine.
//    return 0;
//}
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
