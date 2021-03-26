#ifndef __DF_EVENT_H__
#define __DF_EVENT_H__

#include <string>

namespace df {
	const std::string UNDEFINED_EVENT = "df::undefined";

	class Event {
	private:
		std::string m_event_type;

	public:
		Event();

		virtual ~Event();

		// Set Event Type
		void setType(const std::string& new_type);

		// Get Event Type
		const std::string& getType() const;
	};
}

#endif /*DF_EVENT_H*/
