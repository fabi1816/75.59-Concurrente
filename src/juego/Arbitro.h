#ifndef ARBITRO_H
#define ARBITRO_H

#include <memory>
#include <string>
#include <vector>

#include "Logger.h"
#include "CanalCartas.h"
#include "MarcadorCompartido.h"


namespace game {

	class Arbitro {
		public:
			explicit Arbitro(std::string nombreFifo);
			virtual ~Arbitro() = default;

			int espiarJuego();

		private:
			utils::CanalCartas m_canal;
			MarcadorCompartido m_marcador;
			std::shared_ptr<utils::Logger> m_log;

			std::string buildMensaje(std::vector<int> v) const;
	};
}

#endif
