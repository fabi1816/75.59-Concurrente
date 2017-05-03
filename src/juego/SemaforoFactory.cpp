#include "SemaforoFactory.h"


namespace game {

	std::vector< std::shared_ptr<Turno> > SemaforoFactory::buildTurnos(int cant) {
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
		std::vector< std::shared_ptr<Turno> > v;
		for (int i = 0; i < cant; ++i) {
			v.push_back(std::make_shared<Turno>(semID, i));
		}

		return v;
	}


	void SemaforoFactory::destroyTurnos(std::vector< std::shared_ptr<Turno> > turnos) {
		if (turnos.empty()) {
			return;
		}

		int semID = turnos.front()->getSemId();
		int res = semctl(semID, 0, IPC_RMID);
		checkError(res, "Falló la destruccion de los semaforos en el set");
	}


	void SemaforoFactory::checkError(int res, std::string txt) {
		if (res == -1) {
			throw std::system_error(errno, std::generic_category(), txt);
		}
	}

}

