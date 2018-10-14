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

	extern Image explosionImage;

	//gameplay
	//extern Texture2D ship;
	//extern Texture2D shipMoving;
	//extern Texture2D crosshair;
	//extern Texture2D asteroidExplosion;

	//game
	extern Image asteroidImage;
	extern Texture2D asteroid;
	extern Texture2D asteroidMedium;
	extern Texture2D asteroidSmall;
	extern Texture2D backgroundGame;

	//gameover
	//extern Texture2D shipExplosion;

	
	

	#ifdef AUDIO

	extern Sound ship_explode01;
	extern Sound ship_shoot01;
	extern Sound asteroid_explode01;
	extern Sound powerup01;

	extern Music ship_rocket01;
	extern Music song_alert;

	#endif

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

	void checkAsteroidSprite();
	void resolutionBackground();
	void DrawBackground();
	void Execute();
}
#endif // GAME_H