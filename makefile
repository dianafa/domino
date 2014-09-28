gra.exe: main.o game.o handling.o domino.o
	g++ main.o game.o handling.o domino.o -o gra

main.o: main.cpp
	g++ -c main.cpp -o main.o

game.o: game.cpp game.h
	g++ -c game.cpp -o game.o

handling.o: handling.cpp handling.h
	g++ -c handling.cpp -o handling.o

domino.o: domino.cpp domino.h
	g++ -c domino.cpp -o domino.o


clean:
	rm *.o 
