//------------------------------------------------------------------------------
// CAT high precision timing Application Facility class						  --
// (C) Piero Giubilato 2010-2012, Padova University							  --
//------------------------------------------------------------------------------

//______________________________________________________________________________
// [File name]		"afTimer.h"
// [Author]			"Piero Giubilato"
// [Version]		"1.1"
// [Modified by]	"Piero Giubilato"
// [Date]			"20 Sep 2024"
// [Language]		"c++"
// [Project]		"CAT"
//______________________________________________________________________________

//______________________________________________________________________________

// Overloading check
#ifndef afTimer_H
#define afTimer_H

// Application components
#include "af.h"

// Standard components
#if defined(_WIN32) || defined(_WIN64)	// Windows system specific
	#include <windows.h>
#else	// Unix based system specific
	#include <sys/time.h>
#endif


// ##############################################################################
namespace cat { namespace af {

//______________________________________________________________________________
//! Timer facility for the CAT package
/*! Provides stopwatch timing functions. Once a cat::timer object is created
 *	the 'start()' and 'stop()' calls starts and stops the timing. Note that 
 *  'start()' and 'stop()' are cumulative, i.e. after a stop the measured time 
 *  is summed to the previous one, unless a 'reset()' is invoked.
 *	The 'Elapsed()', 'Elapsed_s()', 'Elapsed_ms()' and 'Elapsed_us()' all 
 *  returns the current timer value in seconds, seconds as well, milliseconds 
 *  and microseconds respectively.
 *	This is a stand-alone .h file, just include and enjoy!
 * 
 *	\author Piero Giubilato
 *	\version 1.1
 *	\date 20 Sep 2024
 */
class timer //: public AF
{
	private:
		
		// Stopwatch timing structure.
		typedef struct {
			#if defined(_WIN32) || defined(_WIN64)
				LARGE_INTEGER frequency;
				LARGE_INTEGER count;
			#else
				timeval count;
			#endif
		} stopWatch;

		// Pivot variables.
		stopWatch _timing;		// Timing.
		double _startTimeUS;	// Starting time.
		double _endTimeUS;		// Ending time.
		double _currentTimeUS;	// Current timer value.
		bool _stopped;			// Stop flag		

	public:
			
		//! Default ctor.
		timer()
		{
			// Reset the timer.
			reset();
		}
		
		//! Starts the timer.
		void start()
		{
			// Store the current time.
			#if defined(_WIN32) || defined(_WIN64)
				QueryPerformanceCounter(&_timing.count);
				_startTimeUS = _timing.count.QuadPart * (1000000.0 / _timing.frequency.QuadPart);
			#else
				gettimeofday(&_timing.count, NULL);
				_startTimeUS = (_timing.count.tv_sec * 1000000.0) + _timing.count.tv_usec;
			#endif
			
			// Marks timer as active.
			_stopped = false;
		}
			
		//! Stops the timer.
		void stop()
		{
			// Grab the current time.
			#if defined(_WIN32) || defined(_WIN64)
				QueryPerformanceCounter(&_timing.count);
				_endTimeUS = _timing.count.QuadPart * (1000000.0 / _timing.frequency.QuadPart);
			#else
				gettimeofday(&_timing.count, NULL);
				_endTimeUS = (_timing.count.tv_sec * 1000000.0) + _timing.count.tv_usec;
			#endif
			
			// Calculate last interval time.
			_currentTimeUS += (_endTimeUS - _startTimeUS);
			_stopped = true;
		}
		
		//! Resets the timer.
		void reset()
		{
			// Reset timing counters.
			#if defined(_WIN32) || defined(_WIN64)
				QueryPerformanceFrequency(&_timing.frequency);
				_timing.count.QuadPart = 0;
			#else
				_timing.count.tv_sec = _timing.count.tv_usec = 0;
			#endif
			
			// Reset others.
			_stopped = true;
			_startTimeUS = 0;
			_endTimeUS = 0;
			_currentTimeUS = 0;
		}
		
		bool running() {return !_stopped; } const

		//! Gets elapsed time in microseconds.	
		double elapsedUS()
		{
			// Grab timing on the fly if not stopped.
			if(!_stopped) {
				#if defined(_WIN32) || defined(_WIN64)
					QueryPerformanceCounter(&_timing.count);
					_endTimeUS = _timing.count.QuadPart * (1000000.0 / _timing.frequency.QuadPart);
				#else
					gettimeofday(&_timing.count, NULL);
					_endTimeUS = (_timing.count.tv_sec * 1000000.0) + _timing.count.tv_usec;
				#endif
			}
			
			// Return current timing.		
			return _currentTimeUS + _endTimeUS - _startTimeUS;
		}

		//! Gets elapsed time in milliseconds.	
		double elapsedMS()
		{
			return this->elapsedUS() * 0.001;
		}

		//! Gets elapsed time in seconds.	
		double elapsedS()
		{
			return this->elapsedUS() * 0.000001;
		}

		//! Gets elapsed time in seconds.	
		double elapsed()
		{
			return this->elapsedS();
		}

};

// #############################################################################
}} // Close namespaces

// Overloading check
#endif
