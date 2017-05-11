#include "CardCheckHandler.h"


namespace game {

	CardCheckHandler::CardCheckHandler(std::string lockFile) 
		: cartaJugada(0), cartaAnterior(0), nuevaCartaEnLaMesa(false), m_lock(lockFile)
	{
	}


	int CardCheckHandler::handleSignal(int) {
		this->m_lock.tomarLockExclusivo();

		// Obtiene las ultimas cartas jugadas
		this->cartaJugada = this->m_mesa.verUltimaCarta();
		this->cartaAnterior = this->m_mesa.verAnteUltimaCarta();

		this->nuevaCartaEnLaMesa = true;

		this->m_lock.liberarLockExclusivo();

		return 0;
	}


	int CardCheckHandler::getCartaJugada() {
		this->m_lock.tomarLockCompartido();
		int c = this->cartaJugada;
		this->m_lock.liberarLockCompartido();

		return c;
	}


	int CardCheckHandler::getCartaAnterior() {
		this->m_lock.tomarLockCompartido();
		int c = this->cartaAnterior;
		this->m_lock.liberarLockCompartido();

		return c;
	}


	bool CardCheckHandler::hayCartaEnLaMesa() {
		this->m_lock.tomarLockCompartido();
		bool b = this->nuevaCartaEnLaMesa;
		this->m_lock.liberarLockCompartido();

		return b;
	}


	void CardCheckHandler::cartaVista() {
		this->m_lock.tomarLockExclusivo();
		this->nuevaCartaEnLaMesa = false;
		this->m_lock.liberarLockExclusivo();
	}

}

