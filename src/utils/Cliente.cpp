#include "Cliente.h"

Cliente :: Cliente ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Cliente :: ~Cliente() {
	this->cola->destruir ();
	delete this->cola;
}
//Recibe el id de la cola y el mensaje a enviar
mensaje Cliente :: enviarPeticion ( const int id,const std::string& texto ) const {
	mensaje peticion;
	mensaje respuesta;

	peticion.mtype = PETICION;
	peticion.id = id;
	//Todo  for me : refactoriza resolviendo problema mesaje
    //Copia el texto en la transaccion(mensaje)
	strcpy ( peticion.estadoDeTransaccion,texto.c_str() );
    //Escribe en cola
	this->cola->escribir ( peticion );
	this->cola->leer ( RESPUESTA,&respuesta );

	return respuesta;
}
