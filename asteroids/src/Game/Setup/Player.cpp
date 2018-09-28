#include "Player.h"

#include "Setup\Game.h"
#include "Setup\Ball.h"

namespace Juego
{
	rocketShip player;
	namespace Gameplay_Section
	{
		void createPlayer()
		{
			player.position = { screenWidth / 2, screenHeight / 2};
			player.pointA = player.position;
			player.pointB = { player.position.x - 30, player.position.y + 50 };
			player.pointC = { player.position.x + 30, player.position.y + 50 };
			player.score = 0;
		}
		
		void playerInput()
		{
			if (IsKeyDown(KEY_W)) player.position.y -= 400 * GetFrameTime();// a = b b = c c = a
			if (IsKeyDown(KEY_S)) player.position.y += 400 * GetFrameTime();
			if (IsKeyDown(KEY_A)) player.position.x -= 400 * GetFrameTime();
			if (IsKeyDown(KEY_D)) player.position.x += 400 * GetFrameTime();
		}

		void playerUpdate()
		{
			player.pointA = player.position;
			player.pointB = { player.position.x - 30, player.position.y + 50 };
			player.pointC = { player.position.x + 30, player.position.y + 50 };
		}

		void playerDraw()
		{
			DrawTriangle(player.pointA, player.pointB, player.pointC, Color GREEN);
			//DrawRectangle(20, 20, 20, 20, RED);
		}
	}
}