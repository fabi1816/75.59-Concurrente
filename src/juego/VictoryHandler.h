#ifndef VICTORY_HANDLER_H
#define VICTORY_HANDLER_H

#include "EventHandler.h"


namespace game {

	class VictoryHandler : public utils::EventHandler {

		public:

			static const int SIG_VICTORIA = SIGUSR2;

			bool finDelJuego;


			VictoryHandler() : finDelJuego(false) { }


			virtual int handleSignal(int signum) {
				if (signum != SIG_VICTORIA) {
					return 1;	// No es la señal esperada
				}

				this->finDelJuego = true;

				return 0;
			}

	};

}

#endif
