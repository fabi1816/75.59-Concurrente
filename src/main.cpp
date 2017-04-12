#include <string>
#include <iostream>

#include "Jugador.h"
#include "Turno.h"



int main() {
	std::cout << "Primera prueba de semaforos" << std::endl;

	std::vector<int> cartasJ1 = { 1, 2, 3, 4 };
	std::vector<int> cartasJ2 = { 1, 2, 3, 4 };

	player::Turno t1("/TurnoJugador1", "/TurnoJugador2");
	player::Turno t2("/TurnoJugador2", "/TurnoJugador1");
	std::cout << "Se crearon los semaforos" << std::endl;

	player::Jugador j1(cartasJ1, t1);
	player::Jugador j2(cartasJ2, t2);
	std::cout << "Se crearon los jugadores" << std::endl;

	return 0;
}
