#ifndef __DF_RESOURCE_MANAGER_H__
#define __DF_RESOURCE_MANAGER_H__

#include "Manager.h"
#include "Frame.h"
#include "Sound.h"
#include "Music.h"

#include <string>
#include <fstream>
#include <vector>

// Two-letter acronym for easier access to manager.
#define RM df::ResourceManager::getInstance()

namespace df {
	class Sprite;

	//Max. number of unique sprite assets in game.
	const int MAX_SPRITES = 1000;

	const int MAX_SOUNDS = 128;
	const int MAX_MUSICS = 128;

	//Delimiters used to parse Sprite files
	const std::string HEADER_TOKEN = "HEADER";
	const std::string BODY_TOKEN = "BODY";
	const std::string FOOTER_TOKEN = "FOOTER";
	const std::string FRAMES_TOKEN = "frames";
	const std::string HEIGHT_TOKEN = "height";
	const std::string WIDTH_TOKEN = "width";
	const std::string COLOR_TOKEN = "color";
	const std::string SLOWDOWN_TOKEN = "slowdown";
	const std::string END_FRAME_TOKEN = "end";
	const std::string VERSION_TOKEN = "version";

	const std::string COLOR_TOKEN_BLACK = "black";
	const std::string COLOR_TOKEN_RED = "red";
	const std::string COLOR_TOKEN_GREEN = "green";
	const std::string COLOR_TOKEN_YELLOW = "yellow";
	const std::string COLOR_TOKEN_BLUE = "blue";
	const std::string COLOR_TOKEN_MAGENTA = "magenta";
	const std::string COLOR_TOKEN_CYAN = "cyan";
	const std::string COLOR_TOKEN_WHITE = "white";

	//Remove '\r' from line if present.
	void discardCR(std::string& str);

	// Get next line from file, with error checking ("" means error).
	std::string getLine(std::ifstream* p_file);

	// Read in next section of data from file as vector of strings.
	// File line number is passed in and updated by this function.
	// Return vector (empty if error).
	std::vector<std::string> readData(std::ifstream* p_file,
		std::string delimiter, int &lineNbr);

	// Match token in vector of lines (e.g. "frames 5").
	// Return corresponding value (e.g., 5) (-1 if not found).
	// Remove any line that matches from vector.
	int matchLineInt(std::vector<std::string>* p_data, const char* token);

	// Match token in vector of line (e.g. "color green").
	// Return corresponding string (e.g. "green") ("" if not found).
	// Remove any line that matches from vector.
	std::string matchLineStr(std::vector<std::string>* p_data, const char* token);

	// Match frame lines until "end", clearing all from vector.
	// File line number is passed in and updated by this function.
	// Return Frame.
	Frame matchFrame(std::vector<std::string>* p_data, int width, int height, int &lineNbr);

	class ResourceManager : public Manager {
	private:
		ResourceManager();
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&);

		Sprite* m_p_sprite[MAX_SPRITES]; //Array of sprites.
		int m_sprite_count; //Count of number of loaded sprites.
		Sound m_sound[MAX_SOUNDS]; //Array of sound buffers.
		int m_sound_count; //Count of number of loaded sounds.
		Music m_music[MAX_MUSICS]; //Array of music buffers.
		int m_music_count; //Count of number of loaded musics.
	
	public:
		// Get the one and only instance of the ResourceManager.
		static ResourceManager& getInstance();

		// Get Resource Manager ready to manage resources.
		int startUp();

		// Shut down Resource Manager, freeing up allocated resources.
		void shutDown();

		// Load sprite from file.
		// Assign indicated label to sprite.
		// Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		// Unload sprite with indicated label.
		// Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		// Find Sprite with indicated label.
		// Return pointer to it if found, else NULL.
		Sprite* getSprite(std::string label) const;

		//Load Sound from file.
		//Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		//Remove Sound with indicated label.
		//Return 0 if ok, else -1.
		int unloadSound(std::string label);

		//Find Sound with indicated label.
		//Return pointer to it if found, else 0.
		Sound* getSound(std::string label);

		//Associate file with Music.
		//Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		//Remove Music with indicated label.
		//Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		//Find Music with indicated label.
		//Return pointer to it if found, else 0.
		Music* getMusic(std::string label);
	};
}

#endif /*DF_RESOURCE_MANAGER_H*/
