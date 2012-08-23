#include "logging.h"
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <ios>
Logging* Logging::m_instance(0);
bool Logging::setupConsoleLog( int numLines) {
	if (!AllocConsole())
		return false;
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&conInfo);
	conInfo.dwSize.Y = numLines;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),conInfo.dwSize);

	//stdout
	long lStdHandle((long)GetStdHandle(STD_OUTPUT_HANDLE));
	int hConsole (_open_osfhandle(lStdHandle,_O_TEXT));
	FILE *fp = _fdopen(hConsole,"w");
	*stdout = *fp;
	setvbuf(stdout,NULL, _IONBF,0);

	//stdin
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConsole = _open_osfhandle(lStdHandle,_O_TEXT);
	fp = _fdopen(hConsole,"r");
	*stdin = *fp;
	setvbuf(stdin,NULL, _IONBF,0);

	//sterr
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConsole = _open_osfhandle(lStdHandle,_O_TEXT);
	fp = _fdopen(hConsole,"w");
	*stderr = *fp;
	setvbuf(stderr,NULL, _IONBF,0);

	//resync c++ operators
	std::ios_base::sync_with_stdio();
	return true;
}


bool Logging::setupFileLog() {
	return true;
}