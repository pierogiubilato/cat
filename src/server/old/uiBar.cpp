//------------------------------------------------------------------------------
// CAT Bar User Interface GUI class											  --
// (C) Piero Giubilato 2011-2013, CERN										  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"uiBar.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"21 Sep 2024"
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
	_group.clear();
	_groupOld.clear();
}

//______________________________________________________________________________
//bar::bar(TwBar* twBar): _TwBar(twBar)
//{
//	/*! Constructor with a TwBar reference. */
//	_group.clear();
//	_groupOld.clear();
//}

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
void bar:cClear()
{
	/*! Clear the TwBar from all components (var, groups, buttons,...) */
//	TwRemoveAllVars(_TwBar);
	_group.clear();
}

//______________________________________________________________________________
void bar::statusSave()
{
	/*! Save the current status (the abstract one, not the one of the underlying 
	 *	TwBar) for later use. The status is saved ONLY if there is at least one
	 *	registered group, otherwise the currently saved status will remain. */
	if (_group.size()) _groupOld = _group;
}

//______________________________________________________________________________
void bar::statusLoad()
{
	/*! Load the saved abstract status. It does NOT apply the loaded status
	 *	to the liked TwBar. To enforce that call StatusSet after this call.
	 *	The load will happen ONLY if a saved status is actually present. */
	if (_groupOld.size()) _group = _groupOld; 
}

//______________________________________________________________________________
void bar::statusGet()
{
	/*! Retrieve the current status of the underlying TwBar. It saves all the 
	 *	present groups and their present status (open, visible, ...). */
	for (size_t i = 0; i < _group.size(); i++) {
//		TwGetParam(_TwBar, _group[i].name.c_str(), "opened", TW_PARAM_INT32, 1, &_group[i].open);	
	}
}

//______________________________________________________________________________
void bar::statusSet()
{
	/*! Apply the last stored status to the underlying TwBar. It tryes to 
	 *	match the stored groups and, in case of matches, put them in the stored
	 *	status (open, active, ...). */
	for (size_t i = 0; i < _group.size(); i++) {
//		TwSetParam(_TwBar, _group[i].name.c_str(), "opened", TW_PARAM_INT32, 1, &_group[i].open);	
	}
}

//______________________________________________________________________________
void bar::statusMatch()
{
	/*! Try to match the status of the current Bar with the saved one. This 
	 *	function does NOT apply the resulting status to the linked TwBar. To
	 *	enforce that call the StatusSet() function after this call. 
	 */
	for (size_t i = 0; i < _groupOld.size(); i++) {
		for (size_t j = 0; j < _group.size(); j++) {
			if (_groupOld[i].name == _group[j].name) {
				_group[j] = _groupOld[i];
			}
		}
	}
}
 
//______________________________________________________________________________
void bar::statusMatch(const bar& ref)
{
	/*! Try to match the status of the current Bar with the one of the passed
	 *	\c bar reference. This function does NOT apply the resulting status to 
	 *	the linked TwBar. To enforce that call the StatusSet() function after 
	 *	this call. 
	 */
	for (size_t i = 0; i < ref._group.size(); i++) {
		for (size_t j = 0; j < _group.size(); j++) {
			if (ref._group[i].name == _group[j].name) {
				_group[j] = ref._group[i];
			}
		}
	}
}

//______________________________________________________________________________
void bar::statusDump()
{
	/*! Dump the current bar status (mostly a debug routine). */
	for (size_t i = 0; i < _group.size(); i++) {
		std::cout << _group[i].name << ": " << _group[i].open << "\n";	
	}
}

//______________________________________________________________________________
void bar::groupAdd(const std::string& name, const int& enable, const int& open)
{
	/*! Add a group to the current bar, setting its name and its status. */
	_group.push_back(barGroup(name, enable, open));
}

//______________________________________________________________________________
void bar::groupAdd(const std::string& name, const int& enable)
{
	/*! Add a group to the current bar, setting its name and its status. */
	_group.push_back(barGroup(name, enable, false));
}

//______________________________________________________________________________
void bar::groupAdd(const std::string& name)
{
	/*! Add a group to the current bar, setting its name and its status. */
	_group.push_back(barGroup(name, true, false));
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
void bar::sortByXY(const std::vector<bar>& barList, std::vector<bar>& barSorted)
{
	/*	Sorts a given \c 'barList' of Bar objects by their x and y position,
	 *	using the western standard of (x <, y <) ordering. Returns the ordered
	 *	list in the \c 'barSorted' vector. Note how the ordered list is added
	 *	to the \c 'barSorted' vector, which hence retains its original content.
	 *	Only NON iconified bars are considered by this routine.
	 */

//	// Position pivots.
//	Uint32* pos	= new Uint32[barList.size() * 2];
//	
//	// Retrieves bars position.
//	for (int i = 0; i < barList.size(); i++) {
////		TwGetParam(barList[i]._TwBar, NULL, "position", TW_PARAM_INT32, 2, &pos[i * 2]);
//	}
//	
//	// Consider the non-iconified and visible bars only.
//	std::vector<int> barIdx;
//	for (int i = 0; i < barList.size(); i++) {
//			
//		// Get bar iconification status.
//		Uint32 icon, visible = 0;
////		TwGetParam(barList[i]._TwBar, NULL, "iconified", TW_PARAM_INT32, 1, &icon);
////		TwGetParam(barList[i]._TwBar, NULL, "visible", TW_PARAM_INT32, 1, &visible);
//		
//		// Bar is on full display, consider it!
//		if (!icon && visible) {
//			//std::cout << "Added bar TwIdx: " << i << "\n";
//			barIdx.push_back(i);
//		}
//	}
//
//	// Orders the bar by left-top order.
//	bool swapped = true;
//	while (swapped) {
//		
//			// Reset swapping.
//			swapped = false;
//		
//			// Swapping cycle
//			for (int i = 1; i < barIdx.size(); i++) {
//			
//				// Get references.
//				int xA = barIdx[i - 1] * 2 + 0; int yA = barIdx[i - 1] * 2 + 1;
//				int xB = barIdx[i] * 2 + 0; int yB = barIdx[i] * 2 + 1;
//		
//				// Check and swap in case.
//				if ((pos[xA] > pos[xB]) || (pos[xA] == pos[xB] && pos[yA] > pos[yB])) {
//					int swap = barIdx[i];
//					barIdx[i] = barIdx[i - 1];
//					barIdx[i - 1] = swap;
//					swapped = true;
//				}
//		}
//	}
//
//	// Fills the output vector.
//	for (unsigned int i = 0; i < barIdx.size(); i++) barSorted.push_back(barList[barIdx[i]]); 
}
		
// #############################################################################
}} // Close namespaces
