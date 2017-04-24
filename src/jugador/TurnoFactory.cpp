#include "TurnoFactory.h"


namespace player {

	std::vector<Turno> TurnoFactory::buildTurnos(int cant) {
		// Crea la key para los semaforos
		key_t k = ftok("/bin/ls", 19);
		checkError(k, "Falló la creación de la key");

		// Crea la cantidad de semaforos señalada
		int semID = semget(k, cant, IPC_CREAT | 0644);
		checkError(semID, "Falló la creación de los semaforos");

		// Inicializa todos los semaforos en cero
		union semun {
			int val;
			struct semid_ds* b;
			unsigned short* ar;
			struct seminfo* in;
		};
		for (int i = 0; i < cant; ++i) {
			semun init = { 0 };
			int res = semctl(semID, 0, SETVAL, init);
			checkError(res, "Falló la inicializacion de los semaforos");
		}

		// Crea los turnos 
		std::vector<Turno> v;
		for (int i = 0; i < cant; ++i) {
			Turno t(semID, i);
			v.push_back(t);
		}

		return v;
	}


	void TurnoFactory::checkError(int res, std::string txt) {
		if (res == -1) {
			throw std::system_error(errno, std::generic_category(), txt);
		}
	}

}

