#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace Juego
{
	struct rocketShip
	{
		Vector2 position;
		Vector2 pointA;
		Vector2 pointB;
		Vector2 pointC;
		int score;
	};

	extern rocketShip player;

	namespace Gameplay_Section
	{
		void createPlayer();
		void playerInput();
		void playerUpdate();
		void playerDraw();
	}
}
#endif // PLAYER_H
