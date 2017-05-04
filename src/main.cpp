#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <memory>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <system_error>

#include "Logger.h"

#include "Jugador.h"
#include "Dealer.h"
#include "Turno.h"
#include "Saludador.h"
#include "SemaforoFactory.h"

#include "VictoryHandler.h"
#include "CardCheckHandler.h"



int main() {
	try {
		std::cout << "Atrevido! v3 - mkII" << std::endl;

		auto log = utils::Logger::getLogger();

		int cantJugadores = 2;
		std::cout << "Cantidad de jugadores: " << cantJugadores << std::endl;
		log->write(cantJugadores, "Es la cantidad de jugadores\n");

		// Repartir las cartas a los jugadores
		std::vector< std::stack<int> > cartas = game::Dealer::getPilas(cantJugadores);

		// Crear turnos para los jugadores
		auto turnos = game::SemaforoFactory::buildTurnos(cantJugadores);

		// El saludador de los jugadores
		std::shared_ptr<game::Saludador> saludador = game::SemaforoFactory::buildSaludador(cantJugadores);

		// Crear un proceso para cada jugador
		for (int i = 0; i < cantJugadores; ++i) {
			pid_t pid = fork();
			if (pid == 0) {
				int prox = (i+1) % cantJugadores;

				game::Jugador j(getpid(), turnos[i], turnos[prox], saludador);
				j.setCartas(cartas[i]);

				return j.jugar();
			}
		}

		// Ignoro las señales de chequeo de cartas/victorias
		signal(game::CardCheckHandler::SIG_CARTA_JUGADA, SIG_IGN);
		signal(game::VictoryHandler::SIG_VICTORIA, SIG_IGN);

		// Señala al primer jugador que comienze el juego
		std::cout << "Empieza el juego" << std::endl;
		log->write("== Comienza el juego de Atrevido ==");
		turnos[0]->signal_v();
		
		// Se esperan que terminen todos los jugadores
		for (int i = 0; i < cantJugadores; ++i) {
			int stat = 0;
			int pid = wait(&stat);
			if (pid == -1) {
				throw std::system_error(errno, std::generic_category(), "Wait error");
			}

			// Si un jugador terminó con status 0 fue el ganador
			if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0) {
				std::cout << "Ganó el proceso: " << pid << std::endl;
				log->write("Tenemos un ganador");
				log->write(pid, "Es el PID del ganador");
			}
		}

		// Destruir semaforos
		game::SemaforoFactory::destroyTurnos(turnos);
		game::SemaforoFactory::destroySaludador(saludador);

		std::cout << "Fin del juego" << std::endl;
		log->write("== Fin del juego de Atrevido ==");

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "\n** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

