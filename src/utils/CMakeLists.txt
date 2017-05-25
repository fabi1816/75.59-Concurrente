
#La lista de clases en el directorio actual
set ( SRCS 
	SharedCounter.cpp
	SyncBarrier.cpp
	Utils.cpp
	Locker.cpp
	Logger.cpp
	Fifo.cpp
	CanalCartas.cpp
	Cliente.cpp
	Mensajes.h
	Cola.h
	Servidor.cpp
    )


#Compila la libreria
add_library ( utils ${SRCS} )

