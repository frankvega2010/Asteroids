#include "Powerups.h"
#include "Setup\Game.h"
#include "Setup\Player.h"

namespace Juego
{
	Powerup powerups[maxPowerups];

	namespace Gameplay_Section
	{
		void createPowerups()
		{
			for (int i = 0; i < maxPowerups; i++)
			{
				powerups[i].activated = false;
				powerups[i].onScreen = false;
				powerups[i].position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };
				powerups[i].radius = 10;
				powerups[i].speed = { 0,0 };
				powerups[i].useTimer = 0;
				powerups[i].useCountdown = 5;
				powerups[i].spawnTimer = 0;
				powerups[i].spawnCountdown = GetRandomValue(15, 30);
			}
		}

		void PowerupsUpdate()
		{
			for (int i = 0; i < maxPowerups; i++)
			{
				if (!powerups[i].onScreen)
				{
					powerups[i].spawnTimer += 1 * GetFrameTime();
					if (powerups[i].spawnTimer  > 1)
					{
						powerups[i].spawnTimer = 0;
						powerups[i].spawnCountdown--;
						if (powerups[i].spawnCountdown < 0)
						{
							powerups[i].spawnCountdown = GetRandomValue(15, 30);
							powerups[i].onScreen = true;
						}
					}
				}

				if (powerups[i].activated)
				{
					powerups[i].useTimer += 1 * GetFrameTime();
				}

				if (powerups[i].useTimer> 1)
				{
					powerups[i].useTimer = 0;
					powerups[i].useCountdown--;
				}

				if (powerups[i].useCountdown < 0)
				{
					player.textureTint = WHITE;
					powerups[i].activated = false;
					powerups[i].useCountdown = 5;
				}

				switch (i)
				{
				case Invicibility: if (powerups[Invicibility].activated) player.textureTint = RED; break;
				case MaxRapidFire: if (powerups[MaxRapidFire].activated) player.textureTint = GOLD; break;
				}

				if (powerups[Invicibility].activated && powerups[MaxRapidFire].activated) player.textureTint = LIME;

				if (CheckCollisionCircles(powerups[i].position, powerups[i].radius, collisionCircle.position, collisionCircle.radius) && powerups[i].onScreen)
				{
					powerups[i].useTimer = 0;

					PlaySound(powerup01);
					powerups[i].activated = true;
					powerups[i].onScreen = false;
					powerups[i].position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };
				}
			}
		}

		void PowerupsDraw()
		{
			if (powerups[Invicibility].activated)
			{
				DrawText(FormatText("Invincibility: %i", powerups[Invicibility].useCountdown), screenWidth / 1.5, screenHeight / 6, 40, YELLOW);
			}

			if (!powerups[Invicibility].activated && powerups[Invicibility].onScreen)
			{
				DrawCircleV(powerups[Invicibility].position, powerups[Invicibility].radius, RED);
			}

			if (powerups[MaxRapidFire].activated)
			{
				DrawText(FormatText("Max Rapid Fire: %i", powerups[MaxRapidFire].useCountdown), screenWidth / 1.5, screenHeight / 4.5, 40, YELLOW);
			}

			if (!powerups[MaxRapidFire].activated && powerups[MaxRapidFire].onScreen)
			{
				DrawCircleV(powerups[MaxRapidFire].position, powerups[MaxRapidFire].radius, GOLD);
			}
		}
	}
}