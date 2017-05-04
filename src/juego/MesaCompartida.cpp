#include "MesaCompartida.h"


namespace game {

	MesaCompartida::MesaCompartida() {
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


	void MesaCompartida::initMesa(int cantJugadores, std::string lockFileName) {
		this->m_mesa->initMesa(cantJugadores);
		this->m_lock = std::unique_ptr<utils::Locker>(new utils::Locker(lockFileName));
	}


	void MesaCompartida::JugarCarta(int carta) {
		this->m_mesa->JugarCarta(carta);
	}


	int MesaCompartida::verUltimaCarta() {
		return this->m_mesa->verUltimaCarta();
	}


	int MesaCompartida::verAnteUltimaCarta() {
		return this->m_mesa->verAnteUltimaCarta();
	}

	
	bool MesaCompartida::colocarMano() {
		return this->m_mesa->colocarMano();
	}

	
	std::stack<int> MesaCompartida::levantarTodasLasCartas() {
		return this->m_mesa->levantarTodasLasCartas();
	}


	int MesaCompartida::getNumeroDeJugadoresJugando() {
		shmid_ds estado;
		shmctl(this->m_shmID, IPC_STAT, &estado);

		return estado.shm_nattch;
	}


}

