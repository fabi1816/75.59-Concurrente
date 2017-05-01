
#La lista de clases en el directorio actual
set ( SRCS 
	SignalHandler.cpp
	Locker.cpp
    )


#Compila la libreria
add_library ( utils ${SRCS} )

