
#La lista de clases en el directorio actual
set ( SRCS 
	Jugador.cpp
	Turno.cpp
	SemaforoFactory.cpp
	Dealer.cpp
	Saludador.cpp
	Mesa.cpp
    )


#Compila la libreria
add_library ( juego ${SRCS} )

