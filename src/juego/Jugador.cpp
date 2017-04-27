#include "Jugador.h"



namespace game {


	Jugador::Jugador(int id, std::vector<int> cartas, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox)
		: m_id(id), m_cartas(cartas), m_turno(t), m_turnoProximoJugador(prox) { }


	int Jugador::jugar() {
		std::cout << this->m_id << " ==> Espero mi turno" << std::endl;

		this->m_turno->wait_p();

		std::cout << this->m_id << " ==> Juego una carta: " << this->m_cartas.back() << std::endl;
		this->m_cartas.pop_back();

		std::cout << this->m_id << " ==> Pasé el turno al siguiente jugador" << std::endl;
		this->m_turnoProximoJugador->signal_v();

		return 0;
	}

}
