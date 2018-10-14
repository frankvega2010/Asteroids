#include "controls.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens\gameplay.h"
#include "Setup/Asteroid.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{
	static const int maxButtonsControls = 2;

	static Buttons buttonsControls[maxButtonsControls];
	static int buttonSelect = 0;
	static int buttonDistance_Controls = 0;
	static bool moreControls = false;

	Image controlSchemeImage;
	Texture2D controlScheme;

	namespace Controls_Section
	{
		static void createControlsButtons()
		{
			for (int i = 0; i < maxButtonsControls; i++)
			{
				buttonsControls[i].position.x = (float)screenWidth / 90.0f;
				buttonsControls[i].position.y = (float)screenHeight / 1.4f + buttonDistance_Controls;
				buttonsControls[i].width = (float)screenWidth / 5.0f;
				buttonsControls[i].height = (float)screenHeight / 12.0f;
				buttonsControls[i].selected = false;
				buttonsControls[i].defaultColor = RED;
				buttonsControls[i].messageColor = BLANK;
				buttonDistance_Controls = buttonDistance_Controls + 100;
			}
		}

		void InitControlsScreen()
		{
			createControlsButtons();

			controlSchemeImage = LoadImage("res/textures/controlscheme01.png");
			ImageResize(&controlSchemeImage, screenWidth, screenHeight);
			controlScheme = LoadTextureFromImage(controlSchemeImage);
			UnloadImage(controlSchemeImage);

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
						moreControls =! moreControls;
						break;
					case 1:
						buttonOption = buttonGoMenu;
						isScreenFinished = true;
						break;
					}
					buttonsControls[i].selected = false;
				}
			}
		}

		void UpdateControlsScreen()
		{
			#ifdef AUDIO
			UpdateMusicStream(song_alert);
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
			DrawBackground();
			AsteroidDraw();

			for (int i = 0; i < maxButtonsControls; i++)
			{
				DrawRectangleLines(buttonsControls[i].position.x, buttonsControls[i].position.y, buttonsControls[i].width, buttonsControls[i].height, buttonsControls[i].defaultColor);

				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttonsControls[i].position.x, buttonsControls[i].position.y, buttonsControls[i].width, buttonsControls[i].height }) || buttonSelect == i)
				{
					buttonsControls[i].messageColor = WHITE;

					switch (i)
					{
					case 1:
						DrawText("Click or Enter ", buttonsControls[i].position.x + 300, buttonsControls[i].position.y, defaultFontSize / 2, buttonsControls[i].messageColor);
						DrawText("to go back!", buttonsControls[i].position.x + 300, buttonsControls[i].position.y + 50, defaultFontSize / 2, buttonsControls[i].messageColor);
						break;
					}
				}
				else
				{
					buttonsControls[i].messageColor = BLANK;
				}
			}

			//More Controls Text
			if (moreControls)
			{
				DrawText(FormatText("How to Play"), screenWidth / 18, 20, defaultFontSize, WHITE);
				DrawText(FormatText("Destroy all asteroids in the least amount of time!"), screenWidth / 18, screenHeight / 8, defaultFontSize / 1.8, WHITE);
				DrawText(FormatText("Powerups"), screenWidth / 18, screenHeight / 4.5, defaultFontSize, WHITE);
				DrawText(FormatText("There are 2 powerups which will help you get a highscore"), screenWidth / 18, screenHeight / 3, defaultFontSize / 1.8, WHITE);
				DrawText(FormatText("Invincibility Powerup"), screenWidth / 18, screenHeight / 2.5, defaultFontSize / 1.8, RED);
				DrawText(FormatText("Makes you invincible to any asteroid for 5 seconds."), screenWidth / 18, screenHeight / 2.2, defaultFontSize / 1.8, RED);
				DrawText(FormatText("Max Rapid Fire Powerup"), screenWidth / 18, screenHeight / 1.9, defaultFontSize / 1.8, GOLD);
				DrawText(FormatText("You will be able to shoot more quickly for 5 seconds."), screenWidth / 18, screenHeight / 1.7, defaultFontSize / 1.8, GOLD);
			}

			DrawText(FormatText("MORE"), buttonsControls[0].position.x + 50, buttonsControls[0].position.y + 5, defaultFontSize, buttonsControls[0].defaultColor);
			DrawText(FormatText("MENU"), buttonsControls[1].position.x + 50, buttonsControls[1].position.y + 5, defaultFontSize, buttonsControls[1].defaultColor);

			// Testing Images
			backgroundGameSource = { 0.0f,0.0f, (float)screenWidth,(float)screenHeight };
			backgroundGameDestination = { 0,0, (float)screenWidth,(float)screenHeight };
			backgroundGameOrigin = { 0,0 };

			if (!moreControls)
			{
				DrawTexturePro(controlScheme, backgroundGameSource, backgroundGameDestination, backgroundGameOrigin, 0, WHITE);
			}
			
		}

		bool FinishControlsScreen()
		{
			return isScreenFinished;
		}

		void DeInitControlsResources()
		{
			UnloadTexture(controlScheme);
			buttonDistance_Controls = 0;
		}
	}
}
