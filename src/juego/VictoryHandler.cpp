#include "VictoryHandler.h"


namespace game {

	VictoryHandler::VictoryHandler(std::string lockFile) : finDelJuego(false), m_lock(lockFile) { }


	int VictoryHandler::handleSignal(int) {
		this->m_lock.tomarLockExclusivo();
		this->finDelJuego = true;
		this->m_lock.liberarLockExclusivo();

		return 0;
	}


	bool VictoryHandler::termino() {
		this->m_lock.tomarLockCompartido();
		bool t = this->finDelJuego;
		this->m_lock.liberarLockCompartido();

		return t;
	}

}
