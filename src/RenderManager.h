#pragma once
#include "Render.h"


class RenderManager
{
public:
	RenderManager();
	int getWindowX();
	int getWindowY();
	void RenderScene(std::vector<Entity*> entities);
	void setWobble(bool doWobble, int amount);
	~RenderManager();
private:
	int _wobbleAmount;
	bool _doWobble;
	char* frame;
	int _cwidth;
	int _cheight;
	int _camX;
	int _camY;
};

