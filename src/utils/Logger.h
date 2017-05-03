//Clase que simula el log del juego


#ifndef LOGGER_H
#define LOGGER_H


#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>

namespace utils {

	class Logger {
        //Recibe el path del archivo donde se guardaran las acciones
		Logger(std::string path);

        //Escribe la fecha y hora,el id del jugdor y mensaje en el archivo y muestra por consola
        void escribir (int idJugador,std::string mensaje);

        //Destructor
        ~Logger();

	};
}

#endif
