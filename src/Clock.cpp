#include "Clock.h"
#include <Windows.h>

namespace df {
	// Retrieve current time in microseconds.
	long int Clock::getCurTimeUs() {
		SYSTEMTIME cur_time;
		
		GetSystemTime(&cur_time);

		return (cur_time.wMinute * 60 * 1000000)
			+ (cur_time.wSecond * 1000000)
			+ (cur_time.wMilliseconds * 1000);
	}

	// Sets previous time to current time.
	Clock::Clock() : m_previous_time(getCurTimeUs()) {
	}

	// Return time elapsed since delta() was last called. -1 if error.
	// Resets previous time.
	// Unit: us.
	int Clock::delta_us() {
		long int cur_time_us = getCurTimeUs();
		long int delta_us = cur_time_us - m_previous_time;

		m_previous_time = cur_time_us;

		return (int)((delta_us >= 0) ? delta_us : -1);
	}

	// Return time elapsed since delta() was last called. -1 if error.
	// Does not reset previous time.
	// Units: us
	int Clock::split_us() const {
		long int delta_us = getCurTimeUs() - m_previous_time;

		return (int)((delta_us >= 0) ? delta_us : -1);
	}
}