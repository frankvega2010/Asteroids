#include "gameplay.h"

#include "Setup\Game.h"
#include "Setup\Player.h"
#include "Setup\Asteroid.h"
#include "Setup\PlayerShoot.h"

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
			createAsteroid();
			createPlayer();
			createShoot();
			createCollisionCircle();
		}

		void UpdateGameplayScreen()
		{
			GameplayInput();
			if (collisionCircle.active)
			{
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
						collisionCircle.active = false;
					}
				}

				for (int i = 0; i < asteroidsMediumLimit; i++)
				{
					if (CheckCollisionCircles(collisionCircle.position, collisionCircle.radius, asteroidsMedium[i].position, asteroidsMedium[i].radius) && asteroidsMedium[i].active)
					{
						collisionCircle.active = false;
					}
				}

				for (int i = 0; i < asteroidsSmallLimit; i++)
				{
					if (CheckCollisionCircles(collisionCircle.position, collisionCircle.radius, asteroidsSmall[i].position, asteroidsSmall[i].radius) && asteroidsSmall[i].active)
					{
						collisionCircle.active = false;
					}
				}
			}

			if (destroyedAsteroidsCount >= (asteroidsSmallLimit + asteroidsMediumLimit + asteroidsBigLimit))
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
			DrawText(FormatText("Your score: %i", destroyedAsteroidsCount), screenWidth / 2, screenHeight / 10, 40, YELLOW);
			ShootDraw();
			playerDraw();
			collisionCircleDraw();
			AsteroidDraw();
			

			if (!(collisionCircle.active))//
			{
				if (destroyedAsteroidsCount >= (asteroidsSmallLimit + asteroidsMediumLimit + asteroidsBigLimit))
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