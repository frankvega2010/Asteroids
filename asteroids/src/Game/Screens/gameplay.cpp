#include "gameplay.h"

#include "Setup\Game.h"
#include "Setup\Player.h"
#include "Setup\Asteroid.h"

namespace Juego
{
	namespace Gameplay_Section
	{
		static void GameplayInput()
		{
			// Gameplay Input
			if (!(collisionCircle.active))
			{
				if (IsKeyPressed(KEY_SPACE))
				{
					collisionCircle.active = true;
					RestartPhase();
				}
			}
			// Player Input
			if (collisionCircle.active)
			{
				playerInput();
			}
		}

		void InitGameplayVariables()
		{
			// Round Variables

			//Execute Functions & Extern variables 
			//createAsteroid();
			createPlayer();
			createCollisionCircle();
		}

		void UpdateGameplayScreen()
		{
			GameplayInput();
			if (collisionCircle.active)
			{
				playerUpdate();
				collisionCircleUpdate();
				AsteroidUpdate();

				// Collision logic: player vs walls
				if (player.position.x > screenWidth + shipHeight) player.position.x = -(shipHeight);
				else if (player.position.x < -(shipHeight)) player.position.x = screenWidth + shipHeight;
				if (player.position.y >(screenHeight + shipHeight)) player.position.y = -(shipHeight);
				else if (player.position.y < -(shipHeight)) player.position.y = screenHeight + shipHeight;

				for (int i = 0; i < asteroidsLimit; i++)
				{
					// Collision logic: ball vs vertical walls FOR BOTH PLAYERS
					if ((asteroids[i].position.x + asteroids[i].radio) >= screenWidth + asteroids[i].radio * 6)
					{
						asteroids[i].position.x = screenWidth - asteroids[i].radio;
						asteroids[i].speed.x *= -1;
						asteroids[i].radio = asteroids[i].radio - 5;
					}
					else if ((asteroids[i].position.x + asteroids[i].radio) <= 0 - asteroids[i].radio * 6)
					{

						asteroids[i].position.x = 0 + asteroids[i].radio;
						asteroids[i].speed.x *= -1;
						asteroids[i].radio = asteroids[i].radio - 5;
					}

					// Collision logic: ball vs horizontal walls
					if ((asteroids[i].position.y - asteroids[i].radio) <= 0 - asteroids[i].radio * 6)
					{

						asteroids[i].position.y = 0 + asteroids[i].radio;
						asteroids[i].speed.y *= -1;
						asteroids[i].radio = asteroids[i].radio - 5;
					}
					if ((asteroids[i].position.y + asteroids[i].radio) >= screenHeight + asteroids[i].radio * 6)
					{
						asteroids[i].position.y = screenHeight - asteroids[i].radio;
						asteroids[i].speed.y *= -1;
						asteroids[i].radio = asteroids[i].radio - 5;
					}

					for (int i = 0; i < asteroidsLimit; i++)
					{
						if (CheckCollisionCircles(collisionCircle.position, collisionCircle.radio, asteroids[i].position, asteroids[i].radio))
						{
							collisionCircle.active = false;				
						}
					}
				}

				for (int i = 0; i < asteroidsLimit; i++)
				{
					if (asteroids[i].radio <= 0)
					{
						asteroids[i].radio = 50;
						asteroids[i].position.x = GetRandomValue(0, screenWidth);
						asteroids[i].position.y = GetRandomValue(0, screenHeight);
						player.score++;
					}
				}
			}

			if (player.score >= 10)
			{
				collisionCircle.active = false;
			}
		}

		void InitGameplayScreen()
		{
			isScreenFinished = false;
		}

		bool FinishGameplayScreen()
		{
			return isScreenFinished;
		}

		void RestartPhase()
		{
			InitGameplayVariables();
		}

		void DrawGameplay()
		{
			DrawText(FormatText("Your score: %i", player.score), screenWidth / 2, screenHeight / 10, 40, YELLOW);
			playerDraw();
			collisionCircleDraw();
			AsteroidDraw();

			if (!(collisionCircle.active))
			{
				if (player.score >= 10)
				{
					DrawText("You won!", screenWidth / 2, screenHeight / 2, 40, YELLOW);
				}
				else
				{
					DrawText("You lost", screenWidth / 2, screenHeight / 2, 40, RED);
				}

			}
		}
	}
}