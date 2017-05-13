#include "Utils.h"


namespace utils {

	void checkError(int result, std::string errMsg) {
		if (result == -1) {
			throw std::system_error(errno, std::generic_category(), errMsg);
		}
	}


	void checkErrorWithInteruption(int result, std::string errMsg) {
		// Que el error no deba ser interrumpido por una señal
		if (result == -1 && errno != EINTR) {
			throw std::system_error(errno, std::generic_category(), errMsg);
		}
	}


	std::string waitHandler(int pid, int stat, int slowSignal) {
		// Ocurrió un error inesperado
		if (pid == -1) {
			throw std::system_error(errno, std::generic_category(), "Wait error");
		}

		std::stringstream ss;

		// El proceso terminó debido a un signal
		if (WIFSIGNALED(stat)) {
			ss << "*\n** El jugador N°" << pid << " ";
			if (WTERMSIG(stat) == slowSignal) {
				ss << "tardó demasiado en prepararse";

			} else {
				ss << "murió debido a la señal: " << WTERMSIG(stat);
			}

		} else if (WIFEXITED(stat)) {	// El proceso terminó normalmente
			// Si un jugador terminó con status 0 fue el ganador
			if (WEXITSTATUS(stat) == 0) {
				ss << "\n== Ganó el jugador N°" << pid << " ==\n";

			} else if (WEXITSTATUS(stat) == 1) {	// Status 1 perdió
				ss << "= El jugador N°" << pid << " perdió =";
			}

		} else {
			ss << "*\n** Error no contemplado";
		}

		return ss.str();
	}

}

