#include <iostream>
#include <raylib.h>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>

#define EMPTY 0
#define X 1
#define O 2

typedef void def;
typedef unsigned short int uint;

using std::thread;

class Gato
{
private:
	/*Almacena las posiciones XY donde se localiza el cuadrado*/
	Vector2 CuadXY[3][3];
	uint CuadEs[3][3];

	/*Texturas*/
	Texture2D Tx_X;
	Texture2D Tx_O;
	bool TexturasListas();

	def ConfigTablero();
	def Entrada();
	def RepresentarTablero();

	/*Verificar ganador Horizontal - Diagonal - Diagonal*/
	def VerificarH();
	def VerificarV();
	def VerificarD();

	def LimpiarTablero();

	uint turno;
	uint Xcount;
	uint Ocount;
public:
	Gato();
};