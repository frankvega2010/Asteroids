#include "Asteroid.h"
#include <cmath>
#include "Game.h"
#include "Player.h"

namespace Juego
{
	Asteroid asteroids[asteroidsLimit];

	namespace Gameplay_Section
	{
		void createAsteroid()
		{
			for (int i = 0; i < asteroidsLimit; i++)
			{
				asteroids[i].position.x = GetRandomValue(0, screenWidth);
				asteroids[i].position.y = GetRandomValue(0, screenHeight);
				asteroids[i].radio = 50;
				asteroids[i].speed = {300,300};
				asteroids[i].active = true;
			}
		}

		void AsteroidUpdate()
		{
			for (int i = 0; i < asteroidsLimit; i++)
			{
				if (asteroids[i].active)
				{
					asteroids[i].position.x += asteroids[i].speed.x * GetFrameTime();
					asteroids[i].position.y += asteroids[i].speed.y * GetFrameTime();
				}
			}
		}

		void AsteroidDraw()
		{
			for (int i = 0; i < asteroidsLimit; i++)
			{
				DrawCircleV(asteroids[i].position, asteroids[i].radio, WHITE);
			}
		}
	}
}