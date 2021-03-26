#ifndef __DF_INPUT_MANAGER_H__
#define __DF_INPUT_MANAGER_H__

#include "Manager.h"
#include <SFML/Graphics.hpp>

// Two-letter acronym for easier access to manager.
#define IM df::InputManager::getInstance()

namespace df {

	class InputManager : public Manager {
	private:
		sf::RenderWindow* m_p_window;

		InputManager();
		InputManager(InputManager const&);
		void operator=(InputManager const&);

	public:
		// Get the one and only instance of the InputManager.
		static InputManager& getInstance();

		// Get window ready to capture input.
		// Return 0 it ok, else -1
		int startUp();

		// Revert back to normal window mode.
		void shutDown();

		// Get input from the keyboard and mouse.
		// Pass event along to all Objects.
		void getInput();

		bool isValid(std::string event_name) const;
	};
}

#endif /*DF_INPUT_MANAGER_H*/
