#include "Turno.h"


namespace player {


	Turno::Turno(int semID, int semNum) : m_semaphoreID(semID), m_semaphoreNum(semNum) { }


	void Turno::wait_p() {
		sembuf sops = { };
		sops.sem_num = this->m_semaphoreNum;
		sops.sem_op = -1;	// Wait

		int res = semop(this->m_semaphoreID, &sops, 1);
		checkErrors(res, "Falló la espera del semaforo");
	}


	void Turno::signal_v() {
		sembuf sops = { };
		sops.sem_num = this->m_semaphoreNum;
		sops.sem_op = 1;	// Signal

		int res = semop(this->m_semaphoreID, &sops, 1);
		checkErrors(res, "Falló la señal del semaforo");
	}

	
	void Turno::checkErrors(int result, std::string msg) const {
		if (result == -1) {
			throw std::system_error(errno, std::generic_category(), msg);
		}
	}

}

