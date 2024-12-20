//------------------------------------------------------------------------------
// Streaming facility for the CAT project	  								  --
// (C) Piero Giubilato 2021-2025, University of Padova                        --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"coStream.hpp"
// [Author]			"Piero Giubilato"
// [Version]		"1.2"
// [Modified by]	"Piero Giubilato"
// [Date]			"22 Sep 2024"
// [Language]		"C++"
//______________________________________________________________________________

// Overloading check
#ifndef catCoStream_H
#define catCoStream_H

// Standard components
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// #############################################################################
namespace cat { namespace co { namespace stream {


// *****************************************************************************
// **						  Streaming Support	Fuctions					  **
// *****************************************************************************

//______________________________________________________________________________
//! Converts the string \c s into a value and store it into the \c t argument.
//!	\c f if the standard format descriptor, can be one of std::hex, std::dec 
//!	or std::oct.
template <typename T> bool value(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
{
	std::istringstream iss(s);
	return !(iss >> f >> t).fail();
}

// *****************************************************************************
// **						  The Streaming Facility						  **
// *****************************************************************************


	// The i/o streaming facility.
	// ---------------------------
		
	//! Notes on this code: template specialization is NOT allowed inside a
	//!	class body! Even if MSVC actually correctly handles it, g++ and the
	//!	majority of compilers will forbid it. This separate header provides
	//!	templatized read/write on stream functionality for default types,
	//!	std::string and std::vector of default types. For strings and vectors
	//!	the number of element is saved as header, allowing the correct read
	//!	back of the data.
	//!	As template specialization (the string case) are actually not-template
	//!	function, the inline keyword is mandatory to avoid function redefinition
	//!	through the code.
	 	

// *****************************************************************************
// **									Write								  **
// *****************************************************************************

//______________________________________________________________________________
template<typename T> void inline write(std::stringstream& ss, const T& val)
{
	//! Write to stream, default types.
	ss.write((char*)&val, sizeof(T));

	// Debug.
	//std::cout << "wrT[" << (T)(val) << "](" << sizeof(T) << ")\n";
}
	
//______________________________________________________________________________
template<> void inline write<std::string>(std::stringstream& ss, const std::string& str)
{
	//! Write to stream, string type.
	size_t n = str.size();				// Number of characters.
	ss.write((char*)&n, sizeof(n));		// Writes the number of characters.
	ss.write(ss.str().c_str(), n);		// Writes the characters.

	// Debug.
	//std::cout << "wrS[" << str << "](" << n << "," << sizeof(n) << ")n";
}

//______________________________________________________________________________
template<typename T> void inline write(std::stringstream& ss, const std::vector<T>& vect)
{
	//! Write to stream, vector of default types.
	size_t s = sizeof(T);				// Size of the data type.
	size_t n = vect.size();				// Vector length (elements).
	ss.write((char*)&n, sizeof(n));		// Writes the length of the vector.
	
	// Writes the vector elements.
	for (auto i = 0; i < n; i++) {
		ss.write((char*)&vect[i], s);
	}

	// Dbeug.
	//std::cout << "wrV["; 
	//for (auto i = 0; i < n - 1; i++) std::cout << vect[i]<< ",";
	//std::cout << vect[n - 1] << "]\n";
}


// *****************************************************************************
// **									Read								  **
// *****************************************************************************

//______________________________________________________________________________
template<typename T> void inline read(std::stringstream& ss, T& val)
{
	//! Read from stream, default types.
	ss.read((char*)&val, sizeof(val));

	// Debug.
	//std::cout << "rdT[" << (T)(val) << "]\n";
}

//______________________________________________________________________________
template<> void inline read<std::string>(std::stringstream& ss, std::string& str)
{	
	//! Read from stream, string type.
	size_t n = 0;
	ss.read((char*)&n, sizeof(n));		// Reads the length of the string.
	char* swap = new char[n];			// Allocates appropriate buffer.
	ss.read(swap, n);					// Reads the string characters into buffer.
	str.assign(swap, n);				// Assign the string.
	delete swap;

	// Debug.
	// std::cout << "rdS[" << swap << "]\n";
}
		
//______________________________________________________________________________
template<typename T> void inline read(std::stringstream& ss, std::vector<T>& vect)
{
	//! Read from stream, vector of default types.
	size_t s = sizeof(T);				// Size of the vector elements.
	size_t n = 0;						// Size of the vector
	ss.read((char*)&n, sizeof(n));		// Reads the length of the vector.
	vect.resize(n);						// Resize the vector.
	for (size_t i = 0; i < n; i++) {
		ss.read((char*)&vect[i], s);
	}

	// Debug.
	//std::cout << "rdV[";
	//for (auto i = 0; i < n - 1; i++) std::cout << vect[i] << ",";
	//std::cout << vect[n - 1] << "]\n";
}



// *****************************************************************************
// **					  Read/Write boolean specialization					  **
// *****************************************************************************

//______________________________________________________________________________
template<typename T> void inline rw(const bool& rd, std::stringstream& ss, T& val)
//! Read/Write from/to stream, default types.
{
	(rd) ? read(ss, val) : write(ss, val);
}

//______________________________________________________________________________
//! Read/Write from/to stream, string type.
template<> void inline rw<std::string>(const bool& rd, std::stringstream& ss,
										std::string& str)
{

	(rd) ?	read< std::string >(ss, str) : 	write< std::string >(ss, str);
}

//______________________________________________________________________________
//! Read/Write from/to stream, vector of standard types.
template<typename T> void inline rw(const bool& rd, std::stringstream& ss,
									std::vector<T>& vect)
{
	(rd) ? read(ss, vect) :	write(ss, vect);
}


// #############################################################################
}}} // Close namespaces

// Overloading check
#endif