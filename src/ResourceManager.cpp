#include "ResourceManager.h"
#include "LogManager.h"
#include "Sprite.h"
#include "Color.h"

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

namespace df {
	//Remove '\r' from line if present.
	void discardCR(std::string& str) {
		if (!str.empty() and (str[str.size()-1] == '\r'))
			str.erase(str.size()-1);
	}

	// Get next line from file, with error checking ("" means error).
	std::string getLine(std::ifstream* p_file) {
		assert(p_file);
		
		std::string line;
		std::getline(*p_file, line);

		if (!p_file->good()) {
			return ""; // File input error.
		}

		discardCR(line);

		return line;
	}

	// Read in next section of data from file as vector of strings.
	// Return vector (empty if error).
	std::vector<std::string> readData(std::ifstream* p_file,
		std::string delimiter, int &lineNbr) {
		std::string begin = "<" + delimiter + ">"; //Section beginning
		std::string end = "</" + delimiter + ">"; //Section end.

		std::vector <std::string> v;

		//Check for beginning.
		std::string s = getLine(p_file);
		if (s != begin) {
			LM.writeLog(IMPORTANT_LVL, "Begin delimiter missing at line %d\n", lineNbr);
			return v; //empty vector indicates error.
		}

		++lineNbr;

		//Read in data until ending (or not found).
		s = getLine(p_file);
		while ((s != end) && !s.empty()) {
			++lineNbr;

			v.push_back(s);
			s = getLine(p_file);
		}

		//If ending not found, then error.
		if (s.empty()) {
			LM.writeLog(IMPORTANT_LVL, "End delimiter missing at line %d\n", lineNbr);
			return std::vector <std::string>(); //empty vector indicates error.
		}

		++lineNbr;
		return v;
	}

	// Match token in vector of lines (e.g. "frames 5").
	// Return corresponding value (e.g., 5) (-1 if not found).
	// Remove any line that matches from vector.
	int matchLineInt(std::vector<std::string>* p_data, const char* token) {
		assert(p_data);
		assert(token);

		int number=-1;

		//Loop through all lines.
		auto iter = p_data->begin(); //vector iterator
		while (iter != p_data->end()) {
			if (!iter->compare(0, strlen(token), token)) {
				number = atoi(iter->substr(strlen(token) + 1).c_str());
				iter = p_data->erase(iter); //Remove item from vector.
				break;
			}
		
			++iter;
		}

		return number;
	}

	// Match token in vector of line (e.g. "color green").
	// Return corresponding string (e.g. "green") ("" if not found).
	// Remove any line that matches from vector.
	std::string matchLineStr(std::vector<std::string>* p_data, const char* token) {
		assert(p_data);
		assert(token);

		std::string str;

		//Loop through all lines.
		auto iter = p_data->begin(); //vector iterator
		while (iter != p_data->end()) {
			if (!iter->compare(0, strlen(token), token)) {
				str = iter->substr(strlen(token) + 1);
				iter = p_data->erase(iter); //Remove item from vector.
				break;
			}

			++iter;
		}

		return str;
	}

	// Match frame lines until "end", clearing all from vector.
	// Return Frame.
	Frame matchFrame(std::vector<std::string>* p_data, int width, int height, int &lineNbr) {
		assert(p_data);

		std::string line, frame_str;

		for (int ii = 0; ii < height; ii++) {
			line = p_data->front();

			if (line.size() != width) {
				LM.writeLog(IMPORTANT_LVL, "Incorrect frame width at line %d: %d should be %d\n", lineNbr, line.size(), width);
				return Frame();
			}

			++lineNbr;
			p_data->erase(p_data->begin());
			frame_str += line;
		}

		line = p_data->front();
		if (line != END_FRAME_TOKEN) {
			LM.writeLog(IMPORTANT_LVL, "Could not find end frame token at line %d\n", lineNbr);
			return Frame();
		}

		++lineNbr;
		p_data->erase(p_data->begin());

		return Frame(width, height, frame_str);
	}


	ResourceManager::ResourceManager() : m_sprite_count(0), m_sound_count(0), m_music_count(0) {
		setType("ResourceManager");
	}

