
#La lista de clases en el directorio actual
set ( SRCS 
	SignalHandler.cpp
	SharedCounter.cpp
	SyncBarrier.cpp
	Utils.cpp
	Locker.cpp
	Logger.cpp
    )


#Compila la libreria
add_library ( utils ${SRCS} )

