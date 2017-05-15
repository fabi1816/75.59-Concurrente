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

			this->m_saludarJugadores.enterBarrier();
			// Fase 3a: Saludar
			char saludo = getSaludo(cartaJugada, cartaAnterior);
			// Fase 3b: Poner la mano en la mesa
			if (saludo == Saludador::ATREVIDO) {
				bool fuiUltimo = this->m_mesa.colocarMano();
				if (fuiUltimo) {
					// Fase 3c: Levantar las cartas de la mesa
					std::stack<int> pilaCartas = this->m_mesa.levantarTodasLasCartas();
					this->m_cartas = Dealer::mergeAndShuffle(this->m_cartas, pilaCartas);
				}
			}
			// Fase 3d: Escuchar todos los saludos
			this->m_saludarJugadores.exitBarrier();

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

}
