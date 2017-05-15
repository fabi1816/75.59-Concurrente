#include "Utils.h"


namespace utils {

	void checkError(int result, std::string errMsg) {
		if (result == -1) {
			throw std::system_error(errno, std::generic_category(), errMsg);
		}
	}


	void checkErrorWithInteruption(int result, std::string errMsg) {
		// Que el error no deba ser interrumpido por una señal
		if (result == -1 && errno != EINTR) {
			throw std::system_error(errno, std::generic_category(), errMsg);
		}
	}


	//---------------------------------------------------------------------

	
	int createSemaphoreSet(char uid, int cant) {
		key_t k= ftok("/bin/ls", uid);
		checkError(k, "Falló la creación de la clave de las barreras");

		int semID = semget(k, cant, IPC_CREAT | 0644);
		checkError(semID, "Falló la creación de los semaforos");

		return semID;
	}


	void destroySamaphoreSet(int semID) {
		int res = semctl(semID, 0, IPC_RMID);
		checkError(res, "Falló la destruccion de la barrera");
	}


}

