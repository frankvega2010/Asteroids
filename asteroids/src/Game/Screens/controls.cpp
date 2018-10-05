#include "controls.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens\gameplay.h"
#include "Setup/Asteroid.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtonsControls = 1;

	static Buttons buttonsControls[maxButtonsControls];
	//static int buttonDistance_Controls = 0;
	static int buttonSelect = 0;

	namespace Controls_Section
	{
		static void createControlsButtons()
		{
			for (int i = 0; i < maxButtonsControls; i++)
			{
				buttonsControls[i].position.x = (float)screenWidth / 90.0f;
				buttonsControls[i].position.y = (float)screenHeight / 1.1f; //+ buttonDistance_Controls;
				buttonsControls[i].width = (float)screenWidth / 5.0f;
				buttonsControls[i].height = (float)screenHeight / 12.0f;
				buttonsControls[i].selected = false;
				buttonsControls[i].defaultColor = RED;
				buttonsControls[i].messageColor = BLANK;

				//buttonDistance_Controls = buttonDistance_Controls + 100;
			}
		}

		void InitControlsScreen()
		{
			createControlsButtons();
			isScreenFinished = false;
		}

		static void ControlsInput()
		{
			if (IsKeyPressed(KEY_DOWN))
			{
				mouse.selected = false;
				buttonSelect++;
				if (buttonSelect > maxButtonsControls - 1)
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

			for (int i = 0; i < maxButtonsControls; i++)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttonsControls[i].selected || IsKeyPressed(KEY_ENTER) && buttonsControls[i].selected)
				{
					switch (i)
					{
					case 0:
						buttonOption = buttonGoMenu;
						break;
					}
					buttonsControls[i].selected = false;
					isScreenFinished = true;
				}
			}
		}

		void UpdateControlsScreen()
		{
			#ifdef AUDIO
						// audio code
			#endif
			AsteroidUpdate();
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };

			ControlsInput();
			for (int i = 0; i < maxButtonsControls; i++)
			{
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttonsControls[i].position.x, buttonsControls[i].position.y, buttonsControls[i].width, buttonsControls[i].height }) || buttonSelect == i)
				{
					buttonSelect = i;
					buttonsControls[i].defaultColor = WHITE;
					buttonsControls[i].selected = true;
				}
				else
				{
					buttonsControls[i].defaultColor = RED;
					buttonsControls[i].selected = false;
				}
			}
		}
		

		void DrawControls()
		{
			AsteroidDraw();


			for (int i = 0; i < maxButtonsControls; i++)
			{
				DrawRectangleLines(buttonsControls[i].position.x, buttonsControls[i].position.y, buttonsControls[i].width, buttonsControls[i].height, buttonsControls[i].defaultColor);

				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttonsControls[i].position.x, buttonsControls[i].position.y, buttonsControls[i].width, buttonsControls[i].height }) || buttonSelect == i)
				{
					buttonsControls[i].messageColor = WHITE;

					switch (i)
					{
					case 0:
						DrawText("Go back to menu!", buttonsControls[i].position.x + 300, buttonsControls[i].position.y, defaultFontSize / 2, buttonsControls[i].messageColor);
						DrawText("", buttonsControls[i].position.x + 300, buttonsControls[i].position.y + 50, defaultFontSize / 2, buttonsControls[i].messageColor);
						break;
					}
				}
				else
				{
					buttonsControls[i].messageColor = BLANK;
				}
			}

			// Testing Images
			DrawTexture(scheme_arrows01, 0, 0, WHITE);
			DrawTexture(scheme_sign01, 350, -100, WHITE);
		}

		bool FinishControlsScreen()
		{
			return isScreenFinished;
		}
	}
}
