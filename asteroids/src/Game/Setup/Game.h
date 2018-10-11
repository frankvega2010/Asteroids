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
	extern Texture2D asteroid;
	extern Texture2D asteroidMedium;
	extern Texture2D asteroidSmall;
	extern Texture2D backgroundGame;
	extern Texture2D crosshair;
	extern Texture2D shipExplosion;
	extern Texture2D asteroidExplosion;

	extern Rectangle backgroundGameSource;
	extern Rectangle backgroundGameDestination;
	extern Vector2 backgroundGameOrigin;

	extern Buttons mouse;
	extern int buttonOption;

	extern int gameScreen;
	extern int screenWidth;
	extern int screenHeight;
	extern int defaultFontSize;

	extern bool isScreenFinished;

	void DrawBackground();
	void Execute();
}
#endif // GAME_H