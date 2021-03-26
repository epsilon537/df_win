#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <string>
#include "ObjectList.h"

namespace df {
	class Event;

	const int MAX_EVENTS = 100; //Max. number of different events.

	class Manager {
	private:
		std::string m_type;	// Manager type identifier.
		bool m_is_started;	// True when started successfully.
		int m_event_count; //number of events.
		std::string m_event_name[MAX_EVENTS]; //List of events.
		ObjectList m_obj_list[MAX_EVENTS]; //Objects interested in event.
		ObjectList m_obj_list_copy[MAX_EVENTS];

		//Check if event is handled by this Manager.
		//If handled, return true, else false.
		virtual bool isValid(std::string event_name) const;

	protected:
		// Set type identifier of Manager.
		void setType(std::string type);

	public:
		Manager();
		virtual ~Manager();

		// Get type identifier of Manager.
		std::string getType() const;

		// Startup Manager.
		// Return 0 if ok, else negative number.
		virtual int startUp();

		// Shutdown Manager.
		virtual void shutDown();

		// Return true when startUp() was executed ok, else false.
		bool isStarted() const;

		//Send event to all interested Objects.
		//Return count of number of events sent.
		int onEvent(const Event* p_event) const;

		//Indicate interest in event.
		//Return 0 if ok, else -1.
		//Note: doesn't check if Object is already registered.
		int registerInterest(Object* p_o, std::string event_type);

		//Indicate no more interest in event.
		//Return 0 if ok, else -1.
		int unregisterInterest(Object* p_o, std::string event_type);
	};

} // end of namespace df

#endif /*MANAGER_H*/
