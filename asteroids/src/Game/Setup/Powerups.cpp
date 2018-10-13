#include "Powerups.h"
#include "Setup\Game.h"
#include "Setup\Player.h"

namespace Juego
{
	Powerup powerupInvincibility;

	namespace Gameplay_Section
	{

		static float powerupInvincibilityTimer = 0;
		static int powerupInvincibilityTimeCountdown = 3;

		void createPowerups()
		{
			powerupInvincibility.activated = false;
			powerupInvincibility.onScreen = true;
			powerupInvincibility.position = { (float)(GetRandomValue(0.0, (float)screenWidth)),(float)(GetRandomValue(0.0, (float)screenHeight)) };
			powerupInvincibility.radius = 10;
			powerupInvincibility.speed = {0,0};
		}

		void PowerupsUpdate()
		{
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
				powerupInvincibilityTimeCountdown = 10;
				player.textureTint = WHITE;
				powerupInvincibility.activated = false;
				powerupInvincibility.onScreen = true;
			}

			if (CheckCollisionCircles(powerupInvincibility.position, powerupInvincibility.radius, collisionCircle.position, collisionCircle.radius) && powerupInvincibility.onScreen)
			{
				powerupInvincibilityTimer = 0;
				player.textureTint = RED;
				PlaySound(powerup01);
				powerupInvincibility.activated = true;
				powerupInvincibility.onScreen = false;				
			}
		}

		void PowerupsDraw()
		{
			if (powerupInvincibility.activated)
			{
				DrawText(FormatText("Powerup: %i", powerupInvincibilityTimeCountdown), screenWidth / 1.5, screenHeight / 14, 40, YELLOW);
			}
			
			if (!powerupInvincibility.activated)
			{
				DrawCircleV(powerupInvincibility.position, powerupInvincibility.radius, RED);
			}
		}
	}
}