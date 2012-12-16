
#ifndef _COMMON_H
#define _COMMON_H

class Renderer;
class Common {
public:
	void Quit();
	bool Common::init(int argc, const char** argv,const char* cmdLine);

private:

	Renderer* m_renderer;

};


#endif