#include "Locker.h"


namespace utils {

	Locker::Locker(std::string lockFile) : m_fileName(lockFile), m_fileDescriptor(0) {
		flock lockExc = { } ;
		flock lockCom = { } ;

		lockExc.l_whence = SEEK_SET;
		lockCom.l_whence = SEEK_SET;

		lockExc.l_start = 0;
		lockCom.l_start = 0;

		lockExc.l_len = 0;
		lockCom.l_len = 0;

		this->m_lockExclusivo = lockExc;
		this->m_lockCompartido = lockCom;
	}


	//---------------------------------------
	

	void Locker::tomarLockExclusivo() {
		this->m_fileDescriptor = abrirArchivoLock(O_WRONLY);

		// Aplica el lock
		this->m_lockExclusivo.l_type = F_WRLCK;
		aplicarLock(this->m_fileDescriptor, this->m_lockExclusivo);
	}

	void Locker::liberarLockExclusivo() {
		// Quita el lock
		this->m_lockExclusivo.l_type = F_UNLCK;
		quitarLock(this->m_fileDescriptor, this->m_lockExclusivo);

		this->m_fileDescriptor = cerrarArchivoLock(this->m_fileDescriptor);
	}


	void Locker::tomarLockCompartido() {
		this->m_fileDescriptor = abrirArchivoLock(O_RDONLY);

		// Aplica el lock
		this->m_lockCompartido.l_type = F_RDLCK;
		aplicarLock(this->m_fileDescriptor, this->m_lockCompartido);
	}

	void Locker::liberarLockCompartido() {
		// Quita el lock
		this->m_lockCompartido.l_type = F_UNLCK;
		quitarLock(this->m_fileDescriptor, this->m_lockCompartido);

		this->m_fileDescriptor = cerrarArchivoLock(this->m_fileDescriptor);
	}


	//---------------------------------------
	
	
	int Locker::abrirArchivoLock(int modo) {
		int fd = open(this->m_fileName.c_str(), modo);
		checkError(fd, "Falló la apertura del archivo de lock");

		return fd;
	}


	int Locker::cerrarArchivoLock(int fd) {
		int res = close(fd);
		checkError(res, "Error al cerrar el archivo de lock");
		
		return 0;
	}


	void Locker::aplicarLock(int fd, flock fl) {
		int res = fcntl(fd, F_SETLKW, fl);
		checkError(res, "Falló el seteo del lock");
	}


	void Locker::quitarLock(int fd, flock fl) {
		int res = fcntl(fd, F_SETLK, fl);
		checkError(res, "Falló la remocion del lock");
	}


	Locker::~Locker() {
		if (this->m_fileDescriptor != 0) {
			int res = close(this->m_fileDescriptor);
			checkError(res, "Error al desctruir el lock");

			this->m_fileDescriptor = 0;
		}
	}


	//---------------------------------------
	

	void Locker::checkError(int result, std::string msg) const {
		if (-1 == result) {
			throw std::system_error(errno, std::generic_category(), msg);
		}
	}

}

