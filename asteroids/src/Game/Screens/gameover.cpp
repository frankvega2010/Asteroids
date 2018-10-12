#include "gameover.h"

#include "Setup/Game.h"
#include "Screens/gameplay.h"
#include "Setup\Player.h"
#include "Setup\Asteroid.h"
#include "Setup\PlayerShoot.h"

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

	namespace GameOver_Section
	{
		static void createGameOverButtons()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.4f;
				buttons[i].position.y = (float)screenHeight / 3.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;
				buttons[i].height = (float)screenHeight / 12.0f;
				buttons[i].selected = false;
				buttons[i].defaultColor = RED;
				buttons[i].messageColor = BLANK;

				buttonDistance = buttonDistance + 100;
			}
		}

		void InitGameOverScreen()
		{
			#ifdef AUDIO
			ship_explode01 = LoadSound("res/sounds/ship_explode01fix.wav");
			SetSoundVolume(ship_explode01, 0.3);
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

			DrawText(FormatText("RESTART"), buttons[0].position.x + 25, buttons[0].position.y + 5, defaultFontSize / 1.3f, buttons[0].defaultColor);
			DrawText(FormatText("QUIT"), buttons[1].position.x + 60, buttons[1].position.y + 5, defaultFontSize, buttons[1].defaultColor);

			if (destroyedAsteroidsCount >= (asteroidsSmallLimit + asteroidsMediumLimit + asteroidsBigLimit) && player.isAlive)
			{
				DrawText("YOU WON!", buttons[0].position.x + 20, buttons[0].position.y - 60, 40, YELLOW);
			}
			else
			{
				DrawText("YOU LOST!", buttons[0].position.x + 20, buttons[0].position.y - 60, 40, RED);
			}

			DrawText(FormatText("Final Score: %i", increasingFinalScore), buttons[0].position.x - 10, buttons[1].position.y + 90, 40, YELLOW);
			DrawText(FormatText("Final Time:"), buttons[0].position.x + 20, buttons[1].position.y + 135, 40, YELLOW);
			DrawTimer(2.2f, 1.9f, 1.45);

			if (isExplosionActive)
			{
				DrawTexturePro(shipExplosion, { 0.0f,0.0f, 60,60 }, { player.position.x,player.position.y, increasingExplosionSize,increasingExplosionSize }, { 0,0 }, 0, Fade(WHITE, increasingExplosionFade));
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

		void DeInitGameOverAudio()
		{
			#ifdef AUDIO
			StopSound(ship_explode01);
			UnloadSound(ship_explode01);
			#endif
		}
	}
}