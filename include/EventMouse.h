#ifndef __DF_EVENT_MOUSE_H__
#define __DF_EVENT_MOUSE_H__

#include "Event.h"
#include "Vector.h"

namespace df {

	const std::string MSE_EVENT = "df::mouse";

	//Set of mouse actions recognized by Dragonfly.
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED
	};

	//Set of mouse buttons recognized by Dragonfly.
	namespace Mouse {
		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE
		};
	}

	class EventMouse : public Event {
	private:
		EventMouseAction m_mouse_action; //Mouse action.
		Mouse::Button m_mouse_button; //Mouse button.
		Vector m_mouse_xy; //Mouse (x,y) coordinates.
	
	public:
		EventMouse();

		//Set mouse event action.
		void setMouseAction(EventMouseAction new_mouse_action);

		//Get mouse event action.
		EventMouseAction getMouseAction() const;

		//Set mouse event button.
		void setMouseButton(Mouse::Button new_mouse_button);

		//Get mouse event button.
		Mouse::Button getMouseButton() const;

		//Set mouse event position.
		void setMousePosition(Vector new_mouse_xy);

		//Get mouse event position.
		Vector getMousePosition() const;

	};
}

#endif /*DF_EVENT_MOUSE_H*/
