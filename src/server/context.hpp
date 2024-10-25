//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER context                   --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"context.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"23 Oct 2024"
// [Language]		"C++"
//______________________________________________________________________________


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
#include <vector>
#include <string>

// Application.
#include "cmd.hpp"


// #############################################################################
namespace cat {

    
    /*! This class contains all the running parameters of the application
        and it is passed through the various steps of the (many) running
        processes.
        Note that the class start the windows management system (SFML library)
        through the constructor itself, to ensure more c++ object management
        with respect to a pointer-based one.
    */
    class context {
        
    public:

        // Application running status.
        enum class runState : int { ongoing, success, failure };

        // General.
        std::string winTitle = "CAT";   //<! Main window title.
        int winWidth = 1280;            //<! Main window startup width.
        int winHeight = 720;            //<! Main window startup height.

        // Command line.
        cat::cmd cmd;                   //<! Command line structure.

        // SFML window.
        sf::RenderWindow window;        //<! The main application window.
        sf::Clock clock;                //<! The main application clock.

        // SFML network server.
        sf::TcpListener server;         //<! Application server.

        // Clients.
        //std::vector<sf::TcpSocket> client;  //<! Connected clients.
        
        // ImGUI User Interface

        // Diligent Core Graphics APIs.

        // Running status.
        runState state;                 //!< Application runnin gstatus.

        //! Ctor.
        context() : state(runState::ongoing) {}

        //! Dtor.
        ~context() {}
    };


    
    // #############################################################################
} // Close namespace "cat".