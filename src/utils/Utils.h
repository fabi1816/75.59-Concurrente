#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdexcept>
#include <system_error>
#include <cerrno>


namespace utils {

	// Checks for errors in system calls
	void checkError(int result, std::string errMsg);

}


#endif
