#include "Asteroid.h"
#include <cmath>
#include "Game.h"
#include "Player.h"

namespace Juego
{
	static float posX = 0;
	static float posY = 0;
	static float speedX = 0;
	static float speedY = 0;
	static bool correctRange = false;
	static float rotationTimerBigAsteroids = 0;
	static float rotationTimerMediumAsteroids = 0;
	static float rotationTimerSmallAsteroids = 0;

	Asteroid asteroidsSmall[asteroidsSmallLimit];
	Asteroid asteroidsMedium[asteroidsMediumLimit];
	Asteroid asteroidsBig[asteroidsBigLimit];

	namespace Gameplay_Section
	{
		void createAsteroid()
		{
			rotationTimerBigAsteroids = 0;
			rotationTimerMediumAsteroids = 0;
			rotationTimerSmallAsteroids = 0;

			for (int i = 0; i < asteroidsBigLimit; i++)
			{
				posX = GetRandomValue(0, screenWidth);

				while (!correctRange)
				{
					if (posX > screenWidth / 2 - 150 && posX < screenWidth / 2 + 150) posX = GetRandomValue(0, screenWidth);
					else correctRange = true;
				}

				correctRange = false;

				posY = GetRandomValue(0, screenHeight);

				while (!correctRange)
				{
					if (posY > screenHeight / 2 - 150 && posY < screenHeight / 2 + 150)  posY = GetRandomValue(0, screenHeight);
					else correctRange = true;
				}

				asteroidsBig[i].position = { posX, posY };

				correctRange = false;
				speedX = GetRandomValue(-asteroidsSpeed, asteroidsSpeed);
				speedY = GetRandomValue(-asteroidsSpeed, asteroidsSpeed);

				while (!correctRange)
				{
					if (speedX == 0 && speedY == 0)
					{
						speedX = GetRandomValue(-asteroidsSpeed, asteroidsSpeed);
						speedY = GetRandomValue(-asteroidsSpeed, asteroidsSpeed);
					}
					else correctRange = true;
				}

				asteroidsBig[i].speed = { speedX, speedY };
				asteroidsBig[i].radius = 40;
				asteroidsBig[i].active = true;
			}


			for (int i = 0; i < asteroidsMediumLimit; i++)
			{
				asteroidsMedium[i].position = { -100, -100 };
				asteroidsMedium[i].speed = { 0, 0 };
				asteroidsMedium[i].radius = 20;
				asteroidsMedium[i].active = false;
			}

			for (int i = 0; i < asteroidsSmallLimit; i++)
			{
				asteroidsSmall[i].position = { -100, -100 };
				asteroidsSmall[i].speed = { 0, 0 };
				asteroidsSmall[i].radius = 10;
				asteroidsSmall[i].active = false;
			}

		}

