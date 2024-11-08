//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Logging utility                              --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"log.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"31 Oct 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Overloading check
#ifndef console_HPP
#define console_HPP

// Standard library
#include <string>
#include <deque>
#include <iostream>
#include <ostream>
#include <sstream>

// Console library.
#include<oof.h>


// Console output shortcut (use OOF library syntax)
// -------------------------------------------------

//// Basic colors.
//#define CAT_CO_BLACK	oof::fg_color({ 0,   0,   0 })
//#define CAT_CO_LBLACK	oof::fg_color({ 64,  64,  64 })
//#define CAT_CO_RED		oof::fg_color({ 128, 0,   0 })
//#define CAT_CO_LRED		oof::fg_color({ 255, 0,	  255 })
//#define CAT_CO_GREEN	oof::fg_color({ 0,	 128, 0 })
//#define CAT_CO_LGREEN	oof::fg_color({ 0,	 255, 0 })
//#define CAT_CO_BLUE		oof::fg_color({ 0,	 0,	  128 })
//#define CAT_CO_LBLUE	oof::fg_color({ 0,	 0,	  255 })
//#define CAT_CO_LBLUE	oof::fg_color({ 0,	 0,	  255 })
//#define CAT_CO_YELLOW	oof::fg_color({ 128, 128, 0 })
//#define CAT_CO_LYELLOW	oof::fg_color({ 255, 255, 0 })
//#define CAT_CO_CYAN		oof::fg_color({ 0,   128, 128 })
//#define CAT_CO_LCYAN	oof::fg_color({ 0,   255, 255 })
//#define CAT_CO_PURPLE	oof::fg_color({ 128, 0,   128 })
//#define CAT_CO_LPURPLE	of::fg_color({ 255, 0,   255 })
//#define CAT_CO_WHITE	oof::fg_color({ 128, 128, 128 })
//#define CAT_CO_LWHITE	oof::fg_color({ 255, 255, 255 })
//
//// Advanced colors.
//#define CAT_CO_AVIO		oof::fg_color({ 0,   64,  128 })
//#define CAT_CO_LAVIO	oof::fg_color({ 0,   128, 255 })
//#define CAT_CO_FUCSIA	oof::fg_color({ 128, 0,   64 })
//#define CAT_CO_LFUCSIA	oof::fg_color({ 255, 0,   128 })
//#define CAT_CO_GRASS	oof::fg_color({ 64,  128, 0 })
//#define CAT_CO_LGRASS	oof::fg_color({ 128, 255, 0 })
//
//// Basic formatting.
//#define CAT_CO_RESET	oof::reset_formatting()
//#define CAT_CO_ULINE	oof::underline(true)
//#define CAT_CO_BOLD		oof::bold(true)
//
//// Standard messages formatting.
//#define CAT_CO_CRITICAL		CAT_CO_LPURPLE << CAT_CO_BOLD
//#define CAT_CO_ERROR		CAT_CO_LRED << CAT_CO_BOLD
//#define CAT_CO_WARNING		CAT_CO_LYELLOW
//#define CAT_CO_IMPORTANT	CAT_CO_LWHITE << CAT_CO_ULINE
//#define CAT_CO_INFO			CAT_CO_LWHITE
//#define CAT_CO_DEBUG		CAT_CO_WHITE


// #############################################################################
namespace cat {


	// #########################################################################
	namespace cl {
		
		// Verbosity
		//----------------------------------------------------------------------
		enum class verbosity : int {
			critical = 0,
			error = 1,
			warning = 2,
			section = 3,
			message = 4,
			info = 5,
			debug = 6,
			all = 99
		};

	// #########################################################################
	} // Enf of "cl" namespace.

// #############################################################################
} // Enf of "cat" namespace.


// Declare overloaded ostream operator << for 'cat::cl::verbosity' enum class.
std::ostream& operator<<(std::ostream& os, const cat::cl::verbosity& v);

// #############################################################################
namespace cat {

//______________________________________________________________________________
class console
{

