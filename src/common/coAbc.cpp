//------------------------------------------------------------------------------
// CAT - C++ Analysis Toolkit - Application basic object implementation		  --
// (C) Piero Giubilato 2011-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coAbstract.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"0.2"
// [Modified by]	"Piero Giubilato"
// [cat]			"18 Nov 2024"
// [Language]		"C++"
//______________________________________________________________________________


// STL components.
#include <algorithm>

// Application components - Shared with end User.
#include "console.hpp"

// Application components - Shared between Server and client.
#include "coAbc.hpp"


//##############################################################################
//namespace cat {


// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Ctor.
cat::co::abc::abc() : _myself(0), 
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
//! Dump the object to the standard stream.
//! \brief dump to the console the object status and main properties.
std::ostream& operator<<(std::ostream& os, const cat::co::abc& c)
{
	// Object status.
	os << "Status: " << cat::cl::message();
	switch (c._status) {
		case cat::co::abc::state::abandoned: os << "abandoned"; break;
		case cat::co::abc::state::modified: os << "modified"; break;
		default: os << "unknown";
	}
	os << cat::cl::reset() << " ";
		
	// Object child(s).
	os << "Child: {" << cat::cl::message();
	for (size_t i = 0; i < c._child.size() - 1; i++) { 
		os << cat::cl::message(std::to_string(c._child[i])) << cat::cl::reset() << ",";
	}
	if (c._child.size() > 0)
	os << cat::cl::message(std::to_string(c._child.back())) << cat::cl::reset() << "} ";

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
//gp::scene* GP::owner() const
//{
//	/*! Returns the GP owner handle (the scene containing the GP). */
//	return _ownerPtr;
//}

//______________________________________________________________________________
//void GP::owner(gp::scene* oPtr)
//{
//	/*! Returns the GP owner handle (the scene containing the GP). */
//	_ownerPtr = oPtr;
//}



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
//! Adds a to the object.
//! \brief adds the child identified by \c cID to the object.
//! \argument cID is a \c cat::co::ID identifier for an object belonging to
//!		the same set as the current one.
//! \return 0 if everything fine, otherwise an error code.
int cat::co::abc::childAdd(const cat::co::ID& cID)
{
	_child.push_back(cID);
	return 0;
	// DEBUG: Do we need to notify the child? Or check for multiple parents?
}

//______________________________________________________________________________
int cat::co::abc::childDel(const cat::co::ID& cID)
//! Remove the child \c cID from the object.
//! \brief Remove the \c cID child from the children list.
//!	\argument cID is a cat::co::ID identifier of a cat:co object belonging to
//!		the same set of the current object, and present on the children list. 
//! \return 0 if the child is correctly removed the function return 0, an error
//!		code otherwise.
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
//! Returns the object child(s).
//! \brief returns a vector containing all the object child(s) IDs. If the 
//!		object ha no children,returns an empty vector.
//! \return a vector of cat::co::ID containing all the children IDs. If there
//!		are no children, returns an empty vector.
std::vector<cat::co::ID> cat::co::abc::childGet() const
{
	// Return a copy of the private container.
	return _child;
}

//______________________________________________________________________________
//! Returns the object child(s) count.
//! \brief returns how many children the object has
//! \return a size_t stating how many children are present.
size_t cat::co::abc::childCount() const
{
	//! Returns the number of childs.
	return _child.size();
}
