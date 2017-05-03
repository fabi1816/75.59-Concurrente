#include "Saludos.h"


namespace game {


	Saludos::Saludos(int semID) : m_semaforoID(semID) { }


	void Saludos::escucharJugadores() {
		// Espera a que sea cero el semaforo
		sembuf sops = { };
		sops.sem_num = 0;
		sops.sem_op = 0;

		int res = semop(this->m_semaforoID, &sops, 1);
		utils::checkError(res, "Error al esperar escuchar a los jugadores");
	}


	void Saludos::saludarJugadores() {
		// Disminuye en uno el contador del semaforo
		sembuf sops = { };
		sops.sem_num = 0;
		sops.sem_op = -1;

		int res = semop(this->m_semaforoID, &sops, 1);
		utils::checkError(res, "Error al saludar a los otros jugadores");
	}

}

