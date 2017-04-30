#include "Locker.h"


namespace utils {

	Locker::Locker(std::string lockFile) : m_fileName(lockFile), m_fileDescriptor(0) {
	}


	void Locker::tomarLockExclusivo() {
		int fd = open(this->m_fileName.c_str(), O_RDONLY);
		checkError(fd, "Falló la apertura del archivo de lock");
		this->m_fileDescriptor = fd;
	}

	void Locker::liberarLockExclusivo() {
		int res = close(this->m_fileDescriptor);
		checkError(res, "Error al liberar el lock");
		this->m_fileDescriptor = 0;
	}


	void Locker::tomarLockCompartido() {
	}

	void Locker::liberarLockCompartido() {
	}


	Locker::~Locker() {
		if (this->m_fileDescriptor != 0) {
			int res = close(this->m_fileDescriptor);
			checkError(res, "Error al desctruir el lock");

			this->m_fileDescriptor = 0;
		}
	}


	void Locker::checkError(int result, std::string msg) const {
		if (-1 == result) {
			throw std::system_error(errno, std::generic_category(), msg);
		}
	}

}

