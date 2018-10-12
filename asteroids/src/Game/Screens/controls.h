#ifndef CONTROLS_H
#define CONTROLS_H
namespace Juego
{
	enum controlsOptions { // pasar a const?
		buttonGoMenu = 12
	};

	//extern Texture2D controlScheme; // CHECK IF ITS USED

	namespace Controls_Section
	{
		void InitControlsScreen();
		void UpdateControlsScreen();
		void DrawControls();
		bool FinishControlsScreen();
		void DeInitControlsResources();
	}
}
#endif // CONTROLS_H
