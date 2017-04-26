#include <unistd.h>
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
		std::cout << "Prueba de juego - mkVIII" << std::endl;

		// Las cartas del jugador
		std::vector<int> cartasJ1 = { 1, 2 };

		// Crear semaforos
		std::vector< std::shared_ptr<player::Turno> > turnos = player::TurnoFactory::buildTurnos(2);
		std::cout << "Semaforos listos" << std::endl;

		// Se crea el jugador de prueba en su propio proceso
		pid_t pid = fork();
		if (pid == 0) {
			player::Jugador jugador1(0, cartasJ1, turnos[0], turnos[1]);

			return jugador1.jugar();
		}

		std::cout << "Espero a que empieze el juego" << std::endl;
		sleep(3);

		// Señala al primer jugador que comienze el juego
		std::cout << "Empieza el juego" << std::endl;
		turnos[0]->signal_v();

		// Se espera por el jugador
		std::cout << "Espero por los jugadores" << std::endl;
		int stat = 0;
		wait(&stat);

		std::cout << "Destruyo los semaforos" << std::endl;
		player::TurnoFactory::destroyTurnos(turnos);

		std::cout << "Fin del juego" << std::endl;

		return 0;

	} catch (const std::system_error &e) {
		std::cout << "** Error: " << e.code() << " -> " << e.what() << std::endl;
		return -1;
	}
}

