
#ifndef _LOGGING_
#define _LOGGING_
//#include <stdio.h>
#include <string>
#include <iostream>


#ifdef Log
#undef Log
#undef LogLine
#endif

class Logging {
	public:

		Logging(bool enabled, bool toConsole = false, bool toFile = false): m_enabled(enabled), m_toConsole(toConsole), m_toFile(toFile)
		{
			if (toConsole)
				setupConsoleLog();
			if (toFile)
				setupFileLog();
		}



		// Singleton setup
		static void CreateLog(bool enabled, bool toConsole = false, bool toFile = false) {
			if (m_instance)
				return;
			m_instance = new Logging(enabled,toConsole,toFile);
		}

		static void DestroyLog() {
			if (!m_instance)
				return;
			delete m_instance;
			m_instance = NULL;
		}

		bool setupFileLog();
		bool setupConsoleLog( int numLines = 200);

		void log(std::wstring& input) {
			if (!m_enabled)
				return;
			std::wcout << input;
		}

		void logLine(std::wstring& input) {
			log(input);
			log("\n");
		}

		void log(const char* input) {
			if (!m_enabled)
				return;
			std::cout << input;
		}

		void logLine(const char* input) {
			log(input);
			log("\n");
		}


		//HACK Temp function
		static void Get() {
			if (m_instance)
				std::cin.get();
		}


		static void Log(std::wstring& input) {
			if (m_instance)
				m_instance->log(input);
		}

		static void LogLine(std::wstring& input) {
			if (m_instance)
				m_instance->logLine(input);
		}

		static void Log(const char* input) {
			if (m_instance)
				m_instance->log(input);
		}


		static void LogLine(const char* input) {
			if (m_instance)
				m_instance->logLine(input);
		}

	private:
		const bool m_enabled;
		const bool m_toConsole;
		const bool m_toFile;
		static Logging* m_instance;



};

#define Log Logging::Log
#define LogLine Logging::LogLine


#endif
