#include "settings.h"

#include "raylib.h"
#include "Setup/Game.h"
#include "Screens/gameplay.h"
#include "Setup/Asteroid.h"
#include "Screens\controls.h"
#include "Setup\Player.h"

using namespace Juego;
using namespace Gameplay_Section;

namespace Juego
{

	//static const int maxButtons = 1;
	static const int maxButtons = 8;
	static const int maxButtonsRight = 4;

	//static Buttons buttons[maxButtons];
	static Buttons buttonsSettings[maxButtons];
	static Buttons buttonsSettingsRight[maxButtonsRight];
	static int buttonSelect = 0;
	//static int buttonSelectLeft = 0;
	static int buttonDistanceSettingsLeft = 0;

	bool resolutionSmall = false;
	bool resolutionNormal = true;
	bool resolutionBig = false;

	static Image asteroidImage;

	namespace Settings_Section
	{
		static void createSettingsButtons()
		{
			//for (int i = 0; i < maxButtons; i++)
			//{
			//	buttons[i].position.x = (float)screenWidth / 90.0f;
			//	buttons[i].position.y = (float)screenHeight / 1.1f; //+ buttonDistance_Controls;
			//	buttons[i].width = (float)screenWidth / 5.0f;
			//	buttons[i].height = (float)screenHeight / 12.0f;
			//	buttons[i].selected = false;
			//	buttons[i].defaultColor = RED;
			//	buttons[i].messageColor = BLANK;
			//}

			for (int i = 0; i < maxButtons; i++)
			{
				buttonsSettings[i].position.x = (float)screenWidth / 90.0f;
				buttonsSettings[i].position.y = (float)screenHeight / 10.0f + buttonDistanceSettingsLeft;
				if (resolutionNormal)
				{
					buttonsSettings[i].width = (float)screenWidth / 4.0f;
					buttonsSettings[i].height = (float)screenHeight / 12.0f;
				}
				else if (resolutionSmall)
				{
					buttonsSettings[i].width = (float)screenWidth / 4.0f;
					buttonsSettings[i].height = (float)screenHeight / 14.0f;//18.0f default
				}
				buttonsSettings[i].selected = false;
				buttonsSettings[i].defaultColor = RED;
				buttonsSettings[i].messageColor = BLANK;

				if (i == 7)
				{
					buttonsSettings[i].position.y = (float)screenHeight / 1.1f;
					buttonsSettings[i].width = (float)screenWidth / 5.0f;
				}

				
				if (resolutionNormal && !(resolutionBig)) buttonDistanceSettingsLeft = buttonDistanceSettingsLeft + 75;
				else if (resolutionSmall) buttonDistanceSettingsLeft = buttonDistanceSettingsLeft + 50;
				else if (resolutionBig && resolutionNormal) buttonDistanceSettingsLeft = buttonDistanceSettingsLeft + 100;
				
				
			}
		}

		static void ChangeResolutionSmall(int screenW,int screenH)
		{
			resolutionSmall = true;
			resolutionNormal = false;
			resolutionBig = false;
			/*#ifdef AUDIO
						PlaySound(pong_select_option1);
			#endif*/
			screenWidth = screenW;
			screenHeight = screenH;
			resolutionBackground();
			defaultFontSize = 60 / 1.6;
			SetWindowSize(screenWidth, screenHeight);
			createSettingsButtons();
			checkAsteroidSprite();
			createAsteroid();
		}

		static void ChangeResolutionNormal(int screenW, int screenH)
		{
			resolutionSmall = false;
			resolutionNormal = true;
			resolutionBig = false;
			/*#ifdef AUDIO
			PlaySound(pong_select_option1);
			#endif*/
			screenWidth = screenW;
			screenHeight = screenH;
			resolutionBackground();
			defaultFontSize = 60;
			SetWindowSize(screenWidth, screenHeight);
			createSettingsButtons();
			checkAsteroidSprite();
			createAsteroid();
		}

		static void ChangeResolutionBig(int screenW, int screenH)
		{
			resolutionSmall = false;
			resolutionNormal = true;
			resolutionBig = true;
			/*#ifdef AUDIO
			PlaySound(pong_select_option1);
			#endif*/
			screenWidth = screenW;
			screenHeight = screenH;
			resolutionBackground();
			defaultFontSize = 60;
			SetWindowSize(screenWidth, screenHeight);
			createSettingsButtons();
			checkAsteroidSprite();
			createAsteroid();
		}

