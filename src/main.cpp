#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include <string>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <cerrno>

#include "Jugador.h"
#include "Turno.h"



int main() {
	try {
		std::cout << "Prueba de juego - mkIV" << std::endl;

		// Las cartas del jugador
		std::vector<int> cartasJ1 = { 1, 2 };

		// Crear semaforo
		key_t k = ftok("/bin/ls", 19);
		if (k == -1) {
			throw std::system_error(errno, std::generic_category(), "Falló la creación de una key");
		}

		int semID = semget(k, 1, IPC_CREAT | 0644);
		if (semID == -1) {
			throw std::system_error(errno, std::generic_category(), "Falló la creación de los semaforos");
		}

		// Init semaforo
		union semun {
			int val;
			struct semid_ds* b;
			unsigned short* ar;
			struct seminfo* in;
		};
		semun init = { 0 };
		int res = semctl(semID, 0, SETVAL, init);
		if (res == -1) {
			throw std::system_error(errno, std::generic_category(), "Falló la inicializacion de los semaforos");
		}

		std::cout << "Semaforo listo" << std::endl;

		// Se crea el jugador de prueba en su propio proceso
		pid_t pid = fork();
		if (pid == 0) {
			std::cout << "--> Se crea al jugagor" << std::endl;
			std::cout << "--> Espero..." << std::endl;

			sembuf sops = { };
			sops.sem_num = 0;
			sops.sem_op = -1;	// Wait
			res = semop(semID, &sops, 1);
			if (res == -1) {
				throw std::system_error(errno, std::generic_category(), "Falló la espera del semaforo");
			}
			
			std::cout << "--> Juego una carta!" << std::endl;
			std::cout << "--> Señalo al siguiente" << std::endl;

			return 0;
		}

		// Señala al primer jugador que comienze el juego
		sleep(3);
		std::cout << "Empieza el juego" << std::endl;
		sembuf sops = { };
		sops.sem_num = 0;
		sops.sem_op = 1;	// Signal
		res = semop(semID, &sops, 1);
		if (res == -1) {
			throw std::system_error(errno, std::generic_category(), "Falló la señal del semaforo");
		}

		// Se espera por el jugador
		std::cout << "Espero por un jugador" << std::endl;
		int stat = 0;
		wait(&stat);

		// Libero el semaforo
		res = semctl(semID, 0, IPC_RMID);
		if (res == -1) {
			throw std::system_error(errno, std::generic_category(), "Falló la eliminación del semaforo");
		}

		std::cout << "Fin del juego" << std::endl;

		return 0;

	} catch (const std::system_error e) {
		std::cout << "** Error: " << e.code() << " -> " << e.what() << std::endl;
		perror(nullptr);
		return -1;
	}
}

