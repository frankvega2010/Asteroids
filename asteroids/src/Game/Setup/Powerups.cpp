#include "Powerups.h"
#include "Setup\Game.h"
#include "Setup\Player.h"

namespace Juego
{
	Powerup powerupInvincibility;
	Powerup powerupmaxRapidFire;

	namespace Gameplay_Section
	{
		static float powerupMaxRapidFireSpawnTimer = 0;
		static int powerupMaxRapidFireSpawn = 25;

		static float powerupMaxRapidFireTimer = 0;
		static int powerupMaxRapidFireTimeCountdown = 6;


		static float powerupInvicibilitySpawnTimer = 0;
		static int powerupInvicibilitySpawn = 15;

		static float powerupInvincibilityTimer = 0;
		static int powerupInvincibilityTimeCountdown = 4;

		void createPowerups()
		{
			powerupInvincibility.activated = false;
			powerupInvincibility.onScreen = true;
			powerupInvincibility.position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };
			powerupInvincibility.radius = 10;
			powerupInvincibility.speed = {0,0};

			powerupmaxRapidFire.activated = false;
			powerupmaxRapidFire.onScreen = true;
			powerupmaxRapidFire.position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };
			powerupmaxRapidFire.radius = 10;
			powerupmaxRapidFire.speed = { 0,0 };
		}

		void PowerupsUpdate() // hacer un array!
		{
			if (!powerupmaxRapidFire.onScreen)
			{
				powerupMaxRapidFireSpawnTimer += 1 * GetFrameTime();
				if (powerupMaxRapidFireSpawnTimer  > 1)
				{
					powerupMaxRapidFireSpawnTimer = 0;
					powerupMaxRapidFireSpawn--;
					if (powerupMaxRapidFireSpawn < 0)
					{
						powerupMaxRapidFireSpawn = 25;
						powerupmaxRapidFire.onScreen = true;
					}
				}
			}

			if (powerupmaxRapidFire.activated)
			{
				powerupMaxRapidFireTimer += 1 * GetFrameTime();
			}

			if (powerupMaxRapidFireTimer > 1)
			{
				powerupMaxRapidFireTimer = 0;
				powerupMaxRapidFireTimeCountdown--;
			}

			if (powerupMaxRapidFireTimeCountdown < 0)
			{
				player.textureTint = WHITE;
				powerupmaxRapidFire.activated = false;
				powerupMaxRapidFireTimeCountdown = 6;
			}

			if (!powerupInvincibility.onScreen)
			{
				powerupInvicibilitySpawnTimer += 1 * GetFrameTime();
				if (powerupInvicibilitySpawnTimer > 1)
				{
					powerupInvicibilitySpawnTimer = 0;
					powerupInvicibilitySpawn--;
					if (powerupInvicibilitySpawn < 0)
					{
						powerupInvicibilitySpawn = 15;
						powerupInvincibility.onScreen = true;
					}
				}
			}

			if (powerupInvincibility.activated)
			{
				powerupInvincibilityTimer += 1 * GetFrameTime();
			}

			if (powerupInvincibilityTimer > 1)
			{
				powerupInvincibilityTimer = 0;
				powerupInvincibilityTimeCountdown--;
			}


			if (powerupInvincibilityTimeCountdown < 0)
			{
				player.textureTint = WHITE;
				powerupInvincibility.activated = false;
				powerupInvincibilityTimeCountdown = 4;
			}

			if (CheckCollisionCircles(powerupInvincibility.position, powerupInvincibility.radius, collisionCircle.position, collisionCircle.radius) && powerupInvincibility.onScreen)
			{
				powerupInvicibilitySpawn = 15;
				powerupInvincibilityTimer = 0;
				player.textureTint = RED;
				PlaySound(powerup01);
				powerupInvincibility.activated = true;
				powerupInvincibility.onScreen = false;	
				powerupInvincibility.position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };
			}

			if (CheckCollisionCircles(powerupmaxRapidFire.position, powerupmaxRapidFire.radius, collisionCircle.position, collisionCircle.radius) && powerupmaxRapidFire.onScreen)
			{
				powerupMaxRapidFireSpawn = 25;
				powerupMaxRapidFireTimer = 0;
				player.textureTint = GOLD;
				PlaySound(powerup01);
				powerupmaxRapidFire.activated = true;
				powerupmaxRapidFire.onScreen = false;
				powerupmaxRapidFire.position = { (float)(GetRandomValue(0.0, screenWidth)),(float)(GetRandomValue(0.0, screenHeight)) };
			}
		}

		void PowerupsDraw()
		{
			if (powerupInvincibility.activated)
			{
				DrawText(FormatText("Invincibility: %i", powerupInvincibilityTimeCountdown), screenWidth / 1.5, screenHeight / 14, 40, YELLOW);
			}

			if (powerupmaxRapidFire.activated)
			{
				DrawText(FormatText("Max Rapid Fire: %i", powerupMaxRapidFireTimeCountdown), screenWidth / 1.5, screenHeight / 14, 40, YELLOW);
			}
			
			if (!powerupInvincibility.activated && powerupInvincibility.onScreen)
			{
				DrawCircleV(powerupInvincibility.position, powerupInvincibility.radius, RED);
			}

			if (!powerupmaxRapidFire.activated && powerupmaxRapidFire.onScreen)
			{
				DrawCircleV(powerupmaxRapidFire.position, powerupmaxRapidFire.radius, GOLD);
			}
		}
	}
}