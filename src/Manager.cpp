#include "Manager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Event.h"
#include <assert.h>

namespace df {

	void Manager::setType(std::string type) {
		m_type = type;
	}

	Manager::Manager() : m_type("Manager"), m_is_started(false), m_event_count(0) {
	}

	Manager::~Manager() {
	}

	// Get type identifier of Manager.
	std::string Manager::getType() const {
		return m_type;
	}

	// Startup Manager.
	// Return 0 if ok, else negative number.
	int Manager::startUp() {
		m_is_started = true;
		return 0;
	}

	// Shutdown Manager.
	void Manager::shutDown() {
		m_is_started = false;
	}

	// Return true when startUp() was executed ok, else false.
	bool Manager::isStarted() const {
		return m_is_started;
	}

	//Send event to all Objects.
	//Return count of number of events sent.
	int Manager::onEvent(const Event* p_event) const {
		int count = 0;

		assert(p_event);

		//Make a copy. If we would operate on the original lists, we might get stuck in a infinite loop.
		memcpy((void*)m_obj_list_copy, (void*)m_obj_list, sizeof(ObjectList) * m_event_count);

		for (int ii = 0; ii < m_event_count; ii++) {
			if (m_event_name[ii] == p_event->getType()) {
				ObjectListIterator li(&m_obj_list_copy[ii]);

				while (!li.isDone()) {
					if (li.currentObject()->isActive()) {
						li.currentObject()->eventHandler(p_event);
						++count;
					}
					li.next();
				}
			}
		}

		return count;
	}

	int Manager::registerInterest(Object* p_o, std::string event_type) {
		if (!isValid(event_type))
			return -1;

		//LM.writeLog("Registering event %s with manager %s\n", event_type.c_str(), getType().c_str());

		//Check if previously added this event.
		for (int ii = 0; ii < m_event_count; ++ii) {
			if (m_event_name[ii] == event_type) {
				m_obj_list[ii].insert(p_o);

				//LM.writeLog("m_event_count=%d\n", m_event_count);
				return 0;
			}
		}

		//New event type.
		if (m_event_count >= MAX_EVENTS) {
			return -1; //Error: list is full.
		}

		m_event_name[m_event_count] = event_type;
		m_obj_list[m_event_count].clear(); //In case we're reusing a scooted list.
		m_obj_list[m_event_count].insert(p_o);
		++m_event_count;

		//LM.writeLog("m_event_count=%d\n", m_event_count);

		return 0;
	}

	int Manager::unregisterInterest(Object* p_o, std::string event_type) {
		//LM.writeLog("Unregistering event %s with manager %s\n", event_type.c_str(), getType().c_str());

		//Check for event
		for (int ii = 0; ii < m_event_count; ii++) {
			if (m_event_name[ii] == event_type) {
				if (m_obj_list[ii].remove(p_o) == -1) {
					return -1;
				}

				//Is list now empty?
				if (m_obj_list[ii].isEmpty()) {
					//Scoot over all items
					for (int jj = ii; jj < m_event_count - 1; jj++) {
						m_obj_list[jj] = m_obj_list[jj + 1];
						m_event_name[jj] = m_event_name[jj + 1];
					}

					--m_event_count;
				}

				//LM.writeLog("m_event_count=%d\n", m_event_count);
				return 0;
			}
		}

		//LM.writeLog("m_event_count=%d\n", m_event_count);
		return -1; //Not found.
	}

	bool Manager::isValid(std::string event_name) const {
		return false;
	}
}