#include "SyncBarrier.h"


namespace utils {

	SyncBarrier::SyncBarrier(char uid, int cantProc, int semID)
		: m_cantProcesos(cantProc), m_lock(uid, "barrier"), m_contador(uid)
	{
		// Setea los valores iniciales de los semaforos
		int resA = setSemaphoreValue(semID, 0, 0);
		utils::checkError(resA, "Falló la inicializacion del primer semaforo");

		int resB = setSemaphoreValue(semID, 1, 1);
		utils::checkError(resB, "Falló la inicializacion del segundo semaforo");

		this->m_semaforoID = semID;
	}

	
	int SyncBarrier::createSemaphoreSet(char uid, int cant) {
		key_t k= ftok("/bin/ls", uid);
		utils::checkError(k, "Falló la creación de la clave de las barreras");

		int semID = semget(k, cant, IPC_CREAT | 0644);
		utils::checkError(semID, "Falló la creación de los semaforos");

		return semID;
	}

	void SyncBarrier::destroySamaphoreSet(int semID) {
		int res = semctl(semID, 0, IPC_RMID);
		utils::checkError(res, "Falló la destruccion de la barrera");
	}

	
	int SyncBarrier::setSemaphoreValue(int semID, int semPos, int val) {
		union semun {
			int val;
			struct semid_ds* b;
			unsigned short* ar;
			struct seminfo* in;
		};

		semun init = { val };
		return semctl(semID, semPos, SETVAL, init);
	}


	void SyncBarrier::enterBarrier() {
		// TODO: Implemetar
	}


	void SyncBarrier::exitBarrier() {
		// TODO: Implemetar
	}


	/**
	 * Wait for zero -> sigOp == 0 
	 * Add to sem/signal/v -> sigOp == 1 
	 * Sustract from sem/wait/p -> sigOp == -1
	 * */
	sembuf SyncBarrier::getSignalOp(int nSem, int sigOp) const {
		sembuf sops;
		sops.sem_num = nSem;
		sops.sem_op = sigOp;
		sops.sem_flg = 0;

		return sops;
	}

}
