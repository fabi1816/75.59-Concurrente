#include "SemaforoFactory.h"


namespace game {


	std::vector< std::shared_ptr<Turno> > SemaforoFactory::buildTurnos(int cant) {
		// Crea la key para los semaforos
		key_t k = ftok("/bin/ls", 19);
		utils::checkError(k, "Falló la creación de la key");

		// Crea la cantidad de semaforos señalada
		int semID = semget(k, cant, IPC_CREAT | 0644);
		utils::checkError(semID, "Falló la creación de los semaforos");

		// Inicializa todos los semaforos en cero
		for (int i = 0; i < cant; ++i) {
			semun init = { 0 };
			int res = semctl(semID, i, SETVAL, init);
			utils::checkError(res, "Falló la inicializacion de los semaforos");
		}

		// Crea los turnos 
		std::vector< std::shared_ptr<Turno> > v;
		for (int i = 0; i < cant; ++i) {
			v.push_back(std::make_shared<Turno>(semID, i));
		}

		return v;
	}


	void SemaforoFactory::destroyTurnos(std::vector< std::shared_ptr<Turno> > turnos) {
		if (turnos.empty()) {
			return;
		}

		int semID = turnos.front()->getSemId();
		int res = semctl(semID, 0, IPC_RMID);
		utils::checkError(res, "Falló la destruccion de los semaforos en el set");
	}


	//---------------------------------------


	std::shared_ptr<Saludador> SemaforoFactory::buildSaludador(int cantJugadores) {
		// Crea la key para el semaforo
		key_t k = ftok("/bin/ls", 20);
		utils::checkError(k, "Falló la creación de la key");

		// Crea e inicializa los semaforos
		int semID = semget(k, 2, IPC_CREAT | 0644);
		utils::checkError(semID, "Falló la creación de los semaforos");

		semun initA = { cantJugadores };
		int resA = semctl(semID, 0, SETVAL, initA);
		utils::checkError(resA, "Falló la inicializacion del primer semaforo");

		semun initB = { 0 };
		int resB = semctl(semID, 1, SETVAL, initB);
		utils::checkError(resB, "Falló la inicializacion del segundo semaforo");

		// Devuelve el saludador dentro de un smart pointer
		return std::make_shared<Saludador>(semID, cantJugadores);
	}


	void SemaforoFactory::destroySaludador(std::shared_ptr<Saludador> s) {
		int res = semctl(s->getSemId(), 0, IPC_RMID);
		utils::checkError(res, "Falló la destruccion de los semaforos");
	}

}

