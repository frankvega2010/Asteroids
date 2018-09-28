#include "credits.h"

#include "raylib.h"
#include "Setup/Game.h"

namespace Juego
{
	namespace Credits_Section
	{
		static void CreditosInput()
		{

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
			
			CreditosInput();
		}

		void InitCreditsScreen()
		{
			isScreenFinished = false;
		}

		bool FinishCreditsScreen()
		{
			return isScreenFinished;
		}

		void DrawCredits()
		{

		}
	}
}