#include "menu.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Setup\Player.h"

using namespace Juego;

namespace Juego
{
	namespace Menu_Section
	{
		static void MenuInput()
		{

		}

		void UpdateMenuScreen()
		{
			#ifdef AUDIO
			// audio code
			#endif
			
			MenuInput();
		}

		void InitMenuScreen()
		{
			isScreenFinished = false;
		}

		bool FinishMenuScreen()
		{
			return isScreenFinished;
		}

		void DrawMenu()
		{

		}
	}
}