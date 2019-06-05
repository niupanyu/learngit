CC := g++
INCLUDE := 
LIB     := -L/usr/local/lib -lboost_system -lboost_random
LIB     += -L/usr/local/lib/ -levent -lhiredis
objects = main.o bimap_func.o demoHiRedis.o



main : $(objects) 
	$(CC) -o main $(objects) $(INCLUDE) $(LIB)

$(objects) : bimap_func.h demoHiRedis.h

clean:
	rm main $(objects)
