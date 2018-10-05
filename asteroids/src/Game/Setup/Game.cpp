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

	Texture2D scheme_arrows01;
	Texture2D scheme_sign01;

	#ifdef AUDIO

	// Audio Code

	#endif

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

		//InitGameplayVariables();

		InitWindow(screenWidth, screenHeight, "Asteroids Ver 0.1");
		
		scheme_arrows01 = LoadTexture("res/textures/controls01.png");	
		scheme_sign01 = LoadTexture("res/textures/arrow01.png");

		InitMenuScreen();
		createAsteroid(); //PONER EN GAMEOVER YENDO AL MENU.
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