#ifndef LOGGER_H
#define LOGGER_H
//Clase que simula el log del juego

namespace utils {

	class Logger {
        //Recibe el path del archivo donde se guardaran las acciones
		Logger(string path);

        //Escribe la fecha y hora,el id del jugdor y mensaje en el archivo y muestra por consola
        void escribir (int IdJugador,string mensaje);

        //Destructor
        ~ Logger();

	};
}

#endif
