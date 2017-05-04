#ifndef MESA_COMPARTIDA_H
#define MESA_COMPARTIDA_H


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <memory>

#include "Mesa.h"
#include "Utils.h"
#include "Locker.h"


namespace game {

	class MesaCompartida {

		public:

			MesaCompartida();

			void initMesa(int cantJugadores, std::string lockFileName);

			void JugarCarta(int carta);

			int verUltimaCarta();
			int verAnteUltimaCarta();

			bool colocarMano();
			std::stack<int> levantarTodasLasCartas();

			virtual ~MesaCompartida();
			
		private:

			int m_shmID;
			Mesa* m_mesa;

			std::unique_ptr<utils::Locker> m_lock;

			int getNumeroDeJugadoresJugando();
	};

}

#endif