		void InitSettingsScreen()
		{
			checkAsteroidSprite();
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
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttonsSettings[i].selected || IsKeyPressed(KEY_ENTER) && buttonsSettings[i].selected)
				{
					switch (i)
					{
					case 0:
						ChangeResolutionBig(1920, 1080);
						break;
					case 1:
						ChangeResolutionBig(1680, 1050);
						break;
					case 2:
						ChangeResolutionNormal(1600, 900);
						break;
					case 3:
						ChangeResolutionNormal(1440, 900);
						break;
					case 4:
						ChangeResolutionNormal(1300, 800);
						break;
					case 5:
						ChangeResolutionNormal(1024, 768);
						break;
					case 6:
						ChangeResolutionSmall(800, 600);
						break;
					case 7:
						buttonOption = buttonGoMenu;
						isScreenFinished = true;
						break;
					}
					buttonsSettings[i].selected = false;
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
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttonsSettings[i].position.x, buttonsSettings[i].position.y, buttonsSettings[i].width, buttonsSettings[i].height }) || buttonSelect == i)
				{
					buttonSelect = i;
					buttonsSettings[i].defaultColor = WHITE;
					buttonsSettings[i].selected = true;
				}
				else
				{
					buttonsSettings[i].defaultColor = RED;
					buttonsSettings[i].selected = false;
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
				DrawRectangleLines(buttonsSettings[i].position.x, buttonsSettings[i].position.y, buttonsSettings[i].width, buttonsSettings[i].height, buttonsSettings[i].defaultColor);

				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttonsSettings[i].position.x, buttonsSettings[i].position.y, buttonsSettings[i].width, buttonsSettings[i].height }) || buttonSelect == i)
				{
					buttonsSettings[i].messageColor = WHITE;

					switch (i)
					{
					case 7:
						DrawText("Click or Enter to go back!", buttonsSettings[i].position.x + (screenWidth / 4.5), buttonsSettings[i].position.y, defaultFontSize / 2, buttonsSettings[i].messageColor);
						DrawText("", buttonsSettings[i].position.x + (screenWidth / 4.5), buttonsSettings[i].position.y + 50, defaultFontSize / 2, buttonsSettings[i].messageColor);
						break;
					}
				}
				else
				{
					buttonsSettings[i].messageColor = BLANK;
				}
			}

			DrawText(FormatText("Placeholder for Settings Screen"), (float)screenWidth / 2.5f, screenHeight / 3.3, defaultFontSize / 1.5, WHITE);


			DrawText(FormatText("1920x1080"), buttonsSettings[0].position.x + 10, buttonsSettings[0].position.y + 5, defaultFontSize, buttonsSettings[0].defaultColor);
			DrawText(FormatText("1680x1050"), buttonsSettings[1].position.x + 10, buttonsSettings[1].position.y + 5, defaultFontSize, buttonsSettings[1].defaultColor);
			DrawText(FormatText("1600x900"), buttonsSettings[2].position.x + 10, buttonsSettings[2].position.y + 5, defaultFontSize, buttonsSettings[2].defaultColor);
			DrawText(FormatText("1440x900"), buttonsSettings[3].position.x + 10, buttonsSettings[3].position.y + 5, defaultFontSize, buttonsSettings[3].defaultColor);
			DrawText(FormatText("1300x800"), buttonsSettings[4].position.x + 10, buttonsSettings[4].position.y + 5, defaultFontSize, buttonsSettings[4].defaultColor);
			DrawText(FormatText("1024x768"), buttonsSettings[5].position.x + 10, buttonsSettings[5].position.y + 5, defaultFontSize, buttonsSettings[5].defaultColor);
			DrawText(FormatText("800x600"), buttonsSettings[6].position.x + 10, buttonsSettings[6].position.y + 5, defaultFontSize, buttonsSettings[6].defaultColor);

			DrawText(FormatText("MENU"), buttonsSettings[7].position.x + 25, buttonsSettings[7].position.y + 5, defaultFontSize, buttonsSettings[7].defaultColor);
		}

		bool FinishSettingsScreen()
		{
			buttonDistanceSettingsLeft = 0;
			return isScreenFinished;
		}

	}
}