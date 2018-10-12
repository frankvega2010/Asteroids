#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	enum gameplayOptions {
		buttonContinue = 20,
		buttonRestart,
		buttonGameOver,
		buttonQuitToMenu
	};

	extern int scoreMultiplier;
	extern bool isExplosionActive;

	namespace Gameplay_Section
	{
		void UpdateGameplayScreen();
		void InitGameplayScreen();
		void InitGameplayVariables();
		void RestartPhase();
		bool FinishGameplayScreen();
		void DrawGameplay();
		void DrawTimer(float widthvalue1, float widthvalue2, float heightvalue1);
		void DeInitGameplayResources();
	}
}
#endif // GAMEPLAY_H