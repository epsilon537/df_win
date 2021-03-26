#include "LogManager.h"
#include <assert.h>
#include <limits.h>
#include "utility.h"

namespace df {

	LogManager::LogManager() : m_do_flush(false), m_log_to_screen(false), m_log_time_string(false), m_p_f(0), m_log_level(DF_DEFAULT_LOG_LEVEL) {
		setType("LogManager");
	}

	LogManager::~LogManager() {
		shutDown();
	}

	//Get the one and only instaance of the LogManager.
	LogManager& LogManager::getInstance() {
		static LogManager logManager;
		return logManager;
	}

	// Start up the LogManager (open logfile "dragonfly.log");
	int LogManager::startUp() {
		m_p_f = fopen(LOGFILE_NAME.c_str(), "w");

		if (m_p_f)
			Manager::startUp();

		return m_p_f ? 0 : -1;
	}

	// Shut down the LogManager (close logfile).
	void LogManager::shutDown() {
		if (m_p_f) {
			int res = fclose(m_p_f);
			assert(res == 0);
			m_p_f = 0;
			Manager::shutDown();
		}
	}

	void LogManager::setLogToScreen(bool do_log_to_screen) {
		m_log_to_screen = do_log_to_screen;
	}

	// Set flush of logfile after each write.
	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}

	// Set logging of current time with log message..
	void LogManager::setLogTime(bool do_log_time) {
		m_log_time_string = do_log_time;
	}

	// Set flush of logfile after each write.
	void LogManager::setLogLevel(int log_level) {
		m_log_level = log_level;
	}

	// Write to logfile. printf formatting.
	// Returns num. bytes written, -1 if error.
	int LogManager::writeLogImp(int log_level, const char* fmt, va_list args) const {
		int res = 0;
		const char* log_level_str_p = 0;

		if (!isStarted())
			return -1;

		if (log_level < m_log_level)
			return 0;

		assert(m_p_f);

		if (m_log_time_string) {
			if (m_log_to_screen)
				printf("%s: ", getTimeString());

			res += fprintf(m_p_f, "%s: ", getTimeString());
			if (res < 0)
				return res;
		}

		switch (log_level) {
		case DBG_LVL:
			log_level_str_p = "DBG: ";
			break;
		case INFO_LVL:
			log_level_str_p = "INFO: ";
			break;
		case IMPORTANT_LVL:
			log_level_str_p = "IMPORTANT: ";
			break;
		case INT_MAX:
			log_level_str_p = "";
			break;
		default:
			static char lvl_str[24];
			int snprintf_res = snprintf(lvl_str, sizeof(lvl_str), "%d: ",
				log_level);
			assert(snprintf_res > 0);
			log_level_str_p = lvl_str;
		}

		assert(log_level_str_p);

		if (m_log_to_screen) {
			printf("%s", log_level_str_p);
			vprintf(fmt, args);
		}

		res += fprintf(m_p_f, "%s", log_level_str_p);
		if (res < 0)
			return res;

		res += vfprintf(m_p_f, fmt, args);
		if (res < 0)
			return res;

		if (m_do_flush) {
			int flush_res = fflush(m_p_f);
			assert(flush_res == 0);
		}

		return res;
	}

	// Write to logfile. printf formatting.
	// Returns num. bytes written, -1 if error.
	int LogManager::writeLog(int log_level, const char* fmt, ...) const {
		int res;

		va_list args;
		va_start(args, fmt);
		res = writeLogImp(log_level, fmt, args);
		va_end(args);

		return res;
	}

	// Write to logfile. printf formatting.
	// using max. log_level.
	// Returns num. bytes written, -1 if error.
	int LogManager::writeLog(const char* fmt, ...) const {
		int res;

		va_list args;
		va_start(args, fmt);
		res = writeLogImp(INT_MAX, fmt, args);
		va_end(args);

		return res;
	}
}