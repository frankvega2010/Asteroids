#ifndef POWERUPS_H
#define POWERUPS_H
#include "raylib.h"

namespace Juego
{
	struct Powerup {
		Vector2 position;
		Vector2 speed;
		int radius;
		bool activated;
		bool onScreen;
	};

	extern Powerup powerupInvincibility;

	namespace Gameplay_Section
	{
		void createPowerups();
		void PowerupsUpdate();
		void PowerupsDraw();
	}
}

#endif //POWERUPS_H