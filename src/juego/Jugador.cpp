#include "Jugador.h"



namespace game {


	Jugador::Jugador(int id, std::stack<int> cartas, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox)
		: m_id(id), m_cartas(cartas), m_turno(t), m_turnoProximoJugador(prox), m_cartaPrev(0)
	{
		utils::SignalHandler::getInstance()->registrarHandler(CardCheckHandler::SIG_CARTA_JUGADA , &this->m_cardHandler);
	}


	int Jugador::jugar() {
		while (!this->m_cartas.empty()) {
			std::cout << "\t" << this->m_id << " ==> Espero mi turno" << std::endl;

			bool esMiTurno = this->m_turno->wait_p();
			if (esMiTurno) {
				std::cout << "\t" << this->m_id << " ==> Juego una carta: " << this->m_cartas.top() << std::endl;
				this->m_cartas.pop();

				// Aviso a todos que hay una carta nueva en la mesa
				utils::SignalHandler::getInstance()->sendSignal(0, CardCheckHandler::SIG_CARTA_JUGADA);
			}

			std::cout << "\t" << this->m_id << " ==> Alguien jugó una carta: " << this->m_cardHandler.cartaJugada << std::endl;
			saludar(this->m_cardHandler.cartaJugada, this->m_cartaPrev);
			this->m_cartaPrev = this->m_cardHandler.cartaJugada;

			// TODO: Escuchar los mensajes de todos los jugadores
			// Podria ser un semaforo que vaya disminuyendo por cada mensaje recibido 
			// hasta llegar a cero y que siga la ejecucion cuando sea cero.

			if (esMiTurno) {
				std::cout << "\t" << this->m_id << " ==> Pasé el turno al siguiente jugador" << std::endl;
				this->m_turnoProximoJugador->signal_v();
			}
		}

		std::cout << "\t" << this->m_id << " ==> GANE!!!" << std::endl;

		// TODO: Mandar un mesaje a todos lo jugadores de que el juego terminó

		return 0;
	}


	void Jugador::saludar(int carta, int cartaPrev) {
		// TODO: Mandar los mensajes al ether
		switch (carta) {
			case 7:
				std::cout << "\t" << this->m_id << " ==> Atrevido" << std::endl;
				break;

			case 10:
				std::cout << "\t" << this->m_id << " ==> Buenos dias señorita" << std::endl;
				break;

			case 11:
				std::cout << "\t" << this->m_id << " ==> Buenas noches caballero" << std::endl;
				break;

			case 12:
				std::cout << "\t" << this->m_id << " ==> ( ゜ω゜)ゝ" << std::endl;
				break;

			default:
				if (carta == cartaPrev) {
					std::cout << "\t" << this->m_id << " ==> Atrevido" << std::endl;
				}
				break;
		}
	}


	Jugador::~Jugador() {
		utils::SignalHandler::getInstance()->removerHandler(CardCheckHandler::SIG_CARTA_JUGADA);
		utils::SignalHandler::destruir();
	}

}
