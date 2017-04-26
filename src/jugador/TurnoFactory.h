#ifndef TURNO_FACTORY_H
#define TURNO_FACTORY_H

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


namespace player {

	class TurnoFactory {
		public:
			static std::vector< std::shared_ptr<Turno> > buildTurnos(int cant);
			static void destroyTurnos(std::vector< std::shared_ptr<Turno> > turnos);

		private:
			TurnoFactory() = default;
			static void checkError(int res, std::string txt);
	};
}

#endif
