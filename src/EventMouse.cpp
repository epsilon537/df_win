#include "EventMouse.h"

namespace df {
	EventMouse::EventMouse() : m_mouse_action(UNDEFINED_MOUSE_ACTION), m_mouse_button(Mouse::UNDEFINED_MOUSE_BUTTON) {
		setType(MSE_EVENT);
	}

	//Set mouse event action.
	void EventMouse::setMouseAction(EventMouseAction new_mouse_action) {
		m_mouse_action = new_mouse_action;
	}

	//Get mouse event action.
	EventMouseAction EventMouse::getMouseAction() const {
		return m_mouse_action;
	}

	//Set mouse event button.
	void EventMouse::setMouseButton(Mouse::Button new_mouse_button) {
		m_mouse_button = new_mouse_button;
	}

	//Get mouse event button.
	Mouse::Button EventMouse::getMouseButton() const {
		return m_mouse_button;
	}

	//Set mouse event position.
	void EventMouse::setMousePosition(Vector new_mouse_xy) {
		m_mouse_xy = new_mouse_xy;
	}

	//Get mouse event position.
	Vector EventMouse::getMousePosition() const {
		return m_mouse_xy;
	}
}