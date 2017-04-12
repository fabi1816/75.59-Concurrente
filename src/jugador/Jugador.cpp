#include "Jugador.h"

namespace player {

Jugador::Jugador(std::vector<int> cartas, Turno &t)
	: m_turno(t), m_cartas(cartas) { }



void Jugador::Jugar() {
	this->m_turno.esperar();

	//Jugar la carta

	this->m_turno.proximo();
}

}
