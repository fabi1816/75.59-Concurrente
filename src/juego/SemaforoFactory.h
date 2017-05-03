#ifndef SEMAFORO_FACTORY_H
#define SEMAFORO_FACTORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <system_error>
#include <cerrno>

#include "Turno.h"


namespace game {

	class SemaforoFactory {
		public:
			static std::vector< std::shared_ptr<Turno> > buildTurnos(int cant);
			static void destroyTurnos(std::vector< std::shared_ptr<Turno> > turnos);

		private:
			SemaforoFactory() = default;
			static void checkError(int res, std::string txt);
	};
}

#endif
