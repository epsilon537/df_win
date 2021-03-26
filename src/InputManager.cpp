#include "InputManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "GameManager.h"

#include <assert.h>

namespace df {
    static sf::Keyboard::Key supported_sf_keycodes[] = {
                sf::Keyboard::A,            ///< The A key
                sf::Keyboard::B,            ///< The B key
                sf::Keyboard::C,            ///< The C key
                sf::Keyboard::D,            ///< The D key
                sf::Keyboard::E,            ///< The E key
                sf::Keyboard::F,            ///< The F key
                sf::Keyboard::G,            ///< The G key
                sf::Keyboard::H,            ///< The H key
                sf::Keyboard::I,            ///< The I key
                sf::Keyboard::J,            ///< The J key
                sf::Keyboard::K,            ///< The K key
                sf::Keyboard::L,            ///< The L key
                sf::Keyboard::M,            ///< The M key
                sf::Keyboard::N,            ///< The N key
                sf::Keyboard::O,            ///< The O key
                sf::Keyboard::P,            ///< The P key
                sf::Keyboard::Q,            ///< The Q key
                sf::Keyboard::R,            ///< The R key
                sf::Keyboard::S,            ///< The S key
                sf::Keyboard::T,            ///< The T key
                sf::Keyboard::U,            ///< The U key
                sf::Keyboard::V,            ///< The V key
                sf::Keyboard::W,            ///< The W key
                sf::Keyboard::X,            ///< The X key
                sf::Keyboard::Y,            ///< The Y key
                sf::Keyboard::Z,            ///< The Z key
                sf::Keyboard::Num0,         ///< The 0 key
                sf::Keyboard::Num1,         ///< The 1 key
                sf::Keyboard::Num2,         ///< The 2 key
                sf::Keyboard::Num3,         ///< The 3 key
                sf::Keyboard::Num4,         ///< The 4 key
                sf::Keyboard::Num5,         ///< The 5 key
                sf::Keyboard::Num6,         ///< The 6 key
                sf::Keyboard::Num7,         ///< The 7 key
                sf::Keyboard::Num8,         ///< The 8 key
                sf::Keyboard::Num9,         ///< The 9 key
                sf::Keyboard::Backspace,    ///< The Backspace key
                sf::Keyboard::Escape,       ///< The Escape key
                sf::Keyboard::LControl,     ///< The left Control key
                sf::Keyboard::LShift,       ///< The left Shift key
                sf::Keyboard::RControl,     ///< The right Control key
                sf::Keyboard::RShift,       ///< The right Shift key
                sf::Keyboard::Comma,        ///< The , key
                sf::Keyboard::Period,       ///< The . key
                sf::Keyboard::Slash,        ///< The / key
                sf::Keyboard::Tilde,        ///< The ~ key
                sf::Keyboard::Space,        ///< The Space key
                sf::Keyboard::Enter,        ///< The Enter/Return keys
                sf::Keyboard::Tab,          ///< The Tab key
                sf::Keyboard::Add,          ///< The + key
                sf::Keyboard::Subtract,     ///< The - key (minus, usually from numpad)
                sf::Keyboard::Left,         ///< Left arrow
                sf::Keyboard::Right,        ///< Right arrow
                sf::Keyboard::Up,           ///< Up arrow
                sf::Keyboard::Down,         ///< Down arrow
                sf::Keyboard::F1,           ///< The F1 key
                sf::Keyboard::F2,           ///< The F2 key
                sf::Keyboard::F3,           ///< The F3 key
                sf::Keyboard::F4,           ///< The F4 key
                sf::Keyboard::F5,           ///< The F5 key
                sf::Keyboard::F6,           ///< The F6 key
                sf::Keyboard::F7,           ///< The F7 key
                sf::Keyboard::F8,           ///< The F8 key
                sf::Keyboard::F9,           ///< The F9 key
                sf::Keyboard::F10,          ///< The F10 key
                sf::Keyboard::F11,          ///< The F11 key
                sf::Keyboard::F12,          ///< The F12 key
                sf::Keyboard::Pause,        ///< The Pause key
    };

