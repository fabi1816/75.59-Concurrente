//
// Created by marcos on 27/04/17.
//

#include "Mesa.h"

namespace memoriaCompartida {

    Mesa::Mesa(std::stack<int> cartas) {
        //Generación de la clave
        key_t clave = ftok("/bin/ls",21);
        if (clave == -1) {
            this->checkErrors(clave, "Falló la creación de la key");
        } else {
            //Crea la memoria compartida
            this->shmId = shmget(clave, sizeof(cartas), 0644 | IPC_CREAT);

            if (this->shmId == -1) {
                this->checkErrors(shmId, "Falló la creación de la memoria compartida");
            }

        }


    }

    void Mesa::checkErrors(int result, std::string msg) const {
        if (result == -1) {
            throw std::system_error(errno, std::generic_category(), msg);
        }
    }

    std::stack <int>* Mesa::observarMesa() {
        //Atacha el bloque de memoria al espacio de direcciones del proceso
        void *ptrTemporal = shmat(this->shmId, NULL, 0);
        if (ptrTemporal == (void *) -1) {
            this->checkErrors( *((int*)ptrTemporal), "No se pudo atachar ");
        }
        else {
            this->ptrDatos = static_cast < std::stack<int>* > ( ptrTemporal );
            return this->ptrDatos;
        }

    }

    Mesa::~Mesa() {
        //Detach del bloque de memoria
        int detach = shmdt(static_cast < void * > (this->ptrDatos));
        if (detach == -1) {
            this->checkErrors(detach, "No se pudo desatachar ");
        } else {
            int procAdosados = this->getNumeroDeJugadoresJugando();
            if (procAdosados == 0) {
                //Marca el segmento a ser destruido (Destruye la mesa)
                shmctl(this->shmId, IPC_RMID, NULL);
            }
        }

    }

    void Mesa::JugarCartaEnMesa(int carta) {
        (*(this->ptrDatos)).push(carta);

    }


    std::stack<int> Mesa::VerCartasEnMesa() {
        return (*(this->ptrDatos));

    }


    int Mesa::getNumeroDeJugadoresJugando() {
        shmid_ds estado;
        shmctl(this->shmId, IPC_STAT, &estado);
        return estado.shm_nattch;
    }
}
