#ifndef LOGGER_H
#define LOGGER_H

#include <unistd.h>

#include <memory>
#include <string>
#include <fstream>

#include "Locker.h"


namespace utils {

	class Logger {

		public:
			static std::shared_ptr<Logger> getLogger();


			// Only writes the given text
			void write(std::string txt);

			// Writes the pid plus any given data
			void writepid(std::string txt);


			virtual ~Logger() = default;

		private:

			static std::shared_ptr<Logger> m_loggerInstance;

			Locker m_logLocker;
			std::ofstream m_fout;


			explicit Logger(std::string fileName);

	};
}

#endif
