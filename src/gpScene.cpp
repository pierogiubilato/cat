//------------------------------------------------------------------------------
// CAT scene Graphic Primitive class							 			  --
// (C) Piero Giubilato 2021-2024, Padova University                           --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"gpScene.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"17 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________


// Application components.
#include "gpScene.h"


// #############################################################################
namespace cat { namespace gp {

// *****************************************************************************
// **							 Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
scene::scene(): _count(0)
{
	/*! scene ctor. A scene is a special GP, which purpose is holding and managing
	 *	all the other scene members GPs. It has owning privileges over the hosted 
	 *	GPs: every GP will be destroyed at scene deletion. Note how a scene has
	 *	always a hosted GP of index 0 which is actually a dummy one.
	 */
  	_scene.clear();
	_scene.push_back(NULL); 
}

//______________________________________________________________________________
scene::~scene() 
{
	/*! Releases all allocated resources. */

	// Delete all the GPs.
	clear();
}


// *****************************************************************************
// **						Overloaded GP public members					  **
// *****************************************************************************

//______________________________________________________________________________
Uint64 scene::type() const
{
	/*! Returns a numeric identification. */
	return GP::type() + GP::ktype::scene;
}

//______________________________________________________________________________
Uint64 scene::version() const
{
	/*! Returns primitive version. */
	return 100;
}

//______________________________________________________________________________
std::string scene::stem() const
{
	/*! Returns a string identification. */
	return "scene";
}

//______________________________________________________________________________
size_t scene::size(const bool& dynamic) const
{
	/*! Returns the complete (full static + full dynamic) allocated space for 
	 *	the GP if \c dynamic = false, the default call. If \c dynamic = true,
	 *	it instead returns only the dynamically allocated space, without any 
	 *	contribution from the static part.
	 */
	
	// Get dynamically allocated size.
	size_t tSize = obj::size(true);
	
	// All the contained adds up to the size!
	for (Uint64 i = 1; i < _scene.size(); i++) {
		if (_scene[i]) tSize += _scene[i]->size();
	}

	// Returns.
	if (dynamic) return tSize;
	else return sizeof(*this) + tSize;	

	// Well done!
	return tSize;
}

//______________________________________________________________________________
void scene::dump(const Uint64& ind) const
{
	/*! Send out all the GP data. */
	GP::dump();

	// scene specifics.
	std::string pad2(ind + CAT_DUMP_PADDING, ' ');
	std::string pad3(ind + 2 * CAT_DUMP_PADDING, ' ');
	std::cout << pad2 << "scene [GPs count: "  << COL(LWHITE) << _count << COL(DEFAULT) << "]\n";	

	// List reference properties.
	for (Uint64 i = 1; i < _scene.size(); i++) {
		if(_scene[i]) _scene[i]->dump(ind + 2 * CAT_DUMP_PADDING);
	}
}

//______________________________________________________________________________
bool scene::stream(std::stringstream& o, const bool& read)
{
	/*! streams an entire scene into/from \c o accordingly to the \c read flag. */
	
	// Streams the parent.
	GP::stream(o, read); 

	// Read from stream.
	if (read) {
		
		// read all the GPs.
		af::stream::read(o, _count);	// GPs total count.
		for (Uint64 i = 0; i < _count; i++) {
			
			// Builds up the new object.
			Uint64 gType = 0;
			af::stream::read(o, gType);	// Get the type.
			_scene.push_back(GP::build(gType)); 
						
			// If it has been created
			if (_scene.back()) {
				
				// Set scene ownership over this GP.
				_scene[i]->owner(this); 

				// Load it with the stream
				if (_scene[i]->stream(o, true)) return true;
			} else {
				std::cout << COL(CAT_COL_ERROR) << "Error" << COL(DEFAULT) 
						  << ": unable to build the specified GP\n";
				return true;
			 }
		}
	
	// Write to stream.
	} else {

		// Writes all the GPs.
		af::stream::write(o, _count);	// GPs total count.
		for (Uint64 i = 1; i < _scene.size(); i++) {
			if(_scene[i]) {
				af::stream::write(o, _scene[i]->type());	// Pre-write the type.
				_scene[i]->stream(o, false);// Write the GP.
			}
		}
	}
	
	// Everything fine!
	return false;
}

//______________________________________________________________________________
void gp::scene::clear()
{
	/*! Clears the scene. */
	for (Uint64 i = 1; i < _scene.size(); i++) {
		delete _scene[i];
	}
	_scene.clear();
	
	// Adds the scene dummy element.
	_scene.push_back(NULL);	 
}

// *****************************************************************************
// **							Public GP management						  **
// *****************************************************************************

//______________________________________________________________________________
GPHnd scene::gpAdd(GP* gp, const gpHnd& pHnd)
{
	/*! Adds the GP \c gp to the scene. Note that the scene will take full
	 *	ownership of the new guest, managing it and eventually taking care 
	 *	of deleting it. Returns the handle assigned to the now hosted GP.
	 *	To speed up GPs search and management, the given gpHnd is actually
	 *	guaranteed to be equal to the index of the GP. When a GP is deleted,
	 *	its slot in the vector is cleared and no more used to avoid possible
	 *	ambiguities in the families relationships. So when scrolling through
	 *	the _scene[] vector pay attention to check for the existence of the
	 *	ith-element before using it.
	 */
	
	// Adds the GP.
	GPHnd gpHnd = _scene.size();
	_scene.push_back(gp);
		
	// Registers GP object into the scene.
	gp->handle(gpHnd);
	
	// Set name if provided name is null.
	if (strlen(gp->name()) == 0) {
		std::stringstream name;
		name << gp->stem() << " " << gpHnd;
		gp->name(name.str().c_str());
	}

	// Sets ownership.
	gp->owner(this); 

	// Sets parent in case.
	gp->parent(0);
	if (pHnd > 0 && pHnd < _scene.size()) {
		if(_scene[pHnd]) {
			_scene[gpHnd]->parent(pHnd);
			_scene[pHnd]->childAdd(gpHnd); 
		}
	}

	// Increase GP count.
	_count++;

	// Return the assigned handle.
	return gpHnd;
}

//______________________________________________________________________________
GPHnd scene::gpAdd(std::stringstream& stream)
{
	/*! Adds a GP generating it directly from a stream. This function assumes 
	 *	the stream have been actually generated by a gp::scene entity. Returns 
	 *	the handle assigned to the just created and now hosted GP.
	 */
	
	// First 8 bytes contain the entity type, so read them and reset position,
	// as the new gp will self-read again its own type.
	Uint64 gpType;
	af::stream::read(stream, gpType);
	stream.seekg(std::ios_base::beg); 	

	// Adds the GP.
	GPHnd gpHnd = _scene.size();
	_scene.push_back(build(gpType));
	
	// Registers GP object into the scene.
	_scene[gpHnd]->handle(gpHnd);
	
	// Set ownership.
	_scene[gpHnd]->owner(this);

	// Sets the GP by using the data into the stream (this will also set
	// the parent).
	_scene[gpHnd]->stream(stream, true);

	// Sets childhood in case.
	GPHnd pHnd = _scene[gpHnd]->parent();
	if (pHnd > 0 && pHnd < _scene.size()) {
		if(_scene[pHnd]) {
			_scene[_scene[gpHnd]->parent()]->childAdd(gpHnd);
		}
	}
	
	// Increase GP count.
	_count++;
	
	// Return the assigned handle.
	return gpHnd;
}

//______________________________________________________________________________
void scene::gpDel(const GPHnd& gpHnd)
{
	/*! Deletes a GP from the scene. It deletes all the family too .*/

	// Checks.
	if (gpHnd == 0 || gpHnd >= _scene.size()) return;
	if (_scene[gpHnd] == 0) return;

	// Deletes the GP
	delete _scene[gpHnd];
	_scene[gpHnd] = 0;

	// Recursively deletes the family
	for (Uint64 i = 1; i < _scene.size(); i++) {
		if (_scene[i]) {
			if (_scene[i]->parent() == gpHnd) gpDel(i); 
		}
	}

	// Decrease GP count. Pay attention that the GP count is always equal
	// or smaller than the _scene vector!
	_count--;
}

//______________________________________________________________________________
GPHnd scene::gpCount() const
{
	/*! Returns the total number of existent GPs in the scene. */
	return _count;
}

//______________________________________________________________________________
size_t gp::scene::gpSize() const
{
	/*! Returns the size of the GPs vector. Could be some GP are
	 *	actually no more existent (NULL pointer in that case).
	 */
	return _scene.size();
}

//______________________________________________________________________________
GP* scene::gpGet(const GPHnd& gpHnd) const
{
	/*! Returns the pointer of the scene GP identified by \c Hnd. */
	if (gpHnd > 0 && gpHnd < _scene.size()) return _scene[gpHnd];
	else return 0;
}

//______________________________________________________________________________
GP* scene::operator[] (const gpHnd& gpHnd) const
{   
	/*! Returns the pointer of the scene GP identified by \c Hnd. */
	return gpGet(gpHnd);
}



// *****************************************************************************
// **							     SERVER SIDE							  **
// *****************************************************************************

// Drawing and UI function are available only on the SERVER side.
#ifdef CAT_SERVER


// *****************************************************************************
// **							    gl Functions							  **
// *****************************************************************************

// *****************************************************************************
// **							    ui Functions							  **
// *****************************************************************************

//______________________________________________________________________________
//void scene::uiBarLoad(ui::Bar& bar)
//{
//	/*!	Load the provided AntTweakBar \c twBar with the specific properties of 
//	 *	the GP. This member should be overloaded to change/add the properties
//	 *	shown on the properties bar by every GP.
//	 */
//
//}

// End of CAT_SERVER if.
#endif


// #############################################################################
}} // Close namespaces