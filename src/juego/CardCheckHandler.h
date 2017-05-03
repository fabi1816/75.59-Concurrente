#ifndef CARDCHECK_HANDLER_H
#define CARDCHECK_HANDLER_H

#include <random>

#include "EventHandler.h"


namespace game {

	class CardCheckHandler : public utils::EventHandler {

		public:

			static const int SIG_CARTA_JUGADA = SIGUSR1;


			int cartaJugada;

			CardCheckHandler() : cartaJugada(0) { }


			virtual int handleSignal(int signum) {
				if (signum != SIG_CARTA_JUGADA) {
					return 1;	// No es la señal esperada
				}

				// Leo la ultima carta jugada de la mesa
				std::minstd_rand rand(signum);	// random, por ahora...
				cartaJugada = rand() & 12;

				return 0;
			}


			virtual ~CardCheckHandler() = default;


	};
}

#endif
