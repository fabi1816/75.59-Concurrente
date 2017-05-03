//
// Created by marcos on 03/05/17.
//Clase que implementa un FIFO,el cual sera utilizados por varios procesos para compartir datos.
//Se usa un buffer de 100 bytes para leer y escribir los datos en el FIFO.
//Hay que pasarle el buffer, para luego convertirlo a strig
//Pasarle el path del archivo ARCHIVO_FIFO = "/tmp/archivo_fifo"; y el BUFFSIZE = 100;
/*Leer
char buffer [ BUFFSIZE ];
Fifo canal;
ssize_t bytesLeidos = canal . leer ( static_cast < void * >( buffer ) , BUFFSIZE ) ;
std :: string mensaje = buffer ;
mensaje . resize ( bytesLeidos ) ;
std :: cout << " [ Lector ] Lei el dato del fifo : " << mensaje << std :: endl ;

Escribir
std :: string dato = " Hola mundo pipes !! " ;
canal . escribir ( static_cast < const void * >( dato . c_str () ) , dato . size () ) ;
*/

#ifndef FIFO_H
#define FIFO_H

#include <string>
#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace utils {

        class Fifo {


        public :
            //Construye  la estrucutra FIFO
            Fifo(const std::string);

            //Cierra el archivo y deslinkea el FIFO de la estructura
             ~ Fifo();

            //Lee el FIFO en un buffer de N bytes.
            ssize_t leer (void * buffer , const ssize_t buffsize) const ;

            //Escribir en el FIFO en un buffer de N bytes.
            ssize_t escribir (const void * buffer , const ssize_t buffsize);

            //Errores en el FIFO
            void checkErrors(int,std::string) const;


        private :
            std::string nombre;
            int fd = 0;
        };
}
#endif //FIFO_H