	public:

		//! Instantiate a console class.
		///
		/// \brief Instantiate a console object, which embeds the 'verbosity'
		///		property to selectively display messages, and a set of format
		///		methods which allow modifying output colors and appearance.
		///	\param v sets the output verbosity. It uses the 'verbosity' class
		///		enum to choose among several possible levels.
		///	\return nothing
		console(const cl::verbosity& v = cl::verbosity::message) : _verbosity(v) {};
		
		//! Destructor. No particular duties.
		~console() {};

		// Methods - support.
		//void verbSet(const verb&);		
		//verb verbGet() const;					
		//bool seen(const verb&) const;
		//void print(const std::ostream&, const verb&) const;

		//! Set the verbosity level.
		///
		/// \brief Set the verbosity level, from a 'cat::cl::verbosity::' enum.
		///	\param v the verbosity level.
		///	\return nothing.
		bool verb(const cl::verbosity& v) { _verbosity = v; }
		

		//! Set the verbosity level.
		///
		/// \brief Set the verbosity level, interpreting a string. If the string
		///		does not match any predefined token, set the verbosity to the default
		///		'cat::cl::verbosity::message' level.
		///	\param str is the string defining the verbosity level. It can be one
		///		of the recognized tokens: {"critical", "error", "warning", "message", 
		///		"info", "debug", "all"}.
		///	\return nothing.
		void verb(const std::string& str) {
			if (str == "critical")		_verbosity = cl::verbosity::critical;
			else if (str== "error")		_verbosity = cl::verbosity::error;
			else if (str== "warning")	_verbosity = cl::verbosity::warning;
			else if (str == "message")	_verbosity = cl::verbosity::message;
			else if (str == "info")		_verbosity = cl::verbosity::info;
			else if (str == "default")	_verbosity = cl::verbosity::debug;
			else if (str == "all")		_verbosity = cl::verbosity::all;
			else _verbosity = cl::verbosity::message;
		}

		//! Get the verbosity level.
		///
		/// \brief Returns the verbosity level.
		///	\param none.
		///	\return the current verbosity level.
		cl::verbosity verb() const { return _verbosity; }

		//! Verify wether a verbosity level is met or not.
		///
		/// \brief Check whether the provided verbosity level is currently met
		///		by the one set in the class.
		///	\param v the verbosity level to check.
		///	\return true if the verbosity level guarantees visibility, false 
		///		otherwise.
		bool show(const cl::verbosity& v) const { return (v <= _verbosity); }

		// Basic ostream operator overload. In this base version, do nothing.
		friend std::ostream& operator<<(std::ostream& os, const cat::console& c)
		{
			return (os);
		}

	protected:

		// No protected at the moment

	private:

		// Current verbosity level.
		cl::verbosity _verbosity;

};




// #############################################################################
namespace cl {

/// Here it is a set of specialized console classes, which purpose is to help 
/// in an uniform manner across the application formatting the output. They are
/// all wrapped within the "cat::cl" namespace, so the user will easily have 
/// them automatically sorted when using any modern intellisense system.

// Appearance
//------------------------------------------------------------------------------

//______________________________________________________________________________
class reset : console
{
	// Basic ostream operator overload. 
	public:
	friend std::ostream& operator<<(std::ostream& os, const cat::cl::reset& c) {
		return (os << oof::reset_formatting());
	}
};

//______________________________________________________________________________
class bold : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::bold& c) {
		return (os << oof::bold(true));
	}
};

//______________________________________________________________________________
class uline : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::uline& c) {
		return (os << oof::underline(true));
	}
};


// Standard foreground colors
//------------------------------------------------------------------------------

//______________________________________________________________________________
class black : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::black& c) {
		return (os << oof::fg_color({ 0, 0, 0 }));
	}
};

//______________________________________________________________________________
class lblack : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lblack& c) {
		return (os << oof::fg_color({ 64, 64, 64 }));
	}
};

//______________________________________________________________________________
class red : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::red& c) {
		return (os << oof::fg_color({ 128, 0, 0 }));
	}
};

//______________________________________________________________________________
class lred : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lred& c) {
		return (os << oof::fg_color({ 255, 0, 64 }));
	}
};

//______________________________________________________________________________
class green : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::green& c) {
		return (os << oof::fg_color({ 0, 128, 0 }));
	}
};

//______________________________________________________________________________
class lgreen : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lgreen& c) {
		return (os << oof::fg_color({ 0, 255, 0 }));
	}
};

//______________________________________________________________________________
class blue : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::blue& c) {
		return (os << oof::fg_color({ 0, 0, 128 }));
	}
};

//______________________________________________________________________________
class lblue : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lblue& c) {
		return (os << oof::fg_color({ 0, 0, 255 }));
	}
};

//______________________________________________________________________________
class yellow : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::yellow& c) {
		return (os << oof::fg_color({ 128, 128, 0 }));
	}
};

//______________________________________________________________________________
class lyellow : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lyellow& c) {
		return (os << oof::fg_color({ 255, 255, 0 }));
	}
};

//______________________________________________________________________________
class cyan : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::cyan& c) {
		return (os << oof::fg_color({ 0, 128, 128 }));
	}
};

//______________________________________________________________________________
class lcyan : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lcyan& c) {
		return (os << oof::fg_color({ 0, 255, 255 }));
	}
};

//______________________________________________________________________________
class purple : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::purple& c) {
		return (os << oof::fg_color({ 128, 0, 128 }));
	}
};

//______________________________________________________________________________
class lpurple : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lpurple& c) {
		return (os << oof::fg_color({ 255, 0, 255 }));
	}
};

//______________________________________________________________________________
class avio : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::avio& c) {
		return (os << oof::fg_color({ 0, 64, 128 }));
	}
};

//______________________________________________________________________________
class lavio : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lavio& c) {
		return (os << oof::fg_color({ 0, 128, 255 }));
	}
};

//______________________________________________________________________________
class fucsia : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::fucsia& c) {
		return (os << oof::fg_color({ 0, 64, 128 }));
	}
};

//______________________________________________________________________________
class lfucsia : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lfucsia& c) {
		return (os << oof::fg_color({ 128, 0, 64 }));
	}
};


//______________________________________________________________________________
class grass : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::grass& c) {
		return (os << oof::fg_color({ 255, 0, 128 }));
	}
};

//______________________________________________________________________________
class lgrass : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lgrass& c) {
		return (os << oof::fg_color({ 128, 0, 64 }));
	}
};

//______________________________________________________________________________
class white : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::white& c) {
		return (os << oof::fg_color({ 255, 0, 128 }));
	}
};

//______________________________________________________________________________
class lwhite : console {
	public: friend std::ostream& operator<<(std::ostream& os, const cat::cl::lwhite& c) {
		return (os << oof::fg_color({ 255, 255, 255 }));
	}
};


// Standard styles
//------------------------------------------------------------------------------

//______________________________________________________________________________
class critical : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::critical& c) {
		return (os << cl::lpurple() << cl::bold());
	}
};

//______________________________________________________________________________
class error : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::error& c) {
		return (os << cl::lred());
	}
};

//______________________________________________________________________________
class warning : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::warning& c) {
		return (os << cl::yellow());
	}
};

//______________________________________________________________________________
class message : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::message& c) {
		return (os << cl::lwhite() << cl::uline());
	}
};

//______________________________________________________________________________
class info : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::info& c) {
		return (os << cl::white());
	}
};

//______________________________________________________________________________
class debug : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::debug& c) {
		return (os << cl::white());
	}
};

//______________________________________________________________________________
class link : console {
	public:	friend std::ostream& operator<<(std::ostream& os, const cat::cl::link& c) {
		return (os << cl::lavio() << cl::uline());
	}
};





// #############################################################################
}  // Close namespace "cl"


// #############################################################################
}  // Close namespace "cat"


// Overloading check
#endif