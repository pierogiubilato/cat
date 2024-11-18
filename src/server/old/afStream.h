//------------------------------------------------------------------------------
// Streaming facility for the CAT project	  								  --
// (C) Piero Giubilato 2021-2025, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afStream.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"21 Sep 2024"
// [Language]		"C++"
// [Project]		"PEAR"
//______________________________________________________________________________

// Overloading check
#ifndef afStream_H
#define afStream_H

// Standard components
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// #############################################################################
namespace cat { namespace af { namespace stream {


// *****************************************************************************
// **						  Streaming Support	Fuctions					  **
// *****************************************************************************

//______________________________________________________________________________
template <typename T> bool value(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
{
	/*! Converts the string \c s into a value and store it into the \c t argument.
	 *	\c f if the standard format descriptor, can be one of std::hex, std::dec 
	 *	or std::oct.
	 */
	std::istringstream iss(s);
	return !(iss >> f >> t).fail();
}

// *****************************************************************************
// **						  The Streaming Facility						  **
// *****************************************************************************


	// The i/o streaming facility.
	// ---------------------------
		
	/*! Notes on this code: template specialization is NOT allowed inside a
	 *	class body! Even if MSVC actually correctly handles it, g++ and the
	 *	majority of compilers will forbid it. This separate header provides
	 *	templatized read/write on stream functionality for default types,
	 *	std::string and std::vector of default types. For strings and vectors
	 *	the number of element is saved as header, allowing the correct read
	 *	back of the data.
	 *	As template specialization (the string case) are actually not-template
	 *	function, the inline keyword is mandatory to avoid function redefinition
	 *	through the code.
	 */
	

// *****************************************************************************
// **									Write								  **
// *****************************************************************************

//______________________________________________________________________________
template<typename T> void inline write(std::stringstream& o, const T& v)
{
	/*! Write to stream, default types. */
	o.write((char*)&v, sizeof(v));
}
	
//______________________________________________________________________________
template<> void inline write<std::string>(std::stringstream& o, const std::string& s)
{
	/* Write to stream, string type. */
	size_t l = s.size();			// Writes the length of the string.
	o.write((char*)&l, sizeof(l));	// Writes the string characters.
	o.write(s.c_str(), l);
}

//______________________________________________________________________________
template<typename T> void inline write(std::stringstream& o, const std::vector<T>& v)
{
	/*! Write to stream, vector of default types. */
	size_t s = sizeof(T);			// Size of the data type.
	size_t l = v.size();				// Vector length.
	o.write((char*)&l, sizeof(l));	// Writes the length of the vector.
	
	// Writes the vector elements.
	for (auto i = 0; i < v.size(); i++) o.write((char*)&v[i], s);
}


// *****************************************************************************
// **									Read								  **
// *****************************************************************************

//______________________________________________________________________________
template<typename T> void inline read(std::stringstream& o, T& v)
{
	/*! Read from stream, default types. */
	o.read((char*)&v, sizeof(v));
}

//______________________________________________________________________________
template<> void inline read<std::string>(std::stringstream& o, std::string& s)
{	
	/*! Read from stream, string type. */
	size_t l = 0;
	o.read((char*)&l, sizeof(l));	// Reads the length of the string.
	char* swap = new char[l];
	o.read(swap, l);				// Reads the string characters.
	s.assign(swap, l);				// Assign the string.
	delete swap;
}
		
//______________________________________________________________________________
template<typename T> void inline read(std::stringstream& o, std::vector<T>& v)
{
	/*! Read from stream, vector of default types. */
	size_t s = sizeof(T);			// Size of the vector elements.
	size_t l = 0;			// Length of the vector
	o.read((char*)&l, sizeof(l));	// Reads the length of the vector.
	for (size_t i = 0; i < l; i++) {
		v.push_back(0);
		o.read((char*)&v[i], s);
	}
}



// *****************************************************************************
// **					  Read/Write boolean indirection					  **
// *****************************************************************************

//______________________________________________________________________________
template<typename T> void inline rw(std::stringstream& o, T& v, const bool& rd)
{
	/*! Read/Write from/to stream, default types. */
	(rd) ?	read<T>(o, v) : 
			write<T>(o, v);
}

//______________________________________________________________________________
template<> void inline rw<std::string>(std::stringstream& o, std::string& s,
									   const bool& rd)
{
	/* Read/Write from/to stream, string type. */
	(rd) ?	read< std::string >(o, s) : 
			write< std::string >(o, s);
}

//______________________________________________________________________________
template<typename T> void inline rw(std::stringstream& o, std::vector<T>& v,
									const bool& rd)
{
	/* Read/Write from/to stream, vector of standard types. */
	(rd) ?	read< std::vector<T> >(o, v) : 
			write< std::vector<T> >(o, v);
}


// #############################################################################
}}} // Close namespaces

// Overloading check
#endif