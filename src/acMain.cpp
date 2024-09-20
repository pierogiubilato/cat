//------------------------------------------------------------------------------
// CAT application core entry point										      --
// (C) Piero Giubilato 2011-2015, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"acMain.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Application components.
#include "acMain.h"
#include "uiSplash.h"
#include "acServer.h"
#include "acLoop.h"
#include "afFile.h"
#include "afFont.h"

// Standard
#include <direct.h>

//______________________________________________________________________________
// The main routines
int main(int argc, char** argv);				//!< Entry point.
void main_CmdParse(const int&, char**);			//!< Command line parser.
void main_Path();								//!< Paths builder.
void main_Credits();							//!< Credits.
void main_Help();								//!< Help.
int main_ServStart();							//!< Starts services.
void main_ServStop();							//!< Stops services.
void main_Info();								//!< Provides status info.

//______________________________________________________________________________
// Private vars
static std::vector<std::string> arg_Key;		// Preset key-list.
static std::vector<std::string> arg_Entry;		// Independent entry.
static std::vector<std::string> arg_Command;	// Command.

//______________________________________________________________________________

// Application Global (ag) settings defaults.
Uint32 cat::ag::_verbose = CAT_VERB_WARN;		// No verbosity by default.
bool cat::ag::_stupShowInfo = false;			// No general info.
bool cat::ag::_stupShowFont = false; 			// No font list dump.
bool cat::ag::_stupShowHelp = false; 			// No quick help.
std::string cat::ag::_pathMain = "";			// No default path.	
std::string cat::ag::_pathFonts = "";			// No default font path.	
Uint32 cat::ag::_screenDPIX = 96;				// Default screen X resolution.
Uint32 cat::ag::_screenDPIY = 96;				// Default screen Y resolution.

// Global application core services.
cat::ac::server* cat::ac::_server = 0;			// No inst. Server.
cat::ac::loop* cat::ac::_loop = 0;				// No inst. Loop.

// Global application facility services.
cat::af::file* cat::af::_file = 0;				// No inst. File Facility.
cat::af::font* cat::af::_font = 0;				// No inst. Font Facility.

//______________________________________________________________________________
int main(int argc, char** argv)
{
	/* Application entry point. */
   	
	// Show credits
	main_Credits();
	
	// Parse command line
	main_CmdParse(argc, argv);

	// Sets all the paths.
	main_Path();

	// Starts the services.
	if(main_ServStart()) return 1;

	// Show info.
	main_Info();
	
	// Shows the Splash.
//	new pear::ui::Splash(1000);	// Self destroying!

	// Startup the main application loop.
	// ----------------------------------
	try {
		cat::ac::_loop = new cat::ac::loop();
		cat::ac::_loop->cmdApp_Run(); 
	}
  	catch (const std::exception& ex) {
		std::cout << "cat: " << ex.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cout << "cat: undefined exception  while starting the Loop.";
		return 1;
	}
	
	// Stops the services.
	main_ServStop();

	// Funny, but just clear console color!
	std::cout << COL(DEFAULT);
	std::cout.flush(); 
	
	// Bye bye! 
	return 0;    
}

//______________________________________________________________________________
int main_ServStart() 
{
	/*! Starts the application-wide services */

	// Startup the SDL library.
	// ------------------------
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
        std::cout << COL(CAT_COL_ERROR) << "pear: SDL initialization failed\n" << COL(DEFAULT);
        return 1;
	}
	
	// Startup the File Facility.
	// --------------------------
	//try {
	//	cat::af::_file = new pear::af::file();
	//}
	//catch (const std::exception& ex) {
	//	std::cout << "cat: " << ex.what() << "\n";
	//	return 1;
	//}
	//catch (...) {
	//	std::cout << "cat: undefined exception while starting the File Facility.";
	//	return 1;
	//}

	// Startup the Font Facility.
	// --------------------------
	//try {
	//	cat::af::_font = new pear::af::font(cat::ag::_PathFonts);
	//}
	//catch (const std::exception& ex) {
	//	std::cout << "cat: " << ex.what() << "\n";
	//	return 1;
	//}
	//catch (...) {
	//	std::cout << "cat: undefined exception while starting the Font Facility.";
	//	return 1;
	//}

	// Startup the Net Server.
	// -----------------------
	try {
		cat::ac::_server = new cat::ac::server(2345);
	}
	catch (const std::exception& ex) {
		std::cout << "cat: " << ex.what() << "\n";
		return 1;
	}
	catch (...) {
		std::cout << "cat: undefined exception while starting the Server.";
		return 1;
	}

	// Everything ok!
	return 0;
}

//______________________________________________________________________________
void main_ServStop() 
{
	/*! Stops the application-wide services */

	// Releases the core services.
	delete cat::ac::_loop;
	delete cat::ac::_server;

	// Releases the facility services.
	delete cat::af::_font;
	delete cat::af::_file;

	// Shuts down the SDL library.
	SDL_Quit();
}

