#include "Powerups.h"
#include "Setup\Game.h"
#include "Setup\Player.h"
#include "Screens\gameplay.h"
#include "Screens\settings.h"
#include "Setup\PlayerShoot.h"

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

				if (resolutionNormal) powerups[i].radius = 10;
				else if (resolutionSmall) powerups[i].radius = 5;

				//powerups[i].radius = 10;
				powerups[i].speed = { 0,0 };
				powerups[i].useTimer = 0;
				powerups[i].useCountdown = 5;
				powerups[i].spawnTimer = 0;
				powerups[i].spawnCountdown = GetRandomValue(5, 20);
			}
		}

		void PowerupsUpdate()
		{
			for (int i = 0; i < maxPowerups; i++)
			{
				if (gameON)
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
								powerups[i].spawnCountdown = GetRandomValue(5, 20);
								powerups[i].onScreen = true;
							}
						}
					}

					if (powerups[i].activated)
					{
						powerups[i].useTimer += 1 * GetFrameTime();
					}
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

					if (i == MaxRapidFire)
					{
						rapidfiretimer = 0;
						maxShoots = 10;
						rapidFireRate = 0.15;
					}
				}

				switch (i)
				{
				case Invincibility: if (powerups[Invincibility].activated) player.textureTint = RED; break;
				case MaxRapidFire: if (powerups[MaxRapidFire].activated) player.textureTint = GOLD; break;
				}

				if (powerups[Invincibility].activated && powerups[MaxRapidFire].activated) player.textureTint = LIME;

				if (CheckCollisionCircles(powerups[i].position, powerups[i].radius, collisionCircle.position, collisionCircle.radius) && powerups[i].onScreen)
				{
					powerups[i].useTimer = 0;

					PlaySound(powerup01);
					powerups[i].activated = true;
					powerups[i].onScreen = false;
					powerups[i].position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };

					if (i == MaxRapidFire)
					{
						rapidfiretimer = 0;
						maxShoots = 30;
						rapidFireRate = 0.05;	
					}
				}
			}
		}

		void PowerupsDraw()
		{
			if (powerups[Invincibility].activated)
			{
				DrawText(FormatText("Invincibility: %i", powerups[Invincibility].useCountdown), screenWidth / 1.7, screenHeight / 6, defaultFontSize / 1.2, YELLOW);
			}

			if (!powerups[Invincibility].activated && powerups[Invincibility].onScreen)
			{
				DrawCircleV(powerups[Invincibility].position, powerups[Invincibility].radius, RED);
				if (resolutionNormal) DrawTexturePro(powerupInvincibility, { 0.0f,0.0f, 30,30 }, { powerups[Invincibility].position.x,powerups[Invincibility].position.y, 30,30 }, { 15,15 }, 0, WHITE);
				else if (resolutionSmall) DrawTexturePro(powerupInvincibility, { 0.0f,0.0f, 15,15 }, { powerups[Invincibility].position.x,powerups[Invincibility].position.y, 15,15 }, { 15 / 2,15 / 2 }, 0, WHITE);
			}

			if (powerups[MaxRapidFire].activated)
			{
				DrawText(FormatText("Max Rapid Fire: %i", powerups[MaxRapidFire].useCountdown), screenWidth / 1.7, screenHeight / 4.5, defaultFontSize / 1.2, YELLOW);
			}

			if (!powerups[MaxRapidFire].activated && powerups[MaxRapidFire].onScreen)
			{
				DrawCircleV(powerups[MaxRapidFire].position, powerups[MaxRapidFire].radius, GOLD);
				if (resolutionNormal) DrawTexturePro(powerupMaxRapidFire, { 0.0f,0.0f, 30,30 } , { powerups[MaxRapidFire].position.x,powerups[MaxRapidFire].position.y, 30,30 }, { 15,15 }, 0, WHITE);
				else if(resolutionSmall) DrawTexturePro(powerupMaxRapidFire, { 0.0f,0.0f, 15,15 }, { powerups[MaxRapidFire].position.x,powerups[MaxRapidFire].position.y, 15,15 }, { 15/2,15/2 }, 0, WHITE);
			}
		}
	}
}