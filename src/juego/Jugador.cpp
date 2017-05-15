#include "Jugador.h"


namespace game {


	Jugador::Jugador(int idJugador, int cantJugadores, std::vector<int> semIDs, std::string keyCode)
	       	: m_idJugador(idJugador), 
		m_jugarCarta(keyCode[0], cantJugadores, semIDs[0]),
		m_chequearCarta(keyCode[1], cantJugadores, semIDs[1]),
		m_saludarJugadores(keyCode[2], cantJugadores, semIDs[2]),
		m_chequearTurno(keyCode[3], cantJugadores, semIDs[3]),
		m_chequearFin(keyCode[4], cantJugadores, semIDs[4])
       	{
		this->m_log = utils::Logger::getLogger();
	}


	int Jugador::jugar(std::stack<int> cartas) {
		this->m_cartas = cartas;

		bool finDelJuego = false;

		do {
			this->m_jugarCarta.enterBarrier();
			// Fase 1: Jugar carta, si corresponde al jugador
			this->m_jugarCarta.exitBarrier();

			this->m_chequearCarta.enterBarrier();
			// Fase 2: Leer la carta que fué jugada en la mesa
			this->m_chequearCarta.exitBarrier();

			this->m_saludarJugadores.enterBarrier();
			// Fase 3a: Saludar
			// Fase 3b: Poner la mano en la mesa
			// Fase 3c: Levantar las cartas de la mesa
			// Fase 3d: Escuchar todos los saludos
			this->m_saludarJugadores.exitBarrier();

			this->m_chequearTurno.enterBarrier();
			// Fase 4: Chequear si el jugador ganó, avisar al siguente jugador que puede jugar una carta
			this->m_chequearTurno.exitBarrier();

			this->m_chequearFin.enterBarrier();
			// Fase 5: Chequear si alguien ganó
			this->m_chequearFin.exitBarrier();

		} while (!finDelJuego);

		return 0;
	}

/*
	bool Jugador::esperarTurno() {
		// Antes de esperar veo si ya jugaron alguna carta 
		if (this->m_victoryHandler.finDelJuego) {
			this->m_log->writepid("No espero mi turno, ya ganó alguien mas");
			return false;
		}

		this->m_log->writepid("[Debug] chequear carta nueva");
		// Antes de esperar veo si alguien ya ganó
		if (this->m_cardHandler.nuevaCartaEnLaMesa) {
			this->m_log->writepid("No espero mi turno, ya hay una carta jugada");
			return false;
		}

		// No tengo que jugar, sino esperar mi turno
		this->m_log->writepid("Espero mi turno de jugar");
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
		this->m_cardHandler.nuevaCartaEnLaMesa = false;
		char saludo = getSaludo(this->m_cardHandler.cartaJugada, this->m_cardHandler.cartaAnterior);

		// Saluda
		this->m_saludador->saludarJugadores(saludo);

		if (saludo == Saludador::ATREVIDO) {
			ejecutarElAtrevido();
		}

		this->m_saludador->escucharJugadores();
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
	*/
}
