#include "Utils.h"


namespace utils {

	void checkError(int result, std::string errMsg) {
		// Que el error no se deba a set interrumpido por una señal
		if (result == -1 && errno != EINTR) {
			throw std::system_error(errno, std::generic_category(), errMsg);
		}
	}

}

