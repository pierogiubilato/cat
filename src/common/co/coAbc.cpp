//------------------------------------------------------------------------------
// CAT - C++ Analysis Toolkit - Application basic object implementation		  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coAbstract.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.5"
// [Modified by]	"Piero Giubilato"
// [cat]			"21 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// STL components.
#include <algorithm>

// Application components - Shared with end User.
#include "console.hpp"

// Application components - Shared between Server and client.
#include "coAbc.hpp"



// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Ctor.
cat::co::abc::abc(): _ID(0), 
					 _parent(0), 
					_status(cat::co::abc::state::uninitialized)
{


}

//______________________________________________________________________________
//! Dtor.
cat::co::abc::~abc()
{

} 


// *****************************************************************************
// **							  Friend members							  **
// *****************************************************************************

//______________________________________________________________________________
std::ostream& operator<<(std::ostream& os, const cat::co::abc& c)
{

	// Bracketing.
	os << "<";

	// Object IDs
	os << "ID: " << cat::cl::grass(std::to_string(c.id()));
	os << " ptr: " << cat::cl::link() << c.ptrConst() << cat::cl::reset();


	// Object status.
	os << " St: " << cat::cl::message();
	switch (c._status) {
		case cat::co::abc::state::uninitialized: 
			os << cat::cl::yellow("0"); 
			break;
		case cat::co::abc::state::abandoned: 
			os << cat::cl::red("A"); 
			break;
		case cat::co::abc::state::modified: 
			os << cat::cl::cyan("M");
			break;
		case cat::co::abc::state::unchanged:
			os << cat::cl::green("U");
			break;
		default: os << cat::cl::critical("unknown");
	}
	os << cat::cl::reset();

	// Object parent.
	os << " Pr: " << cat::cl::grass(std::to_string(c.parent()));
	
	// Object child(s).
	os << " Ch: {" << cat::cl::message();
	if (c._child.size() > 0) {
		for (size_t i = 0; i < c._child.size() - 1; i++) {
			os << cat::cl::message(std::to_string(c._child[i])) 
				<< cat::cl::reset() << ",";
		}
		os << cat::cl::message(std::to_string(c._child.back())) 
			<< cat::cl::reset() << "}";
	} else {
		os << cat::cl::message("0") << "}";
	}
	
	// Close bracketing.
	os << ">";
	
	// Return the stream.
	return os;
}

// *****************************************************************************
// **							  Public members							  **
// *****************************************************************************



// *****************************************************************************
// **							Family public members						  **
// *****************************************************************************



//______________________________________________________________________________
cat::co::ID cat::co::abc::parent() const
{
	//! Returns the GP parent pointer (if any).
	return _parent;
}

//______________________________________________________________________________
void cat::co::abc::parent(const cat::co::ID& pID)
{
	
   _parent = pID;
	
	// Retrieves and store parent pointer.
	//if (_parentHnd && _ownerPtr) _parentPtr = _ownerPtr->gpGet(_parentHnd);
	//else _parentPtr = NULL;
}

//______________________________________________________________________________

int cat::co::abc::childAdd(const cat::co::ID& cID)
{
	_child.push_back(cID);
	return 0;
	// DEBUG: Do we need to notify the child? Or check for multiple parents?
}

//______________________________________________________________________________
int cat::co::abc::childDel(const cat::co::ID& cID)
{
	// Search the children.
	auto pos = std::find(_child.begin(), _child.end(), cID);
	
	// The children was found.
	if (pos != _child.end()) {
		_child.erase(pos);
		return 0;
	
	// cID children was not found.
	} else {
		return -1;
	}
}

//______________________________________________________________________________
std::vector<cat::co::ID> cat::co::abc::childGet() const
{
	// Return a copy of the private container.
	return _child;
}

//______________________________________________________________________________
size_t cat::co::abc::childCount() const
{
	//! Returns the number of childs.
	return _child.size();
}

//______________________________________________________________________________
cat::co::ID cat::co::abc::id() const
{
	//! Returns the number of childs.
	return _ID;
}

//______________________________________________________________________________
cat::co::abc* cat::co::abc::ptr()
{
	//! Returns the number of childs.
	return this;
}

//______________________________________________________________________________
const cat::co::abc* cat::co::abc::ptrConst() const
{
	//! Returns the number of childs.
	return this;
}
