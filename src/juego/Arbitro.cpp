#include "Arbitro.h"


namespace game {

	Arbitro::Arbitro(std::string nombreFifo) : m_canal(nombreFifo) {
		this->m_log = utils::Logger::getLogger();
	}


	int Arbitro::espiarJuego() {
		while (!this->m_marcador.hayGanador()) {
			// Bloquea hasta tener algo para leer
			std::vector<int> v = this->m_canal.espiar();

			if (v.size() > 1) {
				std::string msg = buildMensaje(v);
				this->m_log->write(msg);
			}

		}

		this->m_log->write("[Arbitro] Terminó el juego");

		return -1;
	}


	std::string Arbitro::buildMensaje(std::vector<int> v) const {
		std::string msg = "[Arbitro] El jugador: " + std::to_string(v.front());
		std::string cartas = " tiene las cartas: ";

		for (unsigned int i = 1; i < v.size(); ++i) {
			cartas += std::to_string(v[i]) + ", ";
		}

		return msg + cartas;
	}
}
