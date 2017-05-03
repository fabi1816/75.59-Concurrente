//
// Created by marcos on 03/05/17.
//

#include "Fifo.h"


namespace utils {

    Fifo::Fifo(const std::string nombre):nombre(nombre),fd(-1) {
          //Crea el FIFO
          int fifoCreateStatus = mknod (static_cast <const char *>(nombre.c_str()), S_IFIFO |0666, 0);
          if (fifoCreateStatus == -1){
              checkErrors(fifoCreateStatus,"Falló la creacion del fifo");
          }
          else {
              //Abro el archivo,en forma no bloqueante.
              this->fd = open (nombre.c_str(),O_NONBLOCK);
          }
        }


    ssize_t  Fifo:: leer ( void * buffer , const ssize_t buffsize ) const {
          return read(this->fd, buffer, buffsize);
    }

    void Fifo::checkErrors(int result, std::string msg) const {
         if (result == -1) {
            throw std::system_error(errno, std::generic_category(),msg);
         }
    }

    ssize_t Fifo::escribir (const void* buffer,const ssize_t buffsize) {
          return write(this->fd, buffer, buffsize);
    }

    Fifo ::~ Fifo() {
        //Cierra el archivo
        close (fd) ;
        fd = -1;
        //Destruye el FIFO (Deslinkea el archivo de nuestra estructura).
        unlink (nombre.c_str()) ;
    }
}