#ifndef __DF_EVENT_STEP_H__
#define __DF_EVENT_STEP_H__

#include "Event.h"

namespace df {
	const std::string STEP_EVENT = "df::step";

	class EventStep : public Event {
	private:
		int m_step_count; // Iterator number of game loop.

	public:
		EventStep();

		//Ctor with initial step count
		EventStep(int init_step_count);

		//Set step count.
		void setStepCount(int new_step_count);

		//Get step count.
		int getStepCount() const;
	};
}

#endif /*DF_EVENT_STEP*/
