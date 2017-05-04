#ifndef LOGGER_H
#define LOGGER_H


#include <memory>
#include <string>
#include <fstream>

#include "Locker.h"


namespace utils {

	class Logger {

		public:

			static std::shared_ptr<Logger> getLogger();


			void write(std::string txt);
			void write(int idJugador, std::string txt);
			void write(int idJugador, int n);


			virtual ~Logger() = default;

		private:

			static std::shared_ptr<Logger> m_loggerInstance;

			Locker m_logLocker;
			std::ofstream m_fout;


			Logger(std::string fileName);

	};
}

#endif
