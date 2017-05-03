#include "Jugador.h"


#include <iostream>
#include <unistd.h>


namespace game {


	Jugador::Jugador(int id, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox, std::shared_ptr<Saludador> sal)
		: m_id(id), m_turno(t), m_turnoProximoJugador(prox), m_saludador(sal), m_cartaPrev(0)
	{
		utils::SignalHandler::getInstance()->registrarHandler(CardCheckHandler::SIG_CARTA_JUGADA , &this->m_cardHandler);
	}


	void Jugador::setCartas(std::stack<int> cartas) {
		this->m_cartas = cartas;
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

			// Si es necesario hacemos el saludo
			saludar(this->m_cardHandler.cartaJugada, this->m_cartaPrev);

			this->m_cartaPrev = this->m_cardHandler.cartaJugada;

			if (esMiTurno) {
				std::cout << "\t" << this->m_id << " ==> Pasé el turno al siguiente jugador" << std::endl;
				this->m_turnoProximoJugador->signal_v();
			}
		}

		std::cout << "\t" << this->m_id << " ==> GANE!!!" << std::endl;

		// TODO: Mandar un mesaje a todos lo jugadores de que el juego terminó

		return 0;
	}


	// Saluda a los otros jugadores y espera a que todos saluden
	void Jugador::saludar(int carta, int cartaPrev) {
		// TODO: Mandar los mensajes al ether
		bool saludamos = false;
		switch (carta) {
			case 7:
				std::cout << "\t" << this->m_id << " ==> Atrevido" << std::endl;
				saludamos = true;
				break;

			case 10:
				std::cout << "\t" << this->m_id << " ==> Buenos dias señorita" << std::endl;
				saludamos = true;
				break;

			case 11:
				std::cout << "\t" << this->m_id << " ==> Buenas noches caballero" << std::endl;
				saludamos = true;
				break;

			case 12:
				std::cout << "\t" << this->m_id << " ==> ( ゜ω゜)ゝ" << std::endl;
				saludamos = true;
				break;

			default:
				if (carta == cartaPrev) {
					std::cout << "\t" << this->m_id << " ==> Atrevido" << std::endl;
					saludamos = true;
				}
				break;
		}

		// Si es necesario saludamos a todos los jugadores y esperamos sus respuestas
		if (saludamos) {
			std::cout << "\t" << this->m_id << " ==> Saludar" << std::endl;
			sleep(1);
			this->m_saludador->saludarJugadores();
			this->m_saludador->escucharJugadores();
			this->m_saludador->reset();
		}
	}


	Jugador::~Jugador() {
		utils::SignalHandler::getInstance()->removerHandler(CardCheckHandler::SIG_CARTA_JUGADA);
		utils::SignalHandler::destruir();
	}

}
