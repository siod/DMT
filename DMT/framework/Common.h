
#ifndef _COMMON_H
#define _COMMON_H

class Renderer;
class Resource_manager;
class Input;
class Common {
public:
	Common():m_renderer(NULL),m_resources(NULL),m_running(false) {}
	void Quit();
	bool Common::init(int argc, const char** argv,const char* cmdLine);
	void mainLoop();

	inline bool Running() {
		return m_running;
	}


	Renderer* m_renderer;
	Resource_manager* m_resources;
	Input* m_input;
	bool m_running;

};


#endif