	static Keyboard::Key sf_to_df_keycode(sf::Keyboard::Key sf_keycode) {
		switch (sf_keycode) {
        case sf::Keyboard::A: return Keyboard::A;
        case sf::Keyboard::B: return Keyboard::B;
        case sf::Keyboard::C: return Keyboard::C;
        case sf::Keyboard::D: return Keyboard::D;
        case sf::Keyboard::E: return Keyboard::E;
        case sf::Keyboard::F: return Keyboard::F;
        case sf::Keyboard::G: return Keyboard::G;
        case sf::Keyboard::H: return Keyboard::H;
        case sf::Keyboard::I: return Keyboard::I;
        case sf::Keyboard::J: return Keyboard::J;
        case sf::Keyboard::K: return Keyboard::K;
        case sf::Keyboard::L: return Keyboard::L;
        case sf::Keyboard::M: return Keyboard::M;
        case sf::Keyboard::N: return Keyboard::N;
        case sf::Keyboard::O: return Keyboard::O;
        case sf::Keyboard::P: return Keyboard::P;
        case sf::Keyboard::Q: return Keyboard::Q;
        case sf::Keyboard::R: return Keyboard::R;
        case sf::Keyboard::S: return Keyboard::S;
        case sf::Keyboard::T: return Keyboard::T;
        case sf::Keyboard::U: return Keyboard::U;
        case sf::Keyboard::V: return Keyboard::V;
        case sf::Keyboard::W: return Keyboard::W;
        case sf::Keyboard::X: return Keyboard::X;
        case sf::Keyboard::Y: return Keyboard::Y;
        case sf::Keyboard::Z: return Keyboard::Z;
        case sf::Keyboard::Num0: return Keyboard::NUM0;
        case sf::Keyboard::Num1: return Keyboard::NUM1;
        case sf::Keyboard::Num2: return Keyboard::NUM2;
        case sf::Keyboard::Num3: return Keyboard::NUM3;
        case sf::Keyboard::Num4: return Keyboard::NUM4;
        case sf::Keyboard::Num5: return Keyboard::NUM5;
        case sf::Keyboard::Num6: return Keyboard::NUM6;
        case sf::Keyboard::Num7: return Keyboard::NUM7;
        case sf::Keyboard::Num8: return Keyboard::NUM8;
        case sf::Keyboard::Num9: return Keyboard::NUM9;
        case sf::Keyboard::Backspace: return Keyboard::BACKSPACE;
        case sf::Keyboard::Escape: return Keyboard::ESCAPE;
        case sf::Keyboard::LControl: return Keyboard::LEFTCONTROL;
        case sf::Keyboard::LShift: return Keyboard::LEFTSHIFT;
        case sf::Keyboard::RControl: return Keyboard::RIGHTCONTROL;
        case sf::Keyboard::RShift: return Keyboard::RIGHTSHIFT;
        case sf::Keyboard::Comma: return Keyboard::COMMA;
        case sf::Keyboard::Period: return Keyboard::PERIOD;
        case sf::Keyboard::Slash: return Keyboard::SLASH;
        case sf::Keyboard::Tilde: return Keyboard::TILDE;
        case sf::Keyboard::Space: return Keyboard::SPACE;
        case sf::Keyboard::Enter: return Keyboard::RETURN;
        case sf::Keyboard::Tab: return Keyboard::TAB;
        case sf::Keyboard::Add: return Keyboard::PLUS;
        case sf::Keyboard::Subtract: return Keyboard::MINUS;
        case sf::Keyboard::Left: return Keyboard::LEFTARROW;
        case sf::Keyboard::Right: return Keyboard::RIGHTARROW;
        case sf::Keyboard::Up: return Keyboard::UPARROW;
        case sf::Keyboard::Down: return Keyboard::DOWNARROW;
        case sf::Keyboard::F1: return Keyboard::F1;
        case sf::Keyboard::F2: return Keyboard::F2;
        case sf::Keyboard::F3: return Keyboard::F3;
        case sf::Keyboard::F4: return Keyboard::F4;
        case sf::Keyboard::F5: return Keyboard::F5;
        case sf::Keyboard::F6: return Keyboard::F6;
        case sf::Keyboard::F7: return Keyboard::F7;
        case sf::Keyboard::F8: return Keyboard::F8;
        case sf::Keyboard::F9: return Keyboard::F9;
        case sf::Keyboard::F10: return Keyboard::F10;
        case sf::Keyboard::F11: return Keyboard::F11;
        case sf::Keyboard::F12: return Keyboard::F12;
        case sf::Keyboard::Pause: return Keyboard::PAUSE;
        default: return Keyboard::UNDEFINED_KEY;
		}
	}

	InputManager::InputManager() : m_p_window(0) {
		setType("InputManager");
	}

	// Get the one and only instance of the InputManager.
	InputManager& InputManager::getInstance() {
		static InputManager inputManager;
		return inputManager;
	}

	// Get window ready to capture input.
	// Return 0 it ok, else -1
	int InputManager::startUp() {
		/*DM needs to be running before we can start input manager.*/
		if (!DM.isStarted())
			return -1;

		m_p_window = DM.getWindow();
		assert(m_p_window);

		m_p_window->setKeyRepeatEnabled(false);

		Manager::startUp();

		return 0;
	}

