#include "Saludador.h"


namespace game {

	Saludador::Saludador(char uid, int cantProc, int semID)
	       	: SyncBarrier(uid, cantProc, semID), m_saludo(NADA)
	{
		this->m_log = utils::Logger::getLogger();
	}


	void Saludador::saludarJugadores(int carta, int cartaPrev) {
		// Entrá en la barrera y saluda
		SyncBarrier::enterBarrier();

		this->m_saludo = getSaludo(carta, cartaPrev);
		if (this->m_saludo != NADA) {	// Solo si hubo saludo
			this->m_log->writepid(this->m_saludo);
		}

	}


	void Saludador::escucharJugadores() {
		// Cuando salgo de la barrera es porque escuché a todos
		SyncBarrier::exitBarrier();

		if (this->m_saludo != NADA) {	// Solo si hubo saludo
			this->m_log->writepid("Escuché a todos los jugadores");
		}
	}


	// Devuelve el saludo según las cartas jugadas
	std::string Saludador::getSaludo(int carta, int cartaPrev) const {
		switch (carta) {
			case 7:
				return ATREVIDO;

			case 10:
				return BUENOS_DIAS;

			case 11:
				return BUENAS_NOCHES;

			case 12:
				return VENIA;

			default:
				if (carta == cartaPrev) {
					return ATREVIDO;
				}
				return NADA;
		}
	}


	bool Saludador::griteAtrevido() const {
		return (this->m_saludo == ATREVIDO);
	}

}

