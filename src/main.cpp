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
#include "Disparador.h"
#include "MesaCompartida.h"
#include "SemaforoFactory.h"

#include "VictoryHandler.h"
#include "CardCheckHandler.h"



int main(int argc, char* argv[]) {
	try {
		auto log = utils::Logger::getLogger();

		std::cout << "== Atrevido! v4 - mkXI ==" << std::endl;
		log->write("== Atrevido! ==\n");

		// Uses the argument passed the the program or 4 as the default
		int cantJugadores = (argc > 1) ? atoi(argv[1]) : 4;

		std::cout << "Cantidad de jugadores: " << cantJugadores << std::endl;
		log->write("Cantidad de jugadores: ", cantJugadores);

		// Se crea la mesa donde jugar
		game::MesaCompartida mesa;
		mesa.initMesa(cantJugadores);

		// Repartir las cartas a los jugadores
		std::vector< std::stack<int> > cartas = game::Dealer::getPilas(cantJugadores);

		// Crear turnos para los jugadores
		auto turnos = game::SemaforoFactory::buildTurnos(cantJugadores);

		// El saludador de los jugadores
		std::shared_ptr<game::Saludador> saludador = game::SemaforoFactory::buildSaludador(cantJugadores);

		// Avisa cuando esta listo el jugador
		game::Disparador trigger = game::SemaforoFactory::buildDisparador(cantJugadores);

		// Crear un proceso para cada jugador
		for (int i = 0; i < cantJugadores; ++i) {
			pid_t pid = fork();
			if (pid == 0) {
				int prox = (i+1) % cantJugadores;

				game::Jugador j(turnos[i], turnos[prox], saludador);
				j.setCartas(cartas[i]);

				return j.jugar(trigger);
			}

			log->write("Jugador => ", pid);
		}

		// Ignoro las señales de chequeo de cartas/victorias
		signal(game::CardCheckHandler::SIG_CARTA_JUGADA, SIG_IGN);
		signal(game::VictoryHandler::SIG_VICTORIA, SIG_IGN);

		// Se espera a que todos los jugadores esten listos
		trigger.esperarATodos();

		// Señala al primer jugador que comienze el juego
		std::cout << "\n== Empieza el juego ==" << std::endl;
		log->write("\n== Comienza el juego de Atrevido ==");
		turnos[0]->signal_v();
		
		// Se esperan que terminen todos los jugadores
		for (int i = 0; i < cantJugadores; ++i) {
			int stat = 0;
			int pid = wait(&stat);

			std::string msg = utils::waitHandler(pid, stat, game::CardCheckHandler::SIG_CARTA_JUGADA);
			std::cout << msg << std::endl;
			log->write(msg);
		}

		// Destruir semaforos
		game::SemaforoFactory::destroyDisparador(trigger);
		game::SemaforoFactory::destroySaludador(saludador);
		game::SemaforoFactory::destroyTurnos(turnos);

		std::cout << "\n== Fin del juego ==" << std::endl;
		log->write("\n== Fin del juego de Atrevido ==");

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

