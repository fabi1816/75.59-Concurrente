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
			explicit Disparador(int semID);


			void listo();
			void esperarATodos();

			
			virtual ~Disparador() = default;
	};

}

#endif
