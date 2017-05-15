#include "MarcadorCompartido.h"


namespace game {

	MarcadorCompartido::MarcadorCompartido() : m_lock("marcador.lock") {
		// Generación de la clave
		key_t clave = ftok("/bin/cat", 'Q');
		utils::checkError(clave, "Falló la creación de la key");

		// Crea la memoria compartida
		int shmId = shmget(clave, sizeof(Marcador), 0644 | IPC_CREAT);
		utils::checkError(shmId, "Falló la creación de la memoria compartida");

		// Atacha el bloque de memoria al espacio de direcciones del proceso
		void* ptrTemporal = shmat(shmId, nullptr, 0);
		if (ptrTemporal == (void*) -1) {
			utils::checkError(-1, "Fallo el atachado");
		}

		// Transforma lo almacenado en la memoria en un mesa
		this->m_shmID = shmId;
		this->m_ptrMarcador = static_cast<Marcador*>(ptrTemporal);
	}


	MarcadorCompartido::~MarcadorCompartido() {
		//Detach del bloque de memoria
		int res = shmdt(static_cast<void*>(this->m_ptrMarcador));
		utils::checkError(res, "No se pudo desatachar");

		int procAdosados = this->getNumeroDeJugadoresJugando();
		if (procAdosados == 0) {
			//Marca el segmento a ser destruido
			shmctl(this->m_shmID, IPC_RMID, NULL);
		}
	}


	void MarcadorCompartido::init(int cantJugadores, std::vector<int> idJugadores) {
		this->m_lock.tomarLockExclusivo();
		this->m_ptrMarcador->init(cantJugadores, idJugadores);
		this->m_lock.liberarLockExclusivo();
	}


	void MarcadorCompartido::finJuego(int idGanador) {
		this->m_lock.tomarLockExclusivo();
		this->m_ptrMarcador->finJuego(idGanador);
		this->m_lock.liberarLockExclusivo();
	}


	bool MarcadorCompartido::hayGanador() {
		this->m_lock.tomarLockCompartido();
		bool res = this->m_ptrMarcador->hayGanador();
		this->m_lock.liberarLockCompartido();

		return res;
	}


	int MarcadorCompartido::getIdGanador() {
		this->m_lock.tomarLockCompartido();
		int id = this->m_ptrMarcador->getIdGanador();
		this->m_lock.liberarLockCompartido();

		return id;
	}


	void MarcadorCompartido::finDeTurno(int idJugador) {
		this->m_lock.tomarLockExclusivo();
		this->m_ptrMarcador->finDeTurno(idJugador);
		this->m_lock.liberarLockExclusivo();
	}


	int MarcadorCompartido::getIdProximoJugador() {
		this->m_lock.tomarLockCompartido();
		int id = this->m_ptrMarcador->getIdProximoJugador();
		this->m_lock.liberarLockCompartido();

		return id;
	}


	int MarcadorCompartido::getNumeroDeJugadoresJugando() {
		shmid_ds estado;
		shmctl(this->m_shmID, IPC_STAT, &estado);

		return estado.shm_nattch;
	}

}

