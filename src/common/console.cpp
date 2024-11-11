//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Console utility					          --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"console.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]	        "10 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Console library. Being a header only only, compiles it ONLY HERE ('OOF_IMPL').
#define OOF_IMPL
//#include<oof.h>

// Application units. Compiles the console ONLY HERE ('CAT_CONSOLE_IMPL').
//#define CAT_CONSOLE_IMPL
#include "console.hpp"


// Build ONLY in the translation unit where CAT_CONSOLE_IMPL is defined.
//#ifdef CAT_CONSOLE_IMPL

// Initialize static members.
cat::cl::verb::level cat::cl::verb::_current = cat::cl::verb::message;


// Overload operators for cat::cl::verbosity enum class.
//std::ostream& operator<<(std::ostream& os, const cat::cl::verbosity& v) {
//	std::string str;
//	switch (v) {
//	case cat::cl::verbosity::critical:	str = "critical"; break;
//	case cat::cl::verbosity::error:		str = "error"; break;
//	case cat::cl::verbosity::warning:	str = "warning"; break;
//	case cat::cl::verbosity::message:	str = "message"; break;
//	case cat::cl::verbosity::info:		str = "info"; break;
//	case cat::cl::verbosity::debug:		str = "debug"; break;
//	case cat::cl::verbosity::all:		str = "all"; break;
//	default: str = "unknown";
//	}
//	return os << str;
//}
//#endif


// Standard library.
//#include <sstream>


// #############################################################################
//namespace cat {

// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

////______________________________________________________________________________
//console::console(const console::verb& v, const console::width& w) :
//    _verb(v),
//    _width(w),
//    _indent(indent::main)
//{
//    /*! Verbosity ctor. Start the log with given 'v' verbosity and 'w' width.
//     */
//
//    // Appearance.
//    
//    // Data.
//    //_log.clear();
//    //_lvl.clear();
//}
//
////______________________________________________________________________________
//console::~console()
//{
//    /*! Dtor. Nothing really to do.
//     */
//}


// *****************************************************************************
// **                            Private members                              **
// *****************************************************************************


// *****************************************************************************
// **                           Operators overload                            **
// *****************************************************************************

/*
//______________________________________________________________________________
std::ostream& operator<<(const std::string& s, const log::level& l)
{
    return operator<<(std::ostream("s"), l);
}


//______________________________________________________________________________
std::ostream& operator<<(std::ostream& o, const log::level& l)
{
    if (l <= _verb) {
        return o;
    }
    else {
        return "";
    }
}
*/

