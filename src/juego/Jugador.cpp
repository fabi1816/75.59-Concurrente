#include "Jugador.h"


namespace game {


	Jugador::Jugador(std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox, std::shared_ptr<Saludador> sal)
		: m_turno(t), m_turnoProximoJugador(prox), m_saludador(sal)
	{
		this->m_log = utils::Logger::getLogger();

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
				this->m_log->writepid("Perdí!");
				return 1;
			}

			// Alguien jugó una carta, pude hacer sido yo
			if (this->m_cardHandler.nuevaCartaEnLaMesa) {
				this->m_cardHandler.nuevaCartaEnLaMesa = false;
				chequearCartas();
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
			this->m_log->writepid("No espero mi turno, hay que actuar");
			return false;
		}

		// No tengo que jugar, sino esperar mi turno
		this->m_log->writepid("Espero mi turno de jugar***********");
		return this->m_turno->wait_p();
	}


	void Jugador::jugarCarta() {
		int carta = this->m_cartas.top();
		this->m_cartas.pop();

		// Juega la carta
		this->m_mesa.JugarCarta(carta);

		this->m_log->writepid("Juego una carta: ", carta);

		// Aviso a todos que hay una carta nueva en la mesa
		utils::SignalHandler::getInstance()->sendSignal(0, CardCheckHandler::SIG_CARTA_JUGADA);
	}


	void Jugador::chequearCartas() {
		this->m_log->writepid("Una carta fue jugada: ", this->m_cardHandler.cartaJugada);

		// Chequea si necesita saludar
		char saludo = getSaludo(this->m_cardHandler.cartaJugada, this->m_cardHandler.cartaAnterior);
		if (saludo != Saludador::IGNORAR) {
			this->m_log->writepid("por saludar***********");
			this->m_saludador->saludarJugadores(saludo);
			this->m_log->writepid("salude");

			if (saludo == Saludador::ATREVIDO) {
				ejecutarElAtrevido();
			}

			this->m_log->writepid("por escuchar***********");
			this->m_saludador->escucharJugadores();
			this->m_log->writepid("escuche");
		}
	}


	// Devuelve el saludo según las cartas jugadas
	char Jugador::getSaludo(int carta, int cartaPrev) {
		switch (carta) {
			case 7:
				this->m_log->writepid("Atrevido!");
				return Saludador::ATREVIDO;

			case 10:
				this->m_log->writepid("Buenos dias señorita...");
				return Saludador::BUENOS_DIAS_MISS;

			case 11:
				this->m_log->writepid("Buenas noches caballero.");
				return Saludador::BUENAS_NOCHES_CABALLERO;

			case 12:
				this->m_log->writepid("( ゜ω゜)ゝ");
				return Saludador::VENIA;

			default:
				if (carta == cartaPrev) {
					this->m_log->writepid("Atrevido!");
					return Saludador::ATREVIDO;
				}
				break;
		}

		// No hay que saludar
		this->m_log->writepid("No hay que saludar");
		return Saludador::IGNORAR;
	}

	
	void Jugador::pasarTurno() {
		this->m_log->writepid("Paso el turno al siguiente jugador");
		this->m_turnoProximoJugador->signal_v();
	}


	int Jugador::anunciarFinDelJuego() {
		this->m_log->writepid("Gane!!");

		// Aviso a todos los jugadores que terminó el juego
		utils::SignalHandler::getInstance()->sendSignal(0, VictoryHandler::SIG_VICTORIA);

		return 0;
	}


	void Jugador::ejecutarElAtrevido() {
		bool fuiUltimo = this->m_mesa.colocarMano();
		if (!fuiUltimo) {
			return;
		}

		this->m_log->writepid("Fui el ultimo en colocar la mano en la mesa");

		// Agrego las cartas que levante de la mesa a mi mano
		std::stack<int> pilaCartas = this->m_mesa.levantarTodasLasCartas();
		this->m_cartas = Dealer::mergeAndShuffle(this->m_cartas, pilaCartas);
	}


	Jugador::~Jugador() {
		utils::SignalHandler::getInstance()->removerHandler(CardCheckHandler::SIG_CARTA_JUGADA);
		utils::SignalHandler::getInstance()->removerHandler(VictoryHandler::SIG_VICTORIA);
		utils::SignalHandler::destruir();
	}

}
