#include "credits.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens\gameplay.h"
#include "Setup/Asteroid.h"
#include "Screens\controls.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtonsControls = 1;

	static Buttons buttonsControls[maxButtonsControls];
	static int buttonSelect = 0;

	namespace Credits_Section
	{
		static void createCreditsButtons()
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
			}
		}

		void InitCreditsScreen()
		{
			createCreditsButtons();
			isScreenFinished = false;
		}

		static void CreditosInput()
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

			/*if (IsKeyPressed(KEY_ONE)) // Input Code
			{
				#ifdef AUDIO
								// Audio Code
				#endif
			}*/
		}

		void UpdateCreditsScreen()
		{
			#ifdef AUDIO
								// Audio Code
			#endif
			
			
			AsteroidUpdate();
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };

			CreditosInput();
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
		
		void DrawCredits()
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
						DrawText("Click or Enter to go back!", buttonsControls[i].position.x + 300, buttonsControls[i].position.y, defaultFontSize / 2, buttonsControls[i].messageColor);
						DrawText("", buttonsControls[i].position.x + 300, buttonsControls[i].position.y + 50, defaultFontSize / 2, buttonsControls[i].messageColor);
						break;
					}
				}
				else
				{
					buttonsControls[i].messageColor = BLANK;
				}
			}
			DrawText(FormatText("Simple! Asteroids"), (float)screenWidth / 2.5f * 0.63f, screenHeight / 10, defaultFontSize + 20, WHITE);
			DrawText(FormatText("Beta Build 0.1.5"), (float)screenWidth / 2.5f * 0.63f, screenHeight / 5, defaultFontSize / 2, WHITE);

			DrawText(FormatText("Game made by"), (float)screenWidth / 2.5f, screenHeight / 3.3, defaultFontSize / 1.5, WHITE);
			DrawText(FormatText("Franco Vega aka frankvega"), (float)screenWidth / 3.3f, screenHeight / 2.8, defaultFontSize / 1.5, WHITE);

			DrawText(FormatText("Tools Used"), (float)screenWidth / 2.5f, screenHeight / 2.2, defaultFontSize / 1.5, WHITE);
			DrawText(FormatText("Raylib"), (float)screenWidth / 2.2f, screenHeight / 2.0, defaultFontSize / 1.5, WHITE);

			DrawText(FormatText("MENU"), buttonsControls[0].position.x + 50, buttonsControls[0].position.y + 5, defaultFontSize, buttonsControls[0].defaultColor);
		}

		bool FinishCreditsScreen()
		{
			return isScreenFinished;
		}

	}
}