// *****************************************************************************
// **                             Public members                              **
// *****************************************************************************
//
////______________________________________________________________________________
//void log::verb(const log::severity& sv)
///*! Set current verbosity level. */
//{
//    _verb = sv;
//}
//
//
////______________________________________________________________________________
///*! Returns current verbosity level. */
//log::severity log::verb() const
//{
//    return _verb;
//}
//
//
////______________________________________________________________________________
///*! Returns whether a verbosity level has to be shown depending on the current
//  level status.
//*/
//bool log::isShow(const log::severity& sv) const
//{
//    return (sv <= _verb);
//}
//
//
////______________________________________________________________________________
///*! Set console indent.
//*/
//std::string log::atab(const int& tab) const
//{
//    stringstream ss;
//
//    // Insert 'tab' empty chars.
//    if (tab >= 3) ss << "|";
//    if (tab >= 1) ss << string(tab - 1, ' ');
//    return ss.str();
//}
//
////______________________________________________________________________________
///*! Print on the output stream.
//*/
//void log::print(const stringstream& ss, const log::severity& sv) const
//{
//    // If it has to be shown, do it!
//    if (isShow(sv)) {
//        std::cout << ss.str();
//    }
//}
//
//
////______________________________________________________________________________
//void log::critical(const string& st, const severity& sv)
///*! Add a critical error to the log. */
//{
//    // Add a message to the log.
//    _log.push_back(stringstream(""));
//    _log.back() << atab(_indent);
//    _log.back() << CAT_CO_LPURPLE << st << CAT_CO_RESET;
//    _log.back() << "\n";
//
//    // Print in case.
//    print(_log.back(), sv);
//}
//
//
////______________________________________________________________________________
//void log::error(const string& st, const severity& sv)
///*! Add a error to the log. */
//{
//    // Add a message to the log.
//    _log.push_back(stringstream(""));
//    _log.back() << atab(_indent);
//    _log.back() << _caf.fcol(_caf.BRED) << st << _caf.rst();
//    _log.back() << "\n";
//
//    // Print in case.
//    print(_log.back(), sv);
//}
//
//
////______________________________________________________________________________
//void log::warning(const string& st, const severity& sv)
///*! Add a warning to the log. */
//{
//    // Add a message to the log.
//    _log.push_back(stringstream(""));
//    _log.back() << atab(_indent);
//    _log.back() << _caf.fcol(_caf.BYELLOW) << st << _caf.rst();
//    _log.back() << "\n";
//
//    // Print in case.
//    print(_log.back(), sv);
//}
//
//
////______________________________________________________________________________
//void log::section(const string& st, const severity& sv)
///*! Add a section level to the log. */
//{
//    // Pivot calc.
//    int spad = (int)floor((_widht - st.length() - 4) / 2);
//        
//    // Adjust indet.
//    _indent = indent::I_MAIN;
//    _lvl.push_back(_indent);
//
//    // Add a section block to the log.
//    _log.push_back(stringstream());
//    _log.back() << "\n\n";
//    _log.back() << _caf.fcol(_caf.WHITE);
//    _log.back() << string(_widht, '*') << "\n";
//    _log.back() << string(2, '*');
//    _log.back() << string(spad, ' ');
//    _log.back() << _caf.fstyle(_caf.WHITE, _caf.BOLD) << st << _caf.fstyle(_caf.WHITE, _caf.DEFAULT);
//    _log.back() << string(spad, ' ');
//    _log.back() << string(2, '*') << "\n";
//    _log.back() << string(_widht, '*') << "\n";
//    
//    // Print in case.
//    print(_log.back(), sv);
//
//    // Increase indent.
//    _indent = indent::I_SECTION;
//}
//
//
////______________________________________________________________________________
//void log::message(const string& st, const severity& sv)
///*! Add a message to the log. */
//{
//     // Add a message to the log.
//    _log.push_back(stringstream(""));
//    _log.back() << atab(_indent);
//    _log.back() << st;
//    _log.back() << "\n";
//
//    // Print in case.
//    print(_log.back(), sv);
//}
//
//
////______________________________________________________________________________
//void log::info(const string& st, const severity& sv)
///*! Add a info to the log. */
//{
//    // Add a message to the log.
//    _log.push_back(stringstream(""));
//    _log.back() << atab(_indent);
//    _log.back() << st;
//    _log.back() << "\n";
//
//    // Print in case.
//    print(_log.back(), sv);
//}
//
//
////______________________________________________________________________________
//void log::debug(const string& st, const severity& sv)
///*! Add a debug info to the log. */
//{
//    // Add a message to the log.
//    _log.push_back(stringstream(""));
//    _log.back() << atab(_indent);
//    _log.back() << st;
//    _log.back() << "\n";
//
//    // Print in case.
//    print(_log.back(), sv);
//}
//
//
//
//
//
//
//
///*
////______________________________________________________________________________
//std::ostream& log::add(const level& l, std::ostream& o) const
//{
//    // Clear the stream in case.
//    if (l > _verb) o.clear();
//    
//    // Returns the stream.
//    return o;
//}
//*/
///*
////______________________________________________________________________________
//std::ostream& log::add(std::iostream& o, const log::level& l) const
//{
//    if (l <= _verb) {
//        return o;
//    }
//    else {
//        return std::iostream("");
//    }
//}
//*/
//
// #############################################################################
//} // Closing namespace 'cat'

  
//______________________________________________________________________________
// Overload << operator in the main namespace
//inline std::ostream& operator<<(std::ostream& o, const int verb)
//{

//}




