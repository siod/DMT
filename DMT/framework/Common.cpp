
#include "..\Sys\logging.h"
#include "Common.h"
#include "..\sys\sys_public.h"
#include "..\renderer\renderer.h"

Common com;
Common * common = &com;

void Common::Quit() {
	Sys_Quit();
}

bool Common::init(int argc, const char** argv,const char* cmdLine) {
	Logging::init(true,Logging::LOG_DEBUG,true,false);
	Sys_Init();
	m_renderer = new Renderer();
	m_renderer->init();

	return true;
}
