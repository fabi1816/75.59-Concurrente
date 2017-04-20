#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>

#include <string>
#include <iostream>

#include "Jugador.h"
#include "Turno.h"



int main() {
	std::cout << "Prueba de juego - mkIII" << std::endl;

	// Las cartas del jugador
	std::vector<int> cartasJ1 = { 1, 2 };

	// Mover el semaforo a memoria compartida
	key_t k = ftok("/bin/ls", 19);
	if (k == -1) {
		std::cout << "** Error al crear la key de la memoria compartida" << std::endl;
		return -1;
	}

	int memID = shmget(k, sizeof(sem_t), IPC_CREAT | IPC_EXCL | 0666);
	if (memID == -1) {
		std::cout << "** Error al alocar la memoria compartida " << std::endl;
		perror(nullptr);
		return -1;
	}

	void* shMem = shmat(memID, nullptr, 0);
	if (shMem == (void*) -1) {
		std::cout << "** Error al atachar la memoria compartida" << std::endl;
		return -1;
	}

	// El semaforo que lleva cuenta del turno
	sem_t* turno1 = (sem_t*) shMem;
	int res = sem_init(turno1, 1, 0);
	if (res == -1) {
		std::cout << "** Error al crear el semaforo" << std::endl;
		return -1;
	}

	std::cout << "Semaforo listo" << std::endl;

	// Se crea el jugador de prueba en su propio proceso
	pid_t pid = fork();
	if (pid == 0) {
		std::cout << "Se crea al jugagor" << std::endl;
		std::cout << "Espero..." << std::endl;
		sem_wait(turno1);
		std::cout << "Juego una carta!" << std::endl;
		sem_post(turno1);
		std::cout << "Señalo al siguiente" << std::endl;

		//player::Jugador j(cartasJ1, t1);
		//return j.Jugar();
	}

	// Señala al primer jugador que comienze el juego
	std::cout << "Empieza el juego" << std::endl;
	res = sem_post(turno1);
	if (res == -1) {
		std::cout << "** Error al postear un semaforo" << std::endl;
		return -1;
	}


	// Se espera por el jugador
	std::cout << "Espero por un jugador" << std::endl;
	int stat = 0;
	wait(&stat);

	// Libero el semaforo
	res = sem_destroy(turno1);
	if (res == -1) {
		std::cout << "** Error al eliminar un semaforo" << std::endl;
		return -1;
	}

	// Liberar la memoria compartida
	res = shmctl(memID, IPC_RMID, nullptr);
	if (res == -1) {
		std::cout << "** Error al borrar la memoria compartida" << std::endl;
		return -1;
	}

	res = shmdt(shMem);
	if (res == -1) {
		std::cout << "** Error al desatachar la memoria compartida" << std::endl;
		return -1;
	}

	std::cout << "Fin del juego" << std::endl;

	return 0;
}

