#ifndef LOCKER_H
#define LOCKER_H

#include <fcntl.h>

#include <string>
#include <cerrno>
#include <stdexcept>
#include <system_error>


namespace utils {

	class Locker {
		public:
			Locker(std::string lockFile);

			void tomarLockExclusivo();
			void liberarLockExclusivo();

			void tomarLockCompartido();
			void liberarLockCompartido();

			virtual ~Locker();

		private:
			std::string m_fileName;
			int m_fileDescriptor;

			flock m_lockExclusivo;
			flock m_lockCompartido;


			void checkError(int result, std::string msg) const;
	};

}


#endif
