//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER context                   --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"context.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"11 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Overloading check
#ifndef catContext_HPP
#define catContext_HPP

// STL.
#include <vector>
#include <string>

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

// Application.
#include "cmd.hpp"
#include "window.hpp"


// #############################################################################
namespace cat {

    //! Forward declarations for objects whose pointers will be stored
    //! in this context class..
    //class gui;

    
    //! This class contains all the running parameters and instances of 
    //! the various application elements, and it is shared through the 
    //! various steps of the (many) running processes.
    class context {
        
        public:

            //! Application running status.
            enum class runState : int {
                ongoing, 
                success, 
                failure
            };
    
            //! Command line.
            cat::cmd cmd;                   //<! Command line structure.

            //! Main application window.
            //sf::RenderWindow window;      //<! The main application window.
            //sf::Clock clock;              //<! The main application clock.
            cat::window _window;            //<! The main application window.

            //! SFML network server.
            sf::TcpListener server;         //<! Application server.

            //! Clients.
            std::vector<sf::TcpSocket*> client;  //<! Connected clients.
        
            //! Main GUI.
            //cat::gui _gui;  // THIS should belong to the main window.

            //! Diligent Core Graphics APIs.

            //! Running status.
            runState state;                 //!< Application running status.

            //! Ctor.
            context() : state(runState::ongoing) {}

            //! Dtor.
            ~context() {}
    };
    
    // #############################################################################
} // Close namespace "cat".

// Overload check.
#endif