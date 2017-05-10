#pragma once
#include "Glyph.h"
#include "Entity.h"
#include <vector>
#include <algorithm>
#include <iostream>


struct less_than_key
{
	inline bool operator() (Entity* e1, Entity* e2)
	{
		return (e1->getPos().z < e2->getPos().z);
	}
};


static void Render(int c_w, int c_h, std::vector<Entity> e_list) {
	
}