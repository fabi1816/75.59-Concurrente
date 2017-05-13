#include "SyncBarrier.h"


namespace utils {

	SyncBarrier::SyncBarrier(char uid, int cantProc, int semID)
		: m_semaforoID(semID), m_cantProcesos(cantProc), m_lock(uid, "barrier"), m_contador(uid)
	{
		// Setea los valores iniciales de los semaforos
		int resA = setSemaphoreValue(semID, 0, 0);
		utils::checkError(resA, "Falló la inicializacion del primer semaforo");

		int resB = setSemaphoreValue(semID, 1, 1);
		utils::checkError(resB, "Falló la inicializacion del segundo semaforo");
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
		this->m_lock.tomarLockExclusivo();
		this->m_contador.sumar();
		if (this->m_contador.getValor() == this->m_cantProcesos) {
			sembuf sops[2];
			sops[0] = getSignalOp(1, -1);	// Cierra la 2da barrera
			sops[1] = getSignalOp(0, 1);	// Abre la 1er barrera

			int res = semop(this->m_semaforoID, sops, 2);
			utils::checkError(res, "Error al entrar en la barrera");
		}
		this->m_lock.liberarLockExclusivo();

		// 1er barrera esperar y activar
		sembuf sops[2];
		sops[0] = getSignalOp(0, -1);	// Wait
		sops[1] = getSignalOp(0, 1);	// Signal

		int res = semop(this->m_semaforoID, sops, 2);
		utils::checkError(res, "Error al esperar en la primer barrera");
	}


	void SyncBarrier::exitBarrier() {
		this->m_lock.tomarLockExclusivo();
		this->m_contador.restar();
		if (this->m_contador.getValor() == 0) {
			sembuf sops[2];
			sops[0] = getSignalOp(0, -1);	// Cierra la 1er barrera
			sops[1] = getSignalOp(1, 1);	// Abre la 2da barrera

			int res = semop(this->m_semaforoID, sops, 2);
			utils::checkError(res, "Error al salir de la barrera");
		}
		this->m_lock.liberarLockExclusivo();

		// 2da barrera esperar y activar
		sembuf sops[2];
		sops[0] = getSignalOp(1, -1);	// Wait
		sops[1] = getSignalOp(1, 1);	// Signal

		int res = semop(this->m_semaforoID, sops, 2);
		utils::checkError(res, "Error al esperar en la segunda barrera");
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
