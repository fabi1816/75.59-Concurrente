#ifndef VICTORY_HANDLER_H
#define VICTORY_HANDLER_H

#include "EventHandler.h"


namespace game {

	class VictoryHandler : public utils::EventHandler {

		public:
			static const int SIG_VICTORIA = SIGUSR2;


			bool finDelJuego;


			VictoryHandler() : finDelJuego(false) { }


			virtual int handleSignal(int) {
				this->finDelJuego = true;
				return 0;
			}

	};

}

#endif
