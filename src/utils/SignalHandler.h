#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <signal.h>
#include <stdio.h>

#include <cerrno>
#include <stdexcept>
#include <system_error>

#include "EventHandler.h"


namespace utils {

	class SignalHandler {
		private:
			static SignalHandler* instance;
			static EventHandler* signal_handlers[NSIG];

			SignalHandler() = default;
			static void dispatcher(int signum);

		public:
			static SignalHandler* getInstance();
			static void destruir();

			EventHandler* registrarHandler(int signum, EventHandler* eh);
			int removerHandler(int signum);

			int sendSignal(pid_t pid, int signalNum);

	};
}

#endif
