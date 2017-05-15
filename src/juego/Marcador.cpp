#include "Marcador.h"


namespace game {

	Marcador::Marcador() : m_cantJugadores(0), m_idxJugadorTurno(0), m_idGanador(0) { }


	void Marcador::init(int cantJugadores, std::vector<int> idJugadores) {
		if (idJugadores.size() > 48) {
			throw std::range_error("Demasiados jugadores");
		}

		for (unsigned i = 0; i < idJugadores.size(); ++i) {
			this->m_idJugadores[i] = idJugadores[i];
		}

		this->m_cantJugadores = cantJugadores;
	}


	//---------------------------------------------------------------------


	void Marcador::finJuego(int idGanador) {
		this->m_idGanador = idGanador;
	}


	bool Marcador::hayGanador() {
		return (this->m_idGanador != 0);
	}


	int Marcador::getIdGanador() {
		return this->m_idGanador;
	}


	//---------------------------------------------------------------------


	void Marcador::finDeTurno(int idJugador) {
		int pos = getPosJugador(idJugador);
		this->m_idxJugadorTurno = (pos + 1) % this->m_cantJugadores;
	}


	int Marcador::getIdProximoJugador() {
		return this->m_idJugadores[this->m_idxJugadorTurno];
	}


	int Marcador::getPosJugador(int idJugador) const {
		for (int i = 0; i < this->m_cantJugadores; ++i) {
			int id = this->m_idJugadores[i];
			if (id == idJugador) {
				return i;
			}
		}

		return 0;
	}
}

