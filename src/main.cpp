#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string>
#include <iostream>

#include "Jugador.h"
#include "Turno.h"



int main() {
	std::cout << "Primera prueba de semaforos" << std::endl;

	// Las cartas de cada jugador
	std::vector<int> cartasJ1 = { 1, 2 };
	std::vector<int> cartasJ2 = { 3, 4 };

	// Estos son los semaforos para los turnos
	player::Turno t1("/TurnoJugador1", "/TurnoJugador2");
	player::Turno t2("/TurnoJugador2", "/TurnoJugador1");

	std::cout << "Se crearon los semaforos" << std::endl;

	// Se crean los jugadores en sus propios procesos
	pid_t pid = fork();
	if (pid == 0) {
		std::cout << "Se crea el jugagor 1" << std::endl;
		player::Jugador j(cartasJ1, t1);
		return j.Jugar();
	}

	pid = fork();
	if (pid == 0) {
		std::cout << "Se crea el jugagor 2" << std::endl;
		player::Jugador j(cartasJ2, t2);
		return j.Jugar();
	}

	// Señala al primer jugador que comienze el juego
	std::cout << "Empieza el juego" << std::endl;
	t2.proximo();

	// Se espera por la finalizacion de los jugadores
	for (int i = 0; i < 2; ++i) {
		std::cout << "Espero por un jugador" << std::endl;
		int stat = 0;
		wait(&stat);
	}

	std::cout << "Fin del juego" << std::endl;

	return 0;
}
