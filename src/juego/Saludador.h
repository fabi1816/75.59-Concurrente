#ifndef SALUDADOR_H
#define SALUDADOR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "Utils.h"
#include "Locker.h"


namespace game {

	class Saludador {

		public:
			// Los saludos posibles en el juego
			static const char VENIA = 'V';
			static const char ATREVIDO = 'A';
			static const char BUENOS_DIAS_MISS = 'S';
			static const char BUENAS_NOCHES_CABALLERO = 'C';

			static const char IGNORAR = 'I';


			Saludador(int semID, int shmID);
			virtual ~Saludador();

			void init(int cantJugadores);

			
			// Realiza un saludo a todos los jugadores
			void saludarJugadores(char saludo);

			// Bloquea el proceso hasta que todos los jugadores saluden
			void escucharJugadores();


			int getSemId() const { return this->m_semaforoID; }
			int getShmId() const { return this->m_sharedMemID; }

		private:
			int m_semaforoID;
			int m_cantJugadores;

			// Contador compartido entre procesos
			int m_sharedMemID;
			int* m_contador;

			utils::Locker m_lock;


			// Devuelve la struct para realizar una operacion segun 
			// el valor de sigOp en el semaforo nSem
			sembuf getSignalOp(int nSem, int sigOp);


			// Controlan al contador
			void plus1()  { ++(*this->m_contador); }
			void minus1() { --(*this->m_contador); }
			int getValContador() { return (*this->m_contador); }
	};
}

#endif

