#include "Saludador.h"


namespace game {


	Saludador::Saludador(int semID, int cantJugadores) :
		m_semaforoID(semID), m_cantJugadores(cantJugadores) { }


	void Saludador::escucharJugadores() {
		// Espera a que sea cero el semaforo
		sembuf sops = { };
		sops.sem_num = 0;
		sops.sem_op = 0;

		int res = semop(this->m_semaforoID, &sops, 1);
		utils::checkError(res, "Error al esperar escuchar a los jugadores");

		// Ya se escuchó a todos los juagadores, reseteamos el semaforo
		//reset();	// Parece que esto trae perdida de sincronizacion
	}


	void Saludador::saludarJugadores(char) {
		// Disminuye en uno el contador del semaforo
		sembuf sops = { };
		sops.sem_num = 0;
		sops.sem_op = -1;

		// TODO: Mandar el saludo a algun lado
		int res = semop(this->m_semaforoID, &sops, 1);
		utils::checkError(res, "Error al saludar a los otros jugadores");
	}


	void Saludador::reset() {
		union semun {
			int val;
			struct semid_ds* b;
			unsigned short* ar;
			struct seminfo* in;
		};

		semun init = { this->m_cantJugadores };
		int res = semctl(this->m_semaforoID, 0, SETVAL, init);
		utils::checkError(res, "Falló el reseteo del semaforo");
	}


}

