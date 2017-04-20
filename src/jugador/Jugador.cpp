#include "Jugador.h"

#include <iostream>

namespace player {


Jugador::Jugador(std::vector<int> cartas, Turno &t)
	: m_turno(t), m_cartas(cartas) { }



int Jugador::Jugar() {
	std::cout << "Espero mi turno" << std::endl;
	this->m_turno.esperar();

	//Jugar la carta
	std::cout << "Juego una carta: " << m_cartas[0] << std::endl;

	this->m_turno.proximo();
	std::cout << "Pasé el turno al siguiente jugador" << std::endl;

	return 0;
}

}
