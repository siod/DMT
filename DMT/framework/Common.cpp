
#include "..\..\..\c++\SiLib\SiLog\logging.h"
#include "Common.h"
#include "..\sys\sys_public.h"
#include "..\renderer\renderer.h"
#include "resource_manager.h"
#include "..\input\input.h"

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
	if (!m_resources->init()) {
		LogLine("Failed to load config file, aborting",Logging::LOG_ERROR);
		return false;
	}
	m_renderer = new Renderer();
	m_renderer->init();
	m_input->init();

	/*
	entity* teapot = m_resources->loadEntity("..\\resources\\teapot.obj");
	if (teapot) {
		m_renderer->m_queue.push_back(teapot);
	}
	*/

	m_running=true;
	return true;
}

void Common::mainLoop() {
	float ftime(0.0f);
	m_input->frame();
	m_renderer->frame();
}


std::wstring convertToWideString(const SiString& s) {
	std::wstring ws;
	ws.reserve(s.size());
	ws.resize(mbstowcs(&ws[0], s.c_str(), s.size()));
	return ws;
}

