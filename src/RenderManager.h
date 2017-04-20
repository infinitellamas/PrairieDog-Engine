#pragma once
#include "Render.h"


class RenderManager
{
public:
	RenderManager();
	void RenderScene(std::vector<Entity> entities);
	~RenderManager();
private:
	int _cwidth;
	int _cheight;
};

