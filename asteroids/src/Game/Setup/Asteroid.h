#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"

namespace Juego
{
	const int asteroidsLimit = 5;

	const int asteroidsSpeed = 200; // maybe * GetFrameTime();
	const int asteroidsBigLimit = 4;
	const int asteroidsMediumLimit = 8;
	const int asteroidsSmallLimit = 16;

	struct Asteroid {
		Vector2 position;
		Vector2 speed;
		int radius;
		bool active;
	};

	extern Asteroid asteroidsSmall[asteroidsSmallLimit];
	extern Asteroid asteroidsMedium[asteroidsMediumLimit];
	extern Asteroid asteroidsBig[asteroidsBigLimit];

	//extern Asteroid asteroids[asteroidsLimit];

	namespace Gameplay_Section
	{
		void createAsteroid();
		void AsteroidUpdate();
		void AsteroidDraw();
		void createCollisionCircle();
		void collisionCircleUpdate();
		void collisionCircleDraw();
	}
}
#endif // ASTEROID_H
