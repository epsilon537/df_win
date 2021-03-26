#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectListIterator.h"
#include "EventStep.h"
#include "Clock.h"
#include <Windows.h>
#include <assert.h>
#include <algorithm>

namespace df {

	GameManager::GameManager() : m_game_over(false), m_frame_time_ms(FRAME_TIME_DEFAULT_MS), m_frame_count(0) {
		setType("GameManager");
	}

	// Get the singletone instance.
	GameManager& GameManager::getInstance() {
		static GameManager gameManager;
		return gameManager;
	}

	// Start all GameManager services.
	// Return 0 if ok, else negative number.
	int GameManager::startUp() {
		if (timeBeginPeriod(1) != TIMERR_NOERROR)
			return -1;
		
		if (LM.startUp() < 0)
			return -1;

		if (WM.startUp() < 0)
			return -1;

		if (DM.startUp() < 0)
			return -1;

		if (IM.startUp() < 0)
			return -1;

		if (RM.startUp() < 0)
			return -1;

		//Set world and view size to DM view dimensions
		Box wvBox(Vector(0, 0), (float)DM.getHorizontal(), (float)DM.getVertical());
		WM.setBoundary(wvBox);
		WM.setView(wvBox);

		Manager::startUp();
		return 0;
	}

	// Show down GameManager services.
	void GameManager::shutDown() {
		setGameOver();

		RM.shutDown();
		IM.shutDown();
		DM.shutDown();
		WM.shutDown();
		LM.shutDown();

		MMRESULT res = timeEndPeriod(1);
		assert(res == TIMERR_NOERROR);

		Manager::shutDown();
	}

	// Run game loop.
	void GameManager::run() {
		assert(isStarted());

		Clock clock;
		int loop_time_us, intended_sleep_time_us, actual_sleep_time_us, adjust_time_us=0;

		while (!m_game_over) {
			clock.delta_us(); //Reset clock

			//Do work here.
			EventStep eventStep(++m_frame_count);
			onEvent(&eventStep);
			
			IM.getInput();
			WM.update();
			WM.draw();
			DM.swapBuffers();

			loop_time_us = clock.split_us();
			intended_sleep_time_us = std::max(0, m_frame_time_ms*1000 - loop_time_us - adjust_time_us);
			clock.delta_us(); //Reset clock
			Sleep(intended_sleep_time_us/1000); //Sleep is in ms.
			actual_sleep_time_us = clock.split_us();
			adjust_time_us = std::max(0, actual_sleep_time_us - intended_sleep_time_us);
		}
	}

	// Set game over status to indicated value.
	// true stops game loop.
	void GameManager::setGameOver(bool new_game_over) {
		m_game_over = new_game_over;
	}

	// Get game over status.
	bool GameManager::getGameOver() const {
		return m_game_over;
	}

	// Return frame time.
	// Frame time is target time for game loop in ms.
	int GameManager::getFrameTimeMs() const {
		return m_frame_time_ms;
	}

	int GameManager::getFrameCount() const {
		return m_frame_count;
	}

	bool GameManager::isValid(std::string event_name) const {
		if (event_name == df::STEP_EVENT)
			return true;

		return false;
	}
}