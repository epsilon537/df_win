#include "Music.h"

namespace df {
	Music::Music() : m_music(), m_label() {

	}

	//Associate music buffer with file.
	//Return 0 if ok, else -1.
	int Music::loadMusic(std::string filename) {
		return m_music.openFromFile(filename) ? 0 : -1;
	}

	//Set label associated with music
	void Music::setLabel(std::string new_label) {
		m_label = new_label;
	}

	//Get label associated with music.
	std::string Music::getLabel() const {
		return m_label;
	}

	//Play music.
	//If loop is true, repeat play when done.
	void Music::play(bool loop) {
		m_music.play();
		m_music.setLoop(loop);
	}

	//Stop music.
	void Music::stop() {
		m_music.stop();
	}

	//Pause music.
	void Music::pause() {
		m_music.pause();
	}

	//Return pointer to SFML music.
	sf::Music* Music::getMusic() {
		return &m_music;
	}
}