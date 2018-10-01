#ifndef PLAYERSHOOT_H
#define PLAYERSHOOT_H
#include <cmath>
#include "raylib.h"
#include "Player.h"
#include "Game.h"
#include "Asteroid.h"

namespace Juego
{
	struct Shoot {
		Vector2 position;
		Vector2 speed;
		float rotation;
		int radius;
		int lifespan;
		bool active;
		Color color;
	};

	const int maxShoots = 10;
	extern Shoot shoots[maxShoots];
	extern int destroyedAsteroidsCount;

	namespace Gameplay_Section
	{
		void createShoot();
		void ShootInput();
		void ShootUpdate();
		void ShootDraw();
	}
}

#endif // PLAYERSHOOT_H
