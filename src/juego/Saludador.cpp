#include "Saludador.h"

#include <unistd.h>
#include "Logger.h"

namespace game {


	Saludador::Saludador(int semID, int cantJugadores) :
		m_semaforoID(semID), m_cantJugadores(cantJugadores) { }


	void Saludador::escucharJugadores() {
		// Espera a que sea cero el semaforo
		sembuf sops;
		sops.sem_num = 0;
		sops.sem_op = 0;
		sops.sem_flg = 0;

		auto log = utils::Logger::getLogger();
		log->write(getpid(), "Estoy por Escuchar" );
		log->write(getpid(), getVal());

		int res = semop(this->m_semaforoID, &sops, 1);
		utils::checkError(res, "Error al esperar escuchar a los jugadores");
		
		log->write(getpid(), "Escuché!" );
		log->write(getpid(), getVal());
	}


	void Saludador::saludarJugadores(char) {
		// Disminuye en uno el contador del semaforo
		sembuf sops;
		sops.sem_num = 0;
		sops.sem_op = -1;
		sops.sem_flg = 0;

		auto log = utils::Logger::getLogger();
		log->write(getpid(), "Estoy por saludar" );
		log->write(getpid(), getVal());

		int res = semop(this->m_semaforoID, &sops, 1);
		utils::checkError(res, "Error al saludar a los otros jugadores");
		
		log->write(getpid(), "Saludé!" );
		log->write(getpid(), getVal());
	}


	void Saludador::reset() {
		union semun {
			int val;
			struct semid_ds* b;
			unsigned short* ar;
			struct seminfo* in;
		};

		semun init = { this->m_cantJugadores };

		auto log = utils::Logger::getLogger();
		log->write(getpid(), "**************Resetear" );
		log->write(getpid(), getVal());

		int res = semctl(this->m_semaforoID, 0, SETVAL, init);
		utils::checkError(res, "Falló el reseteo del semaforo");
	}


	int Saludador::getVal() {
		int res = semctl(this->m_semaforoID, 0, GETVAL);
		utils::checkError(res, "Falló el reseteo del semaforo");
		return res;
	}


}

