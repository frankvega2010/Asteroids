#ifndef GAME_H
#define GAME_H

#include "raylib.h"

namespace Juego
{
	enum Screens
	{
		Play = 1,
		Menu,
		Quit
	};

	struct Buttons { //array de botones
		Vector2 position;
		float width;
		float height;
		bool selected;
		Color defaultColor;
	};

	extern Buttons mouse;
	extern int buttonOption;

	extern int gameScreen;
	extern int screenWidth;
	extern int screenHeight;
	extern int defaultFontSize;

	extern bool isScreenFinished;

	void Execute();
}
#endif // GAME_H