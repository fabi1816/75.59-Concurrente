#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include <memory>
#include <vector>
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
		std::cout << "Prueba de juego - mkV" << std::endl;

		// Las cartas del jugador
		std::vector<int> cartasJ1 = { 1, 2 };

		// Crear semaforo
		std::vector< std::unique_ptr<player::Turno> > turnos = player::TurnoFactory::buildTurnos(1);
		std::cout << "Semaforo listo" << std::endl;

		// Se crea el jugador de prueba en su propio proceso
		pid_t pid = fork();
		if (pid == 0) {
			std::cout << "--> Se crea al jugagor" << std::endl;
			std::cout << "--> Espero..." << std::endl;

			turnos[0]->wait_p();
			
			std::cout << "--> Juego una carta!" << std::endl;
			std::cout << "--> Señalo al siguiente" << std::endl;

			return 0;
		}

		sleep(3);

		// Señala al primer jugador que comienze el juego
		std::cout << "Empieza el juego" << std::endl;
		turnos[0]->signal_v();

		// Se espera por el jugador
		std::cout << "Espero por un jugador" << std::endl;
		int stat = 0;
		wait(&stat);

		std::cout << "Destruyo el semaforo" << std::endl;
		turnos[0]->destroy();

		std::cout << "Fin del juego" << std::endl;

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