	// Revert back to normal window mode.
	void InputManager::shutDown() {
		if (!DM.isStarted())
			return;

		assert(m_p_window);

		m_p_window->setKeyRepeatEnabled(true);
	}

	// Get input from the keyboard and mouse.
	// Pass event along to all Objects.
	void InputManager::getInput() {
		// Go through all Window events, extracting recognized ones.
		sf::Event event;

		assert(m_p_window);

		while (m_p_window->pollEvent(event)) {
            //Special case - see if Window closed.
            if (event.type == sf::Event::Closed) {
                GM.setGameOver();
                return;
            }

			//Key was pressed
			if (event.type == sf::Event::KeyPressed) {
				EventKeyboard eventKeyboard;
				eventKeyboard.setKeyboardAction(KEY_PRESSED);
                Keyboard::Key keycode = sf_to_df_keycode(event.key.code);
                if (keycode != Keyboard::UNDEFINED_KEY) {
                    eventKeyboard.setKey(keycode);
                    onEvent(&eventKeyboard);
                }
			}

			//Key was released
			if (event.type == sf::Event::KeyReleased) {
                EventKeyboard eventKeyboard;
                eventKeyboard.setKeyboardAction(KEY_RELEASED);
                Keyboard::Key keycode = sf_to_df_keycode(event.key.code);
                if (keycode != Keyboard::UNDEFINED_KEY) {
                    eventKeyboard.setKey(keycode);
                    onEvent(&eventKeyboard);
                }
			}

			// Mouse was moved
			if (event.type == sf::Event::MouseMoved) {
                EventMouse eventMouse;
                Vector v = Vector((float)event.mouseMove.x/charWidth(), (float)event.mouseMove.y/charHeight());
                eventMouse.setMousePosition(v);
                eventMouse.setMouseAction(MOVED);
                onEvent(&eventMouse);
			}

			//Mouse was clicked
			if (event.type == sf::Event::MouseButtonPressed) {
                EventMouse eventMouse;
                eventMouse.setMouseAction(CLICKED);
                Vector v = Vector((float)event.mouseButton.x/charWidth(), (float)event.mouseButton.y/charHeight());
                eventMouse.setMousePosition(v);

                switch (event.mouseButton.button) {
                case sf::Mouse::Left:
                    eventMouse.setMouseButton(Mouse::LEFT);
                    break;
                case sf::Mouse::Right:
                    eventMouse.setMouseButton(Mouse::RIGHT);
                    break;
                case sf::Mouse::Middle:
                    eventMouse.setMouseButton(Mouse::MIDDLE);
                    break;
                default:
                    break;
                }

                onEvent(&eventMouse);
			}
		}

        for (int ii = 0; ii < sizeof(supported_sf_keycodes); ii++) {
            // Key is currently pressed.
            if (sf::Keyboard::isKeyPressed(supported_sf_keycodes[ii])) {
                EventKeyboard eventKeyboard;
                eventKeyboard.setKeyboardAction(KEY_DOWN);
                Keyboard::Key keycode = sf_to_df_keycode(supported_sf_keycodes[ii]);
                eventKeyboard.setKey(keycode);
                onEvent(&eventKeyboard);
            }
        }

		// Mouse button is currently pressed.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            EventMouse eventMouse;
            eventMouse.setMouseAction(PRESSED);
            Vector v = Vector((float)event.mouseButton.x, (float)event.mouseButton.y);
            eventMouse.setMousePosition(v);
            eventMouse.setMouseButton(Mouse::LEFT);

            onEvent(&eventMouse);
		}

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            EventMouse eventMouse;
            eventMouse.setMouseAction(PRESSED);
            Vector v = Vector((float)event.mouseButton.x, (float)event.mouseButton.y);
            eventMouse.setMousePosition(v);
            eventMouse.setMouseButton(Mouse::RIGHT);

            onEvent(&eventMouse);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
            EventMouse eventMouse;
            eventMouse.setMouseAction(PRESSED);
            Vector v = Vector((float)event.mouseButton.x, (float)event.mouseButton.y);
            eventMouse.setMousePosition(v);
            eventMouse.setMouseButton(Mouse::MIDDLE);

            onEvent(&eventMouse);
        }
	}

    bool InputManager::isValid(std::string event_name) const {
        if (event_name == df::KEYBOARD_EVENT)
            return true;

        if (event_name == df::MSE_EVENT)
            return true;

        return false;
    }
}