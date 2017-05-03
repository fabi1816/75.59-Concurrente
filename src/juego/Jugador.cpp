#include "Jugador.h"



namespace game {


	Jugador::Jugador(int id, std::stack<int> cartas, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox)
		: m_id(id), m_cartas(cartas), m_turno(t), m_turnoProximoJugador(prox), m_cartaPrev(0)
	{
		utils::SignalHandler::getInstance()->registrarHandler(CardCheckHandler::SIG_CARTA_JUGADA , &this->m_cardHandler);
	}


	int Jugador::jugar() {
		while (!this->m_cartas.empty()) {
			msg("Espero mi turno");

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
				msg("Pasé el turno al siguiente jugador");
				this->m_turnoProximoJugador->signal_v();
			}
		}

		msg("GANE!");
		// TODO: Mandar un mesaje a todos lo jugadores de que el juego terminó

		return 0;
	}


	void Jugador::saludar(int carta, int cartaPrev) {
		// TODO: Mandar los mensajes al ether
		switch (carta) {
			case 7:
				msg("Atrevido!");
				break;

			case 10:
				msg("Buenos dias señorita");
				break;

			case 11:
				msg("Buenas noches caballero");
				break;

			case 12:
				msg("( ゜ω゜)ゝ");
				break;

			default:
				if (carta == cartaPrev) {
					msg("Atrevido!");
				}
				break;
		}
	}


	void Jugador::msg(std::string txt) {
		std::cout << "\t" << this->m_id << " ==> " << txt << std::endl;
	}


	Jugador::~Jugador() {
		utils::SignalHandler::getInstance()->removerHandler(CardCheckHandler::SIG_CARTA_JUGADA);
		utils::SignalHandler::destruir();
	}

}
