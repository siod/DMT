#include <windows.h>
#include <string>
#include <iostream>

#include "logging.h"

using std::wstring;



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	if (strstr(cmdLine,"-log") != NULL) {
		Logging::CreateLog(true,true);
	}
	Log("log Test\n");
	Log("DMTv1.0a\n");
	//std::cout << "DMTv1.0a\n";
	Logging::Get();
	Logging::DestroyLog();
	return 0;

}
