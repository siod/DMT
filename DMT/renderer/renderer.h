
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "model.h"
#include "renderView.h"
#include "..\framework\entity.h"
#include <vector>

struct Renderable {
	Renderable(vec3& pos_,vec4& rot_, renderModel& model_)
		:pos(pos_),rot(rot_),model(model_) {}

	vec3& pos;
	vec4& rot;
	renderModel& model;
};

class Renderer {

public:
	void init();
	void populateQueue(std::vector<entity*>& entities);
	void frame();
	void addView(renderView& view);


//private:
	void allocateView(renderView& unallocedView);

	std::vector<renderView> m_views;
	std::vector<Renderable> m_queue;



};

#endif