#include "RenderManager.h"

RenderManager::RenderManager()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	_cwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	_cheight = csbi.srWindow.Bottom - csbi.srWindow.Top; // No +1 here because it makes the console flicker. idk why
	std::cout << "init RenderManager success." << std::endl;
	std::cout.flush();
}

void RenderManager::RenderScene(std::vector<Entity> entities) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	Render(_cwidth, _cheight, entities);
}


RenderManager::~RenderManager()
{
}
