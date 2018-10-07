#ifndef GAME_H
#define GAME_H
#include <string>
#include "raylib.h"
using namespace std;

namespace Juego
{
	enum Screens
	{
		Play = 1,
		Menu,
		Controls,
		GameOver,
		Quit,
		Credits,
		Settings
	};

	struct Buttons { //array de botones
		Vector2 position;
		float width;
		float height;
		bool selected;
		Color messageColor;
		Color defaultColor;
	};

	extern Texture2D scheme_arrows01;
	extern Texture2D scheme_sign01;
	extern Texture2D ship;

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