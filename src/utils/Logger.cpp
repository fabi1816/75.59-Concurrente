#include "Logger.h"
#include <fstream>
namespace utils {

    Logger::Logger(std::string path){
        //Abre archivo para la escritura ubicado en el path.
        std::ofstream archivo(path);

    }

    //Escribe la fecha y hora,el id del jugdor y mensaje en el archivo y muestra por consola
    void Logger::escribir (int idJugador,std::string mensaje) {
        //obtiene el tiempo del sistema
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output, 128,"%d/%m/%y %H:%M:%S",tlocal);
        //Imprime por consola
        std::cout << output << idJugador << mensaje<< std::endl;
        //Escribe en el archivo del log
        //archivo << cadema
        std::cin >> output ,idJugador , mensaje;

    }
    //Destructor
    Logger::~Logger(){};
}

