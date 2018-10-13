#include "Player.h"

#include <cmath>
#include "Setup\Game.h"
#include "Setup\Asteroid.h"
#include "Setup\PlayerShoot.h"
#include "Screens\gameplay.h"

namespace Juego
{
	static int defaultRotationSpeed = 280;
	static int defaultAcceleration = 1.0f;
	static int defaultDeacceleration = 0.01f;
	static int defaultBreakSpeed = 2.0f;
	rocketShip player;
	Circle collisionCircle;
	static const int playerBaseSize = 25;
	float shipHeight = (playerBaseSize / 2) / tanf(20 * DEG2RAD);
	float shipHeightv2 = (playerBaseSize / 2) / tanf(38 * DEG2RAD);

	static Rectangle shipSource = { 0.0f,0.0f, 50,50 };
	static Rectangle shipMovingSource = { 0.0f,0.0f, 50,58 };
	static Rectangle shipDestination;
	static Rectangle shipMovingDestination;
	static Vector2 shipOrigin = { 25,48 };//48 sweet spot
	
	static Vector2 rotationDirection;
	static float rotationAngle = 0.0f;
	static Vector2 normalizedDirection = {0,0};
	static Vector2 playerNewPosition = { 0,0 };

	//Vector2 v1 = { (float)screenWidth / 2 + sinf(player.rotation)*(shipHeight), (float)screenHeight / 2 - cosf(player.rotation)*(shipHeight) };
	//Vector2 v2 = { (float)screenWidth / 2 - cosf(player.rotation)*(playerBaseSize / 2), (float)screenHeight / 2 - sinf(player.rotation)*(playerBaseSize / 2) };
	//Vector2 v3 = { (float)screenWidth / 2 + cosf(player.rotation)*(playerBaseSize / 2), (float)screenHeight / 2 + sinf(player.rotation)*(playerBaseSize / 2) };

	namespace Gameplay_Section
	{
		void createPlayer()
		{
			//player.position = { (float)screenWidth / 2, (float)screenHeight / 2 - shipHeight / 2 };
			player.position = { (float)screenWidth / 2, (float)screenHeight / 2 };
			player.score = 0;
			player.acceleration = {10,10};
			player.rotation = 0.0f;
			player.defaultSpeed = 300.0f;
			player.isAlive = true;
			player.inputActive = false;
			player.textureTint = WHITE;

		}

		void createCollisionCircle()
		{
			collisionCircle.position.x = player.position.x;
			collisionCircle.position.y = player.position.y;
			collisionCircle.radius = 15;
			collisionCircle.speed = { 0,0 };
			collisionCircle.active = true;
		}
		
		void playerInput()
		{
			ShootInput();

			#ifdef AUDIO
			StopMusicStream(ship_rocket01);
			#endif

			//Player logic: acceleration
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
			{
				#ifdef AUDIO
				PlayMusicStream(ship_rocket01);
				#endif
				
				player.inputActive = true;

				normalizedDirection.x = rotationDirection.x / sqrt(pow(rotationDirection.x,2.0) + pow(rotationDirection.y, 2.0));
				normalizedDirection.y = rotationDirection.y / sqrt(pow(rotationDirection.x, 2.0) + pow(rotationDirection.y, 2.0));

				player.acceleration.x += normalizedDirection.x * 250 * GetFrameTime();
				player.acceleration.y += normalizedDirection.y * 250 * GetFrameTime();
			}
		}

		void playerUpdate()
		{

			rotationDirection.x = (float)mouse.position.x - (float)player.position.x;
			rotationDirection.y = (float)mouse.position.y - (float)player.position.y;

			rotationAngle = atan2(rotationDirection.y, rotationDirection.x) + 1.57f;

			player.rotation = rotationAngle;

			// Player logic: movement

			player.position.x = player.position.x + player.acceleration.x * GetFrameTime();
			player.position.y = player.position.y + player.acceleration.y * GetFrameTime();

		}

		void collisionCircleUpdate()
		{
			// Players Collision Circle logic: movement
			collisionCircle.position.x = player.position.x + sinf(player.rotation)*(shipHeightv2);
			collisionCircle.position.y = player.position.y - cosf(player.rotation)*(shipHeightv2);
		}

		void playerDraw()
		{
			shipDestination = { player.position.x,player.position.y, 50,50 };
			shipMovingDestination = { player.position.x,player.position.y, 50,58 };
			
			Vector2 v1 = { player.position.x + sinf(player.rotation)*(shipHeight), player.position.y - cosf(player.rotation)*(shipHeight) };
			Vector2 v2 = { player.position.x - cosf(player.rotation)*(playerBaseSize / 2), player.position.y - sinf(player.rotation)*(playerBaseSize / 2) };
			Vector2 v3 = { player.position.x + cosf(player.rotation)*(playerBaseSize / 2), player.position.y + sinf(player.rotation)*(playerBaseSize / 2) };

			DrawTriangle(v1, v2, v3, MAROON);
			if (player.inputActive)
			{
				DrawTexturePro(shipMoving, shipMovingSource, shipMovingDestination, shipOrigin, rotationAngle*RAD2DEG, player.textureTint);
			}
			else
			{
				DrawTexturePro(ship, shipSource, shipDestination, shipOrigin, rotationAngle*RAD2DEG, player.textureTint);
			}
			
			
		}

		#ifdef TESTING
				void collisionCircleDraw() // only in DEBUG mode
				{
					DrawCircleV({ player.position.x + sinf(player.rotation)*(shipHeightv2), player.position.y - cosf(player.rotation)*(shipHeightv2) }, collisionCircle.radius, { 100, 0, 0, 200 });
					DrawLineEx(player.position, mouse.position, 1, YELLOW);
				}
		#endif
		#ifdef RELEASE
				void collisionCircleDraw() // only in RELEASE mode
				{
					DrawCircleV({ player.position.x + sinf(player.rotation)*(shipHeightv2), player.position.y - cosf(player.rotation)*(shipHeightv2) }, collisionCircle.radius, { 0, 0, 0, 0 });
				}
		#endif
	}
}