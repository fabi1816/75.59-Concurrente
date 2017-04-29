#include "Jugador.h"



namespace game {


	Jugador::Jugador(int id, std::stack<int> cartas, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox)
		: m_id(id), m_cartas(cartas), m_turno(t), m_turnoProximoJugador(prox) 
	{
		utils::SignalHandler::getInstance()->registrarHandler(SIGINT, &this->m_jsig);
	}


	int Jugador::jugar() {
		while (!this->m_cartas.empty()) {
			std::cout << this->m_id << " ==> Espero mi turno" << std::endl;

			this->m_turno->wait_p();
			if (errno == EINTR) {
				std::cout << this->m_id << " ==> Interumpido por una señal" << std::endl;
				return 1;

			} else {	// Mi turno de jugar
				std::cout << this->m_id << " ==> Juego una carta: " << this->m_cartas.top() << std::endl;
				this->m_cartas.pop();

				std::cout << this->m_id << " ==> Pasé el turno al siguiente jugador" << std::endl;
				this->m_turnoProximoJugador->signal_v();
			}
		}

		std::cout << this->m_id << " ==> Me quedé sin cartas" << std::endl;

		return 0;
	}


	Jugador::~Jugador() {
		utils::SignalHandler::destruir();
	}

}
