
#La lista de clases en el directorio actual
set ( SRCS 
	BaseSemaforo.cpp
	Turno.cpp
	Disparador.cpp
	Saludador.cpp
	SemaforoFactory.cpp
	Mesa.cpp
	MesaCompartida.cpp
	Jugador.cpp
	Dealer.cpp
    )


#Compila la libreria
add_library ( juego ${SRCS} )

