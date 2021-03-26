#ifndef __DF_GAME_MANAGER_H__
#define __DF_GAME_MANAGER_H__

#include "Manager.h"

// Two-letter acronym for easier access to manager.
#define GM df::GameManager::getInstance()

namespace df {
	// Default frame time (game loop time) in ms (33ms = 30fps).
	const int FRAME_TIME_DEFAULT_MS = 33;

	class GameManager : public Manager {
	private:
		GameManager(); // Private since a singleton.
		GameManager(GameManager const&); //Don't allow copy.
		void operator=(GameManager const&); //Don't allow assignment.
		bool m_game_over; //Game loop stops when true.
		int m_frame_time_ms; //Target time per game loop in ms.
		int m_frame_count; //Increments by 1 each pass through the game loop.

	public:
		// Get the singletone instance.
		static GameManager& getInstance();

		// Start all GameManager services.
		// Return 0 if ok, else negative number.
		int startUp();

		// Show down GameManager services.
		void shutDown();

		// Run game loop.
		void run();

		// Set game over status to indicated value.
		// true stops game loop.
		void setGameOver(bool new_game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Return frame time.
		// Frame time is target time for game loop in ms.
		int getFrameTimeMs() const;

		// Return current frame counter.
		int getFrameCount() const;

		bool isValid(std::string event_name) const;
	};
}

#endif /*DF_GAME_MANAGER_H*/