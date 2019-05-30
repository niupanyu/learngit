CC := g++
INCLUDE := 
LIB     := -L/usr/local/lib -lboost_system

main : main.o
	$(CC) -o main main.o $(INCLUDE) $(LIB)
main.o : main.cpp
	cc -c main.cpp

clean:
	rm main main.o
