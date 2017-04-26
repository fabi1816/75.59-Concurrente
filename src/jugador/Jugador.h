#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <vector>
#include <memory>
#include <iostream>

#include "Turno.h"


namespace player {


	class Jugador {
		public:
			Jugador(int id, std::vector<int> cartas, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox);

			int jugar();

			virtual ~Jugador() = default;

		private:

			int m_id;
			std::vector<int> m_cartas;

			std::shared_ptr<Turno> m_turno;
			std::shared_ptr<Turno> m_turnoProximoJugador;
	};

}

#endif


