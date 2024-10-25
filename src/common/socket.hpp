//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application Tcp socket protocol definitions  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"socket.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"23 Oct 2024"
// [Language]		"C++"
//______________________________________________________________________________


// SFML Network.
#include <SFML/Network.hpp>

// STL.
#include <vector>
#include <string>

// Application.


// #############################################################################
namespace cat {


    /*! This enum class contains all the commands accepted for the network
        communication between the server and the client(s).
    */
    enum class tcp : uint32_t {
        open,
        close,
        error
    };



    // #############################################################################
} // Close namespace "cat".