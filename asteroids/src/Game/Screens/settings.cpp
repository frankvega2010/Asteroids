#include "settings.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"
#include "Setup/Asteroid.h"
#include "Screens\controls.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtons = 1;
	static const int maxButtonsLeft = 7;
	static const int maxButtonsRight = 4;

	static Buttons buttons[maxButtons];
	static Buttons buttonsSettingsLeft[maxButtonsLeft];
	static Buttons buttonsSettingsRight[maxButtonsRight];
	static int buttonSelect = 0;
	static int buttonDistanceSettingsLeft = 0;

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

			for (int i = 0; i < maxButtonsLeft; i++)
			{
				buttonsSettingsLeft[i].position.x = (float)screenWidth / 90.0f;
				buttonsSettingsLeft[i].position.y = (float)screenHeight / 10.0f + buttonDistanceSettingsLeft;
				buttonsSettingsLeft[i].width = (float)screenWidth / 5.0f;
				buttonsSettingsLeft[i].height = (float)screenHeight / 12.0f;
				buttonsSettingsLeft[i].selected = false;
				buttonsSettingsLeft[i].defaultColor = RED;
				buttonsSettingsLeft[i].messageColor = BLANK;

				buttonDistanceSettingsLeft = buttonDistanceSettingsLeft + 75;
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
			#ifdef AUDIO
			UpdateMusicStream(song_alert);
			#endif

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

			for (int i = 0; i < maxButtonsLeft; i++)
			{
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttonsSettingsLeft[i].position.x, buttonsSettingsLeft[i].position.y, buttonsSettingsLeft[i].width, buttonsSettingsLeft[i].height }) || buttonSelect == i)
				{
					buttonSelect = i;
					buttonsSettingsLeft[i].defaultColor = WHITE;
					buttonsSettingsLeft[i].selected = true;
				}
				else
				{
					buttonsSettingsLeft[i].defaultColor = RED;
					buttonsSettingsLeft[i].selected = false;
				}
			}
		}

		void DrawSettings()
		{
			DrawBackground();
			AsteroidDraw();

			// template for multiple buttons, in this instance only 1 button is used.
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

			// Left side buttons.
			for (int i = 0; i < maxButtonsLeft; i++)
			{
				DrawRectangleLines(buttonsSettingsLeft[i].position.x, buttonsSettingsLeft[i].position.y, buttonsSettingsLeft[i].width, buttonsSettingsLeft[i].height, buttonsSettingsLeft[i].defaultColor);
			}

			DrawText(FormatText("Placeholder for Settings Screen"), (float)screenWidth / 2.5f, screenHeight / 3.3, defaultFontSize / 1.5, WHITE);

			DrawText(FormatText("MENU"), buttons[0].position.x + 50, buttons[0].position.y + 5, defaultFontSize, buttons[0].defaultColor);
		}

		bool FinishSettingsScreen()
		{
			buttonDistanceSettingsLeft = 0;
			return isScreenFinished;
		}

	}
}