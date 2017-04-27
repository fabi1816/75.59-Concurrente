#include <unistd.h>
#include <sys/wait.h>

#include <memory>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <cerrno>

#include "Jugador.h"
#include "Turno.h"
#include "TurnoFactory.h"



int main() {
	try {
		std::cout << "Prueba de juego - mkIIX" << std::endl;

		unsigned int cantJugadores = 4;
		std::cout << "Jugadores = " << cantJugadores << std::endl;

		// TODO: Autogenerar las cartas de los jugadores
		std::stack<int> cartasJ0 = { 1, 2 };
		std::stack<int> cartasJ1 = { 3, 4 };
		std::stack<int> cartasJ2 = { 5, 6 };
		std::stack<int> cartasJ3 = { 7, 8 };

		std::vector< std::stack<int> > cartas = { 1, 2 };

		// Crear semaforos
		typedef std::shared_ptr<player::Turno> autoTurno;
		std::vector<autoTurno> turnos = game::TurnoFactory::buildTurnos(cantJugadores);

		// Se crean los jugadores en sus propios procesos
		for (int i = 0; i < cantJugadores; ++i) {
			pid_t pid = fork();
			if (pid == 0) {
				int prox = (i+1) % cantJugadores;

				game::Jugador j(i, cartasJ1, turnos[i], turnos[prox]);

				return j.jugar();
			}
		}

		// Señala al primer jugador que comienze el juego
		std::cout << "Empieza el juego" << std::endl;
		turnos[0]->signal_v();

		// Se esperan que terminen todos los jugadores
		std::cout << "Espero por los jugadores" << std::endl;
		for (int i = 0; i < cantJugadores; ++i) {
			int stat = 0;
			wait(&stat);
		}

		// Destruir semaforos
		game::TurnoFactory::destroyTurnos(turnos);

		std::cout << "Fin del juego" << std::endl;

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

