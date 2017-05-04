#ifndef SALUDADOR_H
#define SALUDADOR_H

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include "Utils.h"


namespace game {

	class Saludador {

		public:
			// Los saludos posibles en el juego
			static const char VENIA = 'V';
			static const char ATREVIDO = 'A';
			static const char BUENOS_DIAS_MISS = 'S';
			static const char BUENAS_NOCHES_CABALLERO = 'C';

			static const char IGNORAR = 'I';


			Saludador(int semID, int cantJugadores);

			// Bloquea el proceso hasta que todos los jugadores saluden
			void escucharJugadores();

			// Realiza un saludo a todos los jugadores
			void saludarJugadores(char saludo);

			int getSemId() const { return this->m_semaforoID; }

		private:

			int m_semaforoID;
			int m_cantJugadores;

			// Resetea el contador de saludos
			void reset();

	};
}

#endif

