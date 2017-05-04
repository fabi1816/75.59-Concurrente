#include "Jugador.h"


#include <iostream>


namespace game {


	Jugador::Jugador(int id, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox, std::shared_ptr<Saludador> sal)
		: m_id(id), m_turno(t), m_turnoProximoJugador(prox), m_saludador(sal), m_cartaPrev(0)
	{
		utils::SignalHandler::getInstance()->registrarHandler(CardCheckHandler::SIG_CARTA_JUGADA , &this->m_cardHandler);
		utils::SignalHandler::getInstance()->registrarHandler(VictoryHandler::SIG_VICTORIA , &this->m_victoryHandler);
	}


	void Jugador::setCartas(std::stack<int> cartas) {
		this->m_cartas = cartas;
	}


	int Jugador::jugar() {
		while (!this->m_cartas.empty()) {
			bool esMiTurno = esperarTurno();
			if (esMiTurno) {
				jugarCarta();
			}

			// Chequeo si alguien mas se quedó sin cartas
			if (this->m_victoryHandler.finDelJuego) {
				std::cout << "\t" << this->m_id << " ==> Perdí." << std::endl;
				return 1;
			}

			// Alguien jugó una carta, pude hacer sido yo
			if (this->m_cardHandler.nuevaCartaEnLaMesa) {
				chequearCartas();
				this->m_cardHandler.nuevaCartaEnLaMesa = false;
			}

			if (esMiTurno) { // Ya terminó mi turno, paso el turno al proximo jugador
				pasarTurno();
			}
		}

		// Gané
		return anunciarFinDelJuego();
	}


	bool Jugador::esperarTurno() {
		// Antes de esperar chequeo que no tenga algo que hacer
		if (this->m_cardHandler.nuevaCartaEnLaMesa || this->m_victoryHandler.finDelJuego) {
			std::cout << "\t" << this->m_id << " ==> No espero, alguien jugó una carta o perdí" << std::endl;
			return false;
		}

		// No tengo que jugar, sino esperar mi turno
		std::cout << "\t" << this->m_id << " ==> Espero mi turno" << std::endl;
		return this->m_turno->wait_p();
	}


	void Jugador::jugarCarta() {
		std::cout << "\t" << this->m_id << " ==> Juego una carta: " << this->m_cartas.top() << std::endl;
		this->m_cartas.pop();

		// Aviso a todos que hay una carta nueva en la mesa
		utils::SignalHandler::getInstance()->sendSignal(0, CardCheckHandler::SIG_CARTA_JUGADA);
	}


	void Jugador::chequearCartas() {
		std::cout << "\t" << this->m_id << " ==> Alguien jugó una carta: " << this->m_cardHandler.cartaJugada << std::endl;

		char saludo = getSaludo(this->m_cardHandler.cartaJugada, this->m_cartaPrev);
		if (saludo != Saludador::IGNORAR) {
			this->m_saludador->saludarJugadores(saludo);
			this->m_saludador->escucharJugadores();
		}

		this->m_cartaPrev = this->m_cardHandler.cartaJugada;
	}


	// Devuelve el saludo según las cartas jugadas
	char Jugador::getSaludo(int carta, int cartaPrev) {
		switch (carta) {
			case 7:
				std::cout << "\t" << this->m_id << " >>> Atrevido" << std::endl;
				return Saludador::ATREVIDO;

			case 10:
				std::cout << "\t" << this->m_id << " >>> Buenos dias señorita" << std::endl;
				return Saludador::BUENOS_DIAS_MISS;

			case 11:
				std::cout << "\t" << this->m_id << " >>> Buenas noches caballero" << std::endl;
				return Saludador::BUENAS_NOCHES_CABALLERO;

			case 12:
				std::cout << "\t" << this->m_id << " >>> ( ゜ω゜)ゝ" << std::endl;
				return Saludador::VENIA;

			default:
				if (carta == cartaPrev) {
					std::cout << "\t" << this->m_id << " >>> Atrevido" << std::endl;
					return Saludador::ATREVIDO;
				}
				break;
		}

		// No hay que saludar
		return Saludador::IGNORAR;
	}

	
	void Jugador::pasarTurno() {
		std::cout << "\t" << this->m_id << " ==> Pasé el turno al siguiente jugador" << std::endl;
		this->m_turnoProximoJugador->signal_v();
	}


	int Jugador::anunciarFinDelJuego() {
		std::cout << "\t" << this->m_id << " ==> GANE!!!" << std::endl;

		// Aviso a todos los jugadores que terminó el juego
		utils::SignalHandler::getInstance()->sendSignal(0, VictoryHandler::SIG_VICTORIA);

		return 0;
	}


	Jugador::~Jugador() {
		utils::SignalHandler::getInstance()->removerHandler(CardCheckHandler::SIG_CARTA_JUGADA);
		utils::SignalHandler::getInstance()->removerHandler(VictoryHandler::SIG_VICTORIA);
		utils::SignalHandler::destruir();
	}

}
