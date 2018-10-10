#include "Game.h"

#include "Screens/gameplay.h"
#include "Screens/menu.h"
#include "Screens/gameover.h"
#include "Screens/settings.h"
#include "Screens/credits.h"
#include "Screens/controls.h"
#include "Setup\Asteroid.h"

using namespace Juego;
using namespace Gameplay_Section;
using namespace GameOver_Section;
using namespace Menu_Section;
using namespace Settings_Section;
using namespace Credits_Section;
using namespace Controls_Section;

namespace Juego
{
	int gameScreen = Menu;

	int screenWidth;
	int screenHeight;
	Buttons mouse;
	int buttonOption = 0;

	int defaultFontSize = 60;

	bool isScreenFinished;

	//source = { 0.0f,0.0f, (float)screenWidth,(float)screenHeight };
	//dest = { 0,0, (float)screenWidth,(float)screenHeight };
	// origin = { 0,0 };

	Rectangle backgroundGameSource;
	Rectangle backgroundGameDestination;
	Vector2 backgroundGameOrigin;

	Texture2D scheme_arrows01;
	Texture2D scheme_sign01;
	Image shipImage;
	Image asteroidImage;
	Image asteroidSmallImage;
	Image asteroidMediumImage;
	Image backgroundGameImage;
	Image crosshairImage;
	Image explosionImage;
	Texture2D ship;
	Texture2D asteroid;
	Texture2D asteroidMedium;
	Texture2D asteroidSmall;
	Texture2D backgroundGame;
	Texture2D crosshair;
	Texture2D shipExplosion;

	#ifdef AUDIO

	// Audio Code

	#endif

	void DrawBackground()
	{
		backgroundGameSource = { 0.0f,0.0f, (float)screenWidth,(float)screenHeight };
		backgroundGameDestination = { 0,0, (float)screenWidth,(float)screenHeight };
		backgroundGameOrigin = { 0,0 };
		
		DrawTexturePro(backgroundGame, backgroundGameSource, backgroundGameDestination, backgroundGameOrigin, 0, WHITE);
	}

	static void createMouse()
	{
		mouse.position = { (float)GetMouseX(),(float)GetMouseY() };
		mouse.width = 0;
		mouse.height = 0;
		mouse.selected = false;
		mouse.defaultColor = BLANK;
	}

	static void Init()
	{

		SetExitKey(0);

		screenWidth = 1300;
		screenHeight = 800;

		createMouse();

		InitWindow(screenWidth, screenHeight, "Simple! Asteroids");
		
		scheme_arrows01 = LoadTexture("res/textures/controls01.png");	
		scheme_sign01 = LoadTexture("res/textures/arrow01.png");

		crosshairImage = LoadImage("res/textures/crosshair01.png");
		shipImage = LoadImage("res/textures/test01.png");
		asteroidImage = LoadImage("res/textures/asteroid.png");
		backgroundGameImage = LoadImage("res/textures/backgroundgame.png");
		explosionImage = LoadImage("res/textures/explosion01.png");

		
		ImageResize(&backgroundGameImage, screenWidth, screenHeight);

		ImageResize(&explosionImage, 60, 60);
		shipExplosion = LoadTextureFromImage(explosionImage);

		ImageResize(&crosshairImage, 30, 30);
		crosshair = LoadTextureFromImage(crosshairImage);

		ImageResize(&asteroidImage, 90, 90);
		asteroid = LoadTextureFromImage(asteroidImage);

		ImageResize(&asteroidImage, 45, 45);
		asteroidMedium = LoadTextureFromImage(asteroidImage);

		ImageResize(&asteroidImage, 22.5, 22.5);
		asteroidSmall = LoadTextureFromImage(asteroidImage);

		ImageResize(&shipImage, 50, 50);
		ship = LoadTextureFromImage(shipImage);
		
		backgroundGame = LoadTextureFromImage(backgroundGameImage);

		UnloadImage(shipImage);
		UnloadImage(asteroidImage);
		UnloadImage(backgroundGameImage);
		UnloadImage(crosshairImage);
		UnloadImage(explosionImage);

		InitMenuScreen();
		createAsteroid();
	}

	static void Update()
	{
		switch (gameScreen)
		{
		case Play:
		{
			UpdateGameplayScreen();

			if (FinishGameplayScreen())
			{
				switch (buttonOption)
				{
				case buttonQuitToMenu:
				{
					gameScreen = Menu;
					InitMenuScreen();
					break;
				}
				case buttonGameOver:
				{
					gameScreen = GameOver;
					InitGameOverScreen();
					break;
				}
				}
			}
		}
		break;
		case Menu:
		{
			UpdateMenuScreen();

			if (FinishMenuScreen())
			{

				switch (buttonOption)
				{
				case buttonPlay:
				{
					#ifdef AUDIO
										StopMusicStream(pong_menu_song);
					#endif
					RestartPhase();
					gameScreen = Play;
					InitGameplayScreen();
					break;
				}
				case buttonControls:
				{
					gameScreen = Controls;
					InitControlsScreen();
					break;
				}
				case buttonSettings:
				{
					gameScreen = Settings;
					InitSettingsScreen();
					break;
				}
				case buttonCredits:
				{
					gameScreen = Credits;
					InitCreditsScreen();
					break;
				}
				case buttonQuit:
				{
					#ifdef AUDIO
										StopMusicStream(pong_menu_song);
					#endif

					gameScreen = 0;
					return;
					break;
				}
				}
			}
		}
		break;
		case Controls:
		{
			UpdateControlsScreen();

			if (FinishControlsScreen())
			{
				gameScreen = Menu;
				InitMenuScreen();
			}
		}
		break;
		case Credits:
		{
			UpdateCreditsScreen();

			if (FinishCreditsScreen())
			{
				gameScreen = Menu;
				InitMenuScreen();
			}
		}
		break;
		case Settings:
		{
			UpdateSettingsScreen();

			if (FinishSettingsScreen())
			{
				gameScreen = Menu;
				InitMenuScreen();
			}
		}
		break;
		case GameOver:
		{
			UpdateGameOverScreen();

			if (FinishGameOverScreen())
			{
				switch (buttonOption)
				{
				case buttonRestart:
				{
					RestartPhase();
					gameScreen = Play;
					InitGameplayScreen();
					break;
				}
				case buttonQuitToMenu:
				{
					gameScreen = Menu;
					InitMenuScreen();
					break;
				}
				}
			}
		}
		break;
		}
	}

	static void Draw()
	{
		// Basic Drawing Code - Template
		BeginDrawing();
		ClearBackground(BLACK);

		switch (gameScreen)
		{
		case Play: Gameplay_Section::DrawGameplay(); break;
		case GameOver: GameOver_Section::DrawGameOver(); break;
		case Menu: Menu_Section::DrawMenu(); break;
		case Controls: Controls_Section::DrawControls(); break;
		case Credits: Credits_Section::DrawCredits(); break;
		case Settings: Settings_Section::DrawSettings(); break;
		}

		EndDrawing();
	}

	static void DeInit()
	{
		#ifdef AUDIO
				// Audio Code
				CloseAudioDevice();
		#endif
		UnloadTexture(scheme_arrows01);
		UnloadTexture(scheme_sign01);
		UnloadTexture(ship);
		CloseWindow();
	}

	void Execute()
	{
		// Game Loop
		
		Init();
		while (!WindowShouldClose())
		{
			Update();
			if (gameScreen == 0) return;
			Draw();
		}
		DeInit();
		
	}
}