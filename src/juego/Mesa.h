#ifndef MESA_H
#define MESA_H


#include <stack>

#include "Utils.h"


namespace game {

	class Mesa {
		private:

			// Un array estatico para colocar las cartas en la mesa
			int m_pilaCartas[48];
			int m_cantCartas;

			int m_cantTotalJugadores;
			int m_cantManos;


		public:
			Mesa();

			void initMesa(int cantJugadores);

			void JugarCarta(int carta);

			// Permiten ver la ultima y ante-ultima cartas
			int verUltimaCarta();
			int verAnteUltimaCarta();

			// Devuelve true si el jugador es el ultimo en colocar la mano
			bool colocarMano();

			//Levanta todas las cartas de las mesa y la deja vacia.
			std::stack<int> levantarTodasLasCartas();

			virtual ~Mesa() = default;

	};

}

#endif
