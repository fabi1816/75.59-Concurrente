#ifndef SEMAFORO_FACTORY_H
#define SEMAFORO_FACTORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "Utils.h"
#include "Disparador.h"


namespace game {

	class SemaforoFactory {
		public:
			static Disparador buildDisparador(int cantJugadores);
			static void destroyDisparador(Disparador d);


		private:
			SemaforoFactory() = delete;

			// Declaro el union para toda la clase
			typedef union {
				int val;
				struct semid_ds* b;
				unsigned short* ar;
				struct seminfo* in;
			} semun;
	};
}

#endif
