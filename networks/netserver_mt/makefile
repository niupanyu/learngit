CC := g++
INCLUDE :=
LIB := -std=c++11 -lpthread
LIB += -L/usr/local/lib -lboost_system -lboost_thread 
APP_NAME := tcp_server

objects = tcp_server.o

$(APP_NAME) : $(objects)
	$(CC) -o $(APP_NAME) $(objects) $(INCLUDE) $(LIB)


clean:
	rm tcp_server $(objects)
