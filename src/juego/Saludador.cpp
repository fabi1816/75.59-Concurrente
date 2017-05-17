#include "Saludador.h"


namespace game {

	Saludador::Saludador(char uid, int cantProc, int semID)
	       	: SyncBarrier(uid, cantProc, semID), m_griteAtrevido(false)
	{
		this->m_log = utils::Logger::getLogger();
	}


	void Saludador::saludarJugadores(int carta, int cartaPrev) {
		// Entrá en la barrera y saluda
		SyncBarrier::enterBarrier();

		std::string saludo = getSaludo(carta, cartaPrev);
		this->m_griteAtrevido = (saludo ==  "Atrevido!");

		this->m_log->writepid(saludo);

	}


	void Saludador::escucharJugadores() {
		// Cuando salgo de la barrera es porque escuché a todos
		SyncBarrier::exitBarrier();
		this->m_log->writepid("Escuché a todos los jugadores");
	}


	// Devuelve el saludo según las cartas jugadas
	std::string Saludador::getSaludo(int carta, int cartaPrev) const {
		switch (carta) {
			case 7:
				return "Atrevido!";

			case 10:
				return "Buenos dias señorita...";

			case 11:
				return "Buenas noches caballero.";

			case 12:
				return "( ゜ω゜)ゝ";

			default:
				if (carta == cartaPrev) {
					return "Atrevido!";
				}
				return "No hay que saludar";
		}
	}


	bool Saludador::griteAtrevido() const {
		return this->m_griteAtrevido;
	}

}

