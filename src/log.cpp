//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Logger stream utility					      --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [Date]	        "25 Jul 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/log.hpp"


// Standard library
using namespace std;

// Extra libraries
#include "../dependencies/include/rang.hpp"    // Console IO colors.


class log {
public:
    enum Level {
        ERROR = 0,
        WARNING = 1,
        INFO = 2,
        DEBUG = 3
    };

    Verbosity(Level level = INFO) : verbosityLevel(level) {}

    void setLevel(Level level) {
        verbosityLevel = level;
    }

    void error(const std::string& message) const {
        if (verbosityLevel >= ERROR) {
            std::cout << "[ERROR] " << message << std::endl;
        }
    }

    void warning(const std::string& message) const {
        if (verbosityLevel >= WARNING) {
            std::cout << "[WARNING] " << message << std::endl;
        }
    }

    void info(const std::string& message) const {
        if (verbosityLevel >= INFO) {
            std::cout << "[INFO] " << message << std::endl;
        }
    }

    void debug(const std::string& message) const {
        if (verbosityLevel >= DEBUG) {
            std::cout << "[DEBUG] " << message << std::endl;
        }
    }

private:
    Level verbosityLevel;
};

int main() {
    Verbosity logger(Verbosity::DEBUG);

    logger.error("This is an error message.");
    logger.warning("This is a warning message.");
    logger.info("This is an info message.");
    logger.debug("This is a debug message.");

    return 0;
}
