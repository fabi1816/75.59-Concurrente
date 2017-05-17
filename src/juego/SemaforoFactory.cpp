#include "SemaforoFactory.h"


namespace game {

	Disparador SemaforoFactory::buildDisparador(int cantJugadores) {
		// Crea la key
		key_t kSem = ftok("/bin/ls", 48);
		utils::checkError(kSem, "Falló la creación de la clave del semaforo");

		// Crea e inicializa el semaforo
		int semID = semget(kSem, 1, IPC_CREAT | 0644);

		semun init = { cantJugadores };
		int res = semctl(semID, 0, SETVAL, init);
		utils::checkError(res, "Falló la inicializacion del semaforo");

		Disparador d(semID);

		return d;
	}


	void SemaforoFactory::destroyDisparador(Disparador d) {
		int res = semctl(d.getSemId(), 0, IPC_RMID);
		utils::checkError(res, "Falló la destruccion del disparador");
	}

}

