#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"

namespace Juego
{

	const int asteroidsLimit = 5;

	struct Asteroid {
		Vector2 position;
		Vector2 speed;
		int radio;
		bool active;
	};

	
	extern Asteroid asteroids[asteroidsLimit];
	extern Asteroid collisionCircle;

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
