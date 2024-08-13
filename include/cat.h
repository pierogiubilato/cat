//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Main entry point						      --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"main.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"25 Jul 2024"
// [Language]		"C++"
//______________________________________________________________________________


#pragma once


// Standard library
#include <iostream>

// Application units.
#include "../include/cmd.hpp"
#include "../include/log.hpp"


// Main functions.
void init(cat::cmd&);
void setup(const cat::cmd&, cat::log&);
void splash();
void info(const cat::log&);
