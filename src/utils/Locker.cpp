#include "Locker.h"


namespace utils {

	Locker::Locker(std::string lockFile) : m_fileName(lockFile), m_fileDescriptor(0) {
		this->m_lockExclusivo = newEmptyFlock();
		this->m_lockCompartido = newEmptyFlock();
	}


	Locker::Locker(char uid, std::string discriminator) : m_fileDescriptor(0) {
		this->m_fileName = discriminator + "_" + std::to_string(uid) + ".lock";
		this->m_lockExclusivo = newEmptyFlock();
		this->m_lockCompartido = newEmptyFlock();
	}


	flock Locker::newEmptyFlock() const {
		flock fl;
		fl.l_whence = SEEK_SET;
		fl.l_start = 0;
		fl.l_len = 0;
		fl.l_pid = 0;

		return fl;
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
		int fd = open(this->m_fileName.c_str(), modo | O_CREAT, 0777);
		checkError(fd, "Falló la creacion del archivo de lock");

		return fd;
	}


	int Locker::cerrarArchivoLock(int fd) {
		int res = close(fd);
		checkError(res, "Error al cerrar el archivo de lock");

		return 0;
	}


	void Locker::aplicarLock(int fd, flock fl) {
		int res = fcntl(fd, F_SETLKW, &fl);
		checkError(res, "Falló el seteo del lock");
	}


	void Locker::quitarLock(int fd, flock fl) {
		int res = fcntl(fd, F_SETLK, &fl);
		checkError(res, "Falló la remocion del lock");
	}


	Locker::~Locker() {
		// TODO: Por ahora no borramos el archivo de lock
		//int res = unlink(this->m_fileName.c_str());
		//checkError(res, "Error al eliminar archivo de lock");
		
		this->m_fileDescriptor = 0;
		this->m_fileName = "";
	}
	
}

