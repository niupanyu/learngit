CC := g++
INCLUDE := 
LIB     := -L/usr/local/lib -lboost_system -lboost_random

objects = main.o bimap_func.o



main : $(objects) 
	$(CC) -o main $(objects) $(INCLUDE) $(LIB)

$(objects) : bimap_func.h

clean:
	rm main $(objects)
