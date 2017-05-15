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
#include "MesaCompartida.h"


int main(int argc, char* argv[]) {
	try {
		auto log = utils::Logger::getLogger();

		std::cout << "== Atrevido! v5 - mkI ==" << std::endl;
		log->write("== Atrevido! ==\n");

		// Uses the argument passed the the program or 4 as the default
		int cantJugadores = (argc > 1) ? atoi(argv[1]) : 4;

		std::cout << "Cantidad de jugadores: " << cantJugadores << std::endl;
		log->write("Cantidad de jugadores: ", cantJugadores);

		// Se crea la mesa donde jugar
		game::MesaCompartida mesa;
		mesa.initMesa(cantJugadores);

		// Crea los semaforos para las fases de los jugadores
		std::vector<int> semIDs;
		semIDs.push_back(utils::createSemaphoreSet('U', 2));
		semIDs.push_back(utils::createSemaphoreSet('N', 2));
		semIDs.push_back(utils::createSemaphoreSet('D', 2));
		semIDs.push_back(utils::createSemaphoreSet('E', 2));
		semIDs.push_back(utils::createSemaphoreSet('R', 2));

		// Repartir las cartas a los jugadores
		std::vector< std::stack<int> > cartas = game::Dealer::getPilas(cantJugadores);

		// Crear un proceso para cada jugador
		for (int i = 0; i < cantJugadores; ++i) {
			pid_t pid = fork();
			if (pid == 0) {
				game::Jugador j(getpid(), cantJugadores, semIDs, "UNDER");

				return j.jugar(cartas[i]);
			}

			log->write("Jugador => ", pid);
		}

		// TODO: Señala al primer jugador que comienze el juego
		std::cout << "\n== Empieza el juego ==" << std::endl;
		log->write("\n== Comienza el juego de Atrevido ==");
		
		// Se esperan que terminen todos los jugadores
		for (int i = 0; i < cantJugadores; ++i) {
			int stat = 0;
			int pid = wait(&stat);
			if (pid == -1) {	// Ocurrió un error inesperado
				throw std::system_error(errno, std::generic_category(), "Wait error");
			}

			if (!WIFEXITED(stat)) {
				log->write("*\n** Error no contemplado");
			}
		}

		// Destruir semaforos
		utils::destroySamaphoreSet(semIDs[0]);
		utils::destroySamaphoreSet(semIDs[1]);
		utils::destroySamaphoreSet(semIDs[2]);
		utils::destroySamaphoreSet(semIDs[3]);
		utils::destroySamaphoreSet(semIDs[4]);

		std::cout << "\n== Fin del juego ==" << std::endl;
		log->write("\n== Fin del juego de Atrevido ==");

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

