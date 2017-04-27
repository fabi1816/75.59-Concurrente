#include "Dealer.h"


namespace game {

	Dealer::Dealer(int cantPilas) : m_cantPilas(cantPilas) { }


	std::stack<int> Dealer::getPila(int numPila) {
		// Redondea hacia abajo, lo que significa que quedan en el mazo
		int cantCartas = 48 / this->m_cantPilas;

		std::stack<int> pila;
		for (int i = 0; i < cantCartas; ++i) {
			pila.push(i % 12);	// Solo hay doce numeros por palo
		}

		return pila;
	}

}

