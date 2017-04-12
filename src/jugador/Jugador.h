#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <vector>

#include "Turno.h"



class Jugador {
	public:
		Jugador(std::vector<int> cartas, Turno &t);

		void Jugar();

		virtual ~Jugador();

	private:

		Turno &m_turno;
		std::vector<int> m_cartas;
};

#endif


