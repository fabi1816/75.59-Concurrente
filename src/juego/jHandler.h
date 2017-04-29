#ifndef _JHANDLER_H
#define _JHANDLER_H

#include <iostream>

#include "EventHandler.h"


namespace game {

	class jHandler : public utils::EventHandler {
		public:
			virtual int handleSignal(int signum) {
				std::cout << "Señal recibida: " << signum << std::endl;
				return 0;
			}


			virtual ~jHandler() {
				// nothing
			}

	};
}

#endif
