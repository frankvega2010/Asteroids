#include "Game.h"

#include "Screens/gameplay.h"
#include "Screens/menu.h"
#include "Screens/gameover.h"
#include "Screens/settings.h"
#include "Screens/credits.h"
#include "Screens/howtoplay.h"

using namespace Juego;
using namespace Gameplay_Section;
using namespace GameOver_Section;
using namespace Menu_Section;
using namespace Settings_Section;
using namespace Credits_Section;
using namespace Howtoplay_Section;

namespace Juego
{
	int gameScreen = Menu;

	int screenWidth;
	int screenHeight;
	Buttons mouse;
	int buttonOption = 0;

	int defaultFontSize = 60;

	bool isScreenFinished;

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

		InitMenuScreen();
	}

	static void Update()
	{
		// Update Template
		switch (gameScreen)
		{
		case Play:
		{
			UpdateGameplayScreen();

			if (FinishGameplayScreen())
			{
				//gameScreen = GameOver;
				InitGameOverScreen();
			}
		}
		break;
		case Menu:
		{
			UpdateMenuScreen();

			if (FinishMenuScreen())
			{
				switch (gameScreen)// CHANGE THIS? maybe it works
				{
				case Play:
				{
					#ifdef AUDIO
										StopMusicStream(pong_menu_song);
					#endif
					RestartPhase();
					//gamePhase = Gameplay;
					InitGameplayScreen();
					break;
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
				case Quit:
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
		case Menu: Menu_Section::DrawMenu(); break;
		}

		EndDrawing();
	}

	static void DeInit()
	{
		#ifdef AUDIO
				// Audio Code
				CloseAudioDevice();
		#endif
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