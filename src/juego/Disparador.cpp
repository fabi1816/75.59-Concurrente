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

}

