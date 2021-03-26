#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include <stdio.h>
#include "Manager.h"
#include <stdarg.h>

// Two-letter acronym for easier access to manager.
#define LM df::LogManager::getInstance()

#define DF_DEFAULT_LOG_LEVEL df::INFO_LVL

namespace df {
	const std::string LOGFILE_NAME = "dragonfly.log";
	const int DBG_LVL = 100;
	const int INFO_LVL = 200;
	const int IMPORTANT_LVL = 300;

	class LogManager : public Manager {
	private:
		LogManager(); // Private, singleton.
		LogManager(LogManager const&); //Don't allow copy.

		int writeLogImp(int log_level, const char* fmt, va_list args) const;

		void operator=(LogManager const&); //Dont allow assignment.
		bool m_do_flush; //True if flush to disk after each write.
		bool m_log_to_screen; //True if logging to screen is enabled.
		bool m_log_time_string; //True if current time should be logged with each message.
		FILE* m_p_f; //Pointer to logfile struct.
		int m_log_level; // Logging level.

	public:
		~LogManager();

		//Get the one and only instaance of the LogManager.
		static LogManager& getInstance();

		// Start up the LogManager (open logfile "dragonfly.log");
		// Return 0 if ok, else negative number.
		int startUp();

		// Shut down the LogManager (close logfile).
		void shutDown();

		// Set the log_level to be used by the LogManager.
		void setLogLevel(int log_level);

		void setLogToScreen(bool do_log_to_screen = true);

		// Set flush of logfile after each write.
		void setFlush(bool do_flush = true);

		// Set logging of current time with log message..
		void setLogTime(bool do_log_time = true);

		// Write to logfile. printf formatting.
		// Only write if indicated log level >= LogManager log level.
		// Returns num. bytes written, -1 if error.
		int writeLog(int log_level, const char* fmt, ...) const;

		// Write to logfile. printf formatting.
		// using max. log_level.
		// Returns num. bytes written, -1 if error.
		int writeLog(const char* fmt, ...) const;
	};
} // end of namespace df.
#endif /*LOG_MANAGER*/
