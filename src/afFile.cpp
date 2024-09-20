//------------------------------------------------------------------------------
// CAT application facility file class										  --
// (C) Piero Giubilato 2011-2024, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afFile.cpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.0"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
//______________________________________________________________________________

// Application components
#include "afFile.h"

// Dirent POSIX interface (not by default on WIN).
#if defined(_WIN32) || defined(_WIN64)
	#include "dirent/dirent.h"
#else
	#include "dirent.h"
#endif


// #############################################################################
// Open namespaces
namespace cat { namespace af {


// *****************************************************************************
// **								Special Members							  **
// *****************************************************************************

//______________________________________________________________________________
file::file()
{
	/* Standard ctor. */

	
	
}

//______________________________________________________________________________
file::~file() 
{
	/* Releases all allocated resources. */

}


// *****************************************************************************
// **							Private Members								  **
// *****************************************************************************



// *****************************************************************************
// **							Public Members								  **
// *****************************************************************************

//______________________________________________________________________________
bool file::list(const std::string& path, std::vector<std::string>& list)
{
	//! Lists the file of the specified directory.
	/*! Returns all the files found on the specified \c dir. Files are returned
	 *	into the vector of std:string passed as a reference. The function just
	 *	lists the file into the specified path, and does not search in sub-paths.
	 *	Files will be added to the passed vector, which will keep its previous
	 *	content.
	 *	Returns false if everything ok, true on error.
	 */

	// Pivots.
	std::string tmpName("");
	DIR *d, *t;
	struct dirent *dir;
	
	// Opens the dir, returns on error.
	d = opendir(path.c_str());
	if (!d) return true;
	
	// Scans the dir.
	while ((dir = readdir(d)) != NULL) {
		
		// Skip "." and ".."
		if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)) continue; 
		
		// Build a temporary name.
		tmpName = path; //*dir_Name;
		tmpName.append("/");
		tmpName.append(dir->d_name);
		
		// Skip other dirs.
		if (t = opendir(tmpName.c_str())) {closedir(t); continue;}
		
		// Save file name in case
		list.push_back(std::string(tmpName));
	}
	
	// Close the directory.
	closedir(d);
		
	// Everything ok!
	return false;
}





// #############################################################################
}} // Close namespaces
