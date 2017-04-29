#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <stack>
#include <memory>
#include <iostream>

#include "Turno.h"
#include "SignalHandler.h"
#include "jHandler.h"


namespace game {


	class Jugador {
		public:
			Jugador(int id, std::stack<int> cartas, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox);

			int jugar();

			virtual ~Jugador();

		private:

			int m_id;
			std::stack<int> m_cartas;

			std::shared_ptr<Turno> m_turno;
			std::shared_ptr<Turno> m_turnoProximoJugador;

			jHandler m_jsig;
	};

}

#endif


