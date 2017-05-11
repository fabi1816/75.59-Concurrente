#include "Logger.h"


namespace utils {

	std::shared_ptr<Logger> Logger::m_loggerInstance = nullptr;


	std::shared_ptr<Logger> Logger::getLogger() {
		if (m_loggerInstance == nullptr) {
			m_loggerInstance = std::shared_ptr<Logger>(new Logger("log.txt"));
		}

		return m_loggerInstance;
	}


	//---------------------------------------


	Logger::Logger(std::string fileName)
		: m_logLocker(fileName + ".lock"), m_fout(fileName, std::ios_base::trunc) 
	{
	}


	void Logger::write(std::string txt) {
		this->m_logLocker.tomarLockExclusivo();
		this->m_fout << txt << std::endl;
		this->m_logLocker.liberarLockExclusivo();
	}


	void Logger::write(std::string txt, int i) {
		this->m_logLocker.tomarLockExclusivo();
		this->m_fout << txt << i << std::endl;
		this->m_logLocker.liberarLockExclusivo();
	}


	void Logger::writepid(std::string txt) {
		this->m_logLocker.tomarLockExclusivo();
		this->m_fout << getpid() << " -> " << txt << std::endl;
		this->m_logLocker.liberarLockExclusivo();
	}


	void Logger::writepid(std::string txt, int i) {
		this->m_logLocker.tomarLockExclusivo();
		this->m_fout << getpid() << " -> " << txt << i << std::endl;
		this->m_logLocker.liberarLockExclusivo();
	}

}

