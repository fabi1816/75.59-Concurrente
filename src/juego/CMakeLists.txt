
#La lista de clases en el directorio actual
set ( SRCS 
	Jugador.cpp
	Turno.cpp
	SemaforoFactory.cpp
	Dealer.cpp
	Saludos.cpp
    )


#Compila la libreria
add_library ( juego ${SRCS} )

