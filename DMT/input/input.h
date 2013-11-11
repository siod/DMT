

#ifndef __DMT_INPUT__
#define __DMT_INPUT__
#if defined _WIN32
	//typedef Win_input Base_input;
#else

#endif

struct input_vibration {
	unsigned short l;
	unsigned short r;
};
class Input {

public:

	void init();
	void frame();


};
#endif
