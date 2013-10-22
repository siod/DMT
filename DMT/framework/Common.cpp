
#include "..\..\..\c++\SiLib\SiLog\logging.h"
#include "Common.h"
#include "..\sys\sys_public.h"
#include "..\renderer\renderer.h"
#include "resource_manager.h"
#pragma comment(lib, "SiConf.lib")
#pragma comment(lib, "SiLog.lib")

Common com;
Common * common = &com;

void Common::Quit() {
	Log("Shutting down\n",Logging::LOG_DEBUG);
	m_running = false;
}

bool Common::init(int argc, const char** argv,const char* cmdLine) {
	Logging::init(Logging::LOG_DEBUG,true,true,"dmt.log");
	Sys_Init();
	m_resources = new Resource_manager();
	m_resources->init();
	m_renderer = new Renderer();
	m_renderer->init();
	m_resources->loadEntity("..\\resources\\teapot.obj");

	m_running=true;
	return true;
}

void Common::mainLoop() {
	float ftime(0.0f);
	m_renderer->frame();
}


std::wstring convertToWideString(const SiString& s) {
	std::wstring ws;
	ws.reserve(s.size());
	ws.resize(mbstowcs(&ws[0], s.c_str(), s.size()));
	return ws;
}

