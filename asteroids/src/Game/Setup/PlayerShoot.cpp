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
	static float rapidFireRate = 0.15;
	int gameScore = 0; // llevar a gameplay?

	namespace Gameplay_Section
	{
		void createShoot()
		{
			gameScore = 0;

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
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				rapidfiretimer += 1 * GetFrameTime();
				for (int i = 0; i < maxShoots; i++)
				{
					
					if (rapidfiretimer > rapidFireRate)
					{
						if (!shoots[i].active)
						{					//player.position.x + sinf(player.rotation)*(shipHeightv2), player.position.y - cosf(player.rotation)*(shipHeightv2) }, collisionCircle.radius, { 100, 0, 0, 200 }
							shoots[i].position = { player.position.x + sinf(player.rotation)*(shipHeight), player.position.y - cosf(player.rotation)*(shipHeight) };
							shoots[i].active = true;
							shoots[i].speed.x = 2.0*sin(player.rotation)*player.defaultSpeed;
							shoots[i].speed.y = 2.0*cos(player.rotation)*player.defaultSpeed;
							shoots[i].rotation = player.rotation;
							rapidfiretimer = 0;
							break;
						}
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

			// Collision logic: player-shootss vs meteors
			for (int i = 0; i < maxShoots; i++)
			{
				if ((shoots[i].active))
				{
					for (int a = 0; a < asteroidsBigLimit; a++)
					{
						if (asteroidsBig[a].active && CheckCollisionCircles(shoots[i].position, shoots[i].radius, asteroidsBig[a].position, asteroidsBig[a].radius))
						{
							asteroidsBig[a].isExplosionActive = true;
							shoots[i].active = false;
							shoots[i].lifespan = 0;
							asteroidsBig[a].active = false;
							destroyedAsteroidsCount++;
							gameScore = gameScore + 25;

							for (int j = 0; j < 2; j++)
							{
								if (midAsteroidsCount % 2 == 0)
								{
									asteroidsMedium[midAsteroidsCount].position = { asteroidsBig[a].position.x, asteroidsBig[a].position.y };
									asteroidsMedium[midAsteroidsCount].speed = { cos(shoots[i].rotation)*asteroidsSpeed*-1, sin(shoots[i].rotation)*asteroidsSpeed*-1 };
								}
								else
								{
									asteroidsMedium[midAsteroidsCount].position = { asteroidsBig[a].position.x, asteroidsBig[a].position.y };
									asteroidsMedium[midAsteroidsCount].speed = { cos(shoots[i].rotation)*asteroidsSpeed, sin(shoots[i].rotation)*asteroidsSpeed };
								}

								asteroidsMedium[midAsteroidsCount].active = true;
								midAsteroidsCount++;
							}
							a = asteroidsBigLimit;
						}
					}

					for (int b = 0; b < asteroidsMediumLimit; b++)
					{
						if (asteroidsMedium[b].active && CheckCollisionCircles(shoots[i].position, shoots[i].radius, asteroidsMedium[b].position, asteroidsMedium[b].radius))
						{
							asteroidsMedium[b].isExplosionActive = true;
							shoots[i].active = false;
							shoots[i].lifespan = 0;
							asteroidsMedium[b].active = false;
							destroyedAsteroidsCount++;
							gameScore = gameScore + 50;

							for (int j = 0; j < 2; j++)
							{
								if (smallAsteroidsCount % 2 == 0)
								{
									asteroidsSmall[smallAsteroidsCount].position = { asteroidsMedium[b].position.x, asteroidsMedium[b].position.y };
									asteroidsSmall[smallAsteroidsCount].speed = { cos(shoots[i].rotation)*asteroidsSpeed*-1, sin(shoots[i].rotation)*asteroidsSpeed*-1 };
								}
								else
								{
									asteroidsSmall[smallAsteroidsCount].position = { asteroidsMedium[b].position.x, asteroidsMedium[b].position.y };
									asteroidsSmall[smallAsteroidsCount].speed = { cos(shoots[i].rotation)*asteroidsSpeed, sin(shoots[i].rotation)*asteroidsSpeed };
								}

								asteroidsSmall[smallAsteroidsCount].active = true;
								smallAsteroidsCount++;
							}
							b = asteroidsMediumLimit;
						}
					}

					for (int c = 0; c < asteroidsSmallLimit; c++)
					{
						if (asteroidsSmall[c].active && CheckCollisionCircles(shoots[i].position, shoots[i].radius, asteroidsSmall[c].position, asteroidsSmall[c].radius))
						{
							asteroidsSmall[c].isExplosionActive = true;
							shoots[i].active = false;
							shoots[i].lifespan = 0;
							asteroidsSmall[c].active = false;
							destroyedAsteroidsCount++;
							gameScore = gameScore + 100;
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