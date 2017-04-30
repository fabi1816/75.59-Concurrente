#include <unistd.h>
#include <sys/wait.h>

#include <memory>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <system_error>

#include "Jugador.h"
#include "Dealer.h"
#include "Turno.h"
#include "TurnoFactory.h"



int main() {
	try {
		std::cout << "Prueba de juego - mkXII" << std::endl;

		int cantJugadores = 2;
		std::cout << "Jugadores = " << cantJugadores << std::endl;

		// Repartir las cartas a los jugadores
		typedef std::stack<int> pila;
		std::vector<pila> cartas = game::Dealer::getPilas(cantJugadores);

		// Crear turnos para los jugadores
		typedef std::shared_ptr<game::Turno> autoTurno;
		std::vector<autoTurno> turnos = game::TurnoFactory::buildTurnos(cantJugadores);

		// Crear un proceso para cada jugador
		std::vector<pid_t> pids;
		for (int i = 0; i < cantJugadores; ++i) {
			pid_t pid = fork();
			if (pid == 0) {
				int prox = (i+1) % cantJugadores;

				game::Jugador j(i, cartas[i], turnos[i], turnos[prox]);

				return j.jugar();
			}

			pids.push_back(pid);
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
		std::cout << "\n** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

