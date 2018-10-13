#include "Powerups.h"
#include "Setup\Game.h"
#include "Setup\Player.h"

namespace Juego
{
	Powerup powerupInvincibility;

	namespace Gameplay_Section
	{

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
		}

		void PowerupsUpdate()
		{
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
				powerupInvincibilityTimeCountdown = 4;
				player.textureTint = WHITE;
				powerupInvincibility.activated = false;
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
		}

		void PowerupsDraw()
		{
			if (powerupInvincibility.activated)
			{
				DrawText(FormatText("Invincibility: %i", powerupInvincibilityTimeCountdown), screenWidth / 1.5, screenHeight / 14, 40, YELLOW);
			}
			
			if (!powerupInvincibility.activated && powerupInvincibility.onScreen)
			{
				DrawCircleV(powerupInvincibility.position, powerupInvincibility.radius, RED);
			}
		}
	}
}