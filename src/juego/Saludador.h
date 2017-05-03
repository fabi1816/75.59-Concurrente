#ifndef SALUDADOR_H
#define SALUDADOR_H

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include "Utils.h"


namespace game {

	class Saludador {

		public:
			Saludador(int semID, int cantJugadores);

			// Bloquea el proceso hasta que todos los jugadores saluden
			void escucharJugadores();

			// Realiza un saludo a todos los jugadores
			void saludarJugadores();

			// Resetea el contador de saludos
			void reset();

			int getSemId() const { return this->m_semaforoID; }

		private:

			int m_semaforoID;
			int m_cantJugadores;

	};
}

#endif

