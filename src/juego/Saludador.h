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
			const std::string NADA = "nada";
			const std::string VENIA = "( ゜ω゜)ゝ";
			const std::string ATREVIDO = "Atrevido!";
			const std::string BUENOS_DIAS = "Buenos dias señorita...";
			const std::string BUENAS_NOCHES = "Buenas noches caballero.";

			std::string m_saludo;
			std::shared_ptr<utils::Logger> m_log;

			void enterBarrier();
			void exitBarrier();

			// Devuelve el saludo según las cartas jugadas
			std::string getSaludo(int carta, int cartaPrev) const;
	};
}

#endif

