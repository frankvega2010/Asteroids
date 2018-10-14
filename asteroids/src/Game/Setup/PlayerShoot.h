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

	extern int maxShoots;
	const int maxShootsSpecial = 30;
	extern float rapidfiretimer;
	extern float rapidFireRate;

	extern Shoot shoots[maxShootsSpecial];
	extern int gameScore;
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
