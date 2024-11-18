//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER GUI                       --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gui.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"13 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#ifndef catGui_HPP
#define catGui_HPP

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
    class gui {
            
    public:
        
        //! Get singleton instance (thread safe).
        //! \brief instantiate the only allowed one instance of the class. The
        //!     function is thread-safe, i.e. it will check for any concurrent
        //!     call all return a single instantiation.
        //! \return a cat::gui& handle to the instantiated class.
        //static gui* getInstance();
        //{
            //if (_instancePtr == nullptr) {
            //    
            //    // Avoid concurrent instantiation through a scope-limited lock.
            //    std::lock_guard<std::mutex> lock(_mtx);
            //    
            //    // Instantiate the class.
            //    if (_instancePtr == nullptr) {
            //        _instancePtr = new gui();
            //    }
            //}

            //// Return the class object.
            //return *_instancePtr;
        //}
        gui();

        //! Dtor.
        ~gui();
        
        //! Deleted copy constructor.
        gui(const gui&) = delete;
        
        //! Deleted equal operator.
        gui& operator=(const gui&) = delete;

        //! Deleted move operator (technically not required, as there is 
        //! an already defined copy operator)
        gui(gui&&) = delete;

        //! Deleted move assign operator (technically not required, as there 
        //! is an already defined assign operator)
        gui& operator=(gui&&) = delete;

        //!
        int static event(cat::context&);

        //!
        int static draw(cat::context&);


    private:
        
        //! Private constructor.
        //gui() {}

        // Static pointer to the Singleton instance
        gui* _instancePtr;

        // Mutex to ensure thread safety
        std::mutex _mtx;

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