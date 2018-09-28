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
	enum Screens
	{
		Gameplay = 1,
	};

	static int gameScreen = Gameplay;

	float screenWidth;
	float screenHeight;

	bool isScreenFinished;

	#ifdef AUDIO

	// Audio Code

	#endif

	static void Init()
	{
		SetExitKey(0);

		screenWidth = 1300;
		screenHeight = 800;

		InitGameplayVariables();

		InitWindow(screenWidth, screenHeight, "Asteroids Alpha 0.0.1");

		InitGameplayScreen();
	}

	static void DeInit()
	{
	#ifdef AUDIO
		// Audio Code
		CloseAudioDevice();
	#endif
		CloseWindow();
	}

	static void Draw()
	{
		// Basic Drawing Code - Template
		BeginDrawing();
		ClearBackground(BLACK);

		switch (gameScreen)
		{
		case Gameplay: Gameplay_Section::DrawGameplay(); break;
		}

		EndDrawing();
	}

	static void Update()
	{
		// Update Template
		switch (gameScreen)
		{
		case Gameplay:
		{
			UpdateGameplayScreen();

			if (FinishGameplayScreen())
			{
				//gameScreen = GameOver;
				InitGameOverScreen();
			}
		}
		break;
		}
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