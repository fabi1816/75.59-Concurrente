/*
/ Created by marcos on 27/04/17.
 Clase que representa la mesa del juego,implementada atraves de una memoria compartida
*/
#ifndef MESA_H
#define MESA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <stack>

#include "Utils.h"


namespace game {

    class Mesa {
      private:

        int shmId;
        std::stack<int>* ptrDatos;


      public:
        //Crea la mesa usando una memoria compartida obteniendo un puntero a la direccion de inicio de la memoria compartida
        Mesa(std::stack<int> cartas);

        //Cada jugador atacha la memoria compartida,debe ejecutarse desde el proceso del jugador.
        std::stack<int>* observarMesa();

        //Juega cargas en la mesa(escribe en la memoria atachada)
        void JugarCartaEnMesa(int carta);

        //Levanta todas las cartas de las mesa y la deja vacia.
        std::stack<int> tomarTodasLasCartas();

        //Devuelve un stack de enteros con todas las cartas en la mesa actualmente.
        std::stack<int> VerCartasEnMesa();

	//Cantidad de jugadores jugando (que tienen la mesa atachada)
	int getNumeroDeJugadoresJugando();

        //Destruye mesa
        ~ Mesa() ;

    };

}
#endif //MESA_H
