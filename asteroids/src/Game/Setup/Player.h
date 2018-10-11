#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace Juego
{
	struct rocketShip
	{
		Vector2 position;
		Vector2 acceleration;
		float rotation;
		float defaultSpeed;
		int score;
		bool isAlive;
		bool inputActive;
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
		void createCollisionCircle();
		void playerInput();
		void playerUpdate();
		void collisionCircleUpdate();
		void playerDraw();
		void collisionCircleDraw();
	}
}
#endif // PLAYER_H