//______________________________________________________________________________
void main_CmdParse(const int& argc, char** argv)
{
	/*! Parse the command line. Saves all the given parameter into the provided
	 *	paw::obj::Ana structure. It works by cheking for tokens, and for those 
	 *	tokens which requires some parameters it stores up to prmCountLimit
	 *	numbers found after the token, up to the next recognized token.
	 */

	// Types and storage setup.
	enum kArg {kaNull, kaVerb, kaPort};
	int tknType = kaNull;
	const int tknCount = 6;			// Max # different tokens handled.
	const int prmCountLimit = 1;	// Max # parameters per token handled.
	int prmCount[tknCount];
	double prmStore[tknCount][prmCountLimit];
	for (int i = 0; i < tknCount; i++) prmCount[i] = 0;
	
	// Check tokens and load arguments.
	for (int i = 0; i < argc; i++) {
		
		// Arguments and switches.
		std::string argString = argv[i];
		if (argString == "-p") {tknType = kaPort; continue;}
		if (argString == "-v") {tknType = kaVerb; continue;}
		if (argString == "-f") {cat::ag::_stupShowFont = true;	tknType = kaNull; continue;}
		if (argString == "-i") {cat::ag::_stupShowInfo = true;	tknType = kaNull; continue;}
		if (argString == "-h") {cat::ag::_stupShowHelp = true;	tknType = kaNull; continue;}

		// Load token's values into prmStore (doing boundary check on prmStore size).
		if (prmCount[tknType] < prmCountLimit) {
			std::istringstream param (argv[i]);
			param >> prmStore[tknType][prmCount[tknType]];
			prmCount[tknType]++;
		}
	}

	// Transfer stored parameters to the appropriate vars.
	cat::ag::_verbose = static_cast<Uint32>(prmStore[kaVerb][0]);
	//pear::ag::_Verbose = prmStore[kaPort][0];
}

//______________________________________________________________________________
void main_Credits()
{
	/*! Some credits! */
	
	// Color shorts.
	#define CLW COL(LWHITE)
	#define CLG COL(LGREEN)
	#define CLB COL(LBLUE)
	#define CLY COL(LYELLOW)
	#define CLC COL(LCYAN)
	#define CD COL(DEFAULT)

	// Show the name.
	std::cout << "\n\n\n\n"
		<< "***********************************************\n"
		<< "**                                           **\n"
		<< "**    " 
		<< CLG << "C" << CD << "C++  " 
		<< CLG << "A" << CD << "cquisition & " << CLG << "A" << CD << "nalysis  "
		<< CLG << "T" << CD << "oolset    **\n"
		<< "**                                           **\n"
		<< "***********************************************\n";

	// Copyright and version.
	std::cout << "\n"
		<< CLG << "CAT" << CD << " Version " 
		<< CLW << CAT_VER_MAJOR << CD << "." 
		<< CLW << CAT_VER_MINOR << CD << "\n"
		<< "Built: " << CLY << __DATE__ << CD << "\n"
		<< "(C) " << CLB << "University of Padova" << CD << " 2020-2025\n";
		
	// Library references.
	std::cout << "\nBased on:\n"
		<< "2D Graphics:   " << CLW << "SDL Library " << CD
		<< "(" << CLC << "http://www.libsdl.org/" << CD << ")" << "\n"
		<< "3D Graphics:   " << CLW << "OpenGL Library " << CD 
		<< "(" << CLC << "http://www.opengl.org/" << CD << ")" << "\n"
		<< "GL extensions: " << CLW << "GLEW Library " << CD 
		<< "(" << CLC << "http://glew.sourceforge.net/" << CD << ")" << "\n"
		<< "GUI controls:  " << CLW << "Dear ImGUI" << CD 
		<< "(" << CLC << "http://www.antisphere.com" << CD << ")" << "\n"
		<< "NET sockets:   " << CLW << "SDL_net Library " << CD 
		<< "(" << CLC << "http://www.libsdl.org/" << CD << ")" << "\n"
		<< "Font library:  " << CLW << "FreeType Project " << CD 
		<< "(" << CLC << "http://www.freetype.org/" << CD << ")" << "\n"
		<< "Mathematics:   " << CLW << "OpenGL Mathematics " << CD 
		<< "(" << CLC << "http://glm.g-truc.net/" << CD << ")" << "\n";

	// Authors.
	std::cout << "\nAutors:\n" << CLW
		<< "Piero Giubilato\n"
		<< CD << "\n";

	// Release color shorts.
	#undef CLW
	#undef CLG
	#undef CLB
	#undef CLY
	#undef CLC
	#undef CD
}

//______________________________________________________________________________
void main_Path() 
{
	/*! Sets up all the application paths. */
	
	// Retrieves the main path.
	char temp[CAT_PATH_MAXLEN];
	_getcwd(temp, CAT_PATH_MAXLEN) ? cat::ag::_pathMain = temp : cat::ag::_pathMain = "";
	
	// Set up the font path.
	cat::ag::_pathFonts = cat::ag::_PathMain;
	cat::ag::_pathFonts.append(CAT_PATH_FONTS);   
}

//______________________________________________________________________________
void main_Info()
{
	/*! Show some general info at startup. */
	std::cout << "\n";
	
	// Show compilation info ("-i" token).
	if (pear::ag::_stupShowInfo) {

		// Show SDL info.
		SDL_version compiled;
		SDL_version linked;
		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);
		std::cout << COL(LWHITE) << "SDL Library\n" << COL(DEFAULT);
		std::cout << "   Compiled: " << (unsigned int)compiled.major << "." 
								 << (unsigned int)compiled.minor << "." 
								 << (unsigned int)compiled.patch  << "\n",
		std::cout << "   Linked:   " << (unsigned int)linked.major << "." 
								 << (unsigned int)linked.minor << "." 
								 << (unsigned int)linked.patch  << "\n",       
		std::cout << "   Platform: " << SDL_GetPlatform() << "\n";
	
	}

	// Pad and Font info are managed by the Pad and Font manager themselves
	// by checking the global var pear::ag::...... ("-i" and "-f" tokens).

	// Show little help ("-h" token).
	if (cat::ag::_stupShowHelp) main_Help();
}

//______________________________________________________________________________
void main_Help()
{
	/*! Show little on-the-fly help. */
	std::cout << "\nThis is the little, very un-useful help!\n";
}
