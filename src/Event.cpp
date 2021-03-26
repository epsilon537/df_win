#include "Event.h"

namespace df {
	Event::Event() : m_event_type(UNDEFINED_EVENT) {

	}

	Event::~Event() {

	}

	// Set Event Type
	void Event::setType(const std::string& new_type) {
		m_event_type = new_type;
	}

	// Get Event Type
	const std::string& Event::getType() const {
		return m_event_type;
	}
}
