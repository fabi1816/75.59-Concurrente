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
			// Cierra la 2da barrera
			sembuf sops2 = getSignalOp(1, 1);
			int res2 = semop(this->m_semaforoID, &sops2, 1);
			utils::checkError(res2, "Error al saludar a los otros jugadores [C2]");
			
			// Abre la 1er barrera
			sembuf sops1 = getSignalOp(0, -1);
			int res1 = semop(this->m_semaforoID, &sops1, 1);
			utils::checkError(res1, "Error al saludar a los otros jugadores [A1]");
		}
		this->m_lock.liberarLockExclusivo();

		// TODO: 1er barrera esperar y activar

		// Espera a pasar la 1er barrera
		sembuf sWait1 = getSignalOp(0, 0);
		int resWait = semop(this->m_semaforoID, &sWait1, 1);
		utils::checkError(resWait, "Error al saludar a los otros jugadores [W1]");
	}


	void Saludador::escucharJugadores() {
		this->m_lock.tomarLockExclusivo();
		minus1();
		if (getValContador() == 0) {
			// Cierra la 1er barrera
			// Abre la 2da barrera
		}
		this->m_lock.liberarLockExclusivo();

		// TODO: 2da barrera esperar y activar

		sembuf sops1 = getSignalOp(0, 1);
		int res1 = semop(this->m_semaforoID, &sops1, 1);
		utils::checkError(res1, "Error al esperar escuchar a los jugadores [C1]");

		sembuf sops2 = getSignalOp(1, -1);
		int res2 = semop(this->m_semaforoID, &sops2, 1);
		utils::checkError(res2, "Error al esperar escuchar a los jugadores [A2]");

		// Espera a pasar la 2da barrera
		sembuf sWait1 = getSignalOp(1, 0);
		int resWait = semop(this->m_semaforoID, &sWait1, 1);
		utils::checkError(resWait, "Error al esperar escuchar a los jugadores [W2]");
	}


	// Wait for zero -> sigOp == 0
	// Add to sem -> sigOp == 1
	// sustract from sem -> sigOp == -1
	sembuf Saludador::getSignalOp(int nSem, int sigOp) {
		sembuf sops;
		sops.sem_num = nSem;
		sops.sem_op = sigOp;
		sops.sem_flg = 0;

		return sops;
	}

}

