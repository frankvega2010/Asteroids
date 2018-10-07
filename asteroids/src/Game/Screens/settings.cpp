#include "settings.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"
//#include "Setup\Player.h"
#include "Setup/Asteroid.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtonsControls = 1;

	static Buttons buttonsControls[maxButtonsControls];
	static int buttonSelect = 0;

	namespace Settings_Section
	{
		static void SettingsInput()
		{

		}

		void UpdateSettingsScreen()
		{

		}
		void InitSettingsScreen()
		{
			isScreenFinished = false;
		}
		bool FinishSettingsScreen()
		{
			return isScreenFinished;
		}

		void DrawSettings()
		{

		}
	}
}