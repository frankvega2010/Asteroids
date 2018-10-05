#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	enum gameplayOptions {
		buttonContinue = 20,
		buttonRestart,
		buttonQuitToMenu
	};

	namespace Gameplay_Section
	{
		void UpdateGameplayScreen();
		void InitGameplayScreen();
		void InitGameplayVariables();
		void RestartPhase();
		bool FinishGameplayScreen();
		void DrawGameplay();
	}
}
#endif // GAMEPLAY_H