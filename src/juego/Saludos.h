#ifndef SALUDOS_H
#define SALUDOS_H

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include "Utils.h"


namespace game {

	class Saludos {

		public:
			explicit Saludos(int semID);

			// Bloquea el proceso hasta que todos los jugadores saluden
			void escucharJugadores();

			// Realiza un saludo a todos los jugadores
			void saludarJugadores();

		private:

			int m_semaforoID;

	};
}

#endif

