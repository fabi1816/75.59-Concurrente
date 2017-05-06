#include "MesaCompartida.h"


namespace game {

	MesaCompartida::MesaCompartida() : m_lock("mesa_comp.lock") {
		// Generación de la clave
		key_t clave = ftok("/bin/ls", 'M');
		utils::checkError(clave, "Falló la creación de la key");

		// Crea la memoria compartida
		int shmId = shmget(clave, sizeof(Mesa), 0644 | IPC_CREAT);
		utils::checkError(shmId, "Falló la creación de la memoria compartida");

		// Atacha el bloque de memoria al espacio de direcciones del proceso
		void* ptrTemporal = shmat(shmId, nullptr, 0);
		if (ptrTemporal == (void*) -1) {
			utils::checkError(-1, "Fallo el atachado");
		}

		// Transforma lo almacenado en la memoria en un mesa
		this->m_shmID = shmId;
		this->m_mesa = static_cast<Mesa*>(ptrTemporal);
	}

	
	MesaCompartida::~MesaCompartida() {
		//Detach del bloque de memoria
		int res = shmdt(static_cast<void*>(this->m_mesa));
		utils::checkError(res, "No se pudo desatachar");

		int procAdosados = this->getNumeroDeJugadoresJugando();
		if (procAdosados == 0) {
			//Marca el segmento a ser destruido
			shmctl(this->m_shmID, IPC_RMID, NULL);
		}
	}


	void MesaCompartida::initMesa(int cantJugadores) {
		this->m_mesa->initMesa(cantJugadores);
	}


	void MesaCompartida::JugarCarta(int carta) {
		this->m_lock.tomarLockExclusivo();
		this->m_mesa->JugarCarta(carta);
		this->m_lock.liberarLockExclusivo();
	}


	int MesaCompartida::verUltimaCarta() {
		this->m_lock.tomarLockCompartido();
		int carta = this->m_mesa->verUltimaCarta();
		this->m_lock.liberarLockCompartido();

		return carta;
	}


	int MesaCompartida::verAnteUltimaCarta() {
		this->m_lock.tomarLockCompartido();
		int carta = this->m_mesa->verAnteUltimaCarta();
		this->m_lock.liberarLockCompartido();

		return carta;
	}

	
	bool MesaCompartida::colocarMano() {
		this->m_lock.tomarLockExclusivo();
		bool res = this->m_mesa->colocarMano();
		this->m_lock.liberarLockExclusivo();

		return res;
	}

	
	std::stack<int> MesaCompartida::levantarTodasLasCartas() {
		this->m_lock.tomarLockExclusivo();
		std::stack<int> pila = this->m_mesa->levantarTodasLasCartas();
		this->m_lock.liberarLockExclusivo();

		return pila;
	}


	int MesaCompartida::getNumeroDeJugadoresJugando() {
		shmid_ds estado;
		shmctl(this->m_shmID, IPC_STAT, &estado);

		return estado.shm_nattch;
	}

}

