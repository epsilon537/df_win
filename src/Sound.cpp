#include "Sound.h"

namespace df {
	Sound::Sound() : m_sound(), m_sound_buffer(), m_label() {
	}

	Sound::~Sound() {
		m_sound.resetBuffer();
	}

	//Load sound buffer from file.
	//Return 0 if ok, else -1.
	int Sound::loadSound(std::string filename) {
		if (m_sound_buffer.loadFromFile(filename)) {
			m_sound.setBuffer(m_sound_buffer);
			return 0;
		}

		return -1;
	}

	//Set label associated with sound.
	void Sound::setLabel(std::string new_label) {
		m_label = new_label;
	}

	//Get label associated with sound.
	std::string Sound::getLabel() const {
		return m_label;
	}

	//Play sound.
	//If loop is true, repeat play when done.
	void Sound::play(bool loop) {
		m_sound.play();
		m_sound.setLoop(loop);
	}

	//Stop sound.
	void Sound::stop() {
		m_sound.stop();
	}

	//Pause sound.
	void Sound::pause() {
		m_sound.pause();
	}

	//Return SFML sound.
	sf::Sound Sound::getSound() const {
		return m_sound;
	}
}