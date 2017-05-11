#ifndef CARDCHECK_HANDLER_H
#define CARDCHECK_HANDLER_H

#include <string>

#include "Locker.h"
#include "EventHandler.h"
#include "MesaCompartida.h"


namespace game {

	class CardCheckHandler : public utils::EventHandler {

		public:
			static const int SIG_CARTA_JUGADA = SIGUSR1;


			CardCheckHandler(std::string lockFile);

			virtual int handleSignal(int);

			int getCartaJugada();
			int getCartaAnterior();

			bool hayCartaEnLaMesa();
			void cartaVista();

		private:
			int cartaJugada;
			int cartaAnterior;
			bool nuevaCartaEnLaMesa;

			utils::Locker m_lock;

			MesaCompartida m_mesa;

	};
}

#endif
