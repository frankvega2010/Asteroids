#include "Asteroid.h"
#include "Game.h"
#include "Player.h"

namespace Juego
{
	Asteroid asteroids[asteroidsLimit];
	Asteroid collisionCircle;

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

		void createCollisionCircle()
		{		
			collisionCircle.position.x = player.position.x;
			collisionCircle.position.y = player.position.y + 30;
			collisionCircle.radio = 30;
			collisionCircle.speed = { 0,0 };
			collisionCircle.active = true;
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

		void collisionCircleUpdate()
		{
			collisionCircle.position.x = player.position.x;
			collisionCircle.position.y = player.position.y + 30;
		}

		#ifdef TESTING
		void collisionCircleDraw() // only in DEBUG mode
		{
			DrawCircleV(collisionCircle.position, collisionCircle.radio, { 100, 0, 0, 200 });
		}
		#endif

		#ifdef RELEASE
		void collisionCircleDraw() // only in RELEASE mode
		{
			DrawCircleV(collisionCircle.position, collisionCircle.radio, { 0, 0, 0, 0 });
		}
		#endif

		void AsteroidDraw()
		{
			for (int i = 0; i < asteroidsLimit; i++)
			{
				DrawCircleV(asteroids[i].position, asteroids[i].radio, WHITE);
			}
		}
	}
}