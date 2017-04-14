#include <string>
#include <iostream>

#include "Jugador.h"
#include "Turno.h"



int main() {
	std::cout << "Primera prueba de semaforos" << std::endl;

	std::vector<int> cartasJ1 = { 1, 2, 3, 4 };
	std::vector<int> cartasJ2 = { 1, 2, 3, 4 };
	std::vector< std::vector<int> > cartas = { cartasJ1, cartasJ2 };

	player::Turno t1("/TurnoJugador1", "/TurnoJugador2");
	player::Turno t2("/TurnoJugador2", "/TurnoJugador1");
	std::vector<player::Turno> turnos = { t1, t2 };

	std::cout << "Se crearon los semaforos" << std::endl;

	for (int i = 0; i < 2; ++i) {
		pid_t pid = fork();
		if (pid == 0) {
			player::Jugador j(cartas[i], turnos[i]);
			return j.Jugar();
		}
	}

	for (int i = 0; i < 2; ++i) {
		wait();
	}

	std::cout << "Se crearon los jugadores" << std::endl;

	return 0;
}
