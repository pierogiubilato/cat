//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Main entry point						      --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"main.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"25 Jul 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/cat.h"


// Standard library
using namespace std;
#include <iostream>

// Extra libraries
#include "../dependencies/include/rang.hpp"    // Console IO colors.



//______________________________________________________________________________
int main(int argc, char** argv)
{
	cout << rang::fgB::red << "Hello World." << rang::style::reset << endl;
	return 0;
}