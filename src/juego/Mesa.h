#ifndef MESA_H
#define MESA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <string>
#include <stack>


namespace game {
	
	class Mesa {

		private:
			int shmId;
			std::stack<int>* ptrDatos;
			std::stack<int> cartas;

		public:

			//Crea la mesa usando una memoria compartida obteniendo un puntero a la direccion de inicio de la memoria compartida
			Mesa(std::stack<int> cartas);

			//Cada jugador atacha la memoria compartida,debe ejecutarse desde el proceso del jugador.
			std::stack<int>* ObservarMesa();

			//Juega cargas en la mesa(escribe en la memoria atachada)
			void JugarCartaEnMesa(const T &dato);

			//Levanta todas las cartas de las mesa y la deja vacia.
			std::stack<int> tomarTodasLasCartas();

			//Devuelve un stack con todas las cartas en la mesa actualmente.
			std::stack<int> VerCartasEnMesa();

			//Funcion de excepciones
			void checkError(int,std::string);

			//Cantidad de jugadores jugando (que tienen la mesa atachada)
			int getNumeroDeJugadoresJugando();

			//Destruye mesa
			~Mesa();

	};

}


#endif
