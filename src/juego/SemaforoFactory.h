#ifndef SEMAFORO_FACTORY_H
#define SEMAFORO_FACTORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <memory>
#include <vector>
#include <string>

#include "Utils.h"
#include "Turno.h"
#include "Saludos.h"


namespace game {

	class SemaforoFactory {

		public:

			static std::vector< std::shared_ptr<Turno> > buildTurnos(int cant);
			static void destroyTurnos(std::vector< std::shared_ptr<Turno> > turnos);

			static std::shared_ptr<Saludos> buildSaludos(int cantJugadores);
			static void destroySaludos(std::shared_ptr<Saludos> s);

		private:

			SemaforoFactory() = default;

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
