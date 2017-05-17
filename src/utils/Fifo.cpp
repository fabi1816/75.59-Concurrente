//
// Created by marcos on 03/05/17.
//

#include "Fifo.h"


namespace utils {

    Fifo::Fifo(const std::string nombre):nombre(nombre),fd(-1),m_lock(nombre) {
          //Crea el FIFO

          int fifoCreateStatus = mknod (static_cast <const char *>(nombre.c_str()), S_IFIFO |0666, 0);
          if (fifoCreateStatus == -1){
              checkErrors(fifoCreateStatus,"Falló la creacion del fifo");
          }
          else {
              //Abro el archivo,en forma  bloqueante para la lecutra y escritura.
              this->fd = open (nombre.c_str(),O_RDWR);
          }
        }


    ssize_t  Fifo::leer ( void * buffer , const ssize_t buffsize ) {
          this->m_lock.tomarLockExclusivo();
          ssize_t cr = read(this->fd, buffer, buffsize);
          this->m_lock.liberarLockExclusivo();
          return cr;
    }

    void Fifo::checkErrors(int result, std::string msg) const {
         if (result == -1) {
            throw std::system_error(errno, std::generic_category(),msg);
         }
    }

    ssize_t Fifo::escribir (const void* buffer,const ssize_t buffsize) {
          this->m_lock.tomarLockExclusivo();
          ssize_t code = write(this->fd, buffer, buffsize);
          this->m_lock.liberarLockExclusivo();
          return code;
    }

    Fifo ::~ Fifo() {
        //Cierra el archivo
        close (fd) ;
        fd = -1;
        //Destruye el FIFO (Deslinkea el archivo de nuestra estructura).
        unlink (nombre.c_str()) ;
    }
}