		void AsteroidUpdate()
		{
			if (rotationTimerBigAsteroids < 1000) rotationTimerBigAsteroids += 40 * GetFrameTime();
			else rotationTimerBigAsteroids = 0;

			if (rotationTimerMediumAsteroids < 1000) rotationTimerMediumAsteroids += 60 * GetFrameTime();
			else rotationTimerMediumAsteroids = 0;

			if (rotationTimerSmallAsteroids < 1000) rotationTimerSmallAsteroids += 80 * GetFrameTime();
			else rotationTimerSmallAsteroids = 0;
			
			// Meteors logic: big meteors
			for (int i = 0; i < asteroidsBigLimit; i++)
			{
				if (asteroidsBig[i].active)
				{
					// Movement
					asteroidsBig[i].position.x += asteroidsBig[i].speed.x * GetFrameTime();
					asteroidsBig[i].position.y += asteroidsBig[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (asteroidsBig[i].position.x > screenWidth + asteroidsBig[i].radius) asteroidsBig[i].position.x = -(asteroidsBig[i].radius);
					else if (asteroidsBig[i].position.x < 0 - asteroidsBig[i].radius) asteroidsBig[i].position.x = screenWidth + asteroidsBig[i].radius;
					if (asteroidsBig[i].position.y > screenHeight + asteroidsBig[i].radius) asteroidsBig[i].position.y = -(asteroidsBig[i].radius);
					else if (asteroidsBig[i].position.y < 0 - asteroidsBig[i].radius) asteroidsBig[i].position.y = screenHeight + asteroidsBig[i].radius;

					//asteroidsBig[i].rotation += 280 * GetFrameTime();
				}
			}

			// Meteors logic: medium meteors
			for (int i = 0; i < asteroidsMediumLimit; i++)
			{
				if (asteroidsMedium[i].active)
				{
					// Movement
					asteroidsMedium[i].position.x += asteroidsMedium[i].speed.x * GetFrameTime();
					asteroidsMedium[i].position.y += asteroidsMedium[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (asteroidsMedium[i].position.x > screenWidth + asteroidsMedium[i].radius) asteroidsMedium[i].position.x = -(asteroidsMedium[i].radius);
					else if (asteroidsMedium[i].position.x < 0 - asteroidsMedium[i].radius) asteroidsMedium[i].position.x = screenWidth + asteroidsMedium[i].radius;
					if (asteroidsMedium[i].position.y > screenHeight + asteroidsMedium[i].radius) asteroidsMedium[i].position.y = -(asteroidsMedium[i].radius);
					else if (asteroidsMedium[i].position.y < 0 - asteroidsMedium[i].radius) asteroidsMedium[i].position.y = screenHeight + asteroidsMedium[i].radius;
				}
			}

			// Meteors logic: small meteors
			for (int i = 0; i < asteroidsSmallLimit; i++)
			{
				if (asteroidsSmall[i].active)
				{
					// Movement
					asteroidsSmall[i].position.x += asteroidsSmall[i].speed.x * GetFrameTime();
					asteroidsSmall[i].position.y += asteroidsSmall[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (asteroidsSmall[i].position.x > screenWidth + asteroidsSmall[i].radius)asteroidsSmall[i].position.x = -(asteroidsSmall[i].radius);
					else if (asteroidsSmall[i].position.x < 0 - asteroidsSmall[i].radius)asteroidsSmall[i].position.x = screenWidth + asteroidsSmall[i].radius;
					if (asteroidsSmall[i].position.y > screenHeight + asteroidsSmall[i].radius)asteroidsSmall[i].position.y = -(asteroidsSmall[i].radius);
					else if (asteroidsSmall[i].position.y < 0 - asteroidsSmall[i].radius)asteroidsSmall[i].position.y = screenHeight + asteroidsSmall[i].radius;
				}
			}
		}

		void AsteroidDraw()
		{
			// Draw meteors
			for (int i = 0; i < asteroidsBigLimit; i++)
			{
				
				if (asteroidsBig[i].active)
				{
					DrawCircleV(asteroidsBig[i].position, asteroidsBig[i].radius, DARKGRAY);
					DrawTexturePro(asteroid, { 0.0f,0.0f, 90,90 }, { asteroidsBig[i].position.x,asteroidsBig[i].position.y, 90,90 }, { 45,45 }, rotationTimerBigAsteroids, BLUE);
				}
				else 
				{
					DrawCircleV(asteroidsBig[i].position, asteroidsBig[i].radius, Fade(LIGHTGRAY, 0.3f));
					DrawTexturePro(asteroid, { 0.0f,0.0f, 90,90 }, { asteroidsBig[i].position.x,asteroidsBig[i].position.y, 90,90 }, { 45,45 }, 0, DARKGRAY);
				} 
			}

			for (int i = 0; i < asteroidsMediumLimit; i++)
			{
				if (asteroidsMedium[i].active)
				{
					DrawCircleV(asteroidsMedium[i].position, asteroidsMedium[i].radius, GRAY);
					DrawTexturePro(asteroidMedium, { 0.0f,0.0f, 45,45 }, { asteroidsMedium[i].position.x,asteroidsMedium[i].position.y, 45,45 }, { 22.5,22.5 }, rotationTimerMediumAsteroids, BLUE);
				}
				else
				{
					DrawCircleV(asteroidsMedium[i].position, asteroidsMedium[i].radius, Fade(LIGHTGRAY, 0.3f));
					DrawTexturePro(asteroidMedium, { 0.0f,0.0f, 45,45 }, { asteroidsMedium[i].position.x,asteroidsMedium[i].position.y, 45,45 }, { 22.5,22.5 }, 0, DARKGRAY);
				}
			}

			for (int i = 0; i < asteroidsSmallLimit; i++)
			{
				if (asteroidsSmall[i].active)
				{
					DrawCircleV(asteroidsSmall[i].position, asteroidsSmall[i].radius, GRAY);
					DrawTexturePro(asteroidSmall, { 0.0f,0.0f, 22.5,22.5 }, { asteroidsSmall[i].position.x,asteroidsSmall[i].position.y, 22.5,22.5 }, { 11.25f,11.25f }, rotationTimerSmallAsteroids, BLUE);
				}
				else
				{
					DrawCircleV(asteroidsSmall[i].position, asteroidsSmall[i].radius, Fade(LIGHTGRAY, 0.3f));
					DrawTexturePro(asteroidSmall, { 0.0f,0.0f, 22.5,22.5 }, { asteroidsSmall[i].position.x,asteroidsSmall[i].position.y, 22.5,22.5 }, { 11.25f,11.25f }, 0, DARKGRAY);
				}
			}
		}
	}
}