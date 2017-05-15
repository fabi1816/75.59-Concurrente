#ifndef MARCADOR_H
#define MARCADOR_H

#include <vector>
#include <stdexcept>


namespace game {

	/**
	 * Mantiene información respecto del juego en un lugar accesible
	 * para todos lo jugadores (MAX 48).
	 * */
	class Marcador {
		public:
			Marcador();
			virtual ~Marcador() = default;

			// inicializa el marcador, solo debe ser llamado una vez
			void init(int cantJugadores, std::vector<int> idJugadores);

			// Datos de un juego finalizado
			void finJuego(int idGanador);
			bool hayGanador();
			int getIdGanador();

			// Datos sobre quien es el proximo a jugar 
			void finDeTurno(int idJugador);
			int getIdProximoJugador();

		private:
			int m_idJugadores[48];
			int m_cantJugadores;
			int m_idxJugadorTurno;

			int m_idGanador;


			int getPosJugador(int idJugador) const;
	};
}

#endif
