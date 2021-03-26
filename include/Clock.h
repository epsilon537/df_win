#ifndef __CLOCK_H__
#define __CLOCK_H__

namespace df {

	class Clock {
	private:
		long int m_previous_time; // Previous time delta() called, in us.

		// Retrieve current time in microseconds.
		static long int getCurTimeUs();

	public:
		// Sets previous time to current time.
		Clock();

		// Return time elapsed since delta() was last called. -1 if error.
		// Resets previous time.
		// Unit: us.
		int delta_us();

		// Return time elapsed since delta() was last called. -1 if error.
		// Does not reset previous time.
		// Units: us
		int split_us() const;
	};
}
#endif /*CLOCK_H*/