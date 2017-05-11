#include "Saludador.h"


namespace game {


	Saludador::Saludador(int semID, int shmID) :
		m_semaforoID(semID), m_sharedMemID(shmID), m_lock("saludador.lock")
	{
		// Atacha el bloque de memoria al espacio de direcciones del proceso
		void* ptrMem = shmat(shmID, nullptr, 0);
		if (ptrMem == (void*) -1) {
			utils::checkError(-1, "Fallo el atachado");
		}

		// Transforma lo almacenado en la memoria en un contador
		this->m_contador = static_cast<int*>(ptrMem);
	}


	void Saludador::init(int cantJugadores) {
		this->m_cantJugadores = cantJugadores;
		(*this->m_contador) = 0;
	}


	Saludador::~Saludador() {
		// Detach del bloque de memoria
		int res = shmdt(static_cast<void*>(this->m_contador));
		utils::checkError(res, "No se pudo desatachar");
	}


	//---------------------------------------------------------------------


	void Saludador::saludarJugadores(char) {
		this->m_lock.tomarLockExclusivo();
		plus1();
		if (getValContador() == this->m_cantJugadores) {
			sembuf sops[2];
			sops[0] = getSignalOp(1, -1);	// Cierra la 2da barrera
			sops[1] = getSignalOp(0, 1);	// Abre la 1er barrera

			int res = semop(this->m_semaforoID, sops, 2);
			utils::checkError(res, "Error al saludar a los jugadores [S1]");
		}
		this->m_lock.liberarLockExclusivo();

		// 1er barrera esperar y activar
		sembuf sops[2];
		sops[0] = getSignalOp(0, -1);	// Wait
		sops[1] = getSignalOp(0, 1);	// Signal

		int res = semop(this->m_semaforoID, sops, 2);
		utils::checkError(res, "Error al saludar a los jugadores [S2]");
	}


	void Saludador::escucharJugadores() {
		this->m_lock.tomarLockExclusivo();
		minus1();
		if (getValContador() == 0) {
			sembuf sops[2];
			sops[0] = getSignalOp(0, -1);	// Cierra la 1er barrera
			sops[1] = getSignalOp(1, 1);	// Abre la 2da barrera

			int res = semop(this->m_semaforoID, sops, 2);
			utils::checkError(res, "Error al escuchar a los jugadores [E1]");
		}
		this->m_lock.liberarLockExclusivo();

		// 2da barrera esperar y activar
		sembuf sops[2];
		sops[0] = getSignalOp(1, -1);	// Wait
		sops[1] = getSignalOp(1, 1);	// Signal

		int res = semop(this->m_semaforoID, sops, 2);
		utils::checkError(res, "Error al saludar a los jugadores [E2]");
	}


	// Wait for zero -> sigOp == 0
	// Add to sem/signal/v -> sigOp == 1
	// sustract from sem/wait/p -> sigOp == -1
	sembuf Saludador::getSignalOp(int nSem, int sigOp) {
		sembuf sops;
		sops.sem_num = nSem;
		sops.sem_op = sigOp;
		sops.sem_flg = 0;

		return sops;
	}

}

