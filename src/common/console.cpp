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

