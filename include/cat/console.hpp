//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Console output utility                       --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"console.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [cat]			"21 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Overloading check
#ifndef console_HPP
#define console_HPP

// Standard library
#include <string>
#include <deque>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <sstream>

// Console library.
#include <oof.h>


// #############################################################################
namespace cat { namespace cl {
		

//______________________________________________________________________________
//! \brief The 'cat::cl::verb' class manages the console verbosity level.
//!		it is a fully static class.
class verb
{
	public:

		//! Public verbosity values.
		enum level : uint8_t {
			critical = 0,
			error = 1,
			warning = 2,
			section = 3,
			message = 4,
			info = 5,
			debug = 6,
			all = 99
		};

		//! Returns whether a verbosity level has to be shown.
		//! \brief Compares the given verbosity level with the current one, and
		//!		determines whether it is to be shown or not.
		//! \argument 'lvl' the verbosity level to compare.
		//! \return true if it is to be shown, false otherwise.
		static bool show(const level& lvl) {
			return (lvl <= _current);
		}

		//! Set the console verbosity level.
		//! \brief Set the console verbosity level.
		//! \argument 'lvl' the verbosity level to set.
		//! \return nothing.
		static void set(const level& lvl) {
			_current = lvl;
		}

		//! Set the console verbosity level.
		//! \brief Set the console verbosity level.
		//! \argument a std::string 'str' the verbosity level to set.
		//! \return nothing.
		static void set(const std::string& str) {
			if (str == "critical")		_current = critical;
			else if (str == "error")	_current = error;
			else if (str == "warning")	_current = warning;
			else if (str == "message")	_current = message;
			else if (str == "info")		_current = info;
			else if (str == "default")	_current = debug;
			else if (str == "all")		_current = all;
			else _current = message;
		}

		//! Get the console verbosity level.
		//! \brief Get the console verbosity level.
		//! \return a 'cat::cl::verb::level' enum element indicating the current verbosity level.
		static cat::cl::verb::level get() {
			return _current;
		}

		//! Ostream operator overload.
		//! \brief Overloads the output stream operator to give a string naming of 
		//!		the current verbosity level.
		//! \return a 'std::ostream&' ostream object.
		friend std::ostream& operator<<(std::ostream& os, const cat::cl::verb& v) {
			std::string str;
			switch (v._current) {
				case cat::cl::verb::critical:	str = "critical"; break;
				case cat::cl::verb::error:		str = "error"; break;
				case cat::cl::verb::warning:	str = "warning"; break;
				case cat::cl::verb::message:	str = "message"; break;
				case cat::cl::verb::info:		str = "info"; break;
				case cat::cl::verb::debug:		str = "debug"; break;
				case cat::cl::verb::all:		str = "all"; break;
				default: str = "unknown";
			}
			return (os << str);
		}
	
		//private:
		//! Current verbosity level.
		static level _current;
};


//!_____________________________________________________________________________
//! \brief The 'cat::cl::cf' class is the base formatting class for the console 
//!		output. It serves as base class for all the specialized format classes. 
//!		Its basic purpose is to encapsulate a simple operator << overload that
//! 	changes the behaviour of the formatting accordingly to the presence of
//! 	a std::string on creation, to allow a flexible usage of the formatting
//! 	codes.
//! \str is a std::string which, if provided at instantiation, makes the class
//! 	appending a format reset after adding the string to the current output
//! 	stream, simplifying the calls of derived formatting classes.
class cf
{
public:

	//! Default ctor. Sets the class mode to 0 (nothing to print).
	cf() : _sstr(""), _tag("") {}

	//! Template constructor for numbers. Applies the derived class
	//! formatting to the console ouput, and print the number passed
	//! as constructor argument. Reset the console style afterward.
	template<typename T> cf(const T& arg) : _tag("") { _sstr << arg; }

	//! Template constructor specialization for handling strings.
	//! Applies the derived class formatting to the console ouput, 
	//! and print the string passed as constructor argument. Reset 
	//! the console style afterward.
	template <> cf(const std::string& str) : _sstr(str), _tag("") {}

	//! Template constructor specialization for aligned messages.
	//! Applies the derived class formatting to the console ouput, 
	//! explicitly print the type of message, and then the '_str'
	//! string in default console format.
	template<typename T> cf(const T& arg, const std::string& tag) : _tag(tag) { _sstr << arg; }

	//! Template constructor specialization for aligned messages
	//! handling strings. Applies the derived class formatting to 
	//! the console ouput, explicitly print the type of message, 
	//! and then the '_str' string in default console format.
	template <> cf(const std::string& str, const std::string& tag) : _sstr(str), _tag(tag) {}


