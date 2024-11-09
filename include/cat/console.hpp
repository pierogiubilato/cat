﻿//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Console output utility                       --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"console.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.8"
// [Modified by]	"Piero Giubilato"
// [cat]			"09 Nov 2024"
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
#include <oof.h>


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

		// GLOBAL verbosity level.
		//inline verbosity verbosityLevel = verbosity::message;


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
		console(const cl::verbosity& v = cl::verbosity::message) {};
		
		//! Destructor. No particular duties.
		~console() {};

		// Methods - support.
		//void verbSet(const verb&);		
		//verb verbGet() const;					
		//bool seen(const verb&) const;
		//void print(const std::ostream&, const verb&) const;

		//! Set the verbosity level.
		//!
		//! \brief Set the verbosity level, from a 'cat::cl::verbosity::' enum.
		//!	\param v the verbosity level.
		//!	\return nothing.
		static void verb(const cl::verbosity& v) { _verbosity = v; }
		
		//! Set the verbosity level.
		//!
		//! \brief Set the verbosity level, interpreting a string. If the string
		//!		does not match any predefined token, set the verbosity to the default
		//!		'cat::cl::verbosity::message' level.
		//!	\param str is the string defining the verbosity level. It can be one
		//!		of the recognized tokens: {"critical", "error", "warning", "message", 
		//!		"info", "debug", "all"}.
		//!	\return nothing.
		static void verb(const std::string& str) {
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
		static cl::verbosity verb() { return _verbosity; }

		//! Verify wether a verbosity level is met or not.
		///
		/// \brief Check whether the provided verbosity level is currently met
		///		by the one set in the class.
		///	\param v the verbosity level to check.
		///	\return true if the verbosity level guarantees visibility, false 
		///		otherwise.
		static bool show(const cl::verbosity& v) { return (v <= _verbosity); }

		// Basic ostream operator overload. In this base version, do nothing.
		friend std::ostream& operator<<(std::ostream& os, const cat::console& c)
		{
			return (os);
		}

		// Current verbosity level.
		inline static cl::verbosity _verbosity;
		
		std::string _str;

	protected:

		// No protected at the moment.

	private:
				
		// No private at the moment.
};




// #############################################################################
namespace cl {


//______________________________________________________________________________
class cf 
{
	public:
		
		// Ctors.
		cf() : _str("") {}
		cf(const std::string& str) : _str(str) {}
		
		// Basic ostream operator overload. When called by the derived class,
		// 
		friend std::ostream& operator<<(std::ostream& os, const cat::cl::cf& c) {
			if (c._str.size()) os << c._str << oof::reset_formatting();
			return os;
		}

	private:
		std::string _str;
};



/// Here it is a set of specialized console format, which purpose is to help 
/// formatting the output in an uniform manner across the application. They are
/// all wrapped within the "cat::cl" namespace, so the user will easily have 
/// them automatically sorted when using any modern intellisense system.


// Appearance
//------------------------------------------------------------------------------

//______________________________________________________________________________
class reset : cf { public:
	reset() : cf() {}
	reset(const std::string& str) : cf(str) {}
	
	friend std::ostream& operator<<(std::ostream& os, const cat::cl::reset& c) {
		return (os << oof::reset_formatting() << (cf&)c);
	}
};

//______________________________________________________________________________
class bold : cf { public: 
	bold() : cf() {}
	bold(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::bold& c) {
		return (os << oof::bold(true) << (cf&)c);
	}
};

//______________________________________________________________________________
class uline : cf { public: 
	uline() : cf() {}
	uline(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::uline& c) {
		return (os << oof::underline(true) << (cf&)c);
	}
};


// Standard foreground colors
//------------------------------------------------------------------------------

//______________________________________________________________________________
class black : cf { public:
	black() : cf() {}
	black(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::black& c) {
		return (os << oof::fg_color({ 0, 0, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lblack : cf { public: 
	lblack() : cf() {}
	lblack(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lblack& c) {
		return (os << oof::fg_color({ 64, 64, 64 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class red : cf { public: 
	red() : cf() {}
	red(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::red& c) {
		return (os << oof::fg_color({ 128, 0, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lred : cf { public: 
	lred() : cf() {}
	lred(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lred& c) {
		return (os << oof::fg_color({ 255, 0, 64 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class green : cf { public: 
	green() : cf() {}
	green(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::green& c) {
		return (os << oof::fg_color({ 0, 128, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lgreen : cf { public: 
	lgreen() : cf() {}
	lgreen(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lgreen& c) {
		return (os << oof::fg_color({ 0, 255, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class blue : cf { public: 
	blue() : cf() {}
	blue(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::blue& c) {
		return (os << oof::fg_color({ 0, 0, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lblue : cf { public: 
	lblue() : cf() {}
	lblue(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lblue& c) {
		return (os << oof::fg_color({ 0, 0, 255 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class yellow : cf {	public: 
	yellow() : cf() {}
	yellow(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::yellow& c) {
		return (os << oof::fg_color({ 128, 128, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lyellow : cf { public: 
	lyellow() : cf() {}
	lyellow(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lyellow& c) {
		return (os << oof::fg_color({ 255, 255, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class cyan : cf { public: 
	cyan() : cf() {}
	cyan(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::cyan& c) {
		return (os << oof::fg_color({ 0, 128, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lcyan : cf { public: 
	lcyan() : cf() {}
	lcyan(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lcyan& c) {
		return (os << oof::fg_color({ 0, 255, 255 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class purple : cf {	public: 
	purple() : cf() {}
	purple(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::purple& c) {
		return (os << oof::fg_color({ 128, 0, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lpurple : cf { public: 
	lpurple() : cf() {}
	lpurple(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lpurple& c) {
		return (os << oof::fg_color({ 255, 0, 255 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class avio : cf { public: 
	avio() : cf() {}
	avio(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::avio& c) {
		return (os << oof::fg_color({ 0, 64, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lavio : cf { public: 
	lavio() : cf() {}
	lavio(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lavio& c) {
		return (os << oof::fg_color({ 0, 128, 255 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class fucsia : cf {	public: 
	fucsia() : cf() {}
	fucsia(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::fucsia& c) {
		return (os << oof::fg_color({ 0, 64, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lfucsia : cf { public: 
	lfucsia() : cf() {}
	lfucsia(const std::string& str) : cf(str) {}
	
	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lfucsia& c) {
		return (os << oof::fg_color({ 128, 0, 64 }) << (cf&)c);
	}
};


//______________________________________________________________________________
class grass : cf { public: 
	grass() : cf() {}
	grass(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::grass& c) {
		return (os << oof::fg_color({ 255, 0, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lgrass : cf { public: 
	lgrass() : cf() {}
	lgrass(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lgrass& c) {
		return (os << oof::fg_color({ 128, 0, 64 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class white : cf { public: 
	white() : cf() {}
	white(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::white& c) {
		return (os << oof::fg_color({ 255, 0, 128 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lwhite : cf {	public: 
	lwhite() : cf() {}
	lwhite(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lwhite& c) {
		return (os << oof::fg_color({ 255, 255, 255 }) << (cf&)c);
	}
};


// Standard styles
//------------------------------------------------------------------------------

//______________________________________________________________________________
class critical : cf { public:	
	critical() : cf() {}
	critical(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::critical& c) {
		return (os << cl::lpurple() << cl::bold() << (cf&)c);
	}
};

//______________________________________________________________________________
class error : cf { public:	
	error() : cf() {}
	error(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::error& c) {
		return (os << cl::lred() << (cf&)c);
	}
};

//______________________________________________________________________________
class warning : cf { public:	
	warning() : cf() {}
	warning(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::warning& c) {
		return (os << cl::lyellow() << (cf&)c);
	}
};

//______________________________________________________________________________
class message : cf { public:	
	message() : cf() {}
	message(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::message& c) {
		return (os << cl::lwhite() << cl::uline() << (cf&)c);
	}
};

//______________________________________________________________________________
class info : cf { public:	
	info() : cf() {}
	info(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::info& c) {
		return (os << cl::white() << (cf&)c);
	}
};

//______________________________________________________________________________
class debug : cf { public:	
	debug() : cf() {}
	debug(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::debug& c) {
		return (os << cl::white() << (cf&)c);
	}
};

//______________________________________________________________________________
class link : cf { public:	
		
	link() : cf() {}
	link(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::link& c) {
		return (os << cl::lavio() << cl::uline() << (cf&)c);
	}
};





// #############################################################################
}  // Close namespace "cl"


// #############################################################################
}  // Close namespace "cat"


// Overloading check
#endif