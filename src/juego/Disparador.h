#ifndef DISPARADOR_H
#define DISPARADOR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "Utils.h"
#include "BaseSemaforo.h"


namespace game {

	// Para que los jugadores indiquen que estan listos a comenzar
	class Disparador : public BaseSemaforo {
		public:
			static Disparador build(int cantJugadores, char key);
			static void destroy(Disparador d);


			void listo();
			void esperarATodos();

			virtual ~Disparador() = default;

		private:
			explicit Disparador(int semID);

			// Solo es usado por el builder
			typedef union {
				int val;
				struct semid_ds* b;
				unsigned short* ar;
				struct seminfo* in;
			} semun;
	};

}

#endif
