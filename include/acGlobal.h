//------------------------------------------------------------------------------
// CAT application core global definitions									  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"acGlobal.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Overloading check
#if!defined acGlobal_H
#define acGlobal_H

	// Standard libraries
	//#include <iomanip>
	//#include <stddef.h>
	//#include <exception>
	//#include <stdexcept>



	// -------------------------
	// -- Application Version --
	// -------------------------
	#define CAT_VER_MAJOR 0					//!< Release major.
	#define CAT_VER_MINOR 1					//!< Release minor.
	#define CAT_VER_TITLE "CAT 0.1 gamma"	//!< Release title.



	// ------------------------------------
	// -- Global environment definitions --
	// ------------------------------------

	/*! Check that these environmental variables are correctly. */
	// defined accordingly to your building environment:
	// Windows: WIN64 or WIN32
	// Linux:
	// Mac OsX:	
	
	/*! Application path. */
	#define CAT_PATH_MAXLEN 1024				//!< Maximum path length.
	#define CAT_PATH_FONTS "/resources/fonts"	//!< Font path.

	/*! Sets the default Pad windows appearance. */
	constexpr int CAT_PAD_WIDTH = 1024;			//!< Pad width.
	constexpr int CAT_PAD_HEIGHT = 768;			//!< Pad height.;

	/*! Net default parameters. */
	// ...	
	// ...



	// ------------------------------------------
	// -- Data type size --
	// ------------------------------------------

	//#define CAT_TYPE_SIZE_INT sizeof(int);
	//#define CAT_TYPE_SIZE_UINT sizeof(unsigned int);
	//#define CAT_TYPE_SIZE_FLOAT sizeof(float);



	// ----------------------------
	// -- Default fonts elements --
	// ----------------------------

	#define CAT_FONT_DEF_FAMILY "arial"		//!< Default font family.
	#define CAT_FONT_DEF_STYLE "regular"	//!< Default font style.
	#define CAT_FONT_DEF_SIZE_PT 18			//!< Default font size (points).
	#define CAT_FONT_DEF_SIZE_PX 10			//!< Default font size (pixels).



	// ------------------------------------------
	// -- Standard objects printout parameters --
	// ------------------------------------------

	/*! Sets the default colors for general communications. Color codes are
		defined in the pear_Console.h file.*/
	#define CAT_COL_OK LGREEN				//!< Ok.
	#define CAL_COL_WARNING LYELLOW			//!< Warning.
	#define CAT_COL_ERROR LRED				//!< Error.

	/*! Sets default dump number precision. */
	#define CAT_DUMP_PREC_DEFAULT 2			//!< Default decimals.
	#define CAT_DUMP_PREC_GEOMETRY 4		//!< Geometric figures decimals.
	#define CAT_DUMP_PREC_COLOR 3			//!< Color channel decimals.

	/*! Sets the default colors for object properties dumping. Color codes are
		defined in the Console.h file.*/
	#define CAT_DUMP_COL_X YELLOW			//!< X coordinate color.
	#define CAT_DUMP_COL_Y CYAN				//!< Y coordinate color.
	#define CAT_DUMP_COL_Z PURPLE			//!< Z coordinate color.
	#define CAT_DUMP_COL_TYPE LWHITE		//!< Object Type color.
	#define CAT_DUMP_COL_NAME LGREEN		//!< Object Name color.
	#define CAT_DUMP_COL_HANDLE LCYAN		//!< Object Handle color.
	#define CAT_DUMP_COL_VISIBLE WHITE		//!< Object Visible color.
	#define CAT_DUMP_COL_COLOR LBLACK		//!< Object Color color.
	#define CAT_DUMP_COL_PARENT RED			//!< Object Parent color.
	#define CAT_DUMP_COL_CHILD YELLOW		//!< Object Child color.
	
	/*! Sets the default padding value for nested Dump() calls */
	#define CAT_DUMP_PADDING 3				//!< Padding value.
	

	/*! Sets the default Dump() timeout for every object inheriting from cat::Object. 
		A Dump() call will be stopped after CAKE_DUMP_TIMEOUT milliseconds, to avoid
		get stuck in case of erroneous dumping of large objects. */
	#define CAT_DUMP_TIMEOUT 500			//!< Timeout in milliseconds.

	/*! Sets default verbosity levels for the serve-side application */
	#define CAT_VERB_NULL 0					//!< No verbosity at all.
	#define CAT_VERB_DEF 1					//!< Default verbosity.
	#define CAT_VERB_ERR 2					//!< Plus reports errors. 
	#define CAT_VERB_WARN 3					//!< Plus reports warnings. 
	#define CAT_VERB_FULL 4					//!< Plus everything else. 

// End of Overloading check 
#endif