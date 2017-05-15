#ifndef MARCADOR_COMPARTIDO_H
#define MARCADOR_COMPARTIDO_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <vector>
#include <string>
#include <stdexcept>

#include "Utils.h"
#include "Locker.h"
#include "Marcador.h"


namespace game {
	class MarcadorCompartido {
		public:
			MarcadorCompartido();
			virtual ~MarcadorCompartido();

			// inicializa el marcador, solo debe ser llamado una vez
			void init(int cantJugadores, std::vector<int> idJugadores);

			// Datos de un juego finalizado
			void finJuego(int idGanador);
			bool hayGanador();
			int getIdGanador();

			// Datos sobre quien es el proximo a jugar 
			void finDeTurno(int idJugador);
			int getIdProximoJugador();

		private:
			int m_shmID;
			Marcador* m_ptrMarcador;

			utils::Locker m_lock;

			int getNumeroDeJugadoresJugando();
	};
}

#endif
