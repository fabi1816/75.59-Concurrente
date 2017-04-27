
#La lista de clases en el directorio actual
set ( SRCS 
        Jugador.cpp
        Turno.cpp
	TurnoFactory.cpp
    )


#Compila la libreria
add_library ( juego ${SRCS} )

