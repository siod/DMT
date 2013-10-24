
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "model.h"
#include "renderView.h"
#include "..\framework\entity.h"
#include <vector>

class Renderer {

public:
	void init();
	void frame();
	void addView(renderView& view);


//private:
	void allocateView(renderView& unallocedView);

	std::vector<renderView> m_views;
	std::vector<entity*> m_queue;



};

#endif