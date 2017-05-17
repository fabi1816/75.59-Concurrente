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

		do {
			this->m_jugarCarta.enterBarrier();
			// Fase 1: Jugar carta, si corresponde al jugador
			int prox = this->m_marcador.getIdProximoJugador();
			if (prox == this->m_idJugador) {
				int carta = this->m_cartas.top();
				this->m_cartas.pop();

				this->m_mesa.JugarCarta(carta);	// Juega la carta
			}
			this->m_jugarCarta.exitBarrier();

			//-----------------------

			this->m_chequearCarta.enterBarrier();
			// Fase 2: Leer la carta que fué jugada en la mesa
			int cartaJugada = this->m_mesa.verUltimaCarta();
			int cartaAnterior = this->m_mesa.verAnteUltimaCarta();
			this->m_chequearCarta.exitBarrier();

			//-----------------------

			this->m_saludador.saludarJugadores(cartaJugada, cartaAnterior);
			// Fase 3a: Saludar
			// Fase 3b: Poner la mano en la mesa
			if (this->m_saludador.griteAtrevido()) {
				bool fuiUltimo = this->m_mesa.colocarMano();
				if (fuiUltimo) {
					// Fase 3c: Levantar las cartas de la mesa
					std::stack<int> pilaCartas = this->m_mesa.levantarTodasLasCartas();
					this->m_cartas = Dealer::mergeAndShuffle(this->m_cartas, pilaCartas);
				}
			}
			// Fase 3d: Escuchar todos los saludos
			this->m_saludador.escucharJugadores();

			//-----------------------

			this->m_chequearTurno.enterBarrier();
			// Fase 4: Chequear si el jugador ganó, avisar al siguente jugador que puede jugar una carta
			if (this->m_cartas.empty()) {
				this->m_marcador.finJuego(this->m_idJugador);
			}
			this->m_marcador.finDeTurno(this->m_idJugador);
			this->m_chequearTurno.exitBarrier();

			//-----------------------

			this->m_chequearFin.enterBarrier();
			// Fase 5: Chequear si alguien ganó
			finDelJuego = this->m_marcador.hayGanador();
			this->m_chequearFin.exitBarrier();

		} while (!finDelJuego);

		return 0;
	}



}
