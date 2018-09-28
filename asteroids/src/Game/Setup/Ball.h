#ifndef BALL_H
#define BALL_H

#include "raylib.h"

namespace Juego
{
	namespace Gameplay_Section
	{
		void createBall();
		void ballUpdate();
		void ballDraw();
		void ballResetSpeed();
	}
}
#endif // BALL_H
