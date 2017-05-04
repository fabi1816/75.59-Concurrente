#ifndef CARDCHECK_HANDLER_H
#define CARDCHECK_HANDLER_H

#include "EventHandler.h"


namespace game {

	class CardCheckHandler : public utils::EventHandler {

		public:

			static const int SIG_CARTA_JUGADA = SIGUSR1;


			int cartaJugada;
			bool nuevaCartaEnLaMesa;


			CardCheckHandler() : cartaJugada(0), nuevaCartaEnLaMesa(false) { }


			virtual int handleSignal(int) {
				// TODO: Lock de lectura
				// TODO: Obtener la ultima carta de la mesa
				this->cartaJugada = 11;
				// TODO: Liberar lock

				this->nuevaCartaEnLaMesa = true;

				return 0;
			}

	};
}

#endif
