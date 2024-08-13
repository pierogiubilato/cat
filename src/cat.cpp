//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Main entry point						      --
// (C) Piero Giubilato 2011-2024, INFN PD									  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"main.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"01 Aug 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application units
#include "../include/cat.h"
#include "../include/caf.hpp"

#include "../include/pixel.hpp"

// Standard library
#include <stdexcept>
#include <charconv>

// Namespaces
using namespace std;
//using namespace cat;



// Extra libraries
//#include "../dependencies/include/rang.hpp"    // Console IO colors.

//______________________________________________________________________________
int main(int argc, char** argv)
{
	// Application shared support objects.
	//try {
	cat::cmd cmd;	// Command line parser.
	cat::log log;	// Logger.
	//} catch (invalid_argument& e) {
	//	cerr << e.what() << endl;
	//	cout << "Application initialization error." << endl;
	//	cout <<  "Execution terminated with error" << endl;
	//	return -1;
	//}

	// Show splash.
	splash();

	// Init application.
	init(cmd);

	// Parse the command line.
	cmd.parse(argc, argv);

	// Set application.
	setup(cmd, log);

	// Show Info.
	info(log);

	// Load files.
	try {
		// MyFunc(256); //cause an exception to throw
	}
	catch (invalid_argument& e) {
		cerr << e.what() << endl;
		log.error("Error loading files");
		log.message("Execution terminated with error");
		return -1;
	}

	// Do analysis.
	try {
		// MyFunc(256); //cause an exception to throw
	}
	catch (invalid_argument& e) {
		cerr << e.what() << endl;
		log.error("Error doing analysis");
		log.message("Execution terminated with error");
		return -1;
	}

	// Pixel test.
	cat::pixel px1(12, 13, 14);
	cout << "My new pixel px1 is: " << px1 << endl;
	cat::pixel px2;
	cout << "My new pixel px2 is: " << px2 << endl;
	px2 = px1;
	cout << "My new pixel px2 is: " << px2 << endl;
	cat::pixel px3(px2);
	cout << "My new pixel px3 is: " << px3 << endl;


	/*
	cout << "Trying to log!\n";
	//buf << rang::style::bold << "BOLD" << rang::style::reset << endl;
	//buf << rang::style::underline << "Underline" << rang::style::reset << endl;
	//buf << rang::style::italic << "Italic" << rang::style::reset << endl;
	///buf << rang::style::crossed << "Crossed" << rang::style::reset << endl;
	//cout << buf.str();
	cout << "ANSI\n";
	cout << "\033[31;1;4m" << "Pippo" << "\033[0m" << endl;
	stringstream buf;
	buf << "\033[31;5;4m" << "Pippo" << "\033[0m" << endl;
	cout << buf.str();

	// Console color class.
	cat::caf caf;
	cout << caf.fcol(caf.BLUE) << "BLU" << "\n";
	cout << caf.fcol(40,30,200) << "COLOR" << "\n";
	cout << caf.rev() << "INVERTED" << caf.rst() << "\n";
	cout << caf.font(caf.BOLD) << "BOLD" << caf.rst() << "\n";
	cout << caf.font(caf.ITALIC) << "ITALIC" << caf.rst() << "\n";
	cout << caf.font(caf.BLINK) << "BLINK" << caf.rst() << "\n";
	cout << caf.font(caf.UNDERLINE) << "UNDERLINE" << caf.rst() << "\n";
	cout << caf.rst();

		// Start logger.
	cout << "Here starts logger\n";
	cat::log logger(cat::log::V_ALL);
	logger.message("A simple message!");

	logger.section("New section");
	logger.message("Message 1");
	logger.message("Message 2");
	logger.warning("Warning 1");

	logger.section("And now the new section");
	logger.warning("Warning 2");
	*/

	// Bye bye.
	log.message("Execution ended with no error");
	return 0;
}

//______________________________________________________________________________
void init(cat::cmd& cmd)
{
	/* Init the application */

	// Command line arguments.
	//cmd.addArg("file", "set data file", true);
	//cmd.addArg("dir", "set data directory", false);
	

	// Command line options.
	cmd.addOpt("v", "set verbosity level [0=crt, 1=err, 2=wrn, 3=flw, 4=msg, 5=inf, 6=dbg]", false);

}


//______________________________________________________________________________
void setup(const cat::cmd& cmd, cat::log& log)
{
	/* Setup the application main paratmeters */

	
	// Set log verbosity.
	int v;
	std::string sv = cmd.getOptionValue("v", "4");
	std::from_chars(sv.data(), sv.data() + sv.size(), v);
	switch (v) {
		case 0: log.verb(cat::log::V_CRITICAL); break;
		case 1: log.verb(cat::log::V_ERROR); break;
		case 2: log.verb(cat::log::V_WARNING); break;
		case 3: log.verb(cat::log::V_FLOW); break;
		case 4: log.verb(cat::log::V_MESSAGE); break;
		case 5: log.verb(cat::log::V_INFO); break;
		case 6: log.verb(cat::log::V_DEBUG); break;
		default: log.verb(cat::log::V_ALL);
	}
	
}

//______________________________________________________________________________
void splash()
{
	/* Little splash screen */
	cout << endl << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|                             |" << endl;
	cout << "|" 
		 << cat::caf::fcol(cat::caf::BBLUE) << "    C" 
		 << cat::caf::fcol(cat::caf::BWHITE) << "++ "
		 << cat::caf::fcol(cat::caf::BBLUE) << "A"
		 << cat::caf::fcol(cat::caf::WHITE) << "nalysis "
		 << cat::caf::fcol(cat::caf::BBLUE) << "T"
		 << cat::caf::fcol(cat::caf::WHITE) << "emplate"
		 << cat::caf::rst() << "    |" << endl;
	cout << "|                             |" << endl;
	cout << "+-----------------------------+" << endl;
	cout << "|   Build " 
		 << "0" 
		 << "                   |" << endl;
	cout << "+-----------------------------+" << endl;

	cout << endl;




}


//______________________________________________________________________________
void info(const cat::log& log)
{
	// Command line arguments info.
	cout << "Verbosity: " << log.verb() << endl;
}