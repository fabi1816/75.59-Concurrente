#include "Turno.h"

namespace player {


Turno::Turno(std::string actual, std::string proximo) 
	: m_nomberActualSemaforo(actual), m_nomberProximoSemaforo(proximo) 
{
	this->m_actualSemaforo = sem_open(m_nomberActualSemaforo.c_str(), O_CREAT, 0666, 0);
	if (this->m_actualSemaforo == SEM_FAILED) {
		throw std::system_error(errno, std::generic_category(), "Falló la creación de un semaforo");
	}

	this->m_proximoSemaforo = sem_open(m_nomberProximoSemaforo.c_str(), O_CREAT, 0666, 0);
	if (this->m_proximoSemaforo == SEM_FAILED) {
		throw std::system_error(errno, std::generic_category(), "Falló la creación de un semaforo");
	}
}


void Turno::esperar() {
	sem_wait(this->m_actualSemaforo);
}


void Turno::proximo() {
	sem_post(this->m_proximoSemaforo);
}


Turno::~Turno() {
	// Posiblemente alguien mas deberia cerrar los semaforos...
	sem_close(this->m_actualSemaforo);
	sem_close(this->m_proximoSemaforo);
	// Falta hacer unlink
}


}

