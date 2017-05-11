#ifndef VICTORY_HANDLER_H
#define VICTORY_HANDLER_H

#include <string>

#include "Locker.h"
#include "EventHandler.h"


namespace game {

	class VictoryHandler : public utils::EventHandler {

		public:
			static const int SIG_VICTORIA = SIGUSR2;


			VictoryHandler(std::string lockFile);

			virtual int handleSignal(int);
		
			bool termino();

		private:
			bool finDelJuego;
			utils::Locker m_lock;

	};

}

#endif
