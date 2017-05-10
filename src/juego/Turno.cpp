#include "Turno.h"


namespace game {


	Turno::Turno(int semID, int semNum) : m_semaphoreID(semID), m_semaphoreNum(semNum) {
	}


	bool Turno::wait_p() {
		// Wait
		sembuf sops = getSignalOp(-1);

		int res = semop(this->m_semaphoreID, &sops, 1);
		utils::checkError(res, "Falló la espera del semaforo");

		// Si fue interumpido por una signal devuelve false
		return !(res == -1 && errno == EINTR);
	}


	void Turno::signal_v() {
		// Signal
		sembuf sops = getSignalOp(1);

		int res = semop(this->m_semaphoreID, &sops, 1);
		utils::checkError(res, "Falló la señal del semaforo");
	}


	sembuf Turno::getSignalOp(int semOp) const {
		sembuf sops;
		sops.sem_num = this->m_semaphoreNum;
		sops.sem_op = semOp;
		sops.sem_flg = 0;

		return sops;
	}
}

