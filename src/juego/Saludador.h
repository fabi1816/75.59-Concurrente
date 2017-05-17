#ifndef SALUDADOR_H
#define SALUDADOR_H

#include <memory>
#include <string>

#include "Logger.h"
#include "SyncBarrier.h"


namespace game {

	class Saludador : public utils::SyncBarrier {
		public:
			Saludador(char uid, int cantProc, int semID);
			virtual ~Saludador() = default;

			// Es el saludo realizado un "Atrevido!"_
			bool griteAtrevido() const;

			// Realiza un saludo a todos los jugadores
			void saludarJugadores(int carta, int cartaPrev);

			// Espera hasta que todos los jugadores saluden
			void escucharJugadores();

		private:
			bool m_griteAtrevido;
			std::shared_ptr<utils::Logger> m_log;

			void enterBarrier();
			void exitBarrier();

			// Devuelve el saludo según las cartas jugadas
			std::string getSaludo(int carta, int cartaPrev) const;
	};
}

#endif

