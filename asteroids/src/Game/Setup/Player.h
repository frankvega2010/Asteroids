#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace Juego
{
	struct rocketShip
	{
		Vector2 position;
		Vector2 speed;
		float acceleration;
		float rotation;
		float defaultSpeed;
		int score;
	};

	struct Circle {
		Vector2 position;
		Vector2 speed;
		int radius;
		bool active;
	};

	extern rocketShip player;
	extern Circle collisionCircle;
	extern float shipHeight;
	extern float shipHeightv2;

	namespace Gameplay_Section
	{
		void createPlayer();
		void playerInput();
		void playerUpdate();
		void playerDraw();
	}
}
#endif // PLAYER_H
