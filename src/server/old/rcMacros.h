//------------------------------------------------------------------------------
// CAT Remopte Client class, macro expansion								  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"rcMacros.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"32 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#if !defined rcMacros_H
#define rcMacros_H

#include "rcDCs.h"
//#include "gtTools.h"

// #############################################################################
namespace cat { namespace rc {

//! cat rc::macros
/*! cat::rc::macros is an .h only class which lays on top of the rc::core and
 *	rc::DCs classes. It adds macro-stile commands to the client user interface.
 *	Macro means that the implemented functions are not hardcore cat commands or
 *	primitives, but a simple collections of various cat commands and primitives.
 *	They are layered in this class to provide a more uniform user interface
 *	by incapsulating them in the same final interface class.
 *
 *	\author Piero Giubilato
 *	\version 1.0
 *	\date 24 Sep 2024
 */
class macros: public DCs 
{
	public:

	// Special members.
	CAT_API CAT_CALL macros(const char* host, 
							const Uint16& port, 
							const Uint64& verb = 0)
							: DCs(host, port, verb) {;} 

	// Macros commands
	// ---------------
			
	// ********************************** Tripod *******************************

	//! Tripod with parent.
	CAT_API gp::GPHnd CAT_CALL dcTripod(const gp::GPHnd& parent, 
										const double& scale = 1, 
										const char* name = "")
	{
		/* Draws a tripod aligned with the parent reference frame. */
		gp::GPHnd tripod = dcEmpty(parent, "Tripod");
		gp::GPHnd step = 0;
		double PI = 3.141592;	
		double arm = 0.7 * scale;
		double tip = scale - arm;
		double thick = 0.05 * scale;
		double base = 0.15 * scale;

		// Store current brush and fill setting.
		gt::brush oldBrush = dcBrushGet();
		gt::fill oldFill = dcFillGet();

		// Set brush and filling mode.
		dcBrushSet(false, 1, 1, 1, 1, 1, 0, 1);
		dcFillSet(true, 0, 0, 0, 1, false);	
		
		// X axis.
		dcFillColor(1, 0, 0, 1);		
		step = dcFrame(tripod, 0, 0, 0, 0, PI / 2, 0, "X axis rotate");
	//	dcCylinder(step, thick, arm, 10, 1, "Arm");
		step = dcFrame(step, 0, 0, arm, 0, 0, 0, "Translate my Z");
	//	dcCone(step, base, tip, 10, 1, "Tip");

		// Y axis.
		dcFillColor(0, 1, 0, 1);		
		step = dcFrame(tripod, 0, 0, 0, -PI / 2, 0, 0, "Y axis rotate");
	//	dcCylinder(step, thick, arm, 10, 1, "Arm");
		step = dcFrame(step, 0, 0, arm, 0, 0, 0, "Translate my Z");
	//	dcCone(step, base, tip, 10, 1, "Tip");

		// Z axis.
		dcFillColor(0, 0, 1, 1);
		step = dcFrame(tripod, 0, 0, 0, 0, 0, 0, "Z axis rotate");
	//	dcCylinder(step, thick, arm, 10, 1, "Arm");
		step = dcFrame(step, 0, 0, arm, 0, 0, 0, "Translate my Z");
	//	dcCone(step, base, tip, 10, 1, "Tip");
						
		// Origin ball.
		dcFillColor(1, 1, 1, 1);
	//	dcSphere(tripod, base);

		// Restore brush and fill setting.
		dcBrushSet(oldBrush);
		dcFillSet(oldFill);

		// Returns the object handle.
		return tripod;
	}

	//! Tripod with no parent.
	CAT_API gp::GPHnd CAT_CALL dcTripod(const double& scale = 1, const char* name = "")
	{
		return dcTripod(0, scale, name);
	}

	
	// ********************************** Array ********************************
	
	//! Array2D with parent.
	CAT_API gp::GPHnd CAT_CALL dcArray2D(const gp::GPHnd& parent,
										const double* data, 
										const unsigned int& cols, 
										const unsigned int& rows,
										const double& colSize = 0.1,
										const double& rowSize = 0.1,
										const double& height = 1,
										const char* name = "")
	{
		/* Represents a 2D array via a lego-style 3D plot. */
		//GPHnd array2D = dcFrame(parent, 0, 0, 0, 0, 0, 0, "Array2D");
		gp::GPHnd array2D = dcEmpty(parent, "Array2D");

		// Parses the array for max and min.
		double pMax = data[0];
		double pMin = data[0];
		for (unsigned int i = 1; i < rows * cols; i++) {
			if (data[i] > pMax) pMax = data[i];
			if (data[i] < pMin) pMin = data[i];			
		}
		
		// Sets the zero and the scale factor.
		double pScale =	height / (pMax - pMin);
		double pZero = -pMin * pScale;

		// Builds the lego.
		double bOffX = colSize / 2;
		double bOffY = rowSize / 2;
		double bSizeX = colSize * 0.9;
		double bSizeY = rowSize * 0.9;
		
		for (unsigned int y = 0; y < rows; y++) {
			for (unsigned int x = 0; x < cols; x++) {
				double bH = data[y * cols + x] * pScale + pZero;
				double bX = x * colSize + bOffX;
				double bY = y * rowSize + bOffY;
				dcBox(array2D, bX, bY, 0, bSizeX, bSizeY, bH);	
			}
		}
		
		// Return the object handle.
		return array2D;
	}

	//! Array2D with no parent.
	CAT_API gp::GPHnd CAT_CALL dcArray2D(const double* data, 
										const unsigned int& cols, 
										const unsigned int& rows,
										const double& colSize = 0.1,
										const double& rowSize = 0.1,
										const double& height = 1,
										const char* name = "")
	{
		return dcArray2D((gp::GPHnd)0, data, cols, rows, colSize, rowSize, height, name);
	}

}; // End of the class

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
