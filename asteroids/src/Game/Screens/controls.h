#ifndef CONTROLS_H
#define CONTROLS_H
namespace Juego
{
	enum controlsOptions { // pasar a const?
		buttonGoMenu = 12
	};

	namespace Controls_Section
	{
		void InitControlsScreen();
		void UpdateControlsScreen();
		void DrawControls();
		bool FinishControlsScreen();
	}
}
#endif // CONTROLS_H
