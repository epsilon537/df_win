#ifndef __DF_EVENT_OUT_H__
#define __DF_EVENT_OUT_H__

#include "Event.h"

namespace df {
	const std::string OUT_EVENT = "df::out";

	class EventOut : public Event {
	public:
		EventOut();
	};
}

#endif /*EVENT_OUT*/
