//------------------------------------------------------------------------------
// CAT Bar User Interface GUI class											  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiBar.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"08 Aug 2012"
// [Language]		"C++"
//______________________________________________________________________________

// Application components
#include "uiBar.h"


// #############################################################################
namespace cat { namespace ui {

// *****************************************************************************
// **							  Static Members							  **
// *****************************************************************************

// *****************************************************************************
// **							  Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
bar::bar() //: _TwBar(0)
{
	/*! Default ctor. */
	_Group.clear();
	_GroupOld.clear();
}

//______________________________________________________________________________
bar::bar(TwBar* twBar): _TwBar(twBar)
{
	/*! Constructor with a TwBar reference. */
	_Group.clear();
	_GroupOld.clear();
}

//______________________________________________________________________________
bar::~bar() 
{
	/*! Realeses all allocated resources. */
	// Nothing to do here at the moment.		
}


// *****************************************************************************
// **								Private Members							  **
// *****************************************************************************

// *****************************************************************************
// **								Public Members							  **
// *****************************************************************************

//______________________________________________________________________________
void bar::Clear()
{
	/*! Clear the TwBar from all components (var, groups, buttons,...) */
//	TwRemoveAllVars(_TwBar);
	_Group.clear();
}

//______________________________________________________________________________
void bar::StatusSave()
{
	/*! Save the current status (the abstract one, not the one of the underlying 
	 *	TwBar) for later use. The status is saved ONLY if there is at least one
	 *	registered group, otherwise the currently saved status will remain. */
	if (_Group.size()) _GroupOld = _Group;
}

//______________________________________________________________________________
void bar::StatusLoad()
{
	/*! Load the saved abstract status. It does NOT apply the loaded status
	 *	to the liked TwBar. To enforce that call StatusSet afther this call.
	 *	The load will happen ONLY if a saved status is actually present. */
	if (_GroupOld.size()) _Group = _GroupOld; 
}

//______________________________________________________________________________
void bar::StatusGet()
{
	/*! Retrieve the current status of the underlying TwBar. It saves all the 
	 *	present groups and their present status (open, visible, ...). */
	for (size_t i = 0; i < _Group.size(); i++) {
//		TwGetParam(_TwBar, _Group[i].name.c_str(), "opened", TW_PARAM_INT32, 1, &_Group[i].open);	
	}
}

//______________________________________________________________________________
void bar::StatusSet()
{
	/*! Apply the last stored status to the underlying TwBar. It tryes to 
	 *	match the stored groups and, in case of matches, put them in the stored
	 *	status (open, active, ...). */
	for (size_t i = 0; i < _Group.size(); i++) {
//		TwSetParam(_TwBar, _Group[i].name.c_str(), "opened", TW_PARAM_INT32, 1, &_Group[i].open);	
	}
}

//______________________________________________________________________________
void bar::StatusMatch()
{
	/*! Try to match the status of the current Bar with the saved one. This 
	 *	function does NOT apply the resulting status to the linked TwBar. To
	 *	enforce that call the StatusSet() function after this call. 
	 */
	for (size_t i = 0; i < _GroupOld.size(); i++) {
		for (size_t j = 0; j < _Group.size(); j++) {
			if (_GroupOld[i].name == _Group[j].name) {
				_Group[j] = _GroupOld[i];
			}
		}
	}
}
 
//______________________________________________________________________________
void bar::StatusMatch(const Bar& ref)
{
	/*! Try to match the status of the current Bar with the one of the passed
	 *	\c bar reference. This function does NOT apply the resulting status to 
	 *	the linked TwBar. To enforce that call the StatusSet() function after 
	 *	this call. 
	 */
	for (size_t i = 0; i < ref._Group.size(); i++) {
		for (size_t j = 0; j < _Group.size(); j++) {
			if (ref._Group[i].name == _Group[j].name) {
				_Group[j] = ref._Group[i];
			}
		}
	}
}

//______________________________________________________________________________
void bar::StatusDump()
{
	/*! Dump the current bar status (mostly a debug routine). */
	for (size_t i = 0; i < _Group.size(); i++) {
		std::cout << _Group[i].name << ": " << _Group[i].open << "\n";	
	}
}

//______________________________________________________________________________
void bar::GroupAdd(const std::string& name, const int& enable, const int& open)
{
	/*! Add a group to the current bar, setting its name and its status. */
	_Group.push_back(BarGroup(name, enable, open));
}

//______________________________________________________________________________
void bar::GroupAdd(const std::string& name, const int& enable)
{
	/*! Add a group to the current bar, setting its name and its status. */
	_Group.push_back(BarGroup(name, enable, false));
}

//______________________________________________________________________________
void bar::GroupAdd(const std::string& name)
{
	/*! Add a group to the current bar, setting its name and its status. */
	_Group.push_back(BarGroup(name, true, false));
}


//______________________________________________________________________________
//TwBar* bar::PickTop()
//{
//	/*	Pick the current top bar, avoiding non visible or iconified bars. If no
//	 *	one bar has currently the focus, return a null pointer.
//	 */
//
//	// Gets the currently targeted bar (but avoids the help bar or the spot bar).
////	TwBar* bar = TwGetTopBar();
//	if (!bar) return 0;	
//
//	// Checks if visible and not iconified.
//	Uint32 icon, visible = 0;
////	TwGetParam(bar, NULL, "iconified", TW_PARAM_INT32, 1, &icon);
////	TwGetParam(bar, NULL, "visible", TW_PARAM_INT32, 1, &visible);
//		
//	// Bar is on full display, get it!
//	if (!icon && visible) return bar;
//	
//	// No top bar available, return 0;
//	return 0;
//}

//______________________________________________________________________________
void bar::SortByXY(const std::vector<Bar>& barList, std::vector<Bar>& barSorted)
{
	/*	Sorts a given \c 'barList' of Bar objects by their x and y position,
	 *	using the western standard of (x <, y <) ordering. Returns the ordered
	 *	list in the \c 'barSorted' vector. Note how the ordered list is added
	 *	to the \c 'barSorted' vector, which hence retains its original content.
	 *	Only NON iconified bars are considered by this routine.
	 */

	// Position pivots.
	Uint32* pos	= new Uint32[barList.size() * 2];
	
	// Retrieves bars position.
	for (int i = 0; i < barList.size(); i++) {
//		TwGetParam(barList[i]._TwBar, NULL, "position", TW_PARAM_INT32, 2, &pos[i * 2]);
	}
	
	// Consider the non-iconified and visible bars only.
	std::vector<int> barIdx;
	for (int i = 0; i < barList.size(); i++) {
			
		// Get bar iconification status.
		Uint32 icon, visible = 0;
//		TwGetParam(barList[i]._TwBar, NULL, "iconified", TW_PARAM_INT32, 1, &icon);
//		TwGetParam(barList[i]._TwBar, NULL, "visible", TW_PARAM_INT32, 1, &visible);
		
		// Bar is on full display, consider it!
		if (!icon && visible) {
			//std::cout << "Added bar TwIdx: " << i << "\n";
			barIdx.push_back(i);
		}
	}

	// Orders the bar by left-top order.
	bool swapped = true;
	while (swapped) {
		
			// Reset swapping.
			swapped = false;
		
			// Swapping cycle
			for (int i = 1; i < barIdx.size(); i++) {
			
				// Get references.
				int xA = barIdx[i - 1] * 2 + 0; int yA = barIdx[i - 1] * 2 + 1;
				int xB = barIdx[i] * 2 + 0; int yB = barIdx[i] * 2 + 1;
		
				// Check and swap in case.
				if ((pos[xA] > pos[xB]) || (pos[xA] == pos[xB] && pos[yA] > pos[yB])) {
					int swap = barIdx[i];
					barIdx[i] = barIdx[i - 1];
					barIdx[i - 1] = swap;
					swapped = true;
				}
		}
	}

	// Fills the output vector.
	for (unsigned int i = 0; i < barIdx.size(); i++) barSorted.push_back(barList[barIdx[i]]); 
}
		
// #############################################################################
}} // Close namespaces
