#include "PlayerShoot.h"
#include "Screens\gameplay.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	Shoot shoots[maxShoots];

	static int midAsteroidsCount = 0;
	static int smallAsteroidsCount = 0;
	int destroyedAsteroidsCount = 0;
	static float rapidfiretimer = 0;

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

			midAsteroidsCount = 0;
			smallAsteroidsCount = 0;
			destroyedAsteroidsCount = 0;
		}
		void ShootInput()
		{
			// Player shoot logic
			if (IsKeyDown(KEY_SPACE))
			{
				rapidfiretimer += 1 * GetFrameTime();
				for (int i = 0; i < maxShoots; i++)
				{
					
					if (rapidfiretimer > 0.15) // default 1.0 1.5
					{
						if (!shoots[i].active)
						{
							shoots[i].position = { player.position.x + sin(player.rotation*DEG2RAD)*(shipHeight), player.position.y - cos(player.rotation*DEG2RAD)*(shipHeight) };
							shoots[i].active = true;
							shoots[i].speed.x = 2.0*sin(player.rotation*DEG2RAD)*player.defaultSpeed;
							shoots[i].speed.y = 2.0*cos(player.rotation*DEG2RAD)*player.defaultSpeed;
							shoots[i].rotation = player.rotation;
							rapidfiretimer = 0;
							break;
						}
					}		
				}
			} //else if (IsKeyPressed(KEY_SPACE))
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

			// Collision logic: player-shootss vs meteors
			for (int i = 0; i < maxShoots; i++)
			{
				if ((shoots[i].active))
				{
					for (int a = 0; a < asteroidsBigLimit; a++)
					{
						if (asteroidsBig[a].active && CheckCollisionCircles(shoots[i].position, shoots[i].radius, asteroidsBig[a].position, asteroidsBig[a].radius))
						{
							shoots[i].active = false;
							shoots[i].lifespan = 0;
							asteroidsBig[a].active = false;
							destroyedAsteroidsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (midAsteroidsCount % 2 == 0)
								{
									asteroidsMedium[midAsteroidsCount].position = { asteroidsBig[a].position.x, asteroidsBig[a].position.y };
									asteroidsMedium[midAsteroidsCount].speed = { cos(shoots[i].rotation*DEG2RAD)*asteroidsSpeed*-1, sin(shoots[i].rotation*DEG2RAD)*asteroidsSpeed*-1 };
								}
								else
								{
									asteroidsMedium[midAsteroidsCount].position = { asteroidsBig[a].position.x, asteroidsBig[a].position.y };
									asteroidsMedium[midAsteroidsCount].speed = { cos(shoots[i].rotation*DEG2RAD)*asteroidsSpeed, sin(shoots[i].rotation*DEG2RAD)*asteroidsSpeed };
								}

								asteroidsMedium[midAsteroidsCount].active = true;
								midAsteroidsCount++;
							}
							//asteroidsBig[a].position = (Vector2){-100, -100};
							a = asteroidsBigLimit;
						}
					}

					for (int b = 0; b < asteroidsMediumLimit; b++)
					{
						if (asteroidsMedium[b].active && CheckCollisionCircles(shoots[i].position, shoots[i].radius, asteroidsMedium[b].position, asteroidsMedium[b].radius))
						{
							shoots[i].active = false;
							shoots[i].lifespan = 0;
							asteroidsMedium[b].active = false;
							destroyedAsteroidsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (smallAsteroidsCount % 2 == 0)
								{
									asteroidsSmall[smallAsteroidsCount].position = { asteroidsMedium[b].position.x, asteroidsMedium[b].position.y };
									asteroidsSmall[smallAsteroidsCount].speed = { cos(shoots[i].rotation*DEG2RAD)*asteroidsSpeed*-1, sin(shoots[i].rotation*DEG2RAD)*asteroidsSpeed*-1 };
								}
								else
								{
									asteroidsSmall[smallAsteroidsCount].position = { asteroidsMedium[b].position.x, asteroidsMedium[b].position.y };
									asteroidsSmall[smallAsteroidsCount].speed = { cos(shoots[i].rotation*DEG2RAD)*asteroidsSpeed, sin(shoots[i].rotation*DEG2RAD)*asteroidsSpeed };
								}

								asteroidsSmall[smallAsteroidsCount].active = true;
								smallAsteroidsCount++;
							}
							//asteroidsMedium[b].position = (Vector2){-100, -100};
							b = asteroidsMediumLimit;
						}
					}

					for (int c = 0; c < asteroidsSmallLimit; c++)
					{
						if (asteroidsSmall[c].active && CheckCollisionCircles(shoots[i].position, shoots[i].radius, asteroidsSmall[c].position, asteroidsSmall[c].radius))
						{
							shoots[i].active = false;
							shoots[i].lifespan = 0;
							asteroidsSmall[c].active = false;
							destroyedAsteroidsCount++;
							// asteroidsSmall[c].position = (Vector2){-100, -100};
							c = asteroidsSmallLimit;
						}
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