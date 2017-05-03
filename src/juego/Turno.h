#ifndef TURNO_H
#define TURNO_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <string>

#include "Utils.h"


namespace game {

	class Turno {

		public:

			Turno(int semID, int semNum);

			bool wait_p();
			void signal_v();

			int getSemId() const { return this->m_semaphoreID; }

		private:

			int m_semaphoreID;
			int m_semaphoreNum;

	};

}

#endif
