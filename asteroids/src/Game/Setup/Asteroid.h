#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"

namespace Juego
{
	struct Asteroid {
		Vector2 position;
		Vector2 speed;
		int radius;
		bool active;
	};

	const int asteroidsSpeed = 200;
	const int asteroidsBigLimit = 4;
	const int asteroidsMediumLimit = 8;
	const int asteroidsSmallLimit = 16;

	extern Asteroid asteroidsSmall[asteroidsSmallLimit];
	extern Asteroid asteroidsMedium[asteroidsMediumLimit];
	extern Asteroid asteroidsBig[asteroidsBigLimit];

	namespace Gameplay_Section
	{
		void createAsteroid();
		void AsteroidUpdate();
		void AsteroidDraw();
	}
}
#endif // ASTEROID_H