	//! Basic ostream operator overload. When called by the derived class,
	//! it will make automatic formatting depending whether the '_str'
	//! string is present, and the status of the '_set' flag.
	friend std::ostream& operator<<(std::ostream& os, const cat::cl::cf& c) {

		// Explicit mode.
		if (c._tag.size()) {
			os << std::setw(10) << std::right << c._tag
				<< oof::reset_formatting() << "): ";
			os << c._sstr.str() << "\n";
			return os;

		// Message mode.
		} else if (c._sstr.str().size()) {
			return (os << c._sstr.str() << oof::reset_formatting());

			// Format only mode.
		} else {
			return os;
		}
	}

private:
	std::string _tag;
	std::stringstream _sstr;
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
		return (os << oof::fg_color({ 64, 128, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class lgrass : cf { public: 
	lgrass() : cf() {}
	lgrass(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::lgrass& c) {
		return (os << oof::fg_color({ 128, 255, 0 }) << (cf&)c);
	}
};

//______________________________________________________________________________
class white : cf { public: 
	white() : cf() {}
	white(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::white& c) {
		return (os << oof::fg_color({ 128, 128, 128 }) << (cf&)c);
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



// Standard styles (WITHOUT verbosity check)
//------------------------------------------------------------------------------

//______________________________________________________________________________
class link : cf {
public:

	link() : cf() {}
	link(const std::string& str) : cf(str) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::link& c) {
		return (os << cl::lavio() << cl::uline() << (cf&)c);
	}
};



// Standard styles (WITH verbosity check)
//------------------------------------------------------------------------------

//______________________________________________________________________________
class critical : cf { public:	
	critical() : cf() {}
	template <typename T> critical(const T& arg) : cf(arg) {}

	//if (verb)
	friend std::ostream& operator<<(std::ostream& os, const cat::cl::critical& c) {
		if (verb::show(verb::critical)) return (os << cl::lpurple() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class error : cf { public:	
	error() : cf() {}
	template <typename T> error(const T& arg) : cf(arg) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::error& c) {
		if (verb::show(verb::error)) return (os << cl::lred() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class warning : cf { public:	
	warning() : cf() {}
	template <typename T> warning(const T& arg) : cf(arg) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::warning& c) {
		if (verb::show(verb::warning)) return (os << cl::lyellow() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class message : cf { public:	
	message() : cf() {}
	template <typename T> message(const T& arg) : cf(arg) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::message& c) {
		if (verb::show(verb::message)) return (os << cl::lwhite() << cl::uline() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class info : cf { public:	
	info() : cf() {}
	template <typename T> info(const T& arg) : cf(arg) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::info& c) {
		if (verb::show(verb::info)) return (os << cl::lwhite() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class debug : cf { public:	
	debug() : cf() {}
	template <typename T> debug(const T& arg) : cf(arg) {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::debug& c) {
		if (verb::show(verb::debug)) return (os << cl::white() << (cf&)c);
		else return os;
	}
};


// Standard styles messages (TABBED, WITH verbosity check)
//------------------------------------------------------------------------------

//______________________________________________________________________________
class criticalMsg : cf {
public:
	template <typename T> criticalMsg(const T& arg) : cf(arg, "critical") {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::criticalMsg& c) {
		if (verb::show(verb::critical)) return (os << cl::lpurple() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class errorMsg: cf {
public:
	template <typename T> errorMsg(const T& arg) : cf(arg, "error") {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::errorMsg& c) {
		if (verb::show(verb::error)) return (os << cl::lred() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class warningMsg : cf {
public:
	template <typename T> warningMsg(const T& arg) : cf(arg, "warning") {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::warningMsg& c) {
		if (verb::show(verb::warning)) return (os << cl::lyellow() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class messageMsg: cf {
public:
	template <typename T> messageMsg(const T& arg) : cf(arg, "message") {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::messageMsg& c) {
		if (verb::show(verb::message)) return (os << cl::lwhite() << cl::uline() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class infoMsg : cf {
public:
	template <typename T> infoMsg(const T& arg) : cf(arg, "info") {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::infoMsg& c) {
		if (verb::show(verb::info)) return (os << cl::lwhite() << (cf&)c);
		else return os;
	}
};

//______________________________________________________________________________
class debugMsg : cf {
public:
	template <typename T> debugMsg(const T& arg) : cf(arg, "debug") {}

	friend std::ostream& operator<<(std::ostream& os, const cat::cl::debugMsg& c) {
		if (verb::show(verb::debug)) return (os << cl::white() << (cf&)c);
		else return os;
	}
};



// #############################################################################
}}  // Close namespaces


// Overloading check
#endif