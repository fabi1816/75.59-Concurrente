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
#include "Dealer.h"

#include "Arbitro.h"
#include "Jugador.h"
#include "Disparador.h"
#include "MesaCompartida.h"
#include "MarcadorCompartido.h"


int main(int argc, char* argv[]) {
	try {
		auto log = utils::Logger::getLogger();

		std::cout << "== Atrevido! v5 - mkIV ==" << std::endl;
		log->write("== Atrevido! ==\n");

		// Uses the argument passed the the program or 4 as the default
		int cantJugadores = (argc > 1) ? atoi(argv[1]) : 4;

		std::cout << "Cantidad de jugadores: " << cantJugadores << std::endl;
		log->write("Cantidad de jugadores: " + std::to_string(cantJugadores));

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

		// Crear el canal que usa el arbitro
		const std::string nombreCanal = "arbitro.fifo";
		utils::Fifo::createFifoNode(nombreCanal);

		// Repartir las cartas a los jugadores
		std::vector< std::stack<int> > cartas = game::Dealer::getPilas(cantJugadores);
		std::vector<int> pids;

		// Se crea un semaforo para señalar el inicio del juego
		game::Disparador trigger = game::Disparador::build(cantJugadores +1, 'Z');

		//------------------------- Procesos --------------------------

		// Crear un proceso para cada jugador
		for (int i = 0; i < cantJugadores; ++i) {
			pid_t pid = fork();
			if (pid == 0) {
				game::Jugador j(getpid(), cantJugadores, semIDs, "UNDER");

				log->write("Jugador => " + std::to_string(getpid()) + " listo!");
				trigger.listo();

				return j.jugar(cartas[i], nombreCanal);
			}

			pids.push_back(pid);
		}

		// Crea un proceso para el arbitro 
		if (0 == fork()) {
			game::Arbitro arb(nombreCanal);

			log->write("Arbitro => " + std::to_string(getpid()) + " listo!");
			trigger.listo();

			return arb.espiarJuego();
		}

		//-------------------------------------------------------------

		// Ahora que tenemos los pids de todos los jugadores podemos inicializar el marcador
		game::MarcadorCompartido marcador;
		marcador.init(cantJugadores, pids);

		// Cuando todos los jugadores esten listos empieza el juego
		trigger.esperarATodos();
		std::cout << "\n== Empieza el juego ==" << std::endl;
		log->write("\n== Comienza el juego de Atrevido ==");
		
		// Se esperan que terminen todos los jugadores y el arbitro
		for (int i = 0; i < cantJugadores +1; ++i) {
			int stat = 0;
			int pid = wait(&stat);
			if (pid == -1) {	// Ocurrió un error inesperado
				throw std::system_error(errno, std::generic_category(), "Wait error");
			}

			if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0) {
				std::cout << "\nGANADOR: " << pid << "\n" << std::endl;
				log->write("\nGANADOR: " + std::to_string(pid) + "\n");

			} else if (WIFEXITED(stat) && WEXITSTATUS(stat) == 1) {
				log->write("Perdedor: " + std::to_string(pid));

			} else if (WIFEXITED(stat) && WEXITSTATUS(stat) == -1) {
				log->write("El arbitro finalizó su trabajo");

			} else if (!WIFEXITED(stat)) {
				log->write("*\n** Error no contemplado");
			}
		}

		// Destruir semaforos
		utils::destroySamaphoreSet(semIDs[0]);
		utils::destroySamaphoreSet(semIDs[1]);
		utils::destroySamaphoreSet(semIDs[2]);
		utils::destroySamaphoreSet(semIDs[3]);
		utils::destroySamaphoreSet(semIDs[4]);
		game::Disparador::destroy(trigger);

		// Destruir el canal que usa el arbitro
		utils::Fifo::destroyFifoNode(nombreCanal);

		std::cout << "\n== Fin del juego ==" << std::endl;
		log->write("\n== Fin del juego de Atrevido ==");

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "*\n** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

