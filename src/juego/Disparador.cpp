#include "Disparador.h"


namespace game {

	Disparador::Disparador(int semID) : BaseSemaforo(semID) { }


	void Disparador::listo() {
		sembuf sops = getSignalOp(0, -1);
		int res = semop(this->m_semaphoreID, &sops, 1);
		utils::checkError(res, "Falló el listo");
	}


	void Disparador::esperarATodos() {
		sembuf sops = getSignalOp(0, 0);
		int res = semop(this->m_semaphoreID, &sops, 1);
		utils::checkError(res, "Falló el esperar a que todos esten listos");
	}


	//---------------------------------------------------------------------


	Disparador Disparador::build(int cantJugadores, char key) {
		// Crea la key
		key_t kSem = ftok("/bin/ls", key);
		utils::checkError(kSem, "Falló la creación de la clave del semaforo");

		// Crea e inicializa el semaforo
		int semID = semget(kSem, 1, IPC_CREAT | 0644);

		semun init = { cantJugadores };
		int res = semctl(semID, 0, SETVAL, init);
		utils::checkError(res, "Falló la inicializacion del semaforo");

		return Disparador(semID);
	}


	void Disparador::destroy(Disparador d) {
		int res = semctl(d.getSemId(), 0, IPC_RMID);
		utils::checkError(res, "Falló la destruccion del disparador");
	}

}

