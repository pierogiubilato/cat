//#define SDL_MAIN_USE_CALLBACKS 1

// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
#define OOF_IMPL
#include<oof.h>

// SDL windows/events management.
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// STL.
#include <cmath>
#include <iostream>

/* This structure contains all the running parameters of the application
   and it is passed through the various steps of the running process
*/
class appContext {
    
    // The class is more a container for fundamental application properties.
    public:

    
    // Diligent Engine Graphics API.
    
    // SDL System Interface.
    SDL_Window* sdlWindow;
    SDL_Renderer* sdlRenderer;
    SDL_AppResult sdlQuit = SDL_APP_CONTINUE;

    // SDL Network.


    // ImGUI User Interface


    // Special members.
    appContext() : sdlWindow(NULL), sdlRenderer(NULL), sdlQuit(SDL_APP_CONTINUE) {}
    ~appContext() {}
};

// Main proprietary functions.
int appInit(appContext*);
int srvInit(appContext*);
int appSplash(appContext*);
int srvListen(appContext*);
int evnListen(appContext*);
int appLoop(appContext*);
int srvClose(appContext*);
int appClose(appContext*);

// SDL functions
SDL_AppResult sdlInit(appContext*);
SDL_AppResult sdlEvent(appContext*);
SDL_AppResult sdlIterate(appContext*);
SDL_AppResult sdlClose(appContext*);
SDL_AppResult sdlFail();


//______________________________________________________________________________
int main(int argc, char* argv[])
{
    /* CAT Server entry point. The main entry point simply executes initialization
       then hands over control to the 'srvLoop' main application loop.
    */

    // Set up the application context data structure.
    appContext* app = new appContext;

    // Init App.
    appInit(app);

    // Init Server.
    srvInit(app);

    // Splash.
    appSplash(app);

    // Application main loop.
    while (app->sdlQuit == SDL_APP_CONTINUE) {

        // Parse window interaction events.
        //sdlEvent(app);

        // Retrieve user event queue.
        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            // Decide what to do with this event.
            std::cout << "Found event:" << event.type << "\n";
            SDL_Delay(100);
            ///SDL_

            // Quit.    
            if (event.type == SDL_EVENT_QUIT) {
                app->sdlQuit = SDL_APP_SUCCESS;
            }
        }


        // Listen/answers to clients.
        srvListen(app);

        // Update the user interface.
        //

        // Update the scene(s) drawing.
        sdlIterate(app);
    }

    // Bye Bye.
    appClose(app);

    // Check closure.
    if (app->sdlQuit == SDL_APP_SUCCESS) {
        std::cout << "CAT server execution terminated with no error" << std::endl;
        return 0;
    } else {
        std::cout << "CAT server execution terminated with ERROR" << std::endl;
        return -1;
    }
}


//______________________________________________________________________________
int appInit (appContext* app)
{
    /*! Initialize the application, including the windows management,
        event management, graphics API libraries, network libraries.
    */

    // Windows and event management.
    sdlInit(app);

    // Graphics APIs management.

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvInit(appContext* app)
{
    /*! Initialize the server, and start listening.
    */

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appSplash(appContext* app)
{
    /*! Show splash credits.
    */
    
    // CAT.
    std::cout << "+" << std::string(25, char(150)) << "+\n";
    std::cout << "|" << std::string(25, ' ') << "|\n";
    std::cout
        << "|    "
        << oof::fg_color({ 0, 0, 255 }) << "C" << oof::reset_formatting() << "++ "
        << oof::fg_color({ 0, 0, 255 }) << "A" << oof::reset_formatting() << "cquisiiton & "
        << oof::fg_color({ 0, 0, 255 }) << "A" << oof::reset_formatting() << "nalysis "
        << oof::fg_color({ 0, 0, 255 }) << "T" << oof::reset_formatting() << "oolset"
        << "    |\n";
    std::cout << "|" << std::string(25, ' ') << "|\n";
    std::cout << "+" << std::string(25, char(127)) << "+\n";
    
    // A
    
    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvListen(appContext* app)
{
    /*! Collect latest connection request, and parse new I/O data streams from 
        clients arrived since the last check.
    */


    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appLoop(appContext* app)
{
    /*! This is the main application loop, which handles events from the user,
        calls from/to the clients, and display the outputs.
    */


    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int srvClose(appContext* app)
{
    /*! Stop the server from listening, and clear all the sockets to/from the 
        connected clients.
    */



    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int appClose(appContext* app)
{
    /*! Stop the application, close the windows/event managers, shut down the
        graphics APIs.
    */


    // Everything fine.
    return 0;
}




//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================

//______________________________________________________________________________

SDL_AppResult sdlFail()
{
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
    return SDL_APP_FAILURE;
}


//______________________________________________________________________________
SDL_AppResult sdlInit(appContext* app)
{
    
    // init the library, here we make a window so we only need the Video capabilities.
    if (not SDL_Init(SDL_INIT_VIDEO)) {
        app->sdlQuit = SDL_APP_FAILURE;
        return sdlFail();
    }

    // Create the main window.
    SDL_Window* window = SDL_CreateWindow("Window", 352, 430, SDL_WINDOW_RESIZABLE);
    if (not window) {
        return sdlFail();
    }

    // Create the SDL renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (not renderer) {
        return sdlFail();
    }

    // Update application context.
    app->sdlWindow = window;
    app->sdlRenderer = renderer;


    // DEBUG: print some information about the window
    SDL_ShowWindow(window);
    {
        int width, height, bbwidth, bbheight;
        SDL_GetWindowSize(window, &width, &height);
        SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
        SDL_Log("Window size: %ix%i", width, height);
        SDL_Log("Backbuffer size: %ix%i", bbwidth, bbheight);
        if (width != bbwidth) {
            SDL_Log("This is a highdpi environment.");
        }
    }
        
    SDL_Log("Application started successfully!");
    
    // Everything fine.
    return SDL_APP_CONTINUE;
}


//______________________________________________________________________________
SDL_AppResult sdlEvent(appContext* app)
{
    
    // Retrieve user event queue.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        
        // Decide what to do with this event.
        std::cout << "Found event:" << event.type << "\n";
        //SDL_Delay(100);
        ///SDL_

        // Quit.    
        if (event.type == SDL_EVENT_QUIT) {
            app->sdlQuit = SDL_APP_SUCCESS;
        }
    }
    std::cout << "--> End event look\n";
    return SDL_APP_CONTINUE;
}


//______________________________________________________________________________
SDL_AppResult sdlIterate(appContext* app)
{
    
    // draw a color
    auto time = SDL_GetTicks() / 1000.f;
    auto red = (std::sin(time) + 1) / 2.0 * 255;
    auto green = (std::sin(time / 2) + 1) / 2.0 * 255;
    auto blue = (std::sin(time) * 2 + 1) / 2.0 * 255;

    SDL_SetRenderDrawColor(app->sdlRenderer, red, green, blue, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->sdlRenderer);
    SDL_RenderPresent(app->sdlRenderer);

    return app->sdlQuit;
}


//______________________________________________________________________________
void sdlQuit(appContext* app, SDL_AppResult result)
{
    if (app) {
        SDL_DestroyRenderer(app->sdlRenderer);
        SDL_DestroyWindow(app->sdlWindow);
        delete app;
    }

    SDL_Log("Application quit successfully!");
}


