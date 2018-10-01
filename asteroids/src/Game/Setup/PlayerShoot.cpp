#include "PlayerShoot.h"

namespace Juego
{
	Shoot shoots[maxShoots];

	namespace Gameplay_Section
	{
		void createShoot()
		{
			for (int i = 0; i < maxShoots; i++)
			{
				shoots[i].position.x = 0;
				shoots[i].position.y = 0;
				shoots[i].speed.x = 0;
				shoots[i].speed.y = 0;
				shoots[i].rotation = 0;
				shoots[i].radius = 2;
				shoots[i].lifespan = 0;
				shoots[i].color = WHITE;
				shoots[i].active = false;
			}
		}
		void ShootInput()
		{
			// Player shoot logic
			if (IsKeyPressed(KEY_SPACE))
			{
				for (int i = 0; i < maxShoots; i++)
				{
					if (!shoots[i].active)
					{
						shoots[i].position = { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
						shoots[i].active = true;
						shoots[i].speed.x = 2.0*sin(player.rotation*DEG2RAD)*player.defaultSpeed;
						shoots[i].speed.y = 2.0*cos(player.rotation*DEG2RAD)*player.defaultSpeed;
						shoots[i].rotation = player.rotation;
						break;
					}
				}
			}
		}
		void ShootUpdate()
		{
			// Shot logic
			for (int i = 0; i < maxShoots; i++)
			{
				if (shoots[i].active)
				{
					// Movement
					shoots[i].position.x += shoots[i].speed.x * GetFrameTime();
					shoots[i].position.y -= shoots[i].speed.y * GetFrameTime();

					// Collision logic: shoot vs walls
					if (shoots[i].position.x > screenWidth + shoots[i].radius)
					{
						shoots[i].active = false;
						shoots[i].lifespan = 0;//check lifespan if that variable is needed
					}
					else if (shoots[i].position.x < 0 - shoots[i].radius)
					{
						shoots[i].active = false;
						shoots[i].lifespan = 0;
					}
					if (shoots[i].position.y > screenHeight + shoots[i].radius)
					{
						shoots[i].active = false;
						shoots[i].lifespan = 0;
					}
					else if (shoots[i].position.y < 0 - shoots[i].radius)
					{
						shoots[i].active = false;
						shoots[i].lifespan = 0;
					}
				}
			}
		}
		void ShootDraw()
		{
			// Draw shoot
			for (int i = 0; i < maxShoots; i++)
			{
				if (shoots[i].active) DrawCircleV(shoots[i].position, shoots[i].radius, WHITE);
			}
		}
	}
}