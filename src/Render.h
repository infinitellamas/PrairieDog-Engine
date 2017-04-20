#pragma once
#include "Glyph.h"
#include "Entity.h"
#include <vector>
#include <algorithm>
#include <iostream>


struct less_than_key
{
	inline bool operator() (Entity e1, Entity e2)
	{
		return (e1.getPos().z < e2.getPos().z);
	}
};


static void Render(int c_w, int c_h, std::vector<Entity> e_list) {
	std::vector<Entity> sortedEntity = e_list;
	std::sort(e_list.begin(), e_list.end(), less_than_key()); //This should sort from highest z to lowest z
	char* frame = new char[c_w*c_h]; // Current frame
	memset(frame,' ', c_w*c_h); // Set frame to all spaces.

	//For each entity
	for (unsigned int i = 0; i < e_list.size(); i++) {
		//For each glyph in their glyphset
		for (unsigned int k = 0; k < e_list.at(i).getGlyphset().size(); k++) {
			
			// Get world pos of each glyph
			int w_posx = (int)round(e_list.at(i).getPos().x + e_list.at(i).getGlyphset().at(k).getPos().x);
			int w_posy = (int)round(e_list.at(i).getPos().y + e_list.at(i).getGlyphset().at(k).getPos().y);

			// If the glyphs world pos is > -1 and < c_w
			if (w_posx >= 0 && w_posx < c_w) {
				// If the glyphs world pos is > -1 and < c_h
				if (w_posy >= 0 && w_posy < c_h) {
				
					// convert that to the position in the buffer.
					int bufferPos = w_posy * c_w + w_posx;
					char glyph = e_list.at(i).getGlyphset().at(k).getGlyph();
					
					if (glyph != ' ' && glyph != '`') {// Set the char at that pos to this glyph.
						memset(frame + bufferPos, e_list.at(i).getGlyphset().at(k).getGlyph(), 1);
					}if (glyph == '`') { // If it is our specified "remove" character, paste over a space
						memset(frame + bufferPos, ' ', 1);
					}
				}
			}
		}
	}
	
	std::cout.write(frame,c_w*c_h);
	delete frame; 
}