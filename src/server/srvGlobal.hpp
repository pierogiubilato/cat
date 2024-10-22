


// Console library.
//#include <oof.h>


// Console output shortcut (use OOF library syntax)
// -------------------------------------------------

// Basic colors.
#define CCO_BLACK	oof::fg_color({ 0,   0,   0 })
#define CCO_LBLACK	oof::fg_color({ 64,  64,  64 })
#define CCO_RED		oof::fg_color({ 128, 0,   0 })
#define CCO_LRED	oof::fg_color({ 255, 0,	  255 })
#define CCO_GREEN	oof::fg_color({ 0,	 128, 0 })
#define CCO_LGREEN	oof::fg_color({ 0,	 255, 0 })
#define CCO_BLUE	oof::fg_color({ 0,	 0,	  128 })
#define CCO_LBLUE	oof::fg_color({ 0,	 0,	  255 })
#define CCO_LBLUE	oof::fg_color({ 0,	 0,	  255 })
#define CCO_YELLOW	oof::fg_color({ 128, 128, 0 })
#define CCO_LYELLOW	oof::fg_color({ 255, 255, 0 })
#define CCO_CYAN	oof::fg_color({ 0,   128, 128 })
#define CCO_LCYAN	oof::fg_color({ 0,   255, 255 })
#define CCO_PURPLE	oof::fg_color({ 128, 0,   128 })
#define CCO_LPURPLE	oof::fg_color({ 255, 0,   255 })
#define CCO_WHITE	oof::fg_color({ 128, 128, 128 })
#define CCO_LWHITE	oof::fg_color({ 255, 255, 255 })

// Advanced colors.
#define CCO_AVIO	oof::fg_color({ 0,   64,  128 })
#define CCO_LAVIO	oof::fg_color({ 0,   128, 255 })
#define CCO_FUCSIA	oof::fg_color({ 128, 0,   64 })
#define CCO_LFUCSIA	oof::fg_color({ 255, 0,   128 })
#define CCO_GRASS	oof::fg_color({ 64,  128, 0 })
#define CCO_LGRASS	oof::fg_color({ 128, 255, 0 })

// Basic formatting.
#define CCO_RESET	oof::reset_formatting()
#define CCO_ULINE	oof::underline(true)
#define CCO_BOLD	oof::bold(true)




// "cat" namespace opening
// #####################################################################################################################
namespace cat {


// #####################################################################################################################
} // "cat" namespace closing

