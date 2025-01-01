#include "Juego.hpp"

int main()
{

	InitWindow(800, 800, "Gato");
	if (IsWindowReady())
	{
		SetTargetFPS(30);
		SetExitKey(KEY_E);

		std::unique_ptr<Gato> Juego = std::make_unique<Gato>();
	}
	else return -1;

	CloseWindow();

	std::cin.get();
	return 0;
}