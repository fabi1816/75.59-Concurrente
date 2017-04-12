#include <string>
#include <iostream>

#include "Jugador.h"
#include "Turno.h"

using namespace player;


int main() {
	std::cout << "Primera prueba de semaforos" << std::endl;

	std::vector<int> cartasJ1 = { 1, 2, 3, 4 };
	std::vector<int> cartasJ2 = { 1, 2, 3, 4 };

	Turno t1("/TurnoJugador1", "/TurnoJugador2");
	Turno t2("/TurnoJugador2", "/TurnoJugador1");
	std::cout << "Se crearon los semaforos" << std::endl;

	Jugador j1(cartasJ1, t1);
	Jugador j2(cartasJ2, t2);
	std::cout << "Se crearon los jugadores" << std::endl;

	return 0;
}
