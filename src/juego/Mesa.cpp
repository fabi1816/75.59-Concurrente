#include "Mesa.h"


namespace game {


	Mesa::Mesa() : m_cantCartas(0), m_cantTotalJugadores(0), m_cantManos(0) {
	}


	void Mesa::initMesa(int cantJugadores) {
		this->m_cantTotalJugadores = cantJugadores;
	}


	void Mesa::JugarCarta(int carta) {
		this->m_pilaCartas[this->m_cantCartas] = carta;
		++this->m_cantCartas;
	}


	int Mesa::verUltimaCarta() {
		// Todavia no hay cartas
		if (this->m_cantCartas == 0) {
			return 0;
		}

		return this->m_pilaCartas[this->m_cantCartas -1];
	}


	int Mesa::verAnteUltimaCarta() {
		// No hay suficientes cartas
		if (this->m_cantCartas < 2) {
			return 0;
		}
		return this->m_pilaCartas[this->m_cantCartas -2];
	}

	
	bool Mesa::colocarMano() {
		// Cuenta cuantas manos fueron colocadas
		++this->m_cantManos;
		
		if (this->m_cantManos == this->m_cantTotalJugadores) {
			this->m_cantManos = 0;
			return true;
		}

		return false;
	}

	
	std::stack<int> Mesa::levantarTodasLasCartas() {
		std::stack<int> pila;
		for (int i = 0; i < this->m_cantCartas; ++i) {
			pila.push(this->m_pilaCartas[i]);
		}

		this->m_cantCartas = 0;

		return pila;
	}

}

