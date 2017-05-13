#ifndef SYNC_BARRIER_H
#define SYNC_BARRIER_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string>

#include "Locker.h"
#include "SharedCounter.h"


namespace utils {

	class SyncBarrier {
		public:
			SyncBarrier(char uid, int cantProc, int semID);
			virtual ~SyncBarrier() = default;

			void enterBarrier();
			void exitBarrier();

		private:
			int m_semaforoID;
			const int m_cantProcesos;

			Locker m_lock;
			SharedCounter m_contador;	// Contador compartido entre procesos

			// No se pueden copiar las barreras
			SyncBarrier(const SyncBarrier& sb) = delete;
			SyncBarrier& operator=(const SyncBarrier& sb) = delete;

			int setSemaphoreValue(int semID, int semPos, int val);

			sembuf getSignalOp(int nSem, int sigOp) const;

	};
}

#endif
