//------------------------------------------------------------------------------
// CAT - C++ Analysis Template - Application SERVER global definitions		  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"global.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [cat]			"23 Oct 2024"
// [Language]		"C++"
//______________________________________________________________________________




// Console output shortcut (use OOF library syntax)
// -------------------------------------------------

// Basic colors.
#define CAT_CO_BLACK	oof::fg_color({ 0,   0,   0 })
#define CAT_CO_LBLACK	oof::fg_color({ 64,  64,  64 })
#define CAT_CO_RED		oof::fg_color({ 128, 0,   0 })
#define CAT_CO_LRED		oof::fg_color({ 255, 0,	  255 })
#define CAT_CO_GREEN	oof::fg_color({ 0,	 128, 0 })
#define CAT_CO_LGREEN	oof::fg_color({ 0,	 255, 0 })
#define CAT_CO_BLUE		oof::fg_color({ 0,	 0,	  128 })
#define CAT_CO_LBLUE	oof::fg_color({ 0,	 0,	  255 })
#define CAT_CO_LBLUE	oof::fg_color({ 0,	 0,	  255 })
#define CAT_CO_YELLOW	oof::fg_color({ 128, 128, 0 })
#define CAT_CO_LYELLOW	oof::fg_color({ 255, 255, 0 })
#define CAT_CO_CYAN		oof::fg_color({ 0,   128, 128 })
#define CAT_CO_LCYAN	oof::fg_color({ 0,   255, 255 })
#define CAT_CO_PURPLE	oof::fg_color({ 128, 0,   128 })
#define CAT_CO_LPURPLE	of::fg_color({ 255, 0,   255 })
#define CAT_CO_WHITE	oof::fg_color({ 128, 128, 128 })
#define CAT_CO_LWHITE	oof::fg_color({ 255, 255, 255 })

// Advanced colors.
#define CAT_CO_AVIO		oof::fg_color({ 0,   64,  128 })
#define CAT_CO_LAVIO	oof::fg_color({ 0,   128, 255 })
#define CAT_CO_FUCSIA	oof::fg_color({ 128, 0,   64 })
#define CAT_CO_LFUCSIA	oof::fg_color({ 255, 0,   128 })
#define CAT_CO_GRASS	oof::fg_color({ 64,  128, 0 })
#define CAT_CO_LGRASS	oof::fg_color({ 128, 255, 0 })

// Basic formatting.
#define CAT_CO_RESET	oof::reset_formatting()
#define CAT_CO_ULINE	oof::underline(true)
#define CAT_CO_BOLD		oof::bold(true)

// Standard messages formatting.
#define CAT_CO_CRITICAL		CAT_CO_LPURPLE << CAT_CO_BOLD
#define CAT_CO_ERROR		CAT_CO_LRED << CAT_CO_BOLD
#define CAT_CO_WARNING		CAT_CO_LYELLOW
#define CAT_CO_IMPORTANT	CAT_CO_LWHITE << CAT_CO_ULINE
#define CAT_CO_INFO			CAT_CO_LWHITE
#define CAT_CO_DEBUG		CAT_CO_WHITE




// "cat" namespace opening
// #####################################################################################################################
namespace cat {
	//namespace co {
		//enum class col : int {


		//};
			// #####################################################################################################################
	//} // "co" namespace closing
} // "cat" namespace closing

