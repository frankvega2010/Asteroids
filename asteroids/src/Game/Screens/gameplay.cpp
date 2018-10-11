#include "gameplay.h"

#include "Setup\Game.h"
#include "Setup\Player.h"
#include "Setup\Asteroid.h"
#include "Setup\PlayerShoot.h"

namespace Juego
{
	static const int maxButtons = 3;

	static Buttons buttons[maxButtons];
	static int buttonDistance = 0;
	static int buttonSelect = 0;
	static Color optionColor = RED;

	static bool gameON = true;
	static bool gamePaused = false;
	
	static bool timerON = true;
	static float matchTimer = 0.0f;
	static int matchHours = 0;
	static int matchMinutes = 0;
	static int matchSeconds = 0;
	static Color crosshairColor = WHITE;
	bool isExplosionActive = false;
	int scoreMultiplier = 5;

	namespace Gameplay_Section
	{
		static void createPauseButtons()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.4f;
				buttons[i].position.y = (float)screenHeight / 3.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;
				buttons[i].height = (float)screenHeight / 12.0f;
				buttons[i].selected = false;
				buttons[i].defaultColor = GOLD;
				buttons[i].messageColor = BLANK;

				buttonDistance = buttonDistance + 100;
			}
		}

		static void GameplayInput()
		{
			// Gameplay Input
			if (!(gameON))
			{
				ShowCursor();
				if (IsKeyPressed(KEY_SPACE))
				{
					RestartPhase();
				}
			}
			// Player Input
			if (gameON)
			{
				timerON = true;
				crosshairColor = WHITE;
				HideCursor();
				playerInput();			
			}
			
			if (!gamePaused)
			{
				if (IsKeyPressed(KEY_P))
				{
					crosshairColor = BLANK;
					gamePaused = true;
					gameON = false;
				}
			}
			else
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
							gamePaused = false;
							timerON = true;
							gameON = true;
							break;
						case 1:
							RestartPhase();
							break;
						case 2:
							buttonOption = buttonQuitToMenu;
							break;
						}
						buttons[i].selected = false;
						isScreenFinished = true;
					}
				}

				if (IsKeyPressed(KEY_P))
				{
					gamePaused = false;
					gameON = true;
				}
			}
		}

		void InitGameplayVariables()
		{
			// Round Variables

			//Execute Functions & Extern variables 
			timerON = true;
			createPauseButtons();
			HideCursor();
			createAsteroid();
			createPlayer();
			createShoot();
			createCollisionCircle();
			//collisionCircle.active = true;
		}

		void UpdateGameplayScreen()
		{
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };
			GameplayInput();
			if (gameON)
			{
				if (timerON)
				{
					matchTimer += 1 * GetFrameTime(); //FINISH THIS
				}

				if (matchTimer > 1)
				{
					matchTimer = 0;
					if (matchSeconds < 58) // 58
					{
						if (matchSeconds == 29)
						{
							if (scoreMultiplier > 1)
							{
								scoreMultiplier--;
							}
							else
							{
								scoreMultiplier = 1;
							}	
						}
						matchSeconds++;
					}
					else
					{
						matchSeconds = 0;
						if (matchMinutes < 58) // 58
						{
							matchMinutes++;
						}
						else
						{
							matchMinutes = 0;
							matchHours++;
						}
					}
				}
				playerUpdate();
				collisionCircleUpdate();
				ShootUpdate();
				AsteroidUpdate();
				

				// Collision logic: player vs walls
				if (player.position.x > screenWidth + shipHeight) player.position.x = -(shipHeight);
				else if (player.position.x < -(shipHeight)) player.position.x = screenWidth + shipHeight;
				if (player.position.y >(screenHeight + shipHeight)) player.position.y = -(shipHeight);
				else if (player.position.y < -(shipHeight)) player.position.y = screenHeight + shipHeight;

				for (int i = 0; i < asteroidsBigLimit; i++)
				{
					if (CheckCollisionCircles(collisionCircle.position, collisionCircle.radius, asteroidsBig[i].position, asteroidsBig[i].radius) && asteroidsBig[i].active)
					{
						gameON = false;
						buttonOption = buttonGameOver;
						isScreenFinished = true;
						scoreMultiplier = 1;
						isExplosionActive = true;
						break;
					}
				}

				for (int i = 0; i < asteroidsMediumLimit; i++)
				{
					if (CheckCollisionCircles(collisionCircle.position, collisionCircle.radius, asteroidsMedium[i].position, asteroidsMedium[i].radius) && asteroidsMedium[i].active)
					{
						gameON = false;
						buttonOption = buttonGameOver;
						isScreenFinished = true;
						scoreMultiplier = 1;
						isExplosionActive = true;
						break;
					}
				}

				for (int i = 0; i < asteroidsSmallLimit; i++)
				{
					if (CheckCollisionCircles(collisionCircle.position, collisionCircle.radius, asteroidsSmall[i].position, asteroidsSmall[i].radius) && asteroidsSmall[i].active)
					{
						gameON = false;
						buttonOption = buttonGameOver;
						isScreenFinished = true;
						scoreMultiplier = 1;
						isExplosionActive = true;
						break;
					}
				}
			}
			else if (gamePaused)
			{
				timerON = false;
				matchTimer = 0;

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
						buttons[i].defaultColor = GOLD;
						buttons[i].selected = false;
					}
				}
			}


			if (destroyedAsteroidsCount >= (asteroidsSmallLimit + asteroidsMediumLimit + asteroidsBigLimit))
			{
				gameON = false;
				timerON = false;
				matchTimer = 0;
				buttonOption = buttonGameOver;
				isScreenFinished = true;

				//buttons[i].selected = false;
				//isScreenFinished = true;
			}
		}

		void InitGameplayScreen()
		{
			isScreenFinished = false;
		}

		bool FinishGameplayScreen()
		{
			buttonDistance = 0;
			return isScreenFinished;
		}

		void RestartPhase()
		{
			InitGameplayVariables();
			buttonDistance = 0;
			gameON = true;
			timerON = true;
			matchSeconds = 0;
			matchMinutes = 0;
			matchHours = 0;
			scoreMultiplier = 5;
		}

		void DrawTimer(float widthvalue1,float widthvalue2,float heightvalue1)
		{
			if (matchHours > 0) // DrawTimer?
			{
				DrawText(FormatText("%i:", matchHours), screenWidth / (widthvalue1 + 0.25), screenHeight / heightvalue1, 40, YELLOW);
			}

			if (matchMinutes > 0)
			{
				if (matchMinutes > 9)
				{
					DrawText(FormatText("%i:", matchMinutes), screenWidth / widthvalue1, screenHeight / heightvalue1, 40, YELLOW);
				}
				else
				{
					DrawText(FormatText("0"), screenWidth / widthvalue1, screenHeight / 14, 40, YELLOW);
					DrawText(FormatText("%i:", matchMinutes), screenWidth / (widthvalue2 + 0.15), screenHeight / heightvalue1, 40, YELLOW);
				}
			}
			else
			{
				DrawText(FormatText("00:"), screenWidth / widthvalue1, screenHeight / heightvalue1, 40, YELLOW);
			}

			if (matchSeconds > 0)
			{
				if (matchSeconds > 9)
				{
					DrawText(FormatText("%i", matchSeconds), screenWidth / widthvalue2, screenHeight / heightvalue1, 40, YELLOW);
				}
				else
				{
					DrawText(FormatText("0"), screenWidth / widthvalue2, screenHeight / heightvalue1, 40, YELLOW);
					DrawText(FormatText("%i", matchSeconds), screenWidth / (widthvalue2 - 0.10), screenHeight / heightvalue1, 40, YELLOW);
				}
			}
			else
			{
				DrawText(FormatText("00"), screenWidth / widthvalue2, screenHeight / heightvalue1, 40, YELLOW);
			}
		}

		void DrawGameplay()
		{

			DrawBackground();
			collisionCircleDraw();
			
			AsteroidDraw();
			ShootDraw();
			playerDraw();
			DrawText(FormatText("Eliminations: %i", destroyedAsteroidsCount), screenWidth / 70, screenHeight / 14, 40, YELLOW);
			DrawText(FormatText("Time: "), screenWidth / 3.40, screenHeight / 14, 40, YELLOW);
			DrawTimer(2.5f, 2.2f,14.0f);
			DrawTexturePro(crosshair, { 0,0,30,30 }, { mouse.position.x,mouse.position.y,30,30 }, {15,15}, 0, crosshairColor);

			if (!(gameON))
			{
				if (gamePaused)
				{
					DrawRectangle(buttons[0].position.x - 25, buttons[0].position.y - 25, (float)screenWidth / 4.2f, (float)screenHeight / 2.5f, DARKPURPLE);
					for (int i = 0; i < maxButtons; i++)
					{
						DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);
					}
					DrawText("PAUSED", buttons[0].position.x + 50, buttons[0].position.y - 100, 40, GOLD);
					DrawText(FormatText("CONTINUE"), buttons[0].position.x + 10, buttons[0].position.y + 5, defaultFontSize / 1.3, buttons[0].defaultColor);
					DrawText(FormatText("RESTART"), buttons[1].position.x + 8, buttons[1].position.y + 5, defaultFontSize / 1.3, buttons[1].defaultColor);
					DrawText(FormatText("MENU"), buttons[2].position.x + 10, buttons[2].position.y + 5, defaultFontSize / 1.3, buttons[2].defaultColor);
				}
			}
		}
	}
}