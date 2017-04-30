#include <unistd.h>
#include <signal.h>
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
#include "CardCheckHandler.h"



int main() {
	try {
		std::cout << "Prueba de juego - mkXVI" << std::endl;

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

		// Ignoro las señales de chequeo de cartas
		signal(game::CardCheckHandler::SIG_CARTA_JUGADA, SIG_IGN);

		// Señala al primer jugador que comienze el juego
		std::cout << "Empieza el juego" << std::endl;
		turnos[0]->signal_v();
		
		// Se esperan que terminen todos los jugadores
		std::cout << "Espero por los jugadores" << std::endl;
		for (int i = 0; i < cantJugadores; ++i) {
			int stat = 0;
			int res = wait(&stat);
			if (res == -1 && errno != EINTR) {
				throw std::system_error(errno, std::generic_category(), "Wait con error");

			} else if(res == -1 && errno == EINTR) {
				// TODO: Bloquear las señales en el main o ver alguna forma de
				// pasar los pids de todos los jugadores a todos los jugadores
				std::cout << "El Main fue interrumpido por una señal" << std::endl;
				--i;
			}
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

