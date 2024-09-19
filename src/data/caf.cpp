//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Console ANSI Formatting                      --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"caf.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.1"
// [Modified by]	"Piero Giubilato"
// [Date]	        "31 Jul 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/caf.hpp"



// #############################################################################
namespace cat {

// *****************************************************************************
// **                            Special members                              **
// *****************************************************************************

//______________________________________________________________________________
caf::caf()
{
	/* Ctor. */
};

//______________________________________________________________________________
caf::~caf()
{
	/* Dtor. */
};


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
std::string caf::rst()
{
	/* Reset every console formatting to default (color, font, blink,etc). */
	std::stringstream ss;
	ss << "\033[0m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::fcol(const caf::col& c)
{
	/* Set foreground color with standard ANSI codes */
	std::stringstream ss;
	ss << "\033[" << c << "m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::fcol(const int& r, const int& g, const int& b)
{
	/* Set foreground color with arbitrary RGB palette (only recent terminals) */
	std::stringstream ss;
	ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::font(const caf::style& f)
{
	/* Set font style */
	std::stringstream ss;
	ss << "\033[" << f << "m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::fstyle(const caf::col& c, const caf::style& f)
{
	/* Set foreground color and font style */
	std::stringstream ss;
	ss << "\033[" << c << ";" << f << "m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::bcol(const caf::col& c)
{
	/* Set background color with standard ANSI codes */
	std::stringstream ss;
	ss << "\033[" << (c + 10) << "m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::bcol(const int& r, const int& g, const int& b)
{
	/* Set background color with arbitrary RGB palette (only recent terminals) */
	std::stringstream ss;
	ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
	return ss.str();
}


//______________________________________________________________________________
std::string caf::rev()
{
	/* Reverse foreground and background */
	std::stringstream ss;
	ss << "\033[7m";
	return ss.str();
}


// #############################################################################
} // Closing namespace 'cat'



