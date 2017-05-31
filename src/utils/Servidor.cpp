#include "Servidor.h"

Servidor :: Servidor ( const std::string& archivo,const char letra ) {
	this->cola = new Cola<mensaje> ( archivo,letra );
}

Servidor :: ~Servidor () {
	delete this->cola;
}

int Servidor :: recibirPeticion () {
	this->peticionRecibida.id = 0;
	this->cola->leer ( PETICION,&(this->peticionRecibida) );
	return 0;
}

int Servidor :: procesarPeticion () {
	std::stringstream textoRta;
	//TODO FOR ME refactorizar "MENSAJE"
	textoRta << "[Respuesta a " << this->peticionRecibida.estadoDeTransaccion << "]";

	this->respuesta.mtype = RESPUESTA;
	this->respuesta.id = this->peticionRecibida.id;
	//TODO REFACTORIZAR "MENSAJE"
	strcpy ( this->respuesta.estadoDeTransaccion,textoRta.str().c_str() );

	return 0;
}

int Servidor :: responderPeticion () const {
	this->cola->escribir ( this->respuesta );
	return 0;
}

mensaje Servidor :: getPeticionRecibida () {
	return this->peticionRecibida;
}

mensaje Servidor :: getRespuesta () {
	return this->respuesta;
}

