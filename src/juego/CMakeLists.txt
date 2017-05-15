
#La lista de clases en el directorio actual
set ( SRCS 
	BaseSemaforo.cpp
	Disparador.cpp
	SemaforoFactory.cpp
	Mesa.cpp
	MesaCompartida.cpp
	Jugador.cpp
	Dealer.cpp
	Marcador.cpp
    )


#Compila la libreria
add_library ( juego ${SRCS} )

