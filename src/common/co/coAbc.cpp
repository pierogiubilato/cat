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
#include "coStream.hpp"



// *****************************************************************************
// **								Special members							  **
// *****************************************************************************

//______________________________________________________________________________
//! Default Ctor.
cat::co::abc::abc() : _owner(nullptr), _oId(0),_parent(0),
					  _status(cat::co::abc::state::uninitialized)
{

}

//______________________________________________________________________________
//! Container Ctor.
//cat::co::abc::abc(cat::co::set* set, const cat::co::ID_t& id) : 
//					_owner(set),
//					_ID(id), 
//					_parent(0), 
//					_status(cat::co::abc::state::uninitialized)
//{
//
//
//}

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

	// Object ID and pointer.
	os << "ID: " << cat::cl::grass(c.id());
	os << " ptr: " << cat::cl::link() << c.ptrConst() << cat::cl::reset();

	// Object size.
	os << " Size: " << cat::cl::lpurple(c.size());
	

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
	os << " Pr: " << cat::cl::grass(c.parent());
	
	// Object child(s).
	os << " Ch: {" << cat::cl::message();
	if (c._child.size() > 0) {
		for (size_t i = 0; i < c._child.size() - 1; i++) {
			os << cat::cl::message(std::to_string(c._child[i])) 
				<< cat::cl::reset() << ",";
		}
		os << cat::cl::message(c._child.back()) 
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


//______________________________________________________________________________
//! Write/Read the object into a stream.
//! \brief write/read the object to/from a std::stringstream. This is used to 
//!		save/load the object and/or duplicate it across sockets or other means.
//!		Important: thw function writes all the object data, except the object 
//!		type, which MUST be pre-happened to the writing call, so that a factory
//!		will create the right object in the read phase, and then call the stream
//!		read function to recreate it.
//! \argument \c ss is the std::stringstream the object must be written into, or
//!		read from.
//! \argument \c read is a boolean (default false) setting whether the operation
//!		is a write (default) or read one.
//! \return \c 0 if everything right, error code otherwise.
//! 
int cat::co::abc::stream(std::stringstream & ss, const bool& read)
{

	// First, read/write the object type and version.
	if (read) {

		// Check type.
		cat::co::type_t typeCheck = 0;
		cat::co::version_t versionCheck = 0;
		cat::co::stream::read(ss, typeCheck);
		if (typeCheck != type()) {
			std::cout << cat::cl::errorMsg("Invalid type while reading object ") << cat::cl::lavio(this) << "\n";
			//throw std::runtime_error("cat::GP::stream incorrect Type!");
			return -1;
		}
		
		// Check version.
		cat::co::stream::read(ss, versionCheck);
		if (versionCheck != version()) {
			std::cout << cat::cl::errorMsg("Invalid version while reading object ") << cat::cl::lavio(this) << "\n";
			//throw std::runtime_error("cat::GP::Stream incorrect Version!");
			return -1;
		}

		// Write type and version for later checking.
	} else {
		cat::co::stream::write(ss, type());
		cat::co::stream::write(ss, version());
	}

	// Read/Write all the GP properties from/into the stream.
	//cat::co::stream::rw(ss, _status, read);

	// Family.
	cat::co::stream::rw(read, ss, _oId);
	cat::co::stream::rw(read, ss, _parent);
	cat::co::stream::rw(read, ss, _child);


	// Everything fine!
	return 0;
}


// *****************************************************************************
// **							Owner private members						  **
// *****************************************************************************

//______________________________________________________________________________
cat::co::set* cat::co::abc::owner() const
{
	//! Returns the object owner (the contair which manages it).
	return _owner;
}

//______________________________________________________________________________
cat::co::ID_t cat::co::abc::id() const
{
	//! Returns ID used by the owner to identify the object.
	return _oId;
}


// *****************************************************************************
// **							Family public members						  **
// *****************************************************************************



//______________________________________________________________________________
cat::co::ID_t cat::co::abc::parent() const
{
	//! Returns the GP parent pointer (if any).
	return _parent;
}

//______________________________________________________________________________
void cat::co::abc::parent(const cat::co::ID_t& pID)
{
	
   _parent = pID;
	
	// Retrieves and store parent pointer.
	//if (_parentHnd && _ownerPtr) _parentPtr = _ownerPtr->gpGet(_parentHnd);
	//else _parentPtr = NULL;
}

//______________________________________________________________________________

int cat::co::abc::childAdd(const cat::co::ID_t& cID)
{
	_child.push_back(cID);
	return 0;
	// DEBUG: Do we need to notify the child? Or check for multiple parents?
}

//______________________________________________________________________________
int cat::co::abc::childDel(const cat::co::ID_t& cID)
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
std::vector<uint32_t> cat::co::abc::childList() const
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
