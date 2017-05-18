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

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string>

#include "Locker.h"
#include "Utils.h"


namespace utils {

	class Fifo {
		public:
			static void createFifoNode(std::string name);
			static void destroyFifoNode(std::string name);

			//Construye  la estrucutra FIFO
			explicit Fifo(const std::string);

			//Cierra el archivo y deslinkea el FIFO de la estructura
			virtual ~Fifo();

			//Lee el FIFO en un buffer de N bytes.
			ssize_t leer (void * buffer , const ssize_t buffsize);

			//Escribir en el FIFO en un buffer de N bytes.
			ssize_t escribir (const void * buffer , const ssize_t buffsize);

		private:
			int fd;
			std::string nombre;

			utils::Locker m_lockEsc;
			utils::Locker m_lockLec;
	};
}
#endif //FIFO_H
