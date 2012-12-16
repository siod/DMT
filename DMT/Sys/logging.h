
#ifndef _LOGGING_
#define _LOGGING_
//#include <stdio.h>
#include <string>
#include <iostream>


/*
#ifdef Log
#undef Log
#undef LogLine
#endif
*/

class Logging {
	public:
		enum LOG_LEVEL {LOG_DEBUG,
						LOG_INFO,
						LOG_ERROR };
				

		Logging(bool enabled,LOG_LEVEL logLevel, bool toConsole = false, bool toFile = false): m_enabled(enabled), m_toConsole(toConsole), m_toFile(toFile),m_logLevel(logLevel)
		{
			if (toConsole)
				setupConsoleLog();
			if (toFile)
				setupFileLog();
		}



		// Singleton setup
		static void init(bool enabled, LOG_LEVEL level, bool toConsole = false, bool toFile = false) {
			if (m_instance)
				return;
			m_instance = new Logging(enabled,level,toConsole,toFile);
		}

		static void DestroyLog() {
			if (!m_instance)
				return;
			delete m_instance;
			m_instance = NULL;
		}

		bool setupFileLog();
		bool setupConsoleLog( int numLines = 200);

		void log(std::wstring& input,LOG_LEVEL level) {
			if (!m_enabled || level > m_logLevel)
				return;
			std::wcout << input;
		}

		void logLine(std::wstring& input, LOG_LEVEL level) {
			if (!m_enabled || level > m_logLevel)
				return;
			log(input,level);
			log("\n",level);
		}

		void log(const char* input,LOG_LEVEL level) {
			if (!m_enabled || level > m_logLevel)
				return;
			std::cout << input;
		}

		void logLine(const char* input,LOG_LEVEL level) {
			if (!m_enabled || level > m_logLevel)
				return;
			log(input,level);
			log("\n",level);
		}


		//HACK Temp function
		static void Get() {
			if (m_instance)
				std::cin.get();
		}


		static void Log(std::wstring& input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->log(input,level);
		}

		static void LogLine(std::wstring& input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->logLine(input,level);
		}

		static void Log(const char* input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->log(input,level);
		}


		static void LogLine(const char* input,LOG_LEVEL level) {
			if (m_instance)
				m_instance->logLine(input,level);
		}

	private:
		const bool m_enabled;
		const bool m_toConsole;
		const bool m_toFile;
		const LOG_LEVEL m_logLevel;
		static Logging* m_instance;



};


#endif
