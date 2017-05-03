#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdexcept>
#include <system_error>
#include <cerrno>


namespace utils {

	void checkError(int result, std::string errMsg) {
		// Que el error no se deba a set interrumpido por una señal
		if (result == -1 && errno != EINTR) {
			throw std::system_error(errno, std::generic_category(), errMsg);
		}
	}
}


#endif
