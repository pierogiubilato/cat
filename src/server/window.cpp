//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER GUI main interface        --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gui.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"12 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________

// STL.
#include <cmath>
#include <iostream>
#include <string>

// SFML system/windowing library.
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// ImGui interface.
#include "imgui-SFML.h"
#include "imgui.h"

// Application - Shared with end User.
#include "console.hpp"

// Application - Server only.
#include "window.hpp"
#include "context.hpp"


//______________________________________________________________________________
cat::window::window() : _winWidth(800), _winHeight(600), _winTitle("CAT")
{
    //! Start a new (and the only one) instance of the class.

    // Starts the windows and event management.
    //sf::Window _window(sf::VideoMode(_winWidth, _winHeight), _winTitle);
    _window.create(sf::VideoMode(_winWidth, _winHeight), _winTitle);

    // Frame rate limit, to avoid system overload when not necessary.
    _window.setFramerateLimit(60);

    // Create the GUI interface.
    ImGui::SFML::Init(_window);
}


//______________________________________________________________________________
cat::window::~window()
{
    // CLose main SFML window.
    _window.close();

    // Close ImGui.
    //    ImGui::SFML::Shutdown();
}


//______________________________________________________________________________
int cat::window::event(cat::context& ctx)
{
    //! Retrieves and parse events from the user and the system
    

    // Retrieve events from the user/system.
    sf::Event event;

    // Retrieve all the queued events from the user/system.
    while (_window.pollEvent(event)) {

        // First, pass the event to the GUI.
        // ---------------------------------
        //ImGui::SFML::ProcessEvent(_window, event);
        

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

/*
//______________________________________________________________________________
int cat::window::draw(cat::context& ctx)
{
    //! Draw the scene(s) and other interface 3D world elements.
    
    //// Update the GUI.
    //ImGui::SFML::Update(_window, _clock.restart());

    //// ImGui cycle.
    //ImGui::Begin("Hello, world!");
    //ImGui::Button("Look at this pretty button");
    //ImGui::End();

    //// ImGui demo.
    //ImGui::ShowDemoWindow();

    //// Scene drawing.

    //_window.clear();
    ////app.window.draw(shape);
    //ImGui::SFML::Render(_window);
    //_window.display();

    // Everything fine.
    return 0;
}
*/