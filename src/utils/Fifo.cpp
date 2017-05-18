//
// Created by marcos on 03/05/17.
//

#include "Fifo.h"


namespace utils {

	Fifo::Fifo(const std::string nombre) : nombre(nombre), 
		m_lockEsc("o" + nombre + ".lock"), 
		m_lockLec("i" + nombre + ".lock")
       	{
		//Abro el archivo,en forma bloqueante para la lecutra y escritura.
		int fdResult = open(nombre.c_str(), O_RDWR);
		utils::checkError(fdResult, "Error al abrir el Fifo");
		this->fd = fdResult;
	}


	ssize_t Fifo::leer (void* buffer, const ssize_t buffsize ) {
		this->m_lockLec.tomarLockExclusivo();
		ssize_t cr = read(this->fd, buffer, buffsize);
		this->m_lockLec.liberarLockExclusivo();

		return cr;
	}


	ssize_t Fifo::escribir (const void* buffer,const ssize_t buffsize) {
		this->m_lockEsc.tomarLockExclusivo();
		ssize_t code = write(this->fd, buffer, buffsize);
		this->m_lockEsc.liberarLockExclusivo();

		return code;
	}


	Fifo::~Fifo() {
		//Cierra el archivo
		close(fd) ;
		fd = -1;
	}
}
