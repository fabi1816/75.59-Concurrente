#include "CanalCartas.h"


namespace utils {

	CanalCartas::CanalCartas(std::string nomCanal) : Fifo(nomCanal), m_lock("ccartas.lock") { }


	void CanalCartas::mostrar(int id, std::stack<int> pila) {
		// Espacio para: id, cantidad y elementos
		int cantElem = 2 + pila.size();
		int* buff = initBuffer(id, pila, cantElem);

		int res = Fifo::escribir(buff, cantElem * sizeof(int));
		checkError(res, "Error al escribir cartas en el canal");

		deleteBuffer(buff);
	}

	int* CanalCartas::initBuffer(int id, std::stack<int> pila, int cantElementos) {
		// Hago una copia de la pila orginal
		std::stack<int> cpPila(pila);

		int* buff = new int[cantElementos]();

		// Carga los datos en el buffer
		int cantCartas = cpPila.size();
		buff[0] = id;
		buff[1] = cantCartas;
		for (int i = 0; i < cantCartas; ++i) {
			buff[i+2] = cpPila.top();
			cpPila.pop();
		}

		return buff;
	}


	void CanalCartas::deleteBuffer(int* buffer) {
		delete[] buffer;
	}


	std::vector<int> CanalCartas::espiar() {
		m_lock.tomarLockExclusivo();
		// Lee el id y la cantidad de cartas
		int data[2] = { };
		int res = Fifo::leer(data, 2* sizeof(int));
		checkError(res, "Error al leer del canal");

		// Leo las cartas
		std::vector<int> v = leerCartas(data[0], data[1]);

		m_lock.liberarLockExclusivo();

		return v;
	}


	std::vector<int> CanalCartas::leerCartas(int id, int cantCartas) {
		// El id va al principio
		std::vector<int> v = { id };
		if (cantCartas <= 0) {
			// No hay cartas
			return v;
		}

		// Lee las cartas
		int* buff = new int[cantCartas]();
		int res = Fifo::leer(buff, cantCartas * sizeof(int));
		checkError(res, "Error al leer las cartas del canal");

		for (int i = 0; i < cantCartas; ++i) {
			v.push_back(buff[i]);
		}

		delete[] buff;

		return v;
	}
}
