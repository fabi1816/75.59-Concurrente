#include "Jugador.h"


namespace player {

	Jugador::Jugador(std::vector<int> cartas, Turno &t)
		: m_turno(t), m_cartas(cartas) { }



	int Jugador::Jugar() {
		std::cout << "Espero mi turno" << std::endl;
		std::cout << "Juego una carta: " << m_cartas[0] << std::endl;
		std::cout << "Pasé el turno al siguiente jugador" << std::endl;

		return 0;
	}

}
