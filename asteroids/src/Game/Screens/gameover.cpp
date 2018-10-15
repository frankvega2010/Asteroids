#include "gameover.h"

#include "Setup/Game.h"
#include "Screens/gameplay.h"
#include "Setup\Player.h"
#include "Setup\Asteroid.h"
#include "Setup\PlayerShoot.h"
#include "Screens\settings.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtons = 2;

	static Buttons buttons[maxButtons];
	static int buttonDistance = 0;
	static int buttonSelect = 0;

	static Color optionColor = RED;
	static int finalScore;
	static float finalScoreTimer = 0;
	static float explosionTimer = 0;
	static float increasingExplosionSize = 0;
	static float increasingExplosionFade = 1;
	static int increasingFinalScore = 0;
	static bool timerON = true;
	static bool timerExplosionON = true;

	static Rectangle shipExplosionSource = { 0.0f,0.0f, 60,60 };
	static Rectangle shipExplosionSourceSmall = { 0.0f,0.0f,60/2,60/2 };

	static Rectangle shipExplosionDestination;
	static Vector2 shipExplosionOrigin = { 0,0 };

	Texture2D shipExplosion;

	namespace GameOver_Section
	{
		static void createGameOverButtons()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.5f;
				buttons[i].position.y = (float)screenHeight / 3.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;

				if (resolutionNormal) buttons[i].height = (float)screenHeight / 12.0f;
				else if (resolutionSmall) buttons[i].height = (float)screenHeight / 14.0f;

				//buttons[i].height = (float)screenHeight / 12.0f;
				buttons[i].selected = false;
				buttons[i].defaultColor = RED;
				buttons[i].messageColor = BLANK;

				if (resolutionNormal && !(resolutionBig)) buttonDistance = buttonDistance + 100;
				else if (resolutionSmall) buttonDistance = buttonDistance + 50;
				else if (resolutionBig && resolutionNormal) buttonDistance = buttonDistance + 125;
			}
		}

		void InitGameOverScreen()
		{
			if (resolutionNormal)
			{
				explosionImage = LoadImage("res/textures/explosion01.png");
				ImageResize(&explosionImage, 60, 60);
				shipExplosion = LoadTextureFromImage(explosionImage);
			}
			else if (resolutionSmall)
			{
				explosionImage = LoadImage("res/textures/explosion01.png");
				ImageResize(&explosionImage, 60/2, 60/2);
				shipExplosion = LoadTextureFromImage(explosionImage);
			}
			

			UnloadImage(explosionImage);

			#ifdef AUDIO
			ship_explode01 = LoadSound("res/sounds/ship_explode01fix.wav");
			SetSoundVolume(ship_explode01, soundVolume);
			PlaySound(ship_explode01);
			#endif

			finalScore = (gameScore * scoreMultiplier);
			increasingFinalScore = 0;
			finalScoreTimer = 0;
			increasingExplosionSize = 0;
			increasingExplosionFade = 1;
			timerON = true;
			timerExplosionON = true;
			ShowCursor();
			createGameOverButtons();
			isScreenFinished = false;
		}

		static void GameOverInput()
		{
			if (IsKeyPressed(KEY_DOWN))
			{
				mouse.selected = false;
				buttonSelect++;
				if (buttonSelect > maxButtons - 1)
				{
					buttonSelect--;
				}
			}

			if (IsKeyPressed(KEY_UP))
			{
				mouse.selected = false;
				buttonSelect--;
				if (buttonSelect < 0)
				{
					buttonSelect++;
				}
			}

			for (int i = 0; i < maxButtons; i++)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttons[i].selected || IsKeyPressed(KEY_ENTER) && buttons[i].selected)
				{
					switch (i)
					{
					case 0:
						buttonOption = buttonRestart;
						break;
					case 1:
						buttonOption = buttonQuitToMenu;
						createAsteroid();
						break;
					}
					buttons[i].selected = false;
					isScreenFinished = true;
				}
			}
		}

		void UpdateGameOverScreen()
		{
			GameOverInput(); 
			AsteroidUpdate();
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };
			

			for (int i = 0; i < maxButtons; i++)
			{
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }) || buttonSelect == i)
				{
					buttonSelect = i;
					buttons[i].defaultColor = WHITE;
					buttons[i].selected = true;
				}
				else
				{
					buttons[i].defaultColor = RED;
					buttons[i].selected = false;
				}
			}

			if (timerON)
			{
				finalScoreTimer += 1 * GetFrameTime();
			}

			if (timerExplosionON)
			{
				explosionTimer += 1 * GetFrameTime();
			}

			if (explosionTimer > 0.01)
			{
				explosionTimer = 0;
				increasingExplosionSize++;
				increasingExplosionFade = increasingExplosionFade - 0.005;
			}

			if (finalScoreTimer > 0.0001)
			{
				finalScoreTimer = 0;
				increasingFinalScore++;
			}

			if (increasingFinalScore >= finalScore)
			{
				timerON = false;
				finalScoreTimer = 0;
				increasingFinalScore = finalScore;
			}

			if (increasingExplosionSize >= 200)
			{
				timerExplosionON = false;
				explosionTimer = 0;
			}
		}

		void DrawGameOver()
		{
			DrawBackground();
			AsteroidDraw();

			for (int i = 0; i < maxButtons; i++)
			{
				DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);
			}

			DrawText(FormatText("RESTART"), buttons[0].position.x + 10, buttons[0].position.y + 5, defaultFontSize / 1.3, buttons[0].defaultColor);
			DrawText(FormatText("MENU"), buttons[1].position.x + 10, buttons[1].position.y + 5, defaultFontSize / 1.3, buttons[1].defaultColor);

			if (destroyedAsteroidsCount >= (asteroidsSmallLimit + asteroidsMediumLimit + asteroidsBigLimit) && player.isAlive)
			{
				DrawText("YOU WON!", buttons[0].position.x, buttons[0].position.y - 60, defaultFontSize / 1.2, YELLOW);
			}
			else
			{
				DrawText("YOU LOST!", buttons[0].position.x, buttons[0].position.y - 60, defaultFontSize / 1.2, RED);
			}

			DrawText(FormatText("Final Score: %i", increasingFinalScore), buttons[0].position.x - (screenWidth * 0.02), buttons[1].position.y + 90, defaultFontSize / 1.2, YELLOW);
			DrawText(FormatText("Final Time:"), buttons[0].position.x - (screenWidth * 0.02), buttons[1].position.y + 135, defaultFontSize / 1.2, YELLOW);
			if(resolutionNormal) DrawTimer(2.2f, 1.9f, 1.45);
			else if(resolutionSmall) DrawTimer(2.2f, 1.9f, 1.25);

			if (isExplosionActive && !(player.isAlive))
			{
				shipExplosionDestination = { player.position.x,player.position.y, increasingExplosionSize,increasingExplosionSize };

				if(resolutionNormal) DrawTexturePro(shipExplosion, shipExplosionSource, shipExplosionDestination, shipExplosionOrigin, 0, Fade(WHITE, increasingExplosionFade));
				else if(resolutionSmall ) DrawTexturePro(shipExplosion, shipExplosionSourceSmall, shipExplosionDestination, shipExplosionOrigin, 0, Fade(WHITE, increasingExplosionFade));
		
				//DrawTexturePro(shipExplosion, { 0.0f,0.0f, 60,60 }, { player.position.x,player.position.y, increasingExplosionSize,increasingExplosionSize }, { 0,0 }, 0, Fade(WHITE, increasingExplosionFade));
			}
			
		}

		bool FinishGameOverScreen()
		{
			//timerON = false;
			//timerExplosionON = false;
			buttonDistance = 0;
			#ifdef AUDIO
			#endif
			return isScreenFinished;
		}

		void DeInitGameOverResources()
		{
			//UnloadImage(explosionImage);
			#ifdef AUDIO
			StopSound(ship_explode01);
			UnloadSound(ship_explode01);
			#endif
		}
	}
}