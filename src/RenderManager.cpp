#include "RenderManager.h"

RenderManager::RenderManager()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	_cwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	_cheight = csbi.srWindow.Bottom - csbi.srWindow.Top; // No +1 here because it makes the console flicker. idk why
	std::cout << "init RenderManager success." << std::endl;
	std::cout.flush();
	float c_w = _cwidth, c_h = _cheight;
	frame = (char*)malloc(c_w*c_h);//new[] char[c_w*c_h]; // Current frame
}

int RenderManager::getWindowX() {
	return _cwidth;
}

int RenderManager::getWindowY() {
	return _cheight;
}

void RenderManager::RenderScene(std::vector<Entity*> entities) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	std::vector<Entity*> e_list = entities;
	float c_w = _cwidth, c_h = _cheight;

	std::vector<Entity*> sortedEntity = e_list;
	std::sort(e_list.begin(), e_list.end(), less_than_key()); //This should sort from highest z to lowest z
	
	memset(frame, ' ', c_w*c_h); // Set frame to all spaces.

	//For each entity
	for (unsigned int i = 0; i < e_list.size(); i++) {
		//For each glyph in their glyphset
		for (unsigned int k = 0; k < e_list.at(i)->getGlyphset()->size(); k++) {

			// Get world pos of each glyph
			int w_posx = (int)e_list.at(i)->getPos().x + e_list.at(i)->getGlyphset()->at(k).getPos().x;
			int w_posy = (int)e_list.at(i)->getPos().y + e_list.at(i)->getGlyphset()->at(k).getPos().y;

			// If the glyphs world pos is > -1 and < c_w
			if (w_posx >= 0 && w_posx < c_w) {
				// If the glyphs world pos is > -1 and < c_h
				if (w_posy >= 0 && w_posy < c_h) {

					// convert that to the position in the buffer.
					int bufferPos = w_posy * c_w + w_posx;
					char glyph = e_list.at(i)->getGlyphset()->at(k).getGlyph();

					if (glyph != ' ' && glyph != '`') {// Set the char at that pos to this glyph.
						memset(frame + bufferPos, e_list.at(i)->getGlyphset()->at(k).getGlyph(), 1);
					}if (glyph == '`') { // If it is our specified "remove" character, paste over a space
						memset(frame + bufferPos, ' ', 1);
					}
				}
			}
		}
	}
	//Modify buffer 
	if (_doWobble) {
		for (int i = 0; i < c_w*c_h; i++) {
			int val = rand() % 5;
			char k[5] = { '&','%','$','@','?' };
			if (rand() % 3000 < exp(_wobbleAmount)) {
				memset(frame + i, k[val], 1);
			}
		}
	}

	fwrite(frame, c_w*c_h, 1, stdout);
	//std::cout.write(frame, c_w*c_h);
	//free(frame);
}

void RenderManager::setWobble(bool doWobble, int amount) {
	_doWobble = doWobble;
	_wobbleAmount = amount;
}


RenderManager::~RenderManager()
{
}
