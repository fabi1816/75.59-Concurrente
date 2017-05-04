#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <stack>
#include <memory>

#include "Logger.h"

#include "Turno.h"
#include "Saludador.h"
#include "MesaCompartida.h"

#include "SignalHandler.h"
#include "VictoryHandler.h"
#include "CardCheckHandler.h"


namespace game {

	class Jugador {

		public:

			Jugador(int id, std::shared_ptr<Turno> t, std::shared_ptr<Turno> prox, std::shared_ptr<Saludador> sal);

			void setCartas(std::stack<int> cartas);

			int jugar();

			virtual ~Jugador();

		private:

			int m_id;

			std::shared_ptr<utils::Logger> m_log;

			std::shared_ptr<Turno> m_turno;
			std::shared_ptr<Turno> m_turnoProximoJugador;

			std::shared_ptr<Saludador> m_saludador;

			CardCheckHandler m_cardHandler;
			VictoryHandler m_victoryHandler;

			int m_cartaPrev;
			std::stack<int> m_cartas;


			bool esperarTurno();
			void pasarTurno();

			void jugarCarta();
			void chequearCartas();

			char getSaludo(int carta, int cartaPrev);

			int anunciarFinDelJuego();

	};

}

#endif


