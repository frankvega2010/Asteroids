#include "gameover.h"

#include "Setup/Game.h"
#include "Screens/gameplay.h"
#include "Setup\Player.h"

namespace Juego
{
	namespace GameOver_Section
	{
		static void GameOverInput()
		{

		}

		void UpdateGameOverScreen()
		{
			GameOverInput(); 
		}

		void InitGameOverScreen()
		{
			isScreenFinished = false;
		}

		bool FinishGameOverScreen()
		{
			return isScreenFinished;
		}

		void DrawGameOver()
		{

		}
	}
}