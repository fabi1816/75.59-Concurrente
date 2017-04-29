#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <signal.h>
#include <stdio.h>

#include <memory.h>

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

			EventHandler* registrarHandler(int signum,EventHandler* eh);
			int removerHandler(int signum);

	};
}

#endif
