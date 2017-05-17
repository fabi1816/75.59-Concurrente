#include "Jugador.h"


namespace game {


	Jugador::Jugador(int idJugador, int cantJugadores, std::vector<int> semIDs, std::string keyCode)
	       	: m_idJugador(idJugador), 
		m_jugarCarta(keyCode[0], cantJugadores, semIDs[0]),
		m_chequearCarta(keyCode[1], cantJugadores, semIDs[1]),
		m_saludador(keyCode[2], cantJugadores, semIDs[2]),
		m_chequearTurno(keyCode[3], cantJugadores, semIDs[3]),
		m_chequearFin(keyCode[4], cantJugadores, semIDs[4])
       	{
		this->m_log = utils::Logger::getLogger();
	}


	int Jugador::jugar(std::stack<int> cartas) {
		this->m_cartas = cartas;
		bool finDelJuego = false;
		bool ganeElJuego = false;

		do {
			// Fase 1: Jugar carta
			this->m_jugarCarta.enterBarrier();
			jugarCarta();
			this->m_jugarCarta.exitBarrier();

			// Fase 2: Leer la carta que fué jugada
			this->m_chequearCarta.enterBarrier();
			int cartaJugada = this->m_mesa.verUltimaCarta();
			int cartaAnterior = this->m_mesa.verAnteUltimaCarta();
			this->m_log->writepid("En la mesa está la carta " + std::to_string(cartaJugada));
			this->m_chequearCarta.exitBarrier();

			// Fase 3: Saludar y escuchar
			this->m_saludador.saludarJugadores(cartaJugada, cartaAnterior);
			ejecutarAtrevido();
			this->m_saludador.escucharJugadores();

			// Fase 4: Finalizar el turno
			this->m_chequearTurno.enterBarrier();
			ganeElJuego = finalizarTurno();
			this->m_chequearTurno.exitBarrier();

			//-----------------------

			// Fase 5: Chequear fin de juego
			this->m_chequearFin.enterBarrier();
			finDelJuego = this->m_marcador.hayGanador();
			this->m_chequearFin.exitBarrier();

		} while (!finDelJuego);

		// Si gané devuelve 0, si no 1
		return ganeElJuego ? 0 : 1;
	}


	void Jugador::ejecutarAtrevido() {
		if (!this->m_saludador.griteAtrevido()) {
			return;
		}

		// Poner la mano en la mesa
		bool fuiUltimo = this->m_mesa.colocarMano();
		if (fuiUltimo) {
			// Levantar las cartas de la mesa
			std::stack<int> pilaCartas = this->m_mesa.levantarTodasLasCartas();
			int cant = pilaCartas.size();
			this->m_cartas = Dealer::mergeAndShuffle(this->m_cartas, pilaCartas);

			this->m_log->writepid("Perdí el atrevido y levanté " + std::to_string(cant) + " cartas");
		}
	}

	
	void Jugador::jugarCarta() {
		// Si no soy yo, no hago nada
		int prox = this->m_marcador.getIdProximoJugador();
		if (prox != this->m_idJugador) {
			return;
		}

		// Tomo la carta de mi mazo
		int carta = this->m_cartas.top();
		this->m_cartas.pop();

		// Coloca la carta de mi mazo en la mesa
		this->m_mesa.JugarCarta(carta);
		this->m_log->writepid("Jugé la carta " + std::to_string(carta));
	}


	// Devuelve true si me quedé sin cartas
	bool Jugador::finalizarTurno() {
		// Si me quedé sin cartas gané
		if (this->m_cartas.empty()) {
			this->m_marcador.finJuego(this->m_idJugador);
			this->m_log->writepid("Me quedé sin cartas, gané!");

		} else {
			// Indico que terminó mi turno de jugar
			this->m_marcador.finDeTurno(this->m_idJugador);
			this->m_log->writepid("Paso el turno al proximo jugador");
		}

		return this->m_cartas.empty();
	}



}
