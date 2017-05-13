#ifndef SHARED_COUNTER_H
#define SHARED_COUNTER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "Utils.h"


namespace utils {

	class SharedCounter {
		public:
			explicit SharedCounter(char uid);
			virtual ~SharedCounter();

			// Operaciones sobre el contador
			void sumar();
			void restar();

			int getValor() const;

		private:
			int m_sharedMemoriID;
			int* m_ptrSharedValue;


			int createSharedMemID(char uid) const;
			int* getAttachedMem(int shmID) const;

			// Indica si no esta attachada la memoria en otro proceso
			bool isNotAttached(int shmID) const;

			// No se puede copiar el contador
			SharedCounter(const SharedCounter& sc) = delete;
			SharedCounter& operator=(const SharedCounter& sc) = delete;
	};
}

#endif