	// Get the one and only instance of the ResourceManager.
	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager resourceManager;
		return resourceManager;
	}

	// Get Resource Manager ready to manage resources.
	int ResourceManager::startUp() {
		m_sprite_count = 0;
		m_sound_count = 0;
		m_music_count = 0;

		return Manager::startUp();
	}

	// Shut down Resource Manager, freeing up allocated resources.
	void ResourceManager::shutDown() {
		for (int ii = 0; ii < m_sprite_count; ii++) {
			assert(m_p_sprite[ii]);
			delete m_p_sprite[ii];
			m_p_sprite[ii] = 0;
		}

		Manager::shutDown();
	}

	// Load sprite from file.
	// Assigned indicated label to sprite.
	// Return 0 if ok, else -1.
	int ResourceManager::loadSprite(std::string filename, std::string label) {
		if (m_sprite_count >= MAX_SPRITES) {
			LM.writeLog(IMPORTANT_LVL, "RM: Max. sprite limit reached. Can't load sprite: %s\n", label.c_str());
			return -1;
		}

		if (getSprite(label)) {
			LM.writeLog(IMPORTANT_LVL, "RM: Sprite label %s already in use.\n", label.c_str());
			return -1;
		}

		LM.writeLog(INFO_LVL, "RM: loading sprite file: %s\n", filename.c_str());

		std::ifstream ifs;

		ifs.open(filename, std::ifstream::in);

		if (!ifs.good()) {
			LM.writeLog(IMPORTANT_LVL, "RM: Failed to open file: %s\n", filename.c_str());
			return -1;
		}

		int lineNbr = 1;

		//header has sprite format data.
		std::vector<std::string> header = readData(&ifs, HEADER_TOKEN, lineNbr);
		if (header.empty()) {
			LM.writeLog(IMPORTANT_LVL, "Failed to read %s section of file: %s\n", HEADER_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		int frames = matchLineInt(&header, FRAMES_TOKEN.c_str());
		if (frames == -1) {
			LM.writeLog(IMPORTANT_LVL, "Could not find %s field in file: %s\n", FRAMES_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		int height = matchLineInt(&header, HEIGHT_TOKEN.c_str());
		if (height == -1) {
			LM.writeLog(IMPORTANT_LVL, "Could not find %s field in file: %s\n", HEIGHT_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		int width = matchLineInt(&header, WIDTH_TOKEN.c_str());
		if (width == -1) {
			LM.writeLog(IMPORTANT_LVL, "Could not find %s field in file: %s\n", WIDTH_TOKEN.c_str(), filename.c_str());
			return -1;
		}
		
		std::string colorStr = matchLineStr(&header, COLOR_TOKEN.c_str());
		if (colorStr.empty()) {
			LM.writeLog(IMPORTANT_LVL, "Could not find %s field in file: %s\n", COLOR_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		Color color = UNDEFINED_COLOR;

		if (colorStr == COLOR_TOKEN_BLACK)
			color = df::BLACK;
		else if (colorStr == COLOR_TOKEN_RED)
			color = df::RED;
		else if (colorStr == COLOR_TOKEN_GREEN)
			color = df::GREEN;
		else if (colorStr == COLOR_TOKEN_YELLOW)
			color = df::YELLOW;
		else if (colorStr == COLOR_TOKEN_BLUE)
			color = df::BLUE;
		else if (colorStr == COLOR_TOKEN_MAGENTA)
			color = df::MAGENTA;
		else if (colorStr == COLOR_TOKEN_CYAN)
			color = df::CYAN;
		else if (colorStr == COLOR_TOKEN_WHITE)
			color = df::WHITE;
		
		int slowdown = matchLineInt(&header, SLOWDOWN_TOKEN.c_str());
		if (slowdown == -1) {
			LM.writeLog(IMPORTANT_LVL, "Could not find %s field in file: %s\n", SLOWDOWN_TOKEN.c_str(), filename.c_str());
			return -1;
		}
		
		int lineNbrTemp = lineNbr;

		// Body has frame fata
		std::vector<std::string> body = readData(&ifs, BODY_TOKEN, lineNbr);
		if (body.empty()) {
			LM.writeLog(IMPORTANT_LVL, "Failed to read %s section of file: %s\n", BODY_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		//Reset line nbr to beginning of body contents.
		lineNbr = lineNbrTemp + 1;

		Sprite *sprite_p = new Sprite(frames);

		if (!sprite_p) {
			LM.writeLog(IMPORTANT_LVL, "Failed to allocate memory for sprite %s\n", BODY_TOKEN.c_str(), label.c_str());
			return -1;
		}

		for (int ii = 0; ii < frames; ii++) {
			Frame frame = matchFrame(&body, width, height, lineNbr);

			if (frame.isEmpty()) {
				LM.writeLog(IMPORTANT_LVL, "Failed to parse frame data for sprite %s\n", label.c_str());
				return -1;
			}

			sprite_p->addFrame(frame);
		}

		sprite_p->setColor(color);
		sprite_p->setHeight(height);
		sprite_p->setWidth(width);
		sprite_p->setSlowdown(slowdown);
		sprite_p->setLabel(label);

		//Footer has sprite version data.
		std::vector<std::string> footer = readData(&ifs, FOOTER_TOKEN, lineNbr);
		if (footer.empty()) {
			LM.writeLog(IMPORTANT_LVL, "Failed to read %s section of file: %s\n", FOOTER_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		int version = matchLineInt(&footer, VERSION_TOKEN.c_str());
		if (version == -1) {
			LM.writeLog(IMPORTANT_LVL, "Could not find %s field in file: %s\n", VERSION_TOKEN.c_str(), filename.c_str());
			return -1;
		}

		ifs.close();

		m_p_sprite[m_sprite_count++] = sprite_p;

		return 0;
	}

	// Unload sprite with indicated label.
	// Return 0 if ok, else -1.
	int ResourceManager::unloadSprite(std::string label) {
		for (int ii = 0; ii < m_sprite_count; ii++) {
			Sprite* sprite = m_p_sprite[ii];
			assert(sprite);

			if (label == sprite->getLabel()) {
				delete sprite;

				//Scoot over remaining sprites.
				for (int jj = ii; jj < m_sprite_count - 1; jj++) {
					m_p_sprite[jj] = m_p_sprite[jj + 1];
				}

				--m_sprite_count;

				return 0;
			}
		}

		LM.writeLog(INFO_LVL, "Can't unload sprite %s. Sprite not found.\n", label.c_str());
		return -1; //Sprite not found.
	}

	// Find Sprite with indicated label.
	// Return pointer to it if found, else NULL.
	Sprite* ResourceManager::getSprite(std::string label) const {
		for (int ii = 0; ii < m_sprite_count; ii++) {
			Sprite* sprite = m_p_sprite[ii];
			assert(sprite);

			if (label == sprite->getLabel()) {
				return sprite;
			}
		}

		return 0; //Sprite not found.
	}

	//Load Sound from file.
	//Return 0 if ok, else -1.
	int ResourceManager::loadSound(std::string filename, std::string label) {
		if (m_sound_count >= MAX_SOUNDS) {
			LM.writeLog("Sound array full.\n");
			return -1;
		}

		if (m_sound[m_sound_count].loadSound(filename) == -1) {
			LM.writeLog("Unable to load file.\n");
			return -1;
		}

		//All set.
		m_sound[m_sound_count].setLabel(label);
		++m_sound_count;

		return 0;
	}

	//Remove Sound with indicated label.
	//Return 0 if ok, else -1.
	int ResourceManager::unloadSound(std::string label) {
		for (int ii=0; ii < m_sound_count; ii++) {
			if (label == m_sound[ii].getLabel()) {
				//Scoot over remaining sounds.
				for (int jj = ii; jj < m_sound_count - 1; jj++) {
					m_sound[jj] = m_sound[jj + 1];
				}

				--m_sound_count;
				return 0;
			}
		}

		return -1; //Sound not found.
	}

	//Find Sound with indicated label.
	//Return pointer to it if found, else 0.
	Sound* ResourceManager::getSound(std::string label) {
		for (int ii=0; ii < m_sound_count; ii++) {
			if (label == m_sound[ii].getLabel()) {
				return &m_sound[ii];
			}
		}

		return 0; //Sound not found.
	}

	//Associate file with Music.
	//Return 0 if ok, else -1.
	int ResourceManager::loadMusic(std::string filename, std::string label) {
		//Empty label not allowed for music.
		assert(!label.empty());

		if (m_music_count >= MAX_MUSICS) {
			LM.writeLog("Music array full.\n");
			return -1;
		}

		if (m_music[m_music_count].loadMusic(filename) == -1) {
			LM.writeLog("Unable to load file.\n");
			return -1;
		}

		//All set.
		m_music[m_music_count].setLabel(label);
		++m_music_count;

		return 0;
	}

	//Remove Music with indicated label.
	//Return 0 if ok, else -1.
	int ResourceManager::unloadMusic(std::string label) {
		for (int ii=0; ii < m_music_count; ii++) {
			if (label == m_music[ii].getLabel()) {
				m_music[ii].setLabel("");
				return 0;
			}
		}

		return -1;
	}

	//Find Music with indicated label.
	//Return pointer to it if found, else 0.
	Music* ResourceManager::getMusic(std::string label) {
		for (int ii=0; ii < m_music_count; ii++) {
			if (label == m_music[ii].getLabel()) {
				return &m_music[ii];
			}
		}

		return 0; //Music not found.
	}
}