#include "menu.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Setup\Player.h"

using namespace Juego;

namespace Juego
{
	static const int maxButtons = 2;

	static Buttons buttons[maxButtons];
	static int buttonDistance = 0;
	static int buttonSelect = 0;

	//static float buttonOption = 0;
	static Color optionColor = RED;

	namespace Menu_Section
	{
		static void createMenuButtons()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.4f;
				buttons[i].position.y = (float)screenHeight / 2.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;
				buttons[i].height = (float)screenHeight / 12.0f;
				buttons[i].selected = false;
				buttons[i].defaultColor = RED;

				buttonDistance = buttonDistance + 100;
			}
		}

		void InitMenuScreen()
		{
			createMenuButtons();
			//EnableCursor();
			//ShowCursor();
			//ShowCursor();
			isScreenFinished = false;
		}

		static void MenuInput()
		{
			if (IsKeyPressed(KEY_DOWN))
			{
				mouse.selected = false;
				buttonSelect++;
			}

			if (IsKeyPressed(KEY_UP))
			{
				mouse.selected = false;
				buttonSelect--;
			}

			for (int i = 0; i < maxButtons; i++)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttons[i].selected || IsKeyPressed(KEY_ENTER) && buttons[i].selected)
				{
					switch (i)
					{
					case 0:
						buttonOption = buttonPlay;
						break;
					case 1:
						buttonOption = buttonQuit;
						break;
					}
					buttons[i].selected = false;
					isScreenFinished = true;
				}
			}
		}

		void UpdateMenuScreen()
		{
			#ifdef AUDIO
			// audio code
			#endif
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };

			MenuInput();
			for (int i = 0; i < maxButtons; i++)
			{
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }))
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

				if (buttonSelect == i)
				{
						buttons[i].selected = true;
						buttons[i].defaultColor = WHITE;
					
				}
			}
			
		}

		void DrawMenu()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);
			}
			//DrawRectangle(mouse.position.x, mouse.position.y, mouse.width, mouse.height, mouse.defaultColor); // placeholder if you want to use a custom Mouse Icon instead of the windows default one. If you use this remember to put Enbale and Disable Cursor.
			


			//DrawText(FormatText("3. Options"), 10, screenHeight / 3.2, defaultFontSize, WHITE);
			//DrawText(FormatText("4. How to play"), 10, screenHeight / 2.6, defaultFontSize, WHITE);
		}

		bool FinishMenuScreen()
		{
			//DisableCursor();
			return isScreenFinished;
		}
	}
}