
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "model.h"
#include "renderView.h"
#include <vector>

class Renderer {

public:
	void init();
	void frame();
	void addView(renderView& view);


private:
	bool allocateView(renderView& unallocView);

	std::vector<renderView> m_views;
	std::vector<renderModel> m_queue;



};

#endif