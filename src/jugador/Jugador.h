#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <vector>

#include "Turno.h"


namespace player {


class Jugador {
	public:
		Jugador(std::vector<int> cartas, Turno &t);

		int Jugar();

		virtual ~Jugador() = default;

	private:

		Turno &m_turno;
		std::vector<int> m_cartas;
};


}

#endif


