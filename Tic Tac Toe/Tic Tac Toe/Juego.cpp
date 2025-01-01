#include "Juego.hpp"

bool Gato::TexturasListas()
{
	Tx_X = LoadTexture("Media/X.png");
	Tx_O = LoadTexture("Media/O.png");

	if (IsTextureReady(Tx_X) and IsTextureReady(Tx_O))
	{
		Tx_X.width = 180;
		Tx_X.height = 180;
		Tx_O.height = 180;
		Tx_O.width = 180;

		return true;
	}
	else return false;
}

def Gato::ConfigTablero()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CuadXY[i][j].x = ((float)j * 200) + 100;
			CuadXY[i][j].y = ((float)i * 200) + 100;

			CuadEs[i][j] = EMPTY;
		}
	}
	turno = GetRandomValue(1, 2);
}
def Gato::Entrada()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), { CuadXY[i][j].x, CuadXY[i][j].y, 200.0f, 200.0f }) and CuadEs[i][j] == EMPTY)
			{
				DrawRectangle((int)CuadXY[i][j].x + 5, (int)CuadXY[i][j].y + 5, 190.f, 190.0f, { 200, 200, 200, 100 });
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					CuadEs[i][j] = turno;
					if (turno == X) turno = O;
					else turno = X;
				}
			}
		}
	}
}
def Gato::RepresentarTablero()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CuadEs[i][j] == X) DrawTexture(Tx_X, (int)CuadXY[i][j].x, (int)CuadXY[i][j].y, WHITE);
			else if (CuadEs[i][j] == O) DrawTexture(Tx_O, (int)CuadXY[i][j].x, (int)CuadXY[i][j].y, WHITE);
		}
	}
}
def Gato::VerificarH()
{
	for (int i = 0; i < 3; i++)
	{
		if (CuadEs[i][0] != EMPTY)
		{
			if (CuadEs[i][0] == CuadEs[i][1] and CuadEs[i][1] == CuadEs[i][2])
			{
				BeginDrawing();
				ClearBackground(WHITE);

				if (CuadEs[i][0] == X)
				{
					DrawText("X GANA!", 200, 350, 100, BLUE);
					Xcount++;
				}
				else if (CuadEs[i][0] == O)
				{
					DrawText("O GANA!", 200, 350, 100, RED);
					Ocount++;
				}

				EndDrawing();
				std::this_thread::sleep_for(std::chrono::seconds(2));

				ConfigTablero();
			}
		}
	}
}
def Gato::VerificarV()
{
	for (int i = 0; i < 3; i++)
	{
		if (CuadEs[0][i] != EMPTY)
		{
			if (CuadEs[0][i] == CuadEs[1][i] and CuadEs[1][i] == CuadEs[2][i])
			{
				BeginDrawing();
				ClearBackground(WHITE);

				if (CuadEs[0][i] == X)
				{
					DrawText("X GANA!", 200, 350, 100, BLUE);
					Xcount++;
				}
				else if (CuadEs[0][i] == O)
				{
					DrawText("O GANA!", 200, 350, 100, RED);
					Ocount++;
				}
				EndDrawing();

				std::this_thread::sleep_for(std::chrono::seconds(2));
				ConfigTablero();
			}
		}
	}
}
def Gato::VerificarD()
{
	if (CuadEs[0][0] != EMPTY)
	{
		if (CuadEs[0][0] == CuadEs[1][1] and CuadEs[1][1] == CuadEs[2][2])
		{
			BeginDrawing();
			ClearBackground(WHITE);

			if (CuadEs[0][0] == X)
			{
				DrawText("X GANA!", 200, 350, 100, BLUE);
				Xcount++;
			}
			else if (CuadEs[0][0] == O)
			{
				DrawText("O GANA!", 200, 350, 100, RED);
				Ocount++;
			}

			EndDrawing();
			std::this_thread::sleep_for(std::chrono::seconds(2));
			ConfigTablero();
		}
	}

	if (CuadEs[0][2] != EMPTY)
	{

		if (CuadEs[0][2] == CuadEs[1][1] and CuadEs[1][1] == CuadEs[2][0])
		{
			BeginDrawing();
			ClearBackground(WHITE);

			if (CuadEs[1][1] == X)
			{
				DrawText("X GANA!", 200, 350, 100, BLUE);
				Xcount++;
			}
			else if (CuadEs[1][1] == O)
			{
				DrawText("O GANA!", 200, 350, 100, RED);
				Ocount++;
			}

			EndDrawing();
			std::this_thread::sleep_for(std::chrono::seconds(2));
			ConfigTablero();
		}
	}

}
def Gato::LimpiarTablero()
{
	int counter = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (CuadEs[i][j] != EMPTY) counter++;

			if (counter == 9)
			{
				ConfigTablero();
				ClearBackground(WHITE);
			}
		}
	}
}
Gato::Gato()
{
	if (TexturasListas())
	{
		ConfigTablero();

		Xcount = 0;
		Ocount = 0;

		std::unique_ptr<thread> HiloEntrada = std::make_unique<thread>();


		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(WHITE);

			*HiloEntrada = thread(&Gato::Entrada, this);
			HiloEntrada->join();

			/*Informacion*/
			DrawText("Gato", 330, 10, 75.0f, BLACK);

			/*Lineas Verticales*/
			DrawLine(300, 100, 300, 700, GRAY);
			DrawLine(500, 100, 500, 700, GRAY);
			/*Lineas Horizontales*/
			DrawLine(100, 300, 700, 300, GRAY);
			DrawLine(100, 500, 700, 500, GRAY);

			DrawText(TextFormat("X: %i", Xcount), 10, 10, 20, BLUE);
			DrawText(TextFormat("O: %i", Ocount), 10, 30, 20, RED);
			DrawText("R: Reiniciar", 10, 780, 20, BLACK);

			RepresentarTablero();

			VerificarD();
			VerificarH();
			VerificarV();

			LimpiarTablero();

			if (IsKeyPressed(KEY_R))
			{
				ConfigTablero();
				ClearBackground(WHITE);

				Xcount = 0;
				Ocount = 0;
			}

			ClearBackground(WHITE);
			EndDrawing();
		}

		if (HiloEntrada->joinable()) HiloEntrada->join();

		UnloadTexture(Tx_X);
		UnloadTexture(Tx_O);
	}
	else std::cout << "Error al cargar texturas\n";
}