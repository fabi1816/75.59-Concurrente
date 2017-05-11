#ifndef UTILS_H
#define UTILS_H


#include <sys/types.h>
#include <sys/wait.h>

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <cerrno>


namespace utils {

	// Checks for errors in system calls
	void checkError(int result, std::string errMsg);

	// Checks errors when waiting for processes and returns messages
	std::string waitHandler(int pid, int stat, int slowSignal);

}


#endif
