#ifndef CARDCHECK_HANDLER_H
#define CARDCHECK_HANDLER_H

#include "EventHandler.h"
#include "MesaCompartida.h"


namespace game {

	class CardCheckHandler : public utils::EventHandler {

		public:

			static const int SIG_CARTA_JUGADA = SIGUSR1;


			int cartaJugada;
			int cartaAnterior;
			bool nuevaCartaEnLaMesa;


			CardCheckHandler() : cartaJugada(0), nuevaCartaEnLaMesa(false) { }


			virtual int handleSignal(int) {
				// Obtiene las ultimas cartas jugadas
				this->cartaJugada = this->m_mesa.verUltimaCarta();
				this->cartaAnterior = this->m_mesa.verAnteUltimaCarta();

				this->nuevaCartaEnLaMesa = true;

				return 0;
			}

		private:

			MesaCompartida m_mesa;

	};
}

#endif
