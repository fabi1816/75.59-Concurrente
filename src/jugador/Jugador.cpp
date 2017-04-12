#include "Jugador.h"


Jugador::Jugador(std::vector<int> cartas, Turno &t)
	: m_turno(t), m_cartas(cartas) { }


Jugador::~Jugador() { }


void Jugador::Jugar() {
	this->m_turno.esperar();

	//Jugar la carta

	this->m_turno.proximo();
}
