//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application CLIENT entry point               --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"client.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"08 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________







// Overloading check
#ifndef catClient_HPP
#define catClient_HPP

// Application.
#include "cmd.hpp"
#include "console.hpp"

// #############################################################################
namespace cat {


    /*! This class contains the CAT Client core interface. It is the user entry
    *   point and interface to the whole CAT application. While as many clients
    *   as possible may be instantiated within a single application, generally
    *   one application connect to the CAT Server through a single client.
    */
    class client {

    public:

        
        // Connection status.
        enum class status : int {
            connected,
            closed,
            error
        };
               
        
        //! Empty ctor.
        //! \brief Default ctor. Set the server address to 'localhost', the server 
        //!     listening port to '2000', and the verbosity level to 'message'.
        //! \return nothing.
        client();
        
        //! Command line constructor.
        //! \brief Instantiates the client parsing the command line. This will
        //!     automatically search for the '--address [server address]' and 
        //!     '--port [server port]' options, to change the default values
        //!     of 'localhost' (address) and '2000' (port). The command line
        //!     constructor will also look for the '--verb {critical, error,
        //!     , warning, message, info, debug, all}' options to set
        //!     the console verbosity.
        //! \param argc is an integer stating the length of the arguments count.
        //! \param argv[] is the arguments list itself.
        //! \return nothing.
        client(int argc, char* argv[]);

        //! Dtor.
        ~client();

        //! Connects to the server.
        //! \brief Connects the client to the CAT server. Uses the default
        //!     address and port values, which are predefined at startup or
        //!     defined by the command line.
        //! \return To DO.
        status connect();

        //! Connects to the server.
        //! \brief Connects the client to the CAT server. Uses the specified
        //!     'address' (in the form "###.###.###.###" or any resolved name
        //!     like "localhost") and port (e.g. 2000).
        //! \param address is a string containing the server address in a string 
        //!     format of the type "###.###.###.###", or any resolvable name
        //!     like "localhost" (the default value).
        //! \param port is a short unsigned integer defining the server listening 
        //!     port, e.g. "2000".
        //! \return To DO.
        status connect(const std::string& address, const unsigned short& port);

    private:

        // Application and connection status members.
        std::string _srvAddress;
        unsigned short _srvPort;
        unsigned int _timeout = 5000;
        cat::cmd _command;

        // Support
        
        //! Defines the command line parameters and options.
        //! \brief Pre-defines all the command line parameters and options, 
        //!     including default values.
        //! \return 0 on success, error code otherwise.
        int cmdSet();

        //! Parse the command line parameters and options.
        //! \brief Parse the command line looking for options and arguments defined 
        //!     in the cmdSet() function, assigning default values to missing
        //!     parameters.
        //! \return 0 on success, error code otherwise.
        int cmdParse(int argc, char* argv[]);

    };



// #############################################################################
} // Close namespace "cat".





// End of overloading check.
#endif
