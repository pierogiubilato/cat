//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER Window                    --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"window.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#ifndef catWindow_HPP
#define catWindow_HPP

// STL.
#include <vector>
#include <string>
#include <mutex>

// SFML system/windowing library.
//#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// GUI interface.
//#include "imgui-SFML.h"
//#include "imgui.h"

// Application.
//#include "context.hpp"


// #############################################################################
namespace cat {

    // Forward declaration.
    class context;

    //! This class contains all the server GUI elements. It is made singleton.
    class window {
            
    public:
        
        //! Ctor.
        window();

        //! Dtor.
        ~window();
        
        //! Deleted copy constructor.
        window (const window&) = delete;
        
        //! Deleted equal operator.
        window& operator=(const window&) = delete;

        //! Deleted move operator (technically not required, as there is 
        //! an already defined copy operator)
        window(window&&) = delete;

        //! Deleted move assign operator (technically not required, as there 
        //! is an already defined assign operator)
        window& operator=(window&&) = delete;

        //! Parse the window events.
        int event(cat::context&);
        
    private:
        
        // Mutex to ensure thread safety
        //std::mutex _mtx;

        //! Main GUI timing clock.
        sf::Clock _clock;

        //! Main GUI window.
        sf::RenderWindow _window;        

        //! Main window title.
        std::string _winTitle;
        
        //! Main window startup width.
        int _winWidth;
        
        //! Main window startup height.
        int _winHeight;
            
    };

   
    // #############################################################################
} // Close namespace "cat".


// End of overloading check.
#endif