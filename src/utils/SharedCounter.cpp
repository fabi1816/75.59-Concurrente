#include "SharedCounter.h"


namespace utils {

	SharedCounter::SharedCounter(char uid) {
		int shmID = createSharedMemID(uid);
		int* ptrMem = getAttachedMem(shmID);

		this->m_sharedMemoriID = shmID;
		this->m_ptrSharedValue = ptrMem;
	}


	SharedCounter::~SharedCounter() {
		// Des-attacha el bloque de memoria
		int res = shmdt(static_cast<void*>(this->m_ptrSharedValue));
		utils::checkError(res, "No se pudo desattachar la memoria compartida");

		if (isNotAttached(this->m_sharedMemoriID)) {
			res = shmctl(this->m_sharedMemoriID, IPC_RMID, nullptr);
			utils::checkError(res, "Falló la destruccion de la memoria compartida");
		}

		this->m_sharedMemoriID = 0;
		this->m_ptrSharedValue = nullptr;
	}


	int SharedCounter::createSharedMemID(char uid) const {
		// Crea la key y obtiene el ID de la memoria compartida
		key_t k = ftok("/bin/cat", uid);
		utils::checkError(k, "Falló la creación de la clave del contador");

		int shmID = shmget(k, sizeof(int), 0644 | IPC_CREAT);
		utils::checkError(shmID, "Falló la creación de la memoria compartida");

		return shmID;
	}


	int* SharedCounter::getAttachedMem(int shmID) const {
		// Attacha la mem
		void* ptrMem = shmat(shmID, nullptr, 0);
		if (ptrMem == reinterpret_cast<void*>(-1)) {
			utils::checkError(-1, "Fallo el atachado");
		}

		// Transforma lo almacenado en la memoria en un contador
		return static_cast<int*>(ptrMem);
	}


	bool SharedCounter::isNotAttached(int shmID) const {
		shmid_ds stat;
		int res = shmctl(shmID, IPC_STAT, &stat);
		utils::checkError(res, "Falló la consulta de la memoria compartida");

		// Nadie mas tiene attachada la memoria
		return (stat.shm_nattch == 0);
	}


	//---------------------------------------------------------------------


	void SharedCounter::sumar() {
		++(*this->m_ptrSharedValue); 
	}


	void SharedCounter::restar() {
		--(*this->m_ptrSharedValue); 
	}


	int SharedCounter::getValor() const {
		return (*this->m_ptrSharedValue);
	}

}
