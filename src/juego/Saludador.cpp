#include "Saludador.h"


namespace game {


	Saludador::Saludador(int semID, int cantJugadores) :
		m_semaforoID(semID), m_cantJugadores(cantJugadores) { }


	void Saludador::escucharJugadores() {
		// Cierra la 1er barrera
		sembuf sops1 = getSignalOp(0, 1);
		int res1 = semop(this->m_semaforoID, &sops1, 1);
		utils::checkError(res1, "Error al esperar escuchar a los jugadores [C1]");

		// Abre la 2da barrera
		sembuf sops2 = getSignalOp(1, -1);
		int res2 = semop(this->m_semaforoID, &sops2, 1);
		utils::checkError(res2, "Error al esperar escuchar a los jugadores [A2]");

		// Espera a pasar la 2da barrera
		sembuf sWait1 = getSignalOp(1, 0);
		int resWait = semop(this->m_semaforoID, &sWait1, 1);
		utils::checkError(resWait, "Error al esperar escuchar a los jugadores [W2]");
	}


	void Saludador::saludarJugadores(char) {
		// Cierra la 2da barrera
		sembuf sops2 = getSignalOp(1, 1);
		int res2 = semop(this->m_semaforoID, &sops2, 1);
		utils::checkError(res2, "Error al saludar a los otros jugadores [C2]");

		// Abre la 1er barrera
		sembuf sops1 = getSignalOp(0, -1);
		int res1 = semop(this->m_semaforoID, &sops1, 1);
		utils::checkError(res1, "Error al saludar a los otros jugadores [A1]");

		// Espera a pasar la 1er barrera
		sembuf sWait1 = getSignalOp(0, 0);
		int resWait = semop(this->m_semaforoID, &sWait1, 1);
		utils::checkError(resWait, "Error al saludar a los otros jugadores [W1]");
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

