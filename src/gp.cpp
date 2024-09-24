//------------------------------------------------------------------------------
// Graphic Primitives (GP) base class for the CAT application				  --
// (C) Piero Giubilato 2021-2025, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gp.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"24 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

// Application components
#include "gp.h"

// This is to (forward) handle the family/ownership functions.
#include "gpScene.h"

// These are for the object factory, order IS important!
#include "gpStroked.h"
#include "gpFilled.h"
#include "gpFonted.h"
#include "gpEmpty.h"
//#include "pear_gp_Material.h"
#include "gpFrame.h"
#include "gpPoint.h"
//#include "pear_gp_Line.h"
//#include "pear_gp_Polygon.h"
#include "gpBox.h"	
//#include "pear_gp_Tube.h"
//#include "pear_gp_Sphere.h"
//#include "pear_gp_Label.h"


//##############################################################################
namespace cat { namesppace gp {


// *****************************************************************************
// **								Static members							  **
// *****************************************************************************

	// Selection static constants. Define the appearance of lines in selection 
	// mode.
	float GP::_selColor[4] = {1, 1, 1, 1};
	float GP::_selWidth = 3;
	uint16_t GP::_selPattern = 255;
	uint32_t GP::_selFactor = 1;
		


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
GP::GP()
{
	/*! GP (Graphic Primitive) is the root object for all the PEAR graphic
	 *	primitives intended for drawing. It contains the default properties 
	 *  shared by every primitive, plus the management for the "family ties" 
	 *  and other related tasks.
	 */
	init(0, 0);
}

//______________________________________________________________________________
GP::~GP()
{
	/*! Destructor	*/
	
	// Kills all the childs!
	//for (uint32_t i = 0; i < _Child.size(); i++) delete _SPtr[_Child[i]];
} 


// *****************************************************************************
// **							  Private members							  **
// *****************************************************************************

//______________________________________________________________________________
void GP::init(scene* owner, gp::GPHnd pHnd)
{
	// Basic properties.
	_ownerPtr = owner;
	parent(pHnd);	// This sets both parent Handle and Pointer in case of owner.
	_name = new char[2]; strcpy(_name, "");
	_info = new char[2]; strcpy(_info, "");
		
	// Family (Minimize occupation by reserving no space).
	_childHnd.clear();
	_childHnd.reserve(0);

	// Mode.
	_modeVisible = true;
	_modeFrozen = false;
	_modeWire = false;
	_modeSelected = false;		// This one is NOT streamed.
	_modeParsed = false;		// This one is NOT streamed.
	_modeExpanded = false;		// This one is NOT streamed.
	_modeNeedRedraw = false;	// This one is NOT streamed.

	// Inheritance.
	_inhrAppear = true;
	_inhrVisible = true;
	_inhrAlpha = true;
	_inhrWire = true;
	_inhrRef = true;

	// Server side only
	#ifdef CAT_SERVER
//		_glDspListIdx = 0;	//!< Clear the GP associated dDisplayList.
	#endif
}

//______________________________________________________________________________
gp::GPPos GP::offset(const gp::GPDim& dim, const int& alignment)	const
{
	/*! Simply calculates the offset necessary to align a bounding box of
	 *	dimensions \c dim accordingly to the \c alignment parameter passed.
	 *	Coordinates orientation is the standard Argand-Gauss one.
	 */

	// Preset result.
	gpPos result = {0, 0, 0};						
	
	// Calculates offset.
	if (alignment & kal::horLeft)	result.x = 0;
	if (alignment & kal::horRight) result.x = - dim.x;
	if (alignment & kal::horMid)	result.x = - dim.x / 2;
	if (alignment & kal::verTop)	result.y = + dim.y;
	if (alignment & kal::verBottom) result.y = 0;
	if (alignment & kal::verMid)	result.y = + dim.y / 2;
	if (alignment & kal::null)		{result.x = 0; result.y = dim.y /2;}

	// Done.
	return result;
}


// *****************************************************************************
// **							Special public members						  **
// *****************************************************************************

//______________________________________________________________________________
gp::GP* GP::build(const uint64_t& type) const
{
	/*! Build a GP by its type. This call allows to build a specific object with
	 *	no more knowledge about it except the type of GP. If the provided \c type
	 *	does not exist, returns a NULL pointer, otherwise a pointer to the new
	 *	object.
	 */
   
	// Create it!
	switch (type) {
	case cat::CO::oType::stroked: return new gp::stroked();
	case cat::CO::oType::filled:	return new gp::filled();
		case cat::CO::oType::fonted:	return new gp::fonted();
		case cat::CO::oType::scene:	return new gp::scene();
		case cat::CO::oType::empty:	return new gp::empty();
		case cat::CO::oType::material: return new gp::Material();
		case cat::CO::oType::frame:	return new gp::frame();
		case cat::CO::oType::point:	return new gp::point();
		case cat::CO::oType::line:	return new gp::line();
		case cat::CO::oType::polygon: return new gp::polygon();
		case cat::CO::oType::box:	return new gp::box();
		case cat::CO::oType::tube:	return new gp::tube();
		case cat::CO::oType::cylinder: return new gp::cylinder();
		case cat::CO::oType::cone:	return new gp::cone();
		case cat::CO::oType::sphere: return new gp::sphere();
		case cat::CO::oType::gpLabel: return new gp::label();
	}

	// Not recognized type!
	return NULL;
}


// *****************************************************************************
// **							Family public members						  **
// *****************************************************************************

//______________________________________________________________________________
gp::scene* GP::owner() const
{
	/*! Returns the GP owner handle (the scene containing the GP). */
	return _OwnerPtr;
}

//______________________________________________________________________________
void GP::owner(gp::scene* oPtr)
{
	/*! Returns the GP owner handle (the scene containing the GP). */
	_ownerPtr = oPtr;
}

//______________________________________________________________________________
GPHnd GP::parent() const
{
	/*! Returns the GP parent handle (if any). */
	return _parentHnd;
}

//______________________________________________________________________________
void GP::parent(GPHnd pHnd)
{
	/*! Sets the GP parent handle and retrieve its pointer if available. */
   _parentHnd = pHnd;
	
	// Retruieves and store parent pointer.
	if (_parentHnd && _ownerPtr) _parentPtr = _ownerPtr->gpGet(_parentHnd);
	else _parentPtr = NULL;
}

//______________________________________________________________________________
bool GP::childAdd(GPHnd cHnd)
{
	/*! Adds the child \c cHnd to the GP. \c cHnd is the scene handle of the
	 *	child GP. Returns false if everything ok, true on error.
	 */
	_childHnd.push_back(cHnd); 
	return false;
}

//______________________________________________________________________________
bool GP::childDel(GPHnd cHnd)
{
	/*! Remove the child \c cHnd from the GP. If no \c cHnd is found in the child
	 *	list, no child is actually removed and the call returns true. If the
	 *	child is correctly removed the function return false.
	 */

	// Search the handle.
	uint64_t cIdx = 0;
	for (cIdx = 0; cIdx < _childHnd.size(); cIdx++) if (_childHnd[cIdx] == cHnd) break;

	// Removes and exit.
	if (cIdx < _childHnd.size()) {
		_childHnd.erase(_childHnd.begin() + cIdx);
		return false; 

	// Not found, exit with warning.
	} else return true;
	
}

//______________________________________________________________________________
GPHnd GP::childGet(int cIdx) const
{
	/*! Returns the handle to the \c cIdx th child of the GP. If \c cIdx is
	 * out of range returns 0.
	 */
	if (cIdx < _childHnd.size()) return _childHnd[cIdx];
	else return 0;
}

//______________________________________________________________________________
GPHnd GP::childCount() const
{
	/*! Returns the number of childs. */
	return _childHnd.size();
}


// *****************************************************************************
// **						  Default CO public members						  **
// *****************************************************************************

//______________________________________________________________________________
GPHnd GP::handle() const
{
	/*! Returns GP Handle. */
	return _handle;
}

//______________________________________________________________________________
void GP::handle(GPHnd Hnd)
{
	/*! Returns GP Handle. */
   _handle = Hnd;
}

//______________________________________________________________________________
CO::oType GP::type() const
{
	/*! Returns object type. This function MUST be overloaded to differentiate 
	 *	any derived class! 
	 */
   return CO::oType::gpBase;
}

//______________________________________________________________________________
uint64_t GP::version() const
{
	/*! Returns object version. This function MUST be overloaded to differentiate 
	 *	any derived class! Version numbering is made in unit of hundreds for the
	 *	major and decimal for the subversions. So version 2.0 is 200.
	 */
   return 100;
}

//______________________________________________________________________________
std::string GP::stem() const
{
	/*! Returns the object stem, i.e. the class stem. MUST be overloaded */
   return "Null";
}

//______________________________________________________________________________
size_t GP::size(const bool& dynamic) const 
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = 0; // GO::Size(true);
	tSize += sizeof(char) * (std::strlen(_name) + 1);
	tSize += sizeof(char) * (std::strlen(_info) + 1);
	tSize += sizeof(GPHnd) * _childHnd.capacity();

	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	
}

//______________________________________________________________________________
void GP::dump(const int& ind) const
{
 	/*! Dumps on the standard output the relevant GP properties. */

	// Quick out definitions.
	#define CD COL(DEFAULT)
	#define CLW COL(LWHITE)

	// Set paddings.
	std::string pad(ind, ' ');
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');

	// Ouput info
	std::cout << pad << "<" << COL(CAT_DUMP_COL_TYPE) << stem() << CD << ">" << "\n"
	
	// Handles.
	<< pad2 << "Handles ["
			<< "Name: "	<< COL(CAT_DUMP_COL_NAME) << name() << CD << ", "
			<< "Hnd: "	<< COL(CAT_DUMP_COL_HANDLE) << handle() << CD << ", "
			<< "Owner: " << COL(CAT_DUMP_COL_PARENT) << owner() << CD << ", "
			<< "Parent: " << COL(CAT_DUMP_COL_PARENT) << parent() << CD << "]\n"
	
	// Appearance status.
	<< pad2 << "Status ["
			<< "Visi: " << CLW << _modeVisible << CD << ", "
			<< "Wire: " << CLW << _modeWire << CD << ", "	
			<< "Froz: " << CLW << _modeFrozen << CD << ", "	
			<< "Sel: " << CLW << _modeSelected << CD << ", "
			<< "Par: " << CLW << _modeParsed << CD << ", "
			<< "Exp: " << CLW << _modeExpanded << CD << "]\n"

	// Inheritance status.
	<< pad2 << "Inheritance ["
			<< "Global: "<< CLW << _inhrAppear << CD << ", "	
			<< "Visi: "	<< CLW << _inhrVisible << CD << ", "	
			<< "Alpha: " << CLW << _inhrAlpha << CD << ", "	
			<< "Wire: "	<< CLW << _inhrWire << CD << ", "
			<< "Ref: " << CLW << _inhrRef << CD << "]\n";
	
	// Childrens.
	if (childCount()) {
		std::cout << pad2 << "Childs [";		
		for (uint64_t i = 0; i < childCount(); i++) {
			std::cout << COL(CAT_DUMP_COL_CHILD) << _childHnd[i] << CD << "\n";
			if (i < childCount() - 1) std::cout << ", ";
		}
		std::cout << pad2 << "]\n";
	}

	// Release definitions
	#undef CD
	#undef CLW
}

//______________________________________________________________________________
bool GP::stream(std::stringstream& o, const bool& read)
{
	/*! Adds the current GP into the \c o stream (when \c Read = false) or load 
	 *	the GP from the \c o stream (when \c Read = true). 
	 */
	
	// Version/Type check.
	if (read) {
				
		// Check type and version consistency
		uint64_t typeCheck = 0;
		uint64_t versionCheck = 0;
		af::stream::read(o, typeCheck); 
		if (typeCheck != type()) {
			throw std::runtime_error("cat::GP::stream uncorrect Type!");
		}
		af::stream::read(o, versionCheck); 
		if (versionCheck != version()) {
			throw std::runtime_error("cat::GP::Stream uncorrect Version!");
		}
	
	// Write type and version for later checking.
	} else {
		af::stream::write(o, type());
		af::stream::write(o, version());		
	}			

	// Read/Write all the GP properties from/into the stream.
	
	// General.
	af::stream::RW(o, _handle, read);
	af::stream::RW(o, _parentHnd, read);
	af::stream::RW(o, _name, read);
	af::stream::RW(o, _info, read);

	// Style.
	af::stream::RW(o, _modeVisible, read);
	af::stream::RW(o, _modeWire, read);
	af::stream::RW(o, _modeFrozen, read);
	af::stream::RW(o, _modeSelected, read);

	// Inheritance.
	af::stream::RW(o, _inhrAppear, read);
	af::stream::RW(o, _inhrVisible, read);
	af::stream::RW(o, _inhrAlpha, read);
	af::stream::RW(o, _inhrWire, read);
	af::stream::RW(o, _inhrRef, read);

	// Everything fine!
	return false;
}



// *****************************************************************************
// **						Default GP public members						  **
// *****************************************************************************

//______________________________________________________________________________
const char* GP::name() const 
{
	/*! Returns the GP name. */
	return _name;
}

//______________________________________________________________________________
void GP::name(const char* name)
{
	/*! Sets the GP name. */
	
	// Auto naming in case
	std::stringstream pivot("");
	if (!name) pivot << stem() << " " << handle();		
	else pivot << name;
	
	// Updates the name.
	delete[] _name;
	_name = new char[pivot.str().size() + 1];
	strcpy(_name, pivot.str().c_str());
		
	// Set modified status.
	modeNeedRedraw(true);
}

//______________________________________________________________________________
const char* GP::info() const 
{
	/*! Returns the GP info. */
	return _info;
}

//______________________________________________________________________________
void GP::info(const char* info)
{
	/*! Sets the GP info. */
	
	// Auto naming in case
	std::stringstream pivot("");
	if (!info) pivot << "";		
	else pivot << info;
	
	// Updates the name.
	delete[] _Info;
	_info = new char[pivot.str().size() + 1];
	strcpy(_info, pivot.str().c_str());
		
	// Set modified status.
	modeNeedRedraw(true);
}

//______________________________________________________________________________
bool GP::modeSelected() const
{
	/*! Return the selection status of the GP. */
	return _modeSelected;
}

//______________________________________________________________________________
void GP::modeSelected(const bool& sel)
{
	/*! Selects a GP and propagates the selection to any children sharing any
	 *	sort of inheritance relationship. */

	// Self selection.
	_modeSelected = sel;

	// Propagates to all childrens.
	for (uint64_t i = 0; i < _childHnd.size(); i++) {
		GP* child =	_ownerPtr->gp_Get(_childHnd[i]);
		if (child) child->modeSelected(sel);
	}
		
	// Set modified status.
	modeNeedRedraw(true);
}

//______________________________________________________________________________
bool GP::modeVisible() const
{
	/*! Return the visibility status of the GP. It is hierarchical. */
	if (_inhrAppear && _inhrVisible && _ParentPtr) {
		return _ParentPtr->modeVisible() && _modeVisible; 
		
	// No inheritance enabled.
	} else {
		return _modeVisible;
	}
}

//______________________________________________________________________________
void GP::modeVisible(const bool& visible)
{	
	/*! Sets the visible status of the GP. */
	_modeVisible = visible;
	
	// Set modified status.
	modeNeedRedraw(true);
}

//______________________________________________________________________________
bool GP::modeWireframe() const
{
	/*! Return the frozeness status of the GP. */
	return _modeWire;
}

//______________________________________________________________________________
void GP::modeWireframe(const bool& wireframe)
{
	/*! Sets the frozeness status of the GP. */
	_modeWire = wireframe;
	
	// Set modified status.
	modeNeedRedraw(true);
}

//______________________________________________________________________________
bool GP::modeFrozen() const
{
	/*! Return the frozeness status of the GP. */
	return _modeFrozen;
}

//______________________________________________________________________________
void GP::modeFrozen(const bool& frozen)
{
	/*! Sets the frozeness status of the GP. */
	_modeFrozen = frozen;
}

//______________________________________________________________________________
bool GP::modeParsed() const
{
	/*! Return the parsed status of the GP. */
	return _modeParsed;
}

//______________________________________________________________________________
void GP::modeParsed(const bool& parsed)
{
	/*! Sets the parsed status of the GP. */
	_modeParsed = parsed;
}

//______________________________________________________________________________
bool GP::modeExpanded() const
{
	/*! Return the expanded status of the GP. */
	return _modeExpanded;
}

//______________________________________________________________________________
void GP::modeExpanded(const bool& expanded)
{
	/*! Sets the expanded status of the GP. */
	_modeExpanded = expanded;
}

//______________________________________________________________________________
bool GP::modeNeedRedraw() const
{
	/*! Return the changed status of the GP. */
	return _modeNeedRedraw;
}

//______________________________________________________________________________
void GP::modeNeedRedraw(const bool& need)
{
	/*! Sets the changed status of the GP. */
	_modeNeedRedraw = need;

	// Only if true propagate to the parent and the owner.
	if (need) {
		if (_parentPtr)	{
			_parentPtr->modeNeedRedraw(true); 
		} else {
			if (_ownerPtr) _ownerPtr->modeNeedRedraw(true);
		}
	}
}

//______________________________________________________________________________
bool GP::inhrAppear() const
{
	/*! Return gloabl appearance inheritance. */
	return _inhrAppear;
}

//______________________________________________________________________________
void GP::inhrAppear(const bool& inhr)
{
	/*! Return gloabl appearance inheritance. */
	_inhrAppear = inhr;
}

//______________________________________________________________________________
bool GP::inhrVisible() const
{
	/*! Return visibility inheritance. */
	return _inhrVisible;
}

//______________________________________________________________________________
void GP::inhrVisible(const bool& inhr)
{
	/*! Return visibility inheritance. */
	_inhrVisible = inhr;
}

//______________________________________________________________________________
bool GP::inhrAlpha() const
{
	/*! Return alpha channel inheritance. */
	return _inhrAlpha;
}

//______________________________________________________________________________
void GP::inhrAlpha(const bool& inhr)
{
	/*! Sets alpha channel inheritance. */
	_inhrAlpha = inhr;
}

//______________________________________________________________________________
bool GP::inhrWire() const
{
	/*! Return wireframe mode inheritance. */
	return _inhrWire;
}

//______________________________________________________________________________
void GP::inhrWire(const bool& inhr)
{
	/*! Sets wireframe mode inheritance. */
	_inhrWire = inhr;
}

//______________________________________________________________________________
bool GP::inhrRef() const
{
	/*! Return reference frame inheritance. */
	return _inhrRef;
}

//______________________________________________________________________________
void GP::inhrRef(const bool& inhr)
{
	/*! Sets reference frame inheritance. */
	_inhrRef = inhr;
}

// ************************* EXPERIMENTAL

//______________________________________________________________________________
bool GP::modeGet(const uint8_t& flag) const
{
	/*! Retrieves the status of the \c flag argument. */
	return _modeStore & flag;
}

//______________________________________________________________________________
void GP::modeSet(const uint8_t& flag, const bool& status)
{
	/*! Sets the GP status of the \c flag mode. */
	status ? _modeStore |= flag : _modeStore &= ~flag;
}
// *** *********************


// *****************************************************************************
// **					Drawing functions, SERVER ONLY						  **
// *****************************************************************************

// Drawing function are available only for the SERVER.
#ifdef PEAR_SERVER

//______________________________________________________________________________
double GP::glAlpha()
{
	/*! Returns if the gp has any kind of transparency in its constituent
	 *	elements (color, material, brush, ...). The function is hierarchical:
	 *	it digs through all the parents chain to sum up the whole result.
	 */
	
	// Get hierarchical alpha.
	double pAlpha = 1;
	if (_inhrAppear && _inhrAlpha && _parentPtr) {
		pAlpha = _parentPtr->glAlpha();
	}

	//  The basic GP has alpha = 1, so simply pass the parent alpha in case.
	return  pAlpha;
}

//______________________________________________________________________________
void GP::glTrsfApply()
{
	/*! Apply a GP Trsf (MUST be overloaded for those GPs which actually carry
	 *	any transformation). The function is hierarchical: it digs through all 
	 *	the parents chain to sum up the whole result.
	 *	Actually the basic GP class is not applying any transformation, so do
	 *	nothing here! In case of an appropriate overload, this call will make
	 *	it effective through all the family chain.
	 */

	// Transfer to parent.
	if (_ownerPtr) {
		GP* pPtr = _ownerPtr->gpGet(_parentHnd);
		if (pPtr) pPtr->glTrsfApply();  
	}
}

//______________________________________________________________________________
void GP::glTrsfReset()
{
	/*! Reset a GP Trsf (MUST be overloaded for those GPs which actually carry
	 *	any transformation). The function is hierarchical: it digs through all 
	 *	the parents chain to sum up the whole result.
	 *	Actually the basic GP class is not applying any transformation, so do
	 *	nothing here! In case of an appropriate overload, this call will make
	 *	it effective through all the family chain.
	 */

	// Transfer to parent.
	if (_ownerPtr) {
		GP* pPtr = _ownerPtr->gpGet(_parentHnd);
		if (pPtr) pPtr->glTrsfReset();  
	}
}

//______________________________________________________________________________
void GP::glDisplay()
{
	/*! Actually send to the OpenGL state machine the object to be drawn. If
	 *	a display list is available, use it, otherwise simply call the glDraw
	 *	function of the derived GP (this to allow for not using Display Lists
	 *	for very simple objects or while in selection mode).	
	 */

	// Update the name stack. (actually effective in selection mode only).
	glPushName((GLuint)_handle); 
		
	// If the object is actually selected, do not build the display list,
	// but directly draw it, as it can change from draw to draw 
	if (_modeSelected) {

		// Delete the existing list in case, so at the selection period end
		// a new one will be automatically regenerated.
		if (_glDspListIdx) {
			glDeleteLists(_glDspListIdx, 1);
			_glDspListIdx = 0;
		}

		// Draw the object and its selection..
		glDrawSel(); glDrawEnd();
		glDraw(); glDrawEnd();	

	// Fast redraw. If the display list has not already been build builds it,
	// then just displays the list.
	} else {
		if (!_glDspListIdx) glBuild();
		glCallList(_glDspListIdx);
	}

	// Take away the name used for the name stack.
	glPopName();
}

//______________________________________________________________________________
void GP::glBuild()
{
	/*! Manages the display list which contains the OpenGL list of commands
	 *	necessary to render the object. This function, as well as glDisplay,
	 *	should not be overloaded by derived objects, as only glDraw is the
	 *	place where the actual construction of the object is implemented.
	 *	This function has to be called to make any property change effective
	 *	for all objects which use the Display Lists mechanism.
	 */

	// If a list for this object has already been created, remove it.
	if (_glDspListIdx) glDeleteLists(_glDspListIdx, 1);
	
	// Obtains a new list index.
	_glDspListIdx = glGenLists(1);
	
	// Creates the list, but do not display it.
	glNewList(_glDspListIdx, GL_COMPILE);

	// This will call the overloaded glDraw of the derived GP.
	// The glDrawEnd() call is mandatory to properly complete.
	glDraw();
	glDrawEnd();

	// Close the list.
	glEndList();

	// Now the list is saved in memory and ready to be used. Bye!
}

//______________________________________________________________________________
void GP::glDrawSel()
{
	/*! The glDrawSel draws a specific selection "skeleton" to highlight the 
	 *	selected object. Each GP should provide its own specialized glDrawSel 
	 *	overload, aas no basic one is implemented.
	 */

	// Get transformation chain applied.
	glTrsfApply();

	// Set stroke accordingly to the selection static parameters.
	glLineWidth(_selWidth);
	glLineStipple(_selFactor, _selPattern);
	glEnable(GL_LINE_STIPPLE);
}

//______________________________________________________________________________
void GP::glDraw()
{
	/*! Sets all the drawing properties common for all GPs. The _drw* variables
	 *	are class member which could be used by childrens to influence their
	 *	own appearance, so they are stored until the next call to the function.
	 */
								  
	// Get transformation chain applied.
	glTrsfApply();

	// Enable wireframe mode. 
	if (modeWireframe()) {
		glDisable(GL_CULL_FACE);	// Disable non-drawing of deeper objects.
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Only Render Lines.
	
	// Enable default mode.
	} else { 
		glEnable(GL_CULL_FACE);		// Enable non-drawing of deeper objects.
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Render Solids.
	}
}

//______________________________________________________________________________
void GP::glDrawEnd()
{
	/*! Resets the OpenGL drawing pipeline to the condition before the call
	 *	to the glDraw() member. This member MUST ALWAYS be called at the end
	 *	of the topmost GP doing the draw, this way actually being the latest
	 *	drawing action performed for the object.
	 */

	// Reset frame trasformations in case.
	glTrsfReset();	
}


// *****************************************************************************
// **						  UI functions, SERVER ONLY						  **
// *****************************************************************************

//______________________________________________________________________________
void TW_CALL GP::cbkSizeGet(void* value, void* client)
{
	/*! Get the layout mode. */
	*static_cast<uint32_t*>(value) = static_cast<GP*>(client)->size();
}

//______________________________________________________________________________
void GP::uiBarLoad(ui::Bar& bar)
{
	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
	 *	the GP. This member should be overloaded to change/add the properties
	 *	shown on the properties bar by every GP.
	 */
/*
	// Retrieve the TwBarr associated with the owner uiBar.
	TwBar* twBar = bar._TwBar;

	// Id.
	bar.GroupAdd("Id");
	TwAddVarRO(twBar, "iHandle", TW_TYPE_UINT32, &_Handle, "label='Handle' group='Id'");
	TwAddVarRO(twBar, "iParent", TW_TYPE_UINT32, &_ParentHnd, "label='Parent' group='Id'");
	//TwAddVarRW(twBar, "iName", TW_TYPE_STDSTRING, &_Name, "label='Name' group='Id'");
	//TwAddVarRW(twBar, "iInfo", TW_TYPE_STDSTRING, &_Info, "label='Info' group='Id'");
	TwAddVarCB(twBar, "iMemory", TW_TYPE_UINT32, NULL, GP::cbkSizeGet, this, "label='Size (bytes)' group='Id'");
	
	// Mode.
	bar.GroupAdd("Mode");
	TwAddVarRW(twBar, "modeVisible", TW_TYPE_BOOLCPP, &_modeVisible, "label='Visible' group='Mode'");
	TwAddVarRW(twBar, "modeSelected", TW_TYPE_BOOLCPP, &_modeSelected, "label='Selected' group='Mode'");
	TwAddVarRW(twBar, "modeFrozen", TW_TYPE_BOOLCPP, &_modeFrozen, "label='Frozen' group='Mode'");
	TwAddVarRW(twBar, "modeWireframe", TW_TYPE_BOOLCPP, &_modeWire, "label='Wireframe' group='Mode'");

	// Inheritance properties.
	bar.GroupAdd("Inheritance");
	TwAddVarRW(twBar, "inhrAppearance", TW_TYPE_BOOLCPP, &_inhrAppear, "label='Enable inheritance' group='Inheritance'");
	TwAddVarRW(twBar, "inhrVisible", TW_TYPE_BOOLCPP, &_inhrVisible, "label='Inherit visibilty' group='Inheritance'");
	TwAddVarRW(twBar, "inhrAlpha", TW_TYPE_BOOLCPP, &_inhrAlpha, "label='Inherit alpha channel' group='Inheritance'");
	TwAddVarRW(twBar, "inhrWireframe", TW_TYPE_BOOLCPP, &_inhrWire, "label='Inherit wireframe' group='Inheritance'");
	TwAddVarRW(twBar, "inhrReference", TW_TYPE_BOOLCPP, &_inhrRef, "label='Inherit reference' group='Inheritance'");
*/
}

// End of PEAR_SERVER if.
#endif

// #############################################################################
}} // Close Namespace
