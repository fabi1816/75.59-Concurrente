#include "BaseSemaforo.h"


namespace game {


	BaseSemaforo::BaseSemaforo(int semID) : m_semaphoreID(semID) { }


	int BaseSemaforo::getSemId() const {
		return this->m_semaphoreID;
	}


	sembuf BaseSemaforo::getSignalOp(int nSem, int sigOp) const {
		sembuf sops;
		sops.sem_num = nSem;
		sops.sem_op = sigOp;
		sops.sem_flg = 0;

		return sops;
	}

}
