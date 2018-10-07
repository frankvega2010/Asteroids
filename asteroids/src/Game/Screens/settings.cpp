#include "settings.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"
//#include "Setup\Player.h"
#include "Setup/Asteroid.h"
#include "Screens\controls.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtons = 1;

	static Buttons buttons[maxButtons];
	static int buttonSelect = 0;

	namespace Settings_Section
	{
		static void createSettingsButtons()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 90.0f;
				buttons[i].position.y = (float)screenHeight / 1.1f; //+ buttonDistance_Controls;
				buttons[i].width = (float)screenWidth / 5.0f;
				buttons[i].height = (float)screenHeight / 12.0f;
				buttons[i].selected = false;
				buttons[i].defaultColor = RED;
				buttons[i].messageColor = BLANK;
			}
		}

		void InitSettingsScreen()
		{
			createSettingsButtons();
			isScreenFinished = false;
		}

		static void SettingsInput()
		{
			if (IsKeyPressed(KEY_DOWN))
			{
				mouse.selected = false;
				buttonSelect++;
				if (buttonSelect > maxButtons - 1)
				{
					buttonSelect--;
				}
			}

			if (IsKeyPressed(KEY_UP))
			{
				mouse.selected = false;
				buttonSelect--;
				if (buttonSelect < 0)
				{
					buttonSelect++;
				}
			}

			for (int i = 0; i < maxButtons; i++)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttons[i].selected || IsKeyPressed(KEY_ENTER) && buttons[i].selected)
				{
					switch (i)
					{
					case 0:
						buttonOption = buttonGoMenu;
						break;
					}
					buttons[i].selected = false;
					isScreenFinished = true;
				}
			}
		}

		void UpdateSettingsScreen()
		{
			AsteroidUpdate();
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };

			SettingsInput();
			for (int i = 0; i < maxButtons; i++)
			{
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }) || buttonSelect == i)
				{
					buttonSelect = i;
					buttons[i].defaultColor = WHITE;
					buttons[i].selected = true;
				}
				else
				{
					buttons[i].defaultColor = RED;
					buttons[i].selected = false;
				}
			}
		}

		void DrawSettings()
		{
			DrawBackground();
			AsteroidDraw();

			for (int i = 0; i < maxButtons; i++)
			{
				DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);

				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }) || buttonSelect == i)
				{
					buttons[i].messageColor = WHITE;

					switch (i)
					{
					case 0:
						DrawText("Click or Enter to go back!", buttons[i].position.x + 300, buttons[i].position.y, defaultFontSize / 2, buttons[i].messageColor);
						DrawText("", buttons[i].position.x + 300, buttons[i].position.y + 50, defaultFontSize / 2, buttons[i].messageColor);
						break;
					}
				}
				else
				{
					buttons[i].messageColor = BLANK;
				}
			}

			DrawText(FormatText("Placeholder for Settings Screen"), (float)screenWidth / 2.5f, screenHeight / 3.3, defaultFontSize / 1.5, WHITE);

			DrawText(FormatText("MENU"), buttons[0].position.x + 50, buttons[0].position.y + 5, defaultFontSize, buttons[0].defaultColor);
		}

		bool FinishSettingsScreen()
		{
			return isScreenFinished;
		}

	}
}