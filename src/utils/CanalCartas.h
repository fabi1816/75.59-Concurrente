#ifndef CANAL_CARTAS_H
#define CANAL_CARTAS_H


#include <string>
#include <vector>
#include <stack>

#include "Fifo.h"
#include "Locker.h"


namespace utils {

	class CanalCartas : public Fifo {
		public:
			explicit CanalCartas(std::string nomCanal);
			virtual ~CanalCartas() = default;

			// El jugador indicado por el id muestra sus cartas
			void mostrar(int id, std::stack<int> pila);

			// Se recibe un vector cuyo primer elemento es el id del jugador
			// que mostró sus cartas
			std::vector<int> espiar();

		private:
			Locker m_lock;

			ssize_t leer(void* buffer, const ssize_t buffsize);
			ssize_t escribir(const void* buffer, const ssize_t buffsize);

			int* initBuffer(int id, std::stack<int> pila, int tamBuffer);
			void deleteBuffer(int* buffer);

			std::vector<int> leerCartas(int id, int cantCartas);
	};
}

#endif
