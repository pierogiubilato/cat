//------------------------------------------------------------------------------
// CAT - C++ Analysis Toolkit - Application SERVER GUI main interface        --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gui.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Nov 2024"
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

// ImGui interface.
#include "imgui-SFML.h"
#include "imgui.h"

// Application.
#include "gui.hpp"
#include "console.hpp"



// -----------------------------------------------------------------------------
// --					    Static members initialization					  --
// -----------------------------------------------------------------------------

// Singleton reference.
//cat::gui* cat::gui::_instancePtr= nullptr;
//std::mutex cat::gui::_mtx;

// SFM main window.
//sf::RenderWindow cat::gui::_window;
//sf::Clock cat::gui::_clock;

// Main window appearance.
//std::string cat::gui::_winTitle = "CAT";
//int cat::gui::_winWidth = 1024;
//int cat::gui::_winHeight = 768;



//______________________________________________________________________________
//cat::gui* cat::gui::getInstance() {
cat::gui::gui() :
    _winWidth(800), _winHeight(600), _winTitle("CAT")

{
    //! Start a new (and the only one) instance of the class.

    // Check for any concurrent call.
    //if (_instancePtr == nullptr) {
    
        // Avoid concurrent instantiation through a scope-limited lock.
        //std::lock_guard<std::mutex> lock(_mtx);
    
        // Instantiate the class if it has not been done yet.
        //if (_instancePtr == nullptr) {

            // New class.
            //_instancePtr = new gui();
                        
            // Starts the windows and event management.
            //sf::Window _window(sf::VideoMode(_winWidth, _winHeight), _winTitle);
            _window.create(sf::VideoMode(_winWidth, _winHeight), _winTitle);

            // Frame rate limit, to avoid system overload when not necessary.
            _window.setFramerateLimit(60);
            
            // Create the GUI interface.
            ImGui::SFML::Init(_window);
        //}
    //}

    // Return the class object.
    //return _instancePtr;
}


//______________________________________________________________________________
cat::gui::~gui()
{
    // CLose main SFML window.
//    _window.close();

    // Close ImGui.
//    ImGui::SFML::Shutdown();
}



//______________________________________________________________________________
int cat::gui::event(cat::context& ctx)
{
    //! Retrieves and parse events from the user and the system
    

    //// Retrieve events from the user/system.
    //sf::Event event;

    //// Retrieve all the queued events from the user/system.
    //while (_window.pollEvent(event)) {

    //    // First, pass the event to the GUI.
    //    // ---------------------------------
    //    ImGui::SFML::ProcessEvent(_window, event);


    //    // Parse the managed events.
    //    // -------------------------



    //    // Resize.

    //    // Quit.
    //    if (event.type == sf::Event::Closed) {
    //        ctx.state = cat::context::runState::success;
    //    }
    //}

    // Everything fine.
    return 0;
}


//______________________________________________________________________________
int cat::gui::draw(cat::context& ctx)
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