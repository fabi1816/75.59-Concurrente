#ifndef _TURNO_H
#define _TURNO_H

#include <string>
#include <stdexcept>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>


class Turno {
	public:
		Turno(std::string actual, std::string proximo);

		void esperar();
		void proximo();

		virtual ~Turno();

	private:
		std::string m_nomberActualSemaforo;
		std::string m_nomberProximoSemaforo;
		
		sem_t* m_actualSemaforo;
		sem_t* m_proximoSemaforo;
};

#endif