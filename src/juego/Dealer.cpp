#include "Dealer.h"


namespace game {


	std::vector< std::stack<int> > Dealer::getPilas(int cantPilas) {
		// Redondea hacia abajo, lo que significa que quedan cartas en el mazo
		int cantCartas = 48 / cantPilas;

		std::vector< std::stack<int> > pilas;
		for (int i = 0; i < cantPilas; ++i) {

			std::stack<int> pila;
			for (int j = 0; j < cantCartas; ++j) {
				pila.push(j % 12);
			}

			pilas.push_back(pila);
		}

		return pilas;
	}

}

