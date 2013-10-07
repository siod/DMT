
#ifndef _COMMON_H
#define _COMMON_H

class Renderer;
class Resource_manager;
class Common {
public:
	void Quit();
	bool Common::init(int argc, const char** argv,const char* cmdLine);
	void mainLoop();

private:

	Renderer* m_renderer;
	Resource_manager* m_resources;

};


#endif