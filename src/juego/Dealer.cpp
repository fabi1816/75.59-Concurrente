#include "Dealer.h"


namespace game {


	std::vector< std::stack<int> > Dealer::getPilas(int cantPilas) {
		// Redondea hacia abajo, lo que significa que quedan cartas en el mazo
		int cantCartas = 48 / cantPilas;

		std::vector<int> mazo = buildMazo();
		std::vector< std::stack<int> > pilas;
		for (int i = 0; i < cantPilas; ++i) {

			std::stack<int> pila;
			for (int j = 0; j < cantCartas; ++j) {
				pila.push(mazo.back());
				mazo.pop_back();
			}

			pilas.push_back(pila);
		}

		// TODO: Repartir las cartas que quedaron en el mazo

		return pilas;
	}


	std::vector<int> Dealer::buildMazo() {
		std::vector<int> v;

		// 12 Cartas de 4 palos
		for (int i = 0; i < 4; ++i) {
			for (int j = 1; j <= 12; ++j) {
				v.push_back(j);
			}
		}

		// Las mezcla
		std::random_shuffle(v.begin(), v.end());

		return v;
	}


	std::stack<int> Dealer::mergeAndShuffle(std::stack<int> a, std::stack<int> b) {
		std::vector<int> v;

		// Move the items into a vector
		for (unsigned i = 0; i < a.size(); ++i) {
			v.push_back(a.top());
			a.pop();
		}

		for (unsigned i = 0; i < b.size(); ++i) {
			v.push_back(b.top());
			b.pop();
		}

		// Suffle them
		std::random_shuffle(v.begin(), v.end());

		// Move them into a stack 
		std::stack<int> s;
		for (unsigned i = 0; i < v.size(); ++i) {
			s.push(v[i]);
		}

		return s;
	}

}

