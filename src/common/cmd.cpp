//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Command line tiny parser                     --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"cmd.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [Date]	        "01 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "cmd.hpp"

// Standard library.
#include <iostream>
//#include <sstream>

// Use standard namespace:
//using namespace std;


// #############################################################################
namespace cat {

// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
cmd::cmd()
{
    /*! */

}

//______________________________________________________________________________
cmd::~cmd()
{
    /*! Dtor. Nothing really to do.
     */
}


// *****************************************************************************
// **                            Private members                              **
// *****************************************************************************


// *****************************************************************************
// **                           Operators overload                            **
// *****************************************************************************


// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************


//______________________________________________________________________________
void cmd::addArg(const std::string& name, const std::string& description, 
                 const bool& required)
{
	/* Add an argument to the recognized argument list. */
    _args[name] = { false, description, "", required};
}


//______________________________________________________________________________
void cmd::addOpt(const std::string& name, const std::string& description,
                 const bool& required, const bool& requiresValue)
{
	/**/
    _options[name] = { false, description, "", required, requiresValue };
}


//______________________________________________________________________________
bool cmd::isOptionPresent(const std::string& name) const
{
    if (_options.find(name) != _options.end()) {
        return _options.at(name).present;
    }
    return false;
}

// ______________________________________________________________________________
std::string cmd::getOptionValue(const std::string& name, const std::string& defaultValue = "") const
{
    if (_options.find(name) != _options.end()) {
        return _options.at(name).present ? _options.at(name).value : defaultValue;
    }
    return defaultValue;
}

//______________________________________________________________________________
std::string cmd::getArgumentValue(const std::string& name) const {
    if (_args.find(name) != _args.end()) {
        return _args.at(name).value;
    }
    return "";
}


//______________________________________________________________________________
void cmd::printHelp() const 
{
	/* Quick list of available arguments and options. */
    std::cout << "Usage: [options] [arguments]" << std::endl;
	
    // Show options.
    std::cout << "Options:" << std::endl;
	for (const auto& opt : _options) {
        std::cout << "  --" << opt.first << "\t" << opt.second.description;
        if (opt.second.requiresValue) std::cout << " <value>";
        std::cout << std::endl;
	}
	
    // Show arguments.
    std::cout << "Arguments:" << std::endl;
	for (const auto& arg : _args) {
        std::cout << "  " << arg.first << "\t" << arg.second.description;
        if (!arg.second.required) std::cout << " (optional)";
        std::cout << std::endl;
	}
}


//______________________________________________________________________________
int cmd::parse(int argc, char* argv[])
{
    /* Perform command line arguments parsing */
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // Long option.
        if (arg.substr(0, 2) == "--") {
            size_t equalPos = arg.find('=');
            std::string option = arg.substr(2, equalPos - 2);
            std::string value;

            if (equalPos != std::string::npos) {
                value = arg.substr(equalPos + 1);
            } else if (_options[option].requiresValue && i + 1 < argc) {
                value = argv[++i];
            }

            if (_options.find(option) != _options.end()) {
                _options[option].present = true;
                _options[option].value = value;
            
            // Unknown option.
            } else {
                std::cerr << "Unknown option: " << option << std::endl;
                printHelp();
                return -1;
            }
        
        // Argument.
        } else {
            bool matched = false;
            for (auto& argPair : _args) {
                if (!argPair.second.present) {
                    argPair.second.present = true;
                    argPair.second.value = arg;
                    matched = true;
                    break;
                }
            }
            
            // Invalid argument.
            if (!matched) {
                std::cerr << "Unexpected argument: " << arg << std::endl;
                printHelp();
                return -1;
            }
        }
    }

    // Highlights missing (required) arguments.
    for (const auto& argPair : _args) {
        if (argPair.second.required && !argPair.second.present) {
            std::cerr << "Missing required argument: " << argPair.first << std::endl;
            printHelp();
            return -1;
        }
    }

    // Highlights missing (required) options.
    for (const auto& optPair : _options) {
        if (optPair.second.required && !optPair.second.present) {
            std::cerr << "Missing required option: " << optPair.first << std::endl;
            printHelp();
            return -1;
        }
    }

    // Everything fine!
    return 0;
}

// #############################################################################
} // Closing namespace 'cat'




