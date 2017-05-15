
#La lista de clases en el directorio actual
set ( SRCS 
	BaseSemaforo.cpp
	Dealer.cpp
	Disparador.cpp
	Jugador.cpp
	Marcador.cpp
	MarcadorCompartido.cpp
	Mesa.cpp
	MesaCompartida.cpp
	Saludador.cpp
	SemaforoFactory.cpp
	Turno.cpp
    )


#Compila la libreria
add_library ( juego ${SRCS} )

