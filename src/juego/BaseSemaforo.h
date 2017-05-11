#ifndef BASE_SEMAFORO_H
#define BASE_SEMAFORO_H


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


namespace game {

	class BaseSemaforo {
		public:
			explicit BaseSemaforo(int semID);

			int getSemId() const;

			virtual ~BaseSemaforo() = default;


		protected:
			int m_semaphoreID;


			/** 
			 * Devuelve la struct para realizar una operacion segun el valor de 
			 * sigOp en el semaforo nSem
			 *
			 * * Wait for zero -> sigOp == 0
			 * * Add to sem/signal/v -> sigOp == 1
			 * * Sustract from sem/wait/p -> sigOp == -1
			 * */
			sembuf getSignalOp(int nSem, int sigOp) const;
	};
}


#